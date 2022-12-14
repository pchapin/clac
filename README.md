Clac
====

Clac is a programmable calculator inspired by the HP48 series of calculators. It is *not* an
emulation of the HP48. It lacks many of the features of the HP48, but it also has several unique
features of its own.

The primary implementation is in C++ and has three components. The ClacEntity library is a
library of calculator (mostly numeric) data types. The ClacEngine library provides the execution
engine that interpretes calculator input and coordinates the computations. The top level code
defines the user interface. In theory other programs could make use of Clac's entity library and
execution engine while using a different user interface.

In addition, there is a completely independent implementation of Clac written in Java in the
jaClac folder. This implementation does not currently share any code with the C++ version. See
the README in that folder for more information.

Finally, there is a lightweight version of Clac written in Java in the Clacky folder. This
version is independent of both the C++ version and of jaClac. It is suitable for study by novice
programming students using Java.

Building
--------

Building Clac on a Unix-like system is as simple as running make in the top level folder:

    $ make
    
Clac is known to build on Ubuntu 22.04 provided g++ is installed. This build method should also
work on macOS Ventura and Cygwin, but those build environments are not checked as often.

Building the internal API documentation can be done by running doxygen in the top level folder:

    $ doxygen
    
The HTML documentation is in doc/internal/index.html. Clac assumes Doxygen 1.9.1, but other,
similar (higher) versions should also work.

The full documentation can be built by running `pdflatex` in the `doc` folder on `Tutorial.tex`,
`Reference.tex`, and `Design.tex`. This will build the tutorial, the reference manual, and the
design document as three separate documents.

Any text editor can be used, of course, to edit the source code. We tend to use Visual Studio
Code for editing the C++ source and Emacs for editing the LaTeX documentation and embedded
Doxygen comments.

Platform Support
----------------

In addition to using the Makefiles on Unix-like systems as described above, Clac can also be
built in the following ways:

### Linux

+ Using Code::Blocks and the provided `clac.workspace` file. This build configuration is not
  tested frequently, but is supported.
  
### Windows

+ Using Visual Studio 2022 and the provided `clac.sln` file. This build configuration is used
  often, and should be working at all times.
  
+ Using Code::Blocks and the provided `clac.workspace` file. This build configuration is rarely
  used, and may not work.
  
### macOS

+ Using XCode and the provided ... (*Finish Me!*)

Peter Chapin  
chapinp@proton.me  
