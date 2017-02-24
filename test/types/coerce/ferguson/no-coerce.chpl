
record R {
  var x: int;
}

proc R.coercible(type t) param where t == int return false;

proc _cast(type t, r:R) where t == int {
  return r.x;
}

proc acceptsInt(x:int) {
  writeln("In acceptsInt(", x, ")");
}

var rec = new R(10);

var x:int;

writeln(rec);

x = rec;

writeln(x);

acceptsInt(rec);

// Also check explicit cast.
writeln(rec:int);
