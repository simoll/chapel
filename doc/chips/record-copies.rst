.. _record-copies:

Record Copying in Chapel
========================

Status:
  Draft

Authors:
  Michael Ferguson

Abstract
--------

A proposal for when Chapel will introduce record copy and move
operations.

Rationale
---------

Record copy semantics is an issue that cuts accross many portions of the
Chapel language design and implementation.  It is our belief that much of
the complexity in the current implementation stems from lacking a clear
design incorporating details about when copies are necessary. This
document is an attempt to solve that problem.

Description
-----------

This document describes the following areas of record semantics:

 * `copy` and `move` operations 
 * `postblit` and `postmove` methods
 * when `copy` and `move` operations are added by the compiler

Other documents will cover the following:

 * record initialization and destruction (see :ref:`Initializers`)
 * examples: reference counting record, record storing a buffer, and
   record implementing string (see :ref:`record-copies-examples`)
 * array semantics, assuming arrays continue to be implemented as records
   (see :ref:`record-copies-arrays`)
 * how `out` and `inout` argument intents could be improved
   (see :ref:`record-copies-out-inout`)
 * a general copy reduction transformation (see
   :ref:`record-copies-expiring`)
 * how users should think about these record semantics and how the
   semantics might be described in the language specification (see
   :ref:`record-copies-user-view`)

Interesting Records
+++++++++++++++++++

This document is mainly interested in describing the semantics of records
that contain pointers. For example, a record might contain a field of
class type. That field is actually a pointer to a class instance. Such
records rely on when and how record copies are added by the compiler.

Record Initialization and Destruction
+++++++++++++++++++++++++++++++++++++

Record initialization and destruction are described in CHIP 10.  For the
purposes of this document, it suffices to know that records are destroyed
when they go out of scope and at that time a `deinit` method is called.
A typical `deinit` method would free memory used by a pointer field.

Copy and move operations
++++++++++++++++++++++++

Record copy semantics in Chapel are a combination of two factors.

 1) The compiler adds `copy` or `move` operations
 2) The record author implements `postblit` or `postmove` to
    specify how the record should react to a `copy` or `move` operation.

Note that when a type has a run-time component, move and copy operations
need to provide the run-time type to the postblit or postmove function
implemented by the record author. This topic is discussed further in TODO
ref array copy semantics.

The copy operation
******************

A `copy` operation can be added by the compiler when initializing a
destination variable with a source expression that might possibly
continue to exist. A canonical example is:

.. code-block:: chapel

  var x = ...;
  var y = x;    // copy operation occurs here
  ... use both x and y ...;

The `copy` operation consists of:

.. code-block:: chapel

  memcpy(dst, src)
  dst.postblit();


The `postblit` method
*********************

A record specifies how it reacts to a copy by providing a `postblit`
method. At the time that the `postblit` method is called, the `this`
variable is already initialized to a shallow copy. The `postblit` method
is responsible for performing a fixup.

.. code-block:: chapel

  class C {
    var a:int;
  }
  record R {
    var ptr:C;
  }
  proc R.postblit() {
    // Fix up for copy
    // e.g. copy a buffer that should not be shared between instances
    this.ptr = new C(a=this.ptr.a);
  }

If no `postblit` method is provided for a record, the compiler provides
one. The compiler-provided `postblit` method calls the `postblit` method
on each record field in turn.

TODO: the method name `postblit` is not finalized.

The move operation
******************

The `move` operation is added by the compiler to allow records to react
to a record changing storage location. A canonical example is:

.. code-block:: chapel

  record R { ... }
  proc makeR() {
    return new R(...);
  }
  var x = makeR();    // move operation occurs here


The `move` operation consists of:

.. code-block:: chapel

  memcpy(dst, src)
  dst.postmove();

The `postmove` method
*********************

A record can use a `postmove` method to react to a `move` operation.  As
with `postblit`, the `this` variable is already initialized with a
shallow copy at the time that the `postmove` method is called. However,
in contrast to the `postblit` method, the old instance is generally no
longer accessible.

The `postmove` method is useful in support records containing pointers
that sometimes alias and sometimes do not. By specifying a `postmove`
method, the record author can control whether or not two such records
that are stored in different variables can share a pointer. One
application is that the `move` operation can be used to prevent a record
containing a pointer to freed memory from being returned in the following
example:

.. code-block:: chapel

  class C {
    var a:int;
  }
  record R {
    var ptr:C;
    var isalias:bool;
    proc deinit() {
      if !isalias then delete ptr;
    }
    proc postblit() {
      this.ptr = new C(a=this.ptr.a);
      this.isalias = false;
    }
  }
  proc makeAlias(const ref r:R) {
    return new R(ptr=r.ptr, isalias=true);
  }
  proc test() {
    var r = new R(...);
    var alias = makeAlias(r);
    return alias; // returning alias with ptr==r.ptr 
                  // but r.ptr is deleted in r's destructor
  }
  var r = test();
  // now does r.ptr refer to freed memory?

