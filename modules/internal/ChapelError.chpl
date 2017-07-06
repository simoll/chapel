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

    proc Error(_msg: string) {
      msg = _msg;
    }
  }

  // stores multiple errors when they can come up.
  // TODO: should the base class Error have this capability?
  class ErrorGroup : Error {
    var _errors:list(Error);     // list of errors, owned by group
    var _errorsLock: atomicbool; // lock for concurrent access

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
        _errors.append(err);
        _unlockErrors();
      }
    }
    iter these() {
      on this do _lockErrors();
      for err in _errors {
        yield err;
      }
      _unlockErrors();
    }

    proc deinit() {
      on this {
        for err in _errors {
          delete err;
        }
      }
    }
  }

  proc chpl_delete_error(err: Error) {
    delete err;
  }
}
