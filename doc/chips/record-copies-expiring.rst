.. _record-copies-expiring:

Record Copying in Chapel: Eliminating Copies from Expiring Values
=================================================================

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

Discussion of how the design in :ref:`record-copies` might be extended
to generally eliminate unnecessary copies.

TODO: This section needs to be revisited.

Eliminating Copies from Expiring Values
+++++++++++++++++++++++++++++++++++++++

As discussed in the previous section, this program will create extra
array copies even with all of the optional extensions described up to
this point:

.. code-block:: chapel

    proc makeArray() {
      var A:[1..100] int;
      return A;
    }

    proc source(out a, out b) {
      a = makeArray();
      b = makeArray();
    }

    proc sink(in a, in b) {
      writeln(a);
      writeln(b);
    }

    var tmp_a:A[1..100] int;
    var tmp_b:A[1..100] int;
    source(tmp_a, tmp_b);
    sink(tmp_a, tmp_b);


In addition, a program such as this:

.. code-block:: chapel

  {
    var A:[1..4] int;
    var B = A;
    var C = B;
    writeln(C);
  }

creates an extra copy of A that is not needed.


Here we propose that:

 1) the compiler can remove any `copy` if the source of the copy
    is an expiring value (that is, a value that is dead after the copy
    is made except for a call to destroy it - this call to destroy
    it is required ).
 2) when the compiler removes such `copy` operations, it replaces them
    with `move` operations.

There is one case where this behavior might be surprising to a record
author. Suppose that `R` is a record that contains a `ptr` field of a class
type. Suppose a `postblit` function is defined for `R` that allocates a
new `ptr` value in the destination and copies the contents of `ptr`.
Suppose further that a `postmove` function is defined for `R` that does
does not perform the deep copy (and is equivalent to a shallow copy).

Now suppose that `g` is an `R` record value storing a pointer, and that
somehow `alias` is set up as a record storing the same pointer.  Then a
copy is made from `alias` to `x`. Finally, the value pointed to within
`x` is modified.

.. code-block:: chapel

    {
      var g = new R(ptr);
      var alias:R;
      alias.ptr = g.ptr;
      var x = alias; // a copy might be expected here.
                     // if the copy occurs, x.ptr != g.ptr.
                     // if it does not, x.ptr == g.ptr.
      mutate(copy.ptr);
      // has g.ptr changed?
    }

In this case, the optimization might remove the copy from `alias` to `x`,
which would cause the mutate call to modify `g.ptr` instead of a separate
value. This difference changes the way the program behaves. Note that it
is also possible to write this pattern as several function calls so that
the role played by `x` is instead played by a compiler-introduced
temporary.

Here we propose that in cases where a record might store a pointer that aliases
another record, the `postmove` function be implemented by the record author to call
the `postcopy` function. This choice can be made at runtime.  Since the
`move` operations under this proposal correspond to all cases where a value is bound to a
new user variable - by implementing a `postmove` function a record designer can
control this behavior. We have already observed that there are other reasons
for the `string` and `_array` implementations to do this - see
:ref:`record-copies-strings`.

This optimization still meets the *unique storage for a record's fields* idea
from :ref:`record-copies-user-view` since the optimized-away copy is from a dead variable.

Alternative designs include:

 * apply this optimization only to compiler-introduced temporaries
   and always apply it to compiler-introduced temporaries
   (This is the choice that C++ and D made, but it has the disadvantage
   that user variables have different behavior from compiler-introduced
   temporaries - and that this optimization cannot apply to user
   variables).
 * apply this optimization only when the result of a possibly-eliminated
   copy is not logically modified
   (This choice is possible but would require an understanding
   of `const` or some other concept that includes mutation through
   a pointer field, such a transitive immutability).