The record author could prevent `r` from referring to freed memory in
this case by providing the following `postmove` method:

.. code-block:: chapel

  proc R.postmove() {
    if (this.isalias) {
      this.postblit(); // make a new ptr as a copy of old ptr 
    }
  }

If no `postmove` method is provided for a record, the compiler provides
one. The compiler-provided `postmove` method calls the `postmove` method
on each record field in turn.

TODO: the method name `postmove` is not finalized.


Choosing between copy and move operations
+++++++++++++++++++++++++++++++++++++++++

.. _copy-move-table:

The following table shows in which situations a copy or move operation is
added. Each row in this table corresponds to a particular use of an
expression `<expr>`. Each column indicates the kind the expression
`<expr>`. Blank spaces indicate that no copy or move operation is
necessary.

========================  ==========  =========  =========  ============  ============
operation                 value call  local var  outer var  ref argument  ref/ref call
========================  ==========  =========  =========  ============  ============
variable initialization   move        copy       copy       copy          copy     
call as `in` argument     move        copy       copy       copy          copy
value return              move        move       copy/move  copy/move     copy
ref return                            error            
call as `ref` argument                                
========================  ==========  =========  =========  ============  ============

Here is more detail on each operation:

variable initialization
  a variable initialization statement as in

  .. code-block:: chapel

    var a=<expr>;

call as `in` argument
  a function call where `<expr>` corresponds to a formal with `in`
  intent, as in

  .. code-block:: chapel

    proc f(in arg) { ... }
    f(<expr>)

value return
  a return statement in a function that returns `by value` - that is,
  does not have `ref` or `const ref` return intent.

  .. code-block:: chapel

    proc f() {
      return <expr>;
    }

ref return
  a return statement in a function that returns `by ref` - that is, with
  `ref` or `const ref` return intent.

  .. code-block:: chapel

    proc g() ref {
      return <expr>;
    }

call as `ref` argument
  a function call where `<expr>` corresponds to a formal with `ref`
  or `const ref` intent (or in cases where blank intent is `ref` or
  `const ref`), as in

  .. code-block:: chapel

    proc f(ref arg) { ... }
    test(<expr>)


Here is more detail on each expression type. The examples below include
some supporting code and then have the form of `... <expr> ...`.

value call
  a call to a function that returns `by value` - that is, does not
  have `ref` or `const ref` return intent.
 
  .. code-block:: chapel

    proc f() { ... }

    ... f() ...;

local var
  a use of a variable local to a function
 
  .. code-block:: chapel

    proc f() {
      var x = ...;
      ... x ...;
    }

outer var
  a use of a variable not local to a function, including a global
  variable or a variable declared in an outer function.
 
  .. code-block:: chapel

    var global:R = ...;
    proc f() {
      ... global ...;
    }

ref argument
  a use of a formal argument that has the `ref` or `const ref` intent
  (or a blank intent that is `ref` or `const ref`).
 
  .. code-block:: chapel

    proc f(const ref arg) {
      ... arg ...;
    }

ref/ref call
  a use of a ref variable or a call returning with `ref` or `const ref`
  return intent.
 
  .. code-block:: chapel

    ref x = ...;
    ... x ...;

  .. code-block:: chapel

    proc g() ref { ... }
    ... g() ...;



.. _ref-return:

`ref` Return Intent
+++++++++++++++++++

The `ref` or `const ref` return intent indicates that unlike a normal
return, the returned value does not transfer the responsibility for
freeing something to the caller.  In other words, returning something by
`ref` does not change when that variable is destroyed.

Return statements inside a function with `ref` or `const ref` return
intent have the following behavior:

 * The `return` statement in a `ref` or `const ref` return intent
   function does not cause a `move` or `copy` operation to be added. The
   `retVar` is just set to a created reference.
 * unlike non - `ref` returns, coercions and promotions are disabled for
   a ref return intent function. The type of the returned expression must
   match exactly. (This constraint is already described in the language
   specification);
 * it is a program error to return a reference to a value with a type 
   that is different from a function's declared return type.
   This should be flagged as a compile error or an execution-time error.
 * Returning a local variable or temporary in a function with `ref`
   return intent does not prevent that variable or temporary from being
   destroyed and so should be a compile error if possible. In other
   words, it is a program error to return a ref to any variable that is
   allocated on the stack. It is a program error in a ref-return function
   to:

   * directly return a local variable declared by the user.  This can be
     detected with a compiler error.
   * directly return a ref to a call to a function that does not have
     `ref` or `const ref` return intent because that returned value will
     be stored in a function-local temporary. This can be detected with a
     compile error.
   * return a reference to any value that will be destroyed once the
     function exits. It would be difficult for compiler analysis to find
     all such cases.

   
.. _automatic-ref-return:

Automatic `ref` Return Intent
+++++++++++++++++++++++++++++

The table above showed `copy/move` for two value return cases:

 * returning an outer variable
 * returning a ref argument

In these cases, it would be legal to use a `copy` operation. However, in
some situations, the `copy` is unnecessary and oculd be removed by adding
the `ref` or `const ref` return intent to the function.

