proc test() {
  var end = _endCountAlloc(false);
  chpl_setEndCount(end);
  var got_end = chpl_getEndCount();
  assert( end == got_end );
  var group = new ErrorGroup();
  chpl_setErrorGroup(group);
  var got_group = chpl_getErrorGroup();
  assert( group == got_group );
  writeln("OK");
}

test();
