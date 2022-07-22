# files and how they work

`Arithmetic.cpp`: client file for arithmetic program that reads an input file and writes to an output file using the exported BigInteger operations

`BigInteger.cpp`: source code for BigInteger ADT's functions

`BigInteger.h`: header file that declares the interface and functions for BigInteger ADT

`BigIntegerTest.cpp`: test client file for checking the usability of the BigInteger ADT

`List.cpp`: source code for List ADT's functions

`List.h`: header file that declares the interface and functions for List ADT

`ListTest.cpp`: test client file for checking the usability of the List ADT

`Makefile`: file that runs a set of commands that build the program and create the executable file

# build/run/clean

In order to compile and run this program, you will need the Makefile, c source code files, and the header file.

To build the Arithmetic program:
```
$ make
```
and to run Arithmetic:

```
$ ./Arithmetic <input file> <output file>
```

To build the BigInteger test program:
```
$ make BigIntegerTest
```

To remove all binary files, run:
```
$ make clean
```

