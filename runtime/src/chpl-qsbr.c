/*
 * Copyright 2004-2018 Cray Inc.
 * Other additional copyright holders may be indicated within.
 *
 * The entirety of this work is licensed under the Apache License,
 * Version 2.0 (the "License"); you may not use this file except
 * in compliance with the License.
 *
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "chplrt.h"
#include "chpl-thread-local-storage.h"
#include "chpl-mem.h"
#include "chpl-atomics.h"
#include "chpl-tasks.h"
#include "chpl-qsbr.h"

static uint64_t global_epoch = 0;

struct defer_data {
    void *data;
    int numData;
};

// Deferred deletion list and associated epoch
// Ideas: First thread that does not complete within a
// reasonable amount of time gets to handle deleting it.
// If a thread hits a checkpoint and seeing a deferred node,
// it will process one of them; if it is unable to, it will
// 'pass the buck' to the next problematic thread ensuring that
// eventually it will be deleted.
struct defer_node {
  uint64_t targetEpoch;
  struct defer_data ddata;
  struct defer_node *next;
};

// Thread-local data that keeps track of our observed global state.
struct tls_node {
  /*
    The current observed epoch. This is used to ensure that writers
    do not delete an older instance that corresponds to this epoch.
  */
  volatile uint64_t epoch;
  /*
    Number of tasks that this thread has running. Required so
    that threads without tasks (and no longer are able to call
    checkpoints) are not taken into account.
  */
  volatile uint64_t nTasks;
  /*
    List of objects that are queued for deferred deletion. Each
    time a writer has waited for too long on a particular thread,
    it will 'pass the buck' for deletion to the next thread.
  */
  struct defer_node *deferList;
  struct tls_node *next;
};

// List of thread-local data.
static struct tls_node *chpl_qsbr_TLSList;
static CHPL_TLS_DECL(struct tls_node *, chpl_qsbr_readerTLS);

// Initializes TLS; should only need to be called once.
static void init_tls(void);
static void init_tls(void) {
  struct tls_node *node = chpl_calloc(1, sizeof(*node));
  node->epoch = global_epoch;

  // Append to head of list
  struct tls_node *old_head;
  do {
    old_head = chpl_qsbr_TLSList;
    node->next = old_head;
  } while (!atomic_compare_exchange_weak_uintptr_t((uintptr_t *) &chpl_qsbr_TLSList, (uintptr_t) old_head, (uintptr_t) node));

  CHPL_TLS_SET(chpl_qsbr_readerTLS, node);
}

// Waits for readers in 'list' to reach (or pass) the 'targetEpoch', and if so will delete 'data'.
// If a reader does not pass the checkpoint in time, we defer both to the problematic thread.
static void waitForReaders(uint64_t targetEpoch, struct tls_node *list, struct defer_data ddata);
static void waitForReaders(uint64_t targetEpoch, struct tls_node *list, struct defer_data ddata) {
  bool canDelete = true;
  for (struct tls_node *node = list; canDelete && node != NULL; node = node->next) {
    // Look for a thread which is active but is not on the current global epoch and defer
    // deletion to them.
    if (node->nTasks && node->epoch < targetEpoch) {
        canDelete = false;

        // Create new defer node that contains both the target epoch and data.
        struct defer_node *defer = chpl_mem_calloc(1, sizeof(*defer), 0, 0, 0);
        defer->targetEpoch = targetEpoch;
        defer->ddata = ddata;

        // Push...
        struct defer_node *old_head;
        do {
            old_head = (struct defer_node *) atomic_load_uintptr_t((uintptr_t *) &node->deferList);
            defer->next = old_head;
        } while (!atomic_compare_exchange_weak_uintptr_t((uintptr_t *) &node->deferList, (uintptr_t) old_head, (uintptr_t) defer));
    }
  }

  if (canDelete) {
    // Treat as an array?
    if (ddata.numData) {
        void **arr = ddata.data;
        for (int i = 0; i < ddata.numData; i++) {
            chpl_mem_free(arr[i], 0, 0);
        }
    }

    chpl_mem_free(ddata.data, 0, 0);
  }
}

