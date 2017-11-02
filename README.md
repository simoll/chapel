try:

      source util/quickstart/setchplenv.bash
      export CHPL_COMM=gasnet
      make
      ./util/start_test  test/optimizations/cache-remote/ferguson/operations/


and then have a look at the included examples

     assoc-add-files.chpl
     assoc-add-enumerate.chpl
     assoc-add-block.chpl
