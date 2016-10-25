.. _record-copies-user-view:

Record Copying in Chapel: The User's View
=========================================

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

Discussion of how the design in :ref:`record-copies` can be presented to
the user.

The User's View
---------------


TODO : this section probably needs to be completely rewritten. It in fact
only proposes that the return statement copy/no copy not be specified.
Vass has an interesting alternative for the specification.


This section describes how we expect users to think about Chapel's rules
for inserting copies. We expect that some form of this section would be
in the language specification. It is an open question how much additional
detail the specification should include. One reasonable view is that
this section might be the view of a domain scientist, while something
covering the rules below would be available for library authors and
advanced users.

A variable declaration creates unique storage for a record's fields.  The
process of returning may or may not provide unique storage for a record.
The `in` argument intent is treated similarly to a variable declaration
in that the `in` argument has unique storage for the record's fields.
The `ref` argument intents do not imply unique storage. A logical copy
may or may not be needed in order to ensure that a variable has unique
storage.

What does *unique storage for a record's fields* mean?

.. code-block:: chapel

  var a:R;
  a.x = 1;
  var b = a;
  b.x = 2;      // b is a different variable from a, so
  writeln(a.x); // updating b's field x must not change a's field x.

This property only extends to class instances pointed to by a record when
the record is implemented to copy such memory during a logical copy
operation (in other words, when the `postblit()` method copies fields of
class type).

This guiding rule is the same whether types are implicit or explicitly
provided. However, it does not say anything about how a variable is
returned. Lastly, it does not prohibit an implementation from making
temporary copies.

This strategy is meant to support the following use cases:

 * records implementing reference counting (see :ref:`record-copies-ref-count`)
 * records storing some data in buffer (e.g. BigInt record) (see
   :ref:`record-copies-buffer`)
 * strings (see :ref:`record-copies-strings`)
 * arrays (see :ref:`record-copies`)

In particular, if records contain pointers, the expectation is that
typical use of the record will always copy the pointed-to data, or will
always share the pointed-to data. Records that sometimes copy the
pointed-to data and sometimes share it require special care. Arrays and
strings are examples of records that require special care. Implementing
such records requires knowledge of further details that are covered in
the rest of this proposal.

