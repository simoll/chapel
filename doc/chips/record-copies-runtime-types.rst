.. _record-copies-runtime-types:

Extending the Record Copying Semantics to Support Runtime Types
===============================================================

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

The document :ref:`record-copies` ignores certain details about
array runtime types. This document describes how these details can
be handled.

TODO TODO TODO


* `check` call added by the compiler
* `move` and `copy` initialization need a runtime type argument


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


