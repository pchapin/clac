Clac
====

Clac is a programmable calculator inspired by the HP48 series of calculators. It is *not* an
emulation of the HP48. It lacks many of the features of the HP48, but it also has several unique
features of its own.

The primary implementation is here in C++ 2020 and has three components. The ClacEntity library
is a library of calculator (mostly numeric) data types. The ClacEngine library provides the
execution engine that interprets calculator input and coordinates the computations. The top
level code defines the user interface. In theory other programs could make use of Clac's entity
library and execution engine while using a different user interface.

Currenty the user interface of Clac makes use of a cross-platform screen handling library named
Scr. The [Scr library](https://github.com/pchapin/scr) is available on GitHub, but is included
here as a Git submodule. Note that Scr is only used by the user interface code. It is not used
by the ClacEntity library or by the ClacEngine library. Other programs using those libraries do
not need to involve Scr at all.

In addition, there is a completely independent implementation of Clac for Android written in
Kotlin in the [aClac](https://github.com/pchapin/aclac) repository. That implementation does not
currently share any code with the C++ version. See the README in that repository for more
information.


Cloning
-------

The method for cloning Clac to your own system depends on what you are using as a Git client.
In the case of the command line client, consider using the following commands:

    $ git clone https://github.com/pchapin/clac.git Clac
    $ cd Clac
    $ git submodule init
    $ git submodule update
    
The first command clones the repository to a subfolder named `Clac`. Inside that folder the
submodule init command registers the submodule so that it can be tracked properly. The submodule
update command fetches the appropriate revision of the submodule. That may not be the most
recent revision, but it is the revision that is known to work with Clac.

If you wish to update the submodule to the most recent revision (in this case, of Scr), do:

    $ git submodule update --remote
    
However, you should verify that Clac continues to work with this updated revision and, after
making any necessary changes, you should commit the new submodule revision by doing a commit in
the usual way. Other team members will then need to use the submodule update command (afer doing
a pull operation) to update themselves to the new revision of the submodule.


Building
--------

Clac can be built on a Unix-like system by simply running make in the top level folder:

    $ make
    
Clac is known to build on Ubuntu 22.04, Cygwin, and macOS Ventura, provided the required tools
are installed in each environment (g++ and make).

The test program is located in the `check` folder. See the README in that folder for more
information about how to do Clac testing. At the time of this writing the tests are immature.

There are some benchmark programs in the `bench` folder. See the README in that folder for more
information about how to run the Clac benchmarks. At the time of this writing, the benchmarks
are *very* immature.

The internal API documentation can be built by running `doxygen` in the top level folder:

    $ doxygen
    
The HTML documentation is generated to doc/internal/index.html. Clac assumes Doxygen 1.9.1, but
other, similar (higher) versions should also work.

The full documentation can be built by running `pdflatex` in the `doc` folder on `Tutorial.tex`,
`Reference.tex`, and `Design.tex`. This will build the tutorial, the reference manual, and the
design document as three separate documents.

Any text editor can be used, of course, to edit the source code. We tend to use Visual Studio
Code on the Unix platform, but see below for additional platform support.


Platform Support
----------------

In addition to using the Makefiles on Unix-like systems as described above, Clac can also be
built in the following ways:

### Windows

+ Using Visual Studio 2022 and the provided `clac.sln` file. This build configuration is used
  often, and should be working at all times. The recommended way of doing Clac development on
  Windows is by using Visual Studio.
  
+ Using Eclipse for C/C++ Programmers (Eclipse with the CDT). The project files for this
  development environment assume the Cygwin C++ tool chain. If you want to use Eclipse on a
  Unix-like system, you will likely need to make adjustments. Note that the Eclipse project is
  configured to use the provided Makefile to do the actual build.
  
+ Using Code::Blocks and the provided `clac.workspace` file. This build configuration is not
  tested regularly, and may need some adjustments before it will work. Note that the version of
  g++ that is bundled with Code::Blocks 20.03 is too old to work. Clac makes use of several
  newer C++ 2020 features. However, you could reconfigure Code::Blocks to use a newer compiler,
  for example in the Cygwin distribution. It is hoped that a future version of Code::Blocks will
  ship with a newer C++ compiler.
  
### macOS

+ Using XCode and the provided ... (*Finish Me!*)

### Linux

+ Using Code::Blocks and the provided `clac.workspace` file. This build configuration is not
  tested regularly, and may need some adjustments before it will work. Also see the comments
  about Code::Blocks in the Windows subsection above.


Developer Notes
---------------

Makefile dependencies are maintained using a tool named `depend` that can be [found on
GitHub](https://github.com/pchapin/tools). This tool takes a list of source files and crawls
over the includes to generate dependency lists suitable for `make`. The tool is *not* needed to
build Clac, but it may be useful when updating Makefiles.

In each folder containing C++ source files, you will find a file `depend.dep` that contains a
list of .cpp files that should be built. The shell script `depend.sh` runs the `depend` tool on
this file, putting the result in `depend.out`. That output file can be copied and pasted into
the Makefile to update dependency information.
  
Peter Chapin  
chapinp@proton.me  
