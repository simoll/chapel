.. _record-copies-arrays:

Implementing Arrays with Record Copying Semantics
=================================================

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

This document describes how Chapel arrays can be implemented based upon
the rules described in :ref:`record-copies`.

TODO: describe how the rules need to be extended for runtime types.
Describe the `check` operation and when it is invoked (with a table).

Array Semantics
---------------

Arrays in Chapel are implemented with two types:

 1) A wrapper record which is called `_array` in the current
    implementation, and
 2) a subclass of `BaseArr`, such as `DefaultRectangularArr`. The wrapper
    record contains a field pointing to such an object.

To implement Chapel's array semantics, we need to describe what the `copy`,
`move`, and `check` operations do.  Note that the  `_array` record would
contain an `isalias:bool` field in addition to the current fields. This field 
supports array aliases and slices.

  * `copy` will always allocate a new array and copy the array elements.
    It can also perform size checking against declared sizes.
  * `move` will check `isalias`. If it is `true`, it will perform the
    same operation as `copy`. If it is `false`, it just shallow-copies
    the `_array` field elements (and doesn't copy the array data). It
    can also perform size checking against declared sizes.
  * `check` can halt with an error if its type argument does not
    match its array argument.

All 3 of these operations need to implement array bounds checking against
declared sizes. These checks could be removed in `--fast` compiles.

Additionally, because arrays return by value, the compiler will need
to relax l-value checking when promoting a temporary to a `ref`. For
example,

.. code-block:: chapel

  proc returnsArray() {
    var A:[1..10] int;
    return A;
  }
  proc consumesArray(arg) {
    writeln(arg);
  }

  consumesArray(returnsArray());

will need to work, even though for other types it would be an error to
create a `ref` from the value returned from a function.

Without further special handling in the compiler, the resulting semantics
are a slight change from the current behavior. We have identified primarily
one situations in which program behavior would differ under this proposal:

  1) Returning a global array makes a copy

Note that we do not believe that the current specification clearly states
what happens in this case. First, the current specification does not
seem to explicitly say that arrays return semantically by reference -
even though the current behavior is that they return by reference.  (By
return semantically by reference, we mean that a function returning an
array will create a new `_array` record that may alias another array).

This difference in behavior is discussed in :ref:`arrays-by-value`. Note that
the optional extension :ref:`automatic-ref-return` is one way to avoid this
`copy` in most cases.

The Current Strategy for Arrays
+++++++++++++++++++++++++++++++

The current strategy in the compiler uses `initCopy` and `autoCopy`.
`initCopy` performs a deep copy and `autoCopy` increments a reference
count. The normalize pass causes any user variable declaration to
generate `initCopy` as in:

.. code-block:: chapel

  proc returnArray() {
    var A:[1..10] int;
    return A;
  } 
  var A = returnArray(); // becomes prim_move A, initCopy(returnArray())

but it would seem that a copy is not necessary in this case.

Besides adding possibly unnecessary `initCopy` calls in normalize, the compiler
marks most functions as needing an `autoCopy` on the result. The flags
FLAG_DONOR_FN and FLAG_NO_IMPLICIT_COPY controls this behavior. Function
resolution considers these flags when marking many expression temporaries with
FLAG_INSERT_AUTO_COPY and FLAG_INSERT_AUTO_DESTROY.

For example:

.. code-block:: chapel

  proc returnArray() {
    var A:[1..10] int;
    return A;
  }

  proc returnReturnArray() {
    return returnArray();
  }

  var B = returnReturnArray();
  writeln(B);

generates both an `autoCopy` and an `initCopy` - when in fact no copy is
necessary.

Then, `callDestructors` and `removeUnnecessaryAutoCopyCalls` both attempt in
various ways to clean up the mess. The implementation is a series of
hard-to-follow special cases and exceptions.

.. _arrays-by-value:

Returning a global array makes a copy
+++++++++++++++++++++++++++++++++++++

TODO: This section needs to be updated assuming automatic-ref-return.

Here is an example program that would generate a copy of the array
elements under this proposal, where no copy occurs in the current
implementation:

.. code-block:: chapel

  var A:[1..3] int;

  proc f() {
    return A; // copy created as part of returning
  }

  writeln(f());

Note that this difference also applies to `f` returning a ref-intent
argument or any other reference to an outer variable:

.. code-block:: chapel

  var A:[1..3] int;

  proc f(arg) {
    return arg; // copy created as part of returning
  }

  writeln(f(A));

In both of these examples, the copy is made because of the rule
untyped-return-global.

Note that the current implementation already makes a copy if:

 * `f` has a declared return type
 * the result of `f` is assigned into a user variable

