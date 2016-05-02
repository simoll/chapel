.. _record-copies-out-inout:

Record Copying in Chapel: out and inout
=======================================

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
to better support `out` and `inout` argument intents.


Argument Intents
----------------

It is clear that the `in` intent should cause the `copy` operation to be
added in some cases. The current compiler adds `initCopy` calls
at the start of the body of a function with the `in` intent.
However, in order to support optimization of common patterns, this
proposal recommends that any copying in required by the `in`, and `inout`
intents be handled by the caller of the function. Doing these copies in
the caller of the function allows the rules above to apply, so that (for
example) no copy is made passing a value returned by one function to
another with `in` intent. It also allows the :ref:`record-copies-expiring` to
apply to them without needing to be inter-procedural.

In particular, the `in` intent should be treated similarly to a variable
declaration. For example,

.. code-block:: chapel

    proc g(in arg) { ...  }

    g( someExpression );

is nearly equivalent to, under this proposal:

.. code-block:: chapel

    proc g(ref arg) {
      ...;
      (destroy arg)
    }

    var tmp = someExpression;
    g( tmp );

As with a variable declaration, no copy is required if `someExpression`
is a function call - but a copy is required if `someExpression` is
another variable or a function call returning a reference. By adding any
`copy` that is necessary in the caller (vs the callee), the above rules
can apply to minimize these copies.

Here is an example showing the proposed behavior for `in`, `inout`,
and `out` argument intents.

.. code-block:: chapel

    proc g(in inArg, inout inoutArg, out outArg)
    {
      ...;
      inoutArg = f();
      inoutArg = outerVar;
      outArg = f();
      outArg = outerVar;
      ...;
    }

    {
      var inoutVar: t;
      var outVar: t;
      g( inExpr, inoutVar, outVar );
      ...;
    }

It would be translated to the following:

.. code-block:: chapel

    proc g(ref inArg, ref inoutArg, ref outArg) {
      (copies for in/inout are handled in caller)
      ...;
      inoutArg = f();      // assignments to inout and out args
      inoutArg = outerVar; // use assignment overload
      outArg = f();
      outArg = outerVar;
      ...;
      (destroy inArg)
    }

    {
      var inoutVar: t;  // as before
      var outVar: t;    // as before

      var inExprTmp = inExpr;
      var inoutVarTmp = inoutVar;
      var outVarTmp: outVar.type;
      g( inExprTmp, inoutVarTmp, outVarTmp );
      inoutVar = inoutVarTmp; 
      outVar = outVarTmp; 
      ...;
      ( does NOT destroy inExprTmp, that happens in g ) 
      ( destroy inoutVarTmp )
      ( destroy outVarTmp )
      ( destroy outVar as normal )
    }

Note that:
 * assignments to an `inout` or `out` argument within a function use the
   `=` overload
 * multiple assignments to an `inout` or `out` argument are possible
 * `out` and `inout` include unnecessary copies in many cases.

See :ref:`removing-inout` and :ref:`optimizing-out` for specific optional
proposals that could improve the situation with `inout` and `out`. While
these optional proposals do not need to be implemented immediately, the
specification can be worded in a way that permits them to be implemented
in the future without changing the language.

Note that this handling of argument intents needs to happen during or
after function resolution, since it operates on both a called function
and its call sites.

.. _removing-inout:

Removing `inout` argument intent from the language
++++++++++++++++++++++++++++++++++++++++++++++++++

What can you do with `inout` that can't be done more efficiently with
`ref` ? The `inout` intent seems possibly useful for parallelism (as a
task intent) but even there, if the copy back happens in the spawned
tasks, it does nothing to prevent race conditions. Contrast with `in`
which can remove race conditions and fits in well with copy reduction
strategy.

It is worth noting that the `inout` intent predates the `ref` intent.

.. _optimizing-out:

Optimizing `out` arguments
++++++++++++++++++++++++++

The `out` intent could be treated in the same manner as a function return
in that it transfers the responsibility of freeing to the caller. For
example, we would like the following example to not have any copies:

.. code-block:: chapel

    proc g(out arg) {
      arg = f();
    }

    var tmp:t;
    g( tmp );

However, implementing such semantics has some implications:

 1. it would imply that at `out` argument is not initialized
    on the way in to a function body - since e.g. declaring
    `tmp` as an array would allocate space

 2. that would imply that this particular `var tmp:t` does not behave as
    usual - so destinations for `out` arguments would need special
    initialization logic. One approachable way to achieve this logic
    would be to destroy the actuals for `out` intent formals before the
    function call, and to use an optimization to remove initializations
    of a variable that is next used by being destroyed.

 3. it would require either that:

   * it is an error if an `out` argument is not set exactly once on some
     path through a function, or
   * each `out` argument can be set zero or one times on each path
     through a function. If it is set zero times, it will be
     default-initialized. Or,
   * each path through a function will default-initialize each `out`
     argument if it is not set, and use the `=` overload to set it if it
     has already been set once. For example:

     .. code-block:: chapel

         proc g(out outArg)
         {
           ...;
           outArg = f();  // first time outArg is set is initialization
           outArg = f();  // second time outArg is set is assignment
           ...;
         }

     The required compiler support for differentiating initializing `out`
     arguments from assigning them has some similarities to some phase 1
     initializer proposals.

The current implementation implements the copies sometimes implied by
`inout` and `out` with a call to the assignment function `=`. The
advantage of the proposed design is that it allows optimization for
certain typical cases such as:

.. code-block:: chapel

    proc g(out outArg) {
      outArg = f();
    }

    var r:R;
    g(r);

In particular, the example above would not generate any copies. Compare
with the version using `=` which would - for an array - perform a deep
copy of the array elements.

The following example shows a scenario in which copies would occur under
the rules in this section, but where these copies could be optimized away by
:ref:`record-copies-expiring`.

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

In particluar, under the rules in this section:

 * tmp_a and tmp_b will allocate memory
 * before the call to source, tmp_a and tmp_b would be destroyed
 * then call to source would move the arrays it created into tmp_a and
   tmp_b
 * the call to sink would copy tmp_a and tmp_b because the formal
   argument is a different variable than the actual.

