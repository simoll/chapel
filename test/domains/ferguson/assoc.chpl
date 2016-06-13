writeln("Making domain");
var D = {1, 2, 3, 5, 7};
//writeln("Result type");
//writeln(D.type:string);
//writeln("Result n slots ", D._value.tableSize);
//writeln("Result slots domain ", D._value.tableDom);
//writeln("Result table size num ", D._value.tableSizeNum);
writeln("Result");
for i in D.sorted() {
  writeln(i);
}

writeln("Making array");
var A:[D] int;
//writeln("Result dataDom ", A._value.dataDom);
//writeln("Result data.size ", A._value.data.size);
writeln("Setting element 2");
A[2] = 2;

writeln("Result");
for i in D.sorted() {
  writeln(i, " : ", A[i]);
}

writeln("Reassigning Domain");
D = {2, 4};
writeln("Result");
for i in D.sorted() {
  writeln(i);
}

writeln("Array Result");
for i in D.sorted() {
  writeln(i, " : ", A[i]);
}


writeln("Copying Domain");
var D2 = D;
writeln("Result");
for i in D2.sorted() {
  writeln(i);
}


writeln("Creating empty domain");
// Try setting domain after array is created
var D3:domain(int);
var A3:[D3] int;

for i in D3.sorted() {
  writeln(i);
}

writeln("Replacing empty domain");
D3 = {1, 2};
for i in D3.sorted() {
  writeln(i, " : ", A3[i]);
}

var empty:domain(int);
D3 = empty;

writeln("Assigning back to empty domain");
for i in D3.sorted() {
  writeln(i, " : ", A3[i]);
}
