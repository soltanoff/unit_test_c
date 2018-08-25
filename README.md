# Unit test for C

This is the "list example" from the Check.

This demonstrates using Check with CMake.

CMake:
========================

You need the following programs installed on your system:
  -- CMake 2.8
  -- Check 0.9.9
  -- (pkg-config 0.26 is optional)

Somewhat earlier versions of these programs might work.

NOTE: If pkg-config is not installed on the system, and MSVC is being used,
the install location of Check must be inserted manually into the
`tests/CMakeLists.txt` file, by setting the variable `CHECK_INSTALL_DIR`
to the install location. Look at the `tests/CMakeLists.txt` file for
a commented out example.

Then, do as follows for a Unix-compatible shell:
```
$ cmake .
$ make
$ make test
```
or the following for MSVC:
```
$ cmake -G "NMake Makefiles" .
$ nmake
$ nmake test
```
Don't do `make install` or `nmake install` unless you want to install the good example.

`good.c` and `good.h` are built as a library.  `src/main.c:main()` is a
client of `libgood.la`, just as `tests/check_good.c:main()` is a client
of `libgood.la`

To use the CMake example in another project, start with the following files:
```
   example
   |--- CMakeFiles.txt
   |--- cmake
   |    |--- config.h.in
   |    |--- FindCheck.cmake
   |--- src
   |    |--- CMakeFiles.txt
   |--- tests
        |--- CMakeFiles.txt
```
