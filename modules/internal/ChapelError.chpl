/*
 * Copyright 2004-2017 Cray Inc.
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

module ChapelError {
  use ChapelStandard;

  // Base class for errors
  // TODO: should base class Error have a string message at all?
  // TODO: should Error include list pointers for ErrorGroup?
  class Error {
    var msg: string;

    proc init() {
    }

    proc init(_msg: string) {
      msg = _msg;
      super.init();
    }

    pragma "no doc"
    var _next: Error; // managed by lock in record ErrorGroupRecord
  }

  // Used by the runtime to accumulate errors. Needs
  // only support adding errors concurrently. Errors
  // will be read from this after all tasks that can add
  // errors have completed; then it no longer needs
  // to be parallel-safe.
  pragma "no doc"
  record chpl_ErrorGroup {
    var _head: Error;
    var _errorsLock: atomicbool;
    // this atomic controls:
    //  - _head
    //  - all list elements ->_next

    inline proc _lockErrors() {
      // WARNING: If you are calling this function directly from
      // a remote locale, you should consider wrapping the call in
      // an on clause to avoid excessive remote forks due to the
      // testAndSet()
      while (_errorsLock.testAndSet()) do chpl_task_yield();
    }
    inline proc _unlockErrors() {
      _errorsLock.clear();
    }
    proc append(err: Error) {
      on this {
        _lockErrors();
        var tmp = _head;
        err._next = tmp;
        _head = err;
        _unlockErrors();
      }
    }
    proc empty() {
      return _head == nil;
    }
  }

  // Converts from the internal record to a
  // user-facing Error.
  // TODO - call this instead of ErrorGroup.init for flexibility
  proc chpl_convertErrorGroup(ref group:chpl_ErrorGroup) {
    // This could return the actual Error if there was only one,
    // instead of returning a singleton ErrorGroup.
  }

  // stores multiple errors when they can come up.
  class ErrorGroup : Error {
    var _head: Error;

    pragma "no doc"
    proc init(ref group:chpl_ErrorGroup) {
      _head = group._head;
      group._head = nil;
      super.init("error group");
    }
    proc init() {
      _head = nil;
    }

    iter these() {
      var e = _head;
      while e != nil {
	yield e;
	e = e._next;
      }
    }

    proc deinit() {
      var e = _head;
      var todelete: Error;
      while e != nil {
        todelete = e;
	e = e._next;
        delete todelete;
      }
    }
  }

  pragma "no doc"
  proc chpl_delete_error(err: Error) {
    delete err;
  }
}