void chpl_qsbr_init(void) {
    CHPL_TLS_INIT(chpl_qsbr_readerTLS);
}

void chpl_qsbr_onTaskCreation(void) {
  struct tls_node *node = CHPL_TLS_GET(chpl_qsbr_readerTLS);
  if (node == NULL) {
    init_tls();
    node = CHPL_TLS_GET(chpl_qsbr_readerTLS);
  }

  // Notify that we are now in-use.
  node->nTasks++;
}


void chpl_qsbr_onTaskDestruction(void) {
  struct tls_node *tls = CHPL_TLS_GET(chpl_qsbr_readerTLS);
  if (tls == NULL) {
    init_tls();
    tls = CHPL_TLS_GET(chpl_qsbr_readerTLS);
  }

  // Notify that we have one less task
  tls->nTasks--;

  // If we are the last task, empty our defer list...
  while (tls->nTasks == 0 && tls->deferList) {
    // Pop
    struct defer_node *dnode;
    do {
      dnode = (struct defer_node *) atomic_load_uintptr_t((uintptr_t *) &tls->deferList);
    } while (!atomic_compare_exchange_weak_uintptr_t((uintptr_t *) &tls->deferList, (uintptr_t) dnode, (uintptr_t) dnode->next));

    // Only process threads that come after us as a previous thread would have been processed
    // before us and newly registered threads are pushed as the head of the tls_list.
    waitForReaders(dnode->targetEpoch, tls->next, dnode->ddata);
    chpl_mem_free(dnode, 0, 0);
  }
}

void chpl_qsbr_checkpoint(void) {
    struct tls_node *tls = CHPL_TLS_GET(chpl_qsbr_readerTLS);
    if (tls == NULL) {
        init_tls();
        tls = CHPL_TLS_GET(chpl_qsbr_readerTLS);
    }

    // Observe the current epoch.
    tls->epoch = global_epoch;

    // Handle a single deferred object we have, if any
    if (tls->deferList) {
        // Pop
        struct defer_node *dnode;
        do {
            dnode = (struct defer_node *) atomic_load_uintptr_t((uintptr_t *) &tls->deferList);
        } while (!atomic_compare_exchange_weak_uintptr_t((uintptr_t *) &tls->deferList, (uintptr_t) dnode, (uintptr_t) dnode->next));

        // Only process threads that come after us as a previous thread would have been processed
        // before us and newly registered threads are pushed as the head of the tls_list.
        waitForReaders(dnode->targetEpoch, tls->next, dnode->ddata);
        chpl_mem_free(dnode, 0, 0);
    }
}

void chpl_qsbr_defer_deletion(void *data) {
    uint64_t epoch = atomic_fetch_add_uint_least64_t(&global_epoch, 1);
    waitForReaders(epoch, chpl_qsbr_TLSList, (struct defer_data) { .data = data, .numData = 0 });
}

void chpl_qsbr_defer_deletion_multi(void **arrData, int numData) {
    uint64_t epoch = atomic_fetch_add_uint_least64_t(&global_epoch, 1);
    waitForReaders(epoch, chpl_qsbr_TLSList, (struct defer_data) { .data = arrData, .numData = numData});
}

void chpl_qsbr_exit(void) {
    // Clean thread-local storage
    while (chpl_qsbr_TLSList) {
        struct tls_node *node = chpl_qsbr_TLSList;
        chpl_qsbr_TLSList = chpl_qsbr_TLSList->next;

        while (node->deferList) {
            struct defer_node *dnode = node->deferList;
            node->deferList = node->deferList->next;

            if (dnode->ddata.numData) {
                void **arr = dnode->ddata.data;
                for (int i = 0; i < dnode->ddata.numData; i++) {
                    chpl_mem_free(arr[i], 0, 0);
                }
            }

            chpl_mem_free(dnode->ddata.data, 0, 0);
            chpl_mem_free(dnode, 0, 0);
        }

        chpl_mem_free(node, 0, 0);
    }
}
