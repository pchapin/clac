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

The C++ version of Clac can be built with Visual Studio on Windows and g++ (via Code::Blocks or
Makefiles) on Unix-like systems (Linux, macOS, Cygwin). Not all build control files are fully up
to date. At the time of this writing (Dec 2022) Clac development is being done primarly on Linux
using g++ and Makefiles with Visual Studio Code as the development environment. Thus the
Code::Blocks and Visual Studio build control files may need adjusting, as they are only
infrequently checked.

API documentation for Clac is built using the Doxygen tool. The User Manual, Reference Manual,
and Tutorial are built using LaTeX. These tools are only needed if the documentation is to be
built.

Building
--------

Building Clac on a Unix-like system is as simple as running make in the top level folder:

    $ make
    
Clac is known to build on Ubuntu 22.04 provided g++ is installed. At the time of this writing
Clac does *not* build on macOS Ventura, but that may change soon. Clac is intended to also be
buildable on Cygwin, but that has not yet been tested.

Building the internal API documentation can be done by running doxygen in the top level folder:

    $ doxygen
    
The HTML documentation is in doc/internal/index.html. Clac assumes Doxygen 1.9.1, but other,
similar versions should also work.

Peter C. Chapin  
peter@pchapin.org  