Note that the proposed implementation would not make a copy if:

 * `f` returns a new array

Here is a related example that would have different output under this
proposal:

.. code-block:: chapel

  var A:[1..3] int;

  proc f() {
    return A; // makes a copy under proposal, not in current compiler
  }
  proc g(x) {
    x[1] = 1;
  }
  g(f());
  writeln(A);

Under this proposal, this program would produce `0 0 0`, but the current
implementation produces `1 0 0`

In :ref:`automatic-ref-return`, we discuss one possible strategy that could
remove this difference from the current behavior in most cases. Even with that
optional strategy, the following program would have different output:

.. code-block:: chapel

  var A:[1..3] int;

  proc f(x:bool) {
    if x then return A;
    else {
      var tmp:[1..0] int;
      return tmp;
    }
  }
  proc g(x) {
    x[1] = 1;
  }
  g(f(true));
  writeln(A);

It produces `1 0 0` in the current implementation, but would produce `0 0 0`
under the proposal, because returning `A` from within `f` would make a copy.
The :ref:`automatic-ref-return` strategy cannot remove this copy since `f`
sometimes returns a local array (and it would not be legal to return the local
array by ref). It might be reasonable to make such functions result in
a compilation error.

A further alternative here would be for the the untyped-return-global
case to use a different `copy` operation, perhaps called `copyRef`, for arrays.
In some ways this approach is similar to :ref:`automatic-ref-return` but less
general.

More Array Examples
+++++++++++++++++++

(Note that the `isalias` field is `false` for all of the `_array` records in
these examples).

Array Example 1
***************

.. code-block:: chapel

   proc createArray() {
     var retA: [1..10000] real;
     return retA;
   }
   var A = createArray();

`retA` is an `_array`. In the process of returning from `createArray`, `move`
is called. `move` is called a second time when initializing the `A` variable
and again does not perform a deep copy.  Thus, the desired behavior is
achieved: the array is returned without any copies.

Array Example 2
***************

.. code-block:: chapel

   var outerA: [1..10000] real;
   proc returnExistingArray() {
     return outerA;
   }
   var A = returnExistingArray();

The process of returning from `returnExistingArray` calls `copy` with an
`outerA` argument. This copy is `move` d into `A`. That results in the desired
semantics: `A` refers to a different array than `outerA`. Note that
:ref:`automatic-ref-return` could transform the above case into the following
case.

Array Example 3
***************

.. code-block:: chapel

   var outerA: [1..10000] real;
   proc returnExistingArray() ref {
     return outerA;
   }
   var A = returnExistingArray();

The process of returning from `returnExistingArray` does not create a
copy of the array `outerA` since it returns with `ref` intent. However,
the variable initialization for `A` is using a ref and so is treated the
same as initialization from another variable. That results in a `copy`
operation.  That gives in the desired semantics: `A` refers to a
different array than `outerA`.

Array Example 4
***************

.. code-block:: chapel

   var outerA: [1..10000] real;
   proc returnExistingArray() {
     return outerA;
   }
   proc consumesArray(A:[] real) { ... }
   consumesArray(returnExistingArray());

This example would have different behavior from the current (v1.13)
compiler as discussed in the :ref:`arrays-by-value` section, unless the
:ref:`automatic-ref-return` strategy is applied. That strategy would
automatically change this example to the following:

.. code-block:: chapel

   var outerA: [1..10000] real;
   proc returnExistingArray() ref {
     return outerA;
   }
   proc consumesArray(A:[] real) { ... }
   consumesArray(returnExistingArray());

The result is that the additional copy is avoided. `returnExistingArray` does
not create a copy in the process of returning with the `ref` intent. Since the
function `consumesArray` takes in `A` by blank intent, which is `ref` for
arrays, no copy is made when passing the ref returned to that function. That
gives the desired semantics: no copy is added for this program.

Array Example 5
***************

.. code-block:: chapel

   proc createArray() {
     var retA: [1..10000] real;
     return retA;
   }
   proc consumesArray(A:[] real) { ... }
   consumesArray(createArray());

As we have previously discussed, the process of returning from
`createArray` would not create a copy. The call to `consumesArray` also
does not create a copy. Note that it would still not make a copy in this
case even if it had the `in` argument intent.  That gives the desired
result: no copy is necessary.

Array Example 6
***************

.. code-block:: chapel

   record RecordStoringArray{ var field; }
   proc createArray() {
     var retA: [1..10000] real;
     return retA;
   }
   proc consumesArray(A:[] real) {
     return new RecordStoringArray(A);
   }
   consumesArray(createArray());