For example, consider this program:

.. code-block:: chapel

  record R { ... }
  var global:R = ...;

  proc f() {
    return global;
  }

  writeln(f());

This program causes the record `global` to be copied in the process of
being output, since it is copied during the process of returning from
`f`.  This copy is unnecessary in this example and could be optimized
away. A user might explicitly remove the copies by adding the `const ref`
return intent to `f`.

A further example is this program:

.. code-block:: chapel

  record R { ... }

  proc xform(const ref arg) {
    arg[1] += 1;
    return arg;
  }

  var x:R = ...;
  var y = xform(xform(xform(x)));

Note that if `arg` had the `in` intent, the rules above would optimize
away the copies. However, when `arg` has the `const ref` intent, the
copies can be removed by adding the `const ref` return intent to `xform`.

Both of these programs will not have unnecessary copies because of the
rule described in this section.

The `ref` or `const ref` return intent is added automatically for
functions that always:

  * return a formal argument, where the formal had `ref` or `const ref`
    intent, or
  * return a outer scope variable

The new return intent should match the default argument intent. For user
records, that is `const ref`, but for arrays, it would be `ref`.

Note that it is important to restrict this rule to ref arguments and
outer variables.  It would not in general be valid for this rule to apply
to all functions that always return a ref expression. For example, in the
following:

.. code-block:: chapel

  record R { var x:int; }
  proc f() {
    var a = new R(12);
    ref refA = a; 
    return refA; 
  }

  writeln(f());

the value returned in `f` is always a reference, but it would make the
program erroneous to add the `const ref` return intent to it.

.. commented out 

  Note that for a record, it it is already illegal to assign to the result
  of call not marked with `const ref` return intent. For example

  .. code-block:: chapel

    record R { var x:int; }
    var global = new R(12);

    proc f() {
      return global;
    }

    f() = new R(1);

  results in the error "illegal lvalue in assignment". The transforamtion
  changes this code to:

  .. code-block:: chapel

    record R { var x:int; }
    var global = new R(12);

    proc f() const ref {
      return global;
    }

    f() = new R(1);

  in which the assignment to the result of `f()` is still an error.


.. commented out

  Things to watch out for:

   * returning a reference to a local variable
     (wouldn't want to change a correct program into an incorrect one)
     For example,

     .. code-block:: chapel

        proc f() {
          var x = 12;
          ref y = x; 
          return y; 
        }

        writeln(f());

     This example does not meet the criteria for the transformation above,
     since it returns neither an *outer scope variable* nor a
     *particular ref argument*. This transformation should probably not
     apply to functions returning arbitrary function calls that
     return a `ref`.

     Alternatives include:

       * functions that always return a ref (including the result of a call
         or a ref variable) could be candidates for this transformation. In
         that case, we would probably want to detect common cases of
         returning a ref to a variable that will go out of scope and make
         them into compilation errors. Note though that without language
         changes it is probably not reasonable to expect the compiler to
         detect all such cases.

   * functions returning a reference to a variable
     with unknown lifetime (local? global?). It would be a problem
     if the returned reference has a longer lifetime than
     the variable it refers to.

  Revisiting our earlier examples,

  .. code-block:: chapel

    var A:[1..3] int;

    proc f() {
      return A;
    }

    writeln(f());

  applying the transformation above would change it into the following:

  .. code-block:: chapel

    var A:[1..3] int;

    proc f() ref {
      return A;
    }

    writeln(f());

  Note that a copy of A would still be made in a case such as

  .. code-block:: chapel

    var B = f();

  since f() is a reference and is treated as another variable.

  This example is similarly improved by the transformation:

  .. code-block:: chapel

    proc xform(arg) {
      arg[1] += 1;
      return arg;
    }

    var A:[1..4] int;
    var B = xform(xform(xform(A)));

  Since the array argument to xform is passed by reference and always
  returned, xform can return by reference:

  .. code-block:: chapel

    proc xform(arg) ref {
      arg[1] += 1;
      return arg;
    }

    var A:[1..4] int;
    var B = xform(xform(xform(A)));

  In that case, A is modified by each xform call, instead of sometimes being a
  temporary being modified. This difference is observable if A is not dead after
  its use as an argument.

  This transformation makes the blank return intent not always `by value`.
  In some cases it would be the same as the `ref` or `const ref` return
  intent. We might consider enabling the `out` keyword to be used as an
  explicit return intent as an alternative to `ref`.  If we did so,
  functions with an `out` return intent would not be eligible for this
  transformation. Additionally, we would probably want to also adopt the
  optional extension :ref:`optimizing-out` for language consistency
  reasons.

  Alternatives:

   * create a performance warning. When a function always returns a global
     or an argument, warn that a copy can be removed if the function
     is declared with the `ref` return intent.

`inout` and `out` argument intents
++++++++++++++++++++++++++++++++++

TODO: describe the semantics of `inout` and `out` argument intents
(probably drawing from :ref:`record-copies-out-inout` but with less
implementation detail)

