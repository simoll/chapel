/* The Computer Language Benchmarks Game
   http://benchmarksgame.alioth.debian.org/

   contributed by Ben Harshbarger and Brad Chamberlain
   derived from the GNU C version by Mr Ledrug
*/

const table = initTable("ATCGGCTAUAMKRYWWSSYRKMVBHDDHBVNN\n\n");

proc main(args: [] string) {
  const consoleIn = openfd(0),
        stdin = consoleIn.reader(locking=false);
  var data: [1..consoleIn.length()] uint(8),
      idx = 1,
      start = 0;

  //
  // don't continue until all process() tasks complete
  //
  sync {
    var numRead: int;

    while stdin.readline(data, numRead, idx) {
      //
      // Look for the start of a section
      //
      if data[idx] == ascii(">") {
        if start then 
          //
          // Spawn a task to work on the previous section
          //
          begin process(data, start, idx-2);
        
        start = idx;
      }
      idx += numRead; 
    }

    // work on the final section
    process(data, start, idx-2);
  }

  const stdoutBin = openfd(1).writer(iokind.native, locking=false, 
                                     hints=QIO_CH_ALWAYS_UNBUFFERED);
  stdoutBin.write(data);
}


proc process(data, in start, end) {
  //
  // Skip the header information
  //
  while data[start] != ascii("\n") do 
    start += 1;
  start += 1;

  const extra = (end - start) % 61,
        off = 60 - extra;

  if off > 0 then
    for m in (start+extra)..(end-1) by 61 {
      for i in 0..#off by -1 do
        data[m+1+i] = data[m+i];
      data[m+1] = ascii("\n");
    }

  const middle = (end-start)/2;
  for i in 0 .. middle {
    const c = table[data[start+i]];
    data[start+i] = table[data[end-i]];
    data[end-i] = c;
  }
}

proc initTable(param pairs) {
  var table: [1..128] uint(8);

  for param i in 1..pairs.length do
    if i%2 {
      table[ascii(pairs[i])] = ascii(pairs[i+1]):uint(8);
      if pairs[i] != "\n" then
        table[ascii(pairs[i].toLower())] = ascii(pairs[i+1]):uint(8);
    }

  return table;
}