As before, `createArray` does not call `copy` in the process of
returning. The value returned will be destroyed after the `consumesArray`
call. The call to `consumesArray` does not create a copy since it is
passing by reference. The initialization function for
`RecordStoringArray` initializes `field` field with another variable;
therefore a `copy` operation is included. That gives an acceptable
result: `retA` is copied into the record `field` as in the current
compiler.  It might be possible to eliminate this unnecessary copy by
automatically changing the default argument intent to an `in` intent in
some cases.

Array Example 7
***************

.. code-block:: chapel

  config const n = 3;
  proc retA() :[1..n] int
  {
    var A:[1..4] int;
    return A;
  }

  var A = retA();

This example shows why `move` is added in such cases and why it takes in
a run-time type argument for arrays. The program shown is a run-time
error depending on user input, but no `copy` operation is necessary.

.. _ref-return-array:

ref return intent for arrays
++++++++++++++++++++++++++++

The current compiler ignores the `ref` return intent for functions returning
arrays. Here we propose a different strategy.  As described in the
:ref:`ref-return` section, returning something by reference should not change
when that thing is destroyed.

This proposal assumes that a `ref` to an array is actually a `ref` to an
`_array` wrapper record (that is, the ref type is `_ref(_array)`).

Run-time type checking is necessary to detect at runtime array size mismatch
errors such as in this case:

.. code-block:: chapel

  var A:[1..4] int;

  proc retA() ref :[1..3] int
  {
    return A; // error: 1..4 does not match 1..3
  }

  writeln(retA());

Here, the compiler should generate a `check(rtt)` call in `retA` that
checks that the declared return type `:[1..3] int` matches A's type
`:[1..4]`.

Here is an example that should work without error:

.. code-block:: chapel

  var outerArray:[1..100] int;
  proc f() ref {
    return outerArray;
  }

This example should not copy `outerArray` in the process of returning it,
since it is returning by `ref`. There will be no `move` or `copy` operation.
No `check` call is necessary since `f` does not have a declared return
type.  The returned reference will point to the `outerArray` `_array`
record.  In this way, the `ref` has no impact on the lifetime of
`outerArray` and will become invalid if `outerArray` is destroyed.

It is not legal to return a local variable by ref:

.. code-block:: chapel

  proc f() ref {
    var localArray:[1..100] int;
    return localArray; // error: returning local by ref
  }

  writeln(f()[1]);

This example should be a compilation error. Since returning with `ref` intent
has no impact on the lifetime of the returned variable, `localArray` should
continue to be destroyed when `f` exits, so that any use of the data in the
returned value would be a use-after-free. Note that the current (1.13)
compiler does allow this program.

Alternatives:
 * The `ref` type for `_array` could be the same as `_array`.
   To construct a `ref` for an array, the compiler would call `makeRef`
   in the process of returning. The `makeRef` call will set `isalias` to `true`
   and perform any necessary run-time type checking.
 * Allow returning a local array by `ref` by relaxing the rule for arrays
   specifically. That might require `copyRef` and `moveRef` operations.
   The current compiler relaxes this rule by making `ref` the same as
   blank intent for arrays.
 * As discussed in :ref:`ref-return`, an alternative approach is for the
   `ref` type for `_array` to be a different type that has the same
   fields. In this way, the `move` and `copy` operations for a `ref(_array)`
   could perform the actions described here for `makeRef`.
 * If returning a slice of a local array is a program error, we could
   make functions returning arrays by `ref` behave the same as if they
   were marked without the `ref` return intent. This is in some ways
   more consistent with the current behavior.

.. _record-copying-array-slices:

Array slices
++++++++++++

Array slices are a tricky case for the same reasons as `string.localize()`
discussed above (see :ref:`record-copies-strings`).

The proposed strategy uses an `_array` `isalias` `bool` field that is
generally `false` but set to `true` when a slice is created. It implements
`move` for `_array` to perform a copy when `isalias` is `true`, and also
marks the function implementing array slice with a special pragma to
prevent it from calling `move` when returning.

Slice Example 1
***************

Consider this example program:

.. code-block:: chapel

  proc f() {
    var A:[1..4] int;
    return A[2..3];
  }

  var A_slice = f();
  writeln(A_slice);

It currently (in v1.13) outputs `0 0` but would result in an invalid
program/core dump if the return from `f` did not make a copy of the slice
or somehow arrange for the slice to take ownership of the original array.
The problem is that the `A` variable is destroyed at the end of `f`'s
scope.

