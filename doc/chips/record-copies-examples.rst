.. _record-copies-examples:

Record Copying in Chapel: Examples
==================================

Status:
  Draft

Authors:
  Michael Ferguson

Abstract
--------

Rationale
---------


Description
-----------

Examples supporting the design in :ref:`record-copies`.

TODO: This document needs revisiting to reduce extra concepts.
In particular, the alternatives sections should probably be commented
out.

.. _record-copies-ref-count:

Supporting Reference Counting
-----------------------------

A record that implements reference counting is supported by this
proposal. For the purposes of this document, we will call such a record
`_refcnt`. The `_refcnt` `postmove` function  - which is called in a
`move` operation - does nothing.  The `_refcnt` `postblit` - which is
called in a `copy` operation - bumps the reference count. The record's
destruction function decrements the reference count. Any `ref` to a
`_refcnt` record does not cause changes in the reference count. Returning
a `_refcnt` with a `ref` return intent does not change the reference
count.

Intuitively, there is no need to change the reference count for a
`_refcnt` variable unless that variable arrives at a new user variable.

Note that the pointer inside each `_refcnt` to another object (e.g. a
class instance) does not change when the `_refcnt` is copied.

The following is an example implementation of a `_refcnt` type.

.. code-block:: chapel

  class shared_count {
    var count: atomic int = 1;

    proc retain() {
      count.add(1);
    }
    proc release() {
      var oldValue = count.fetchSub(1);
      return oldValue - 1;
    }
  }

  // this could also be called `shared_ptr` to correspond
  // with the C++ feature.
  record _refcnt {
    var p;               // contained pointer (class type)
    var pn:shared_count; // reference counter

    proc init(p) {
      if !isClass(p.type) then
        compilerError("_refcnt only works with classes");
      this.p = p;
      pn = new shared_count();
    }
    proc deinit() {
      release();
    }
    proc release() {
      var count = pn.release();
      if count == 0 {
        delete p;
        delete pn;
      }
    }
    proc retain() {
      pn.retain();
    }

    // (not trying to propose the specific names here,
    //  and depending on other initializer work, not all
    //  of these are necessary).
    proc postblit() {
      // called after this is initialized with
      // a bit copy of another record, as a part of a
      // copy operation.
      //
      // so this.p and this.pn are already initialized.
      retain();
    }
    proc postmove() {
      // called after this is initialized with
      // a bit copy of another record, as a part of
      // a move operation
      //
      // no further action is necessary
      // the compiler default would also do nothing
      // this is here just for completeness
    }
  }

  proc =(ref lhs:_refcnt, rhs:_refcnt) {
    // alternatively, could rely on a compiler
    // = implementation in terms of postblit.
    rhs.retain();
    lhs.release();
    lhs.p = rhs.p;
    lhs.pn = rhs.pn;
  }

Here is an example program using `_refcnt`:

.. code-block:: chapel

  proc f() {

    var x=new _refcnt(new MyClass());
    // now x's ref count is 1

    var y=x;  // causes copy operation which increments ref count to 2

    return y; // causes move operation which does not change ref count

    // (destroy x) decrements ref count to 1
  }

  var z = f(); // calls move, leaving ref count at 1
  // (destroy z) decrements ref count to 0, freeing MyClass.

.. _record-copies-buffer:

Supporting Records Storing a Buffer
-----------------------------------

Suppose that a record conceptually stores a variable number of fields, or
stores a number of fields too large to be reasonably stored on the stack.
Such a record could be implemented with a pointer to some memory that is
owned by the record. 

For example,

.. code-block:: chapel

  class buffer {
    var d:int;
    var e:int;
    var f:int;
    var g:int;
    var h:int;
  }
  
  record R {
    var a:int;
    var b:int;
    var c:int;

    // the idea is to store fields d-h on the heap
    // instead of the stack in order to save stack space.
    // So, these fields are accessible through the
    // following variable which points to them.
    var buf:buffer; // (implementation private)
  }


