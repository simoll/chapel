use myrecord;

proc make(i:int) {
  var ret: R;
  ret.init(x = i);
  ret.verify();
  return ret;
}

proc foo(rec: R) {
  rec.verify();
  rec.increment();
  rec.verify();
}

proc myfunction() {
  foo(make(1));
}

myfunction();

verify();
