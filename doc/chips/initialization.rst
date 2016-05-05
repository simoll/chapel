.. _initialization:

Initialization in Chapel
========================

Status:
  Draft

Authors:
  Michael Ferguson

Abstract
--------

A description of what constitutes initialization and the different kinds
of initialization in Chapel programs.

Rationale
---------

This document provides common language for describing initialization
and some basic understanding of when initialization occurs.

Description
-----------

When a new Chapel variable is created, it is initialized. In other words,
it is set to some initial state.

In the discussion below, we will assume that `R` is a non-generic record
and `C` is a non-generic class.


Record Initialization
+++++++++++++++++++++

.. code-block:: chapel

  var x:R;

`x` is automatically initialized by a call to `x.init()`.

.. code-block:: chapel

  var x:R = noinit;

`x` is automatically initialized by a call to `x.init(noinit=true)`,
or `x.init()` if the first version does not resolve.

.. code-block:: chapel

  var x:R = new R(<args>);
  // or, equivalently
  var x = new R(<args>);

`x` is initialized by a call to `x.init(<args>)`.

.. code-block:: chapel

  var x:R = ...;
  var y:R = x;
  ... use x and y ...

`y` and `x` refer to different record variables.  We say that `y` is
`copy initialized` from `x`.

.. code-block:: chapel

  record MyRecord {
    var field:R;

    proc init(const ref arg:R) {
      field = arg;   // Note Here
      super.init();
    }
  }

This example shows field initialization. The statement `field = arg`
causes `field` to be `copy initialized` from `arg`.

.. code-block:: chapel

  proc returnR() {
    var ret = new R(<args>);
    return ret;
  }
  var x:R = returnR();

`x` is initialized to have the same value as `ret` which is returned in
`returnR`. Since the value moves from `ret` to `x`, we say that `x` is
`move initialized` from `ret`.

There are many other situations in which `copy` or `move` initialization
occur. The document :ref:`record-copies` describes these in detail.

.. code-block:: chapel

  var x:R;
  var y:R;
  ...;
  x = y;

The statement `x = y` here is called assignment. It is different from
initialization. It will be translated to a call to the `=` operator with
the arguments `x` and `y`. Assignment is different from initialization
because in assignment, the left-hand-side variable has already been
initialized and is being set again.

Class Initialization
++++++++++++++++++++

.. code-block:: chapel

  var x:C;

`x` is automatically initialized to `nil`.

.. code-block:: chapel

  var x:C = new C(<args>);
  // or, equivalently
  var x = new C(<args>);

`x` is automatically initialized to the result of:

 1) allocating memory for a class instance of type `C`
 2) invoking `x.init(<args>)` to initialize that instance

.. code-block:: chapel

  var x:C = ...;
  var y:C = x;

`y` and `x` point to the same class instance. We can say that the
variable `y` is initialized from the variable `x`. That initialization
just amounts to copying a pointer value and no user-defined initializer
is invoked.

Related Documents
+++++++++++++++++

 * :ref:`Initializers` describes how initializers can be specified
 * :ref:`record-copies` describes exactly when copy or move
   initialization occur.