In this case, the record `R` should work the same as if the fields `d`,
`e`, `f`, ... s were stored directly inside the record. To support that
behavior:

 * the constructor/initializer for `R` would allocate `buf`.
 * the destructor/deinitializer for `R` would delete `buf`.
 * the `copy` operation would create a new `buf` containing a copy
   of the original data

   .. code-block:: chapel

     proc R.postblit() {
       // called after this is initialized with
       // a bit copy of another record, as a part of a
       // copy operation.
       //
       // so this.a,b,c,buf are already initialized
       this.buf = new buffer(buf.d, buf.e, buf.f, buf.g, buf.h);
     }

 * the `move` operation does nothing other than `memcpy`.

   .. code-block:: chapel

      proc R.postmove() {
        // called after this is initialized with
        // a bit copy of another record, as a part of
        // a move operation
        //
        // no further action is necessary
        // the compiler default would also do nothing
        // this is here just for completeness
      }

While this example may seem contrived, it can be viewed as a simpler
version of a string or array. It is useful as a simpler example because
it is clear what behavior is expected (namely - it should work the same
as if all fields were stored directly in the record).

In this example, it would be invalid to create two user variables `A` and
`B` that both store the same `buf` pointer. Ideally, the
implementation-private `buf` field would be protected so that it is not
possible for programs doing that to compile. A program that did manage to
set up such an alias would probably contain a double-free.

.. _record-copies-strings:

Strings
-------

The record implementing a string is similar to the :ref:`record-copies-buffer` case
described above, but there is one important exception. Strings store a
pointer to the string data in a `buff` field. It *is* possible for two
strings to be created that share a `buff` field. The `localize()` call
is a function that does that in the current implementation. Also,
copies of strings created from string literals will all share a buffer
to the same original string literal data. These are immutable, unlike
the `localize` case.

For example:

.. code-block:: chapel
 
  var A:string = someExpression;
  var B = A.localize();

  // Now changing data pointed to by A.buff or B.buff affects both

While changing the data pointed to by the `buff` field directly is not
supported in the string implementation, the `+=` function is supported
and can, in some situations, change that that data. However, the
`localize` function is only meant to create a compiler-introduced
temporary string so that something like:

.. code-block:: chapel
 
  A.localize().c_str();
  
can be used as an expression, since it is invalid to call `c_str()` on a
remote string.

Thus, while it is technically possible for strings to alias each other
and be mutable, this situation is the exception.

The implementation envisaged for the `string` record is the following:

 * the `string` record stores an additional `bool` field `aliasMutable`
 * strings created for string literals have `aliasMutable` set to `false`
 * `localize` returns a new string with `aliasMutable` set to `true` 
 * `move` checks `aliasMutable` and copies the buffer if `true`.
   Otherwise, it shares the buffer between the source and the destination
   of the move.

   .. code-block:: chapel

      proc string.postmove() {
        // called after this is initialized with
        // a bit copy of another record, as a part of
        // a move operation
        //
        if this.aliasMutable {
          // create a new, owned buffer that is a copy of this.buff
          var new_buf = chpl_here_alloc(...);
          memcpy(new_buff, this.buff, s.len);
          this.owned = true;
          this.buff = new_buf;
        }
        // Do nothing aliasMutable is false
      }

 * `copy` creates a new buffer with the same data as the source of the
   copy. This corresponds to the existiting chpl__initCopy for strings.

In this way, a program such as:

.. code-block:: chapel

  proc f(x:int) {
    var s:string;
    s += x:string;
    return s.localize(); // returns a string pointing to
                         // a buffer freed in this function,
                         // but the compiler-inserted `move` operation
                         // will be implemented to copy the buffer.
  }

  writeln(f(100));

will not core-dump, since the process of returning the result of `s.localize()`
from `f` will invoke `move`, which will in turn create a copy.

One issue with this pattern is that it is unclear how to write the `localize`
function. The initial approach proposed here is to mark `localize` with a
pragma that indicates that the `move` operation should not be invoked when
returning.

Possible alternative strategies might include:

  * implement `localize` as an initializer/constructor. While
    initializers/constructors don't return in the usual sense, and so
    wouldn't invoke `move`, code calling `localize` would have to
    be rewritten.
  * instead of `aliasMutable`, use a counter or a second boolean field, so that
    the first `move` operation results in sharing the buffer, but subsequent `move`
    calls create a copy
  * allow `string` to specify a different `ref` type and mark `localize`
    as returning by `ref`. Make the `ref` type contain the same fields as the
    string record. Mark `localize` with the `ref` return intent. Then
    the `move` would be omitted.