The proposed strategy will have the slice construction function set
`isalias` to `true`, and then the `move` operation made in the process of
returning will create a copy of the array slice.

Slice Example 2
***************

.. code-block:: chapel

  var A:[1..4] int;

  proc f() {
    return A[2..3];
  }

  proc g(x) {
    x[2] = 1;
  }

  g(f());
  writeln(A);

Currently (in v1.13) outputs `0 1 0 0`. Under the proposal, it would
output `0 0 0 0` because a `move` operation is invoked in the `return`
from `f` and `isalias` is true, resulting in a copy.

This proposal does not include a user-facing way to manually restore the
old behavior. Note though that the slice function uses a pragma that
could possibly generalized into a user-facing feature.

Slice Example 3
***************

.. code-block:: chapel

  var A:[1..4] int;
  var A_slice = A[2..3];
  A_slice[2] = 1;
  writeln(A);

Currently outputs `0 0 0 0`. Will still do that because `move` for array slice
from variable initialization will detect `isalias` and perform a full copy.

Slice Example 4
***************

.. code-block:: chapel

  var A:[1..4] int;
  var A_slice => A[2..3];
  A_slice[2] = 1;
  writeln(A);

Currently outputs `0 1 0 0`. It could still do that if `=>` is not considered
normal variable initialization, but more like `ref` initialization.

Slice Example 5
***************

.. code-block:: chapel

  var A:[1..4] int;
  var A_slice => A[2..3];
  proc f() ref {
    return A_slice;
  }

  f() = 1;
  writeln(A);

Currently outputs `0 1 1 0`. It will continue to do so under this proposal,
since `copy` and `move` for `_array` are not called when returning by ref.

It should be possible to create a `ref` to the temporary `_array` record
returned by a function. Therefore, this example could also be written:

.. code-block:: chapel

  var A:[1..4] int;
  ref A_slice = A[2..3];
  proc f() ref {
    return A_slice;
  }

  f() = 1;
  writeln(A);


Slice Example 6
***************

.. code-block:: chapel

  proc f() ref {
    var A:[1..4] int;
    return A[2..3];
  }

  writeln(f());

Currently (v1.13) outputs `0 0`. It should be a compile error under the
proposal, since it returns a local (temporary) variable by `ref`.

Implementing the Slice Function
*******************************

One issue is that the implementation of array slicing is almost certainly
a function. Let's suppose it is called `slice`. That function would look
something like this:

.. code-block:: chapel

  pragma "no move on return"
  proc _array.slice(ranges: range(?) ..rank) {
    var d = _dom((..ranges));
    var a = _value.dsiSlice(d._value);
    a._arrAlias = _value;
    var ret = new _array(a, a);
    ret.isalias = true;
    return ret; // no `move` operation can be added here,
                // because `move` will copy a slice in order
                // to make Example 1 work
  }

As we have already described, the `move` operation for `_array` would
copy the array data in the case of `isalias=true`. For that reason,
the `slice` function needs to disable the `move` on return.

Alternatives:

 * change var B = A[InnerD]; to not create a copy of the slice

 * introduce a new type for array slices:

   * array slicing could return a new type such as `_arraySlice`
   * the `move` operation from the new type to an `_array` would perform a
     deep copy

 * implement the slice construction function to specially handle
   expiring values and take ownership of them. That would allow
   the first example above to work without adding a copy.

_array Implementation Alternatives
----------------------------------

* "ownership bit" idea discussed previously - this approach requires separate
  copy fn for user variable init from return (or some other way to distinguish).

  It could be possible to distinguish `copy` and `move` operations from
  dead/expiring values. (e.g. expiring could be an argument to these
  calls).
  Otherwise, return outerVar would always make a copy. One serious drawback
  with this approach is that it cannot tolerate extra copies of
  compiler temporaries in case the compiler is not as tidy as possible
  about generating the copies. Thus, it would be just as much work
  as the current proposal.

* reference counting - we do not believe the language requires array reference
  counting

* It would be possible to pull out the type checking operations in `move`
  and `copy` - e.g. adding a call to `check` instead of passing in the
  types - but  the current strategy has the advantage of enabling
  coercions in some cases (for example, a `move` from an array of shape
  1..10 to one of shape
  0..9).

* Arrays could return always by ref, or sometimes by ref and sometimes by
  value.  This document describes sometimes by ref sometimes by value.
  If they always returned by ref, an array return `copy` operation could
  set `isalias` to `true`. Would still want initialization `copy` to do
  something else (copy elements).  Note though that always returning
  arrays by `ref` is more semantically challenging. Slicing, returning
  local variables by `ref`, and knowing when to free arrays are issues.


