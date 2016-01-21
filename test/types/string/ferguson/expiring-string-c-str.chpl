config const debug = false;

var globalString:string;

globalString += "a";

proc getGlobalString()
{
  return globalString;
}

proc doit() {
  extern proc printf(fmt:c_string, buf);

  // if mallocGoodSize > 3 e.g. on mac os x
  var a = globalString;
  a += "b";
  var b = a.localize();
  var c = b;
  var d = c;
  //writeln(a._size);
  //writeln(b._size);
  d += "c";
  //writeln(d._size);
  //a.printbuf();
  //b.printbuf();
  //c.printbuf();
  //d.printbuf();
  if debug {
    printf("a %p\n", a.buff);
    printf("d %p\n", a.buff);
  }
  writeln("ab  ", a);
  writeln("ab  ", a.c_str():string);
  if debug {
    printf("a %p\n", a.buff);
    printf("d %p\n", a.buff);
  }
  writeln("abc ", d);
  writeln("abc ", d.c_str():string);
  //writeln(b);
  //writeln(b.c_str():string);
}

doit();
