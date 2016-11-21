var tupRange: 3*range;
for t in tupRange do
  t = 1..1;
writeln(tupRange);

var tupInt: 3*int;
for t in tupInt do
  t = 1;
writeln(tupInt);

// check leader, follower, and standalone iterators
var otherTup: 3*range;

forall i in tupRange {
  i = 2..2;
}
writeln(tupRange);
forall i in tupInt {
  i = 2;
}
writeln(tupInt);

forall (i,j) in zip(tupRange, tupInt) {
  i = 3..3;
  j = 3;
}
writeln(tupRange);
writeln(tupInt);

forall (i,j) in zip(tupInt, tupRange) {
  i = 4;
  j = 4..4;
}
writeln(tupRange);
writeln(tupInt);
