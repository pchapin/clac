Clac
====

Clac is a programmable calculator inspired by the HP48 series of calculators. It is *not* an
emulation of the HP48. It lacks many of the features of the HP48, but it also has several unique
features of its own.

This implementation is in C++ 2020 and has three components. The ClacEntity library is a library of
calculator data types. The ClacEngine library provides the execution engine that interprets
calculator input and coordinates the computations. The ClacConsoleUI component defines the user
interface. At this time, the UI is a simple "scrolling text" console interface. This has the
advantage of being highly portable, even if not very glamorous. Adding more powerful UIs, perhaps
more than one, is an area for future development.

In theory, other programs could use Clac's entity library and execution engine while using a
different user interface. The intention is for the core of Clac to be embeddable in other
applications. The feasibility of this has not been tested.

There is a completely independent implementation of Clac for Android written in Kotlin in the
[aClac](https://github.com/pchapin/aclac) repository. That implementation does not share any code
with the C++ version. It is also extremely immature. See the README in that repository for more
information.

## Cloning

The method for cloning Clac to your system depends on what you are using as a Git client. In the
case of the command line client, consider using the following commands:

```bash
git clone https://github.com/pchapin/clac.git Clac
cd Clac
git submodule init
git submodule update
```

Calc depends on the SpicaCpp library, which is included as a Git submodule. The first command above
clones the repository to a subfolder named `Clac` (feel free to use whatever name you like). Inside
that folder, the `submodule init` command registers the submodule so that it can be tracked
properly. The `submodule update` command fetches the appropriate revision of the submodule.

## Building

Clac is built using CMake. There are several CMake presets provided for various development
environments. See the file `CMakePresets.json` for more information about the available presets.
Choose the preset that matches your development environment and use it to configure the build. For
example, using the `windows-x64-debug` preset, you can configure and build Clac as follows:

```bash
cmake --preset windows-x64-debug
cmake --build --preset windows-x64-debug
```

All build artifacts will be placed in the `build/windows-x64-debug` folder (in this case), including
the executable file. You can change the build type (Debug, Release, etc.) by using a different
preset.

Most modern C++ IDEs have built-in support for CMake. If you are using an IDE, you can likely just
open the project folder and select the appropriate preset to configure and do the build. Using the
presets promotes build consistency across different development environments.

## Documentation

The internal API documentation can be built by running `doxygen` in the top level folder:

```bash
doxygen
```

The HTML documentation is generated to `docs/api/index.html`.

The full documentation in LaTeX can be built by running `pdflatex` in the `docs` folder on
`Tutorial.tex`, `Reference.tex`, and `Design.tex` separately. This will build the tutorial, the
reference manual, and the design document, respectively, as three independent documents.

The folder `ClacNotes` contains an [Obsidian](https://obsidian.md/) vault with various notes about
the design and implementation of Clac. Unlike the formal documentation in `docs`, these notes are
more informal and dynamic. Obsidian stores notes in plain Markdown format, so they can be read and
edited with any text editor. The Obsidian vault is just a convenient way to organize the notes and
to take advantage of Obsidian's features for linking and navigating between notes.

## Platforms and Tooling

Clac is intended to build on Windows, macOS, and Linux using compilers that are "native" to each
platform. Consult the list of CMake presets for the currently supported platforms and tool chains.

Any development environment with CMake support should be usable for developing Clac. I tend to use a
variety: Visual Studio, CLion, Visual Studio Code, Zed, Helix, Emacs, etc. The project-specific
settings for these environments are being committed to the Clac repository. I realize this is a
controversial practice, but since I am currently the only developer, I find it convenient to have
project-specific settings synchronized across my machines via Git. If other developers join the
project, we can revisit this practice and make adjustments as needed.

I do make an effort to keep machine-specific settings out of the repository so that, in theory, the
project-specific settings should work anywhere and for any user.

## Historical Notes

Clac is very old. The original version was written in the 1990s as an exercise in learning C++, and
as a collaboration between me and my friend Peter Nikoladis. The C++ code from that original version
predates C++ 98, and is in an ancient style, written by two inexperienced programmers.

Since then, Clac has undergone several refactorings. Currently, the codebase is a hodgepodge of
coding styles, with some sections being reasonably modern and others still reflecting the program's
ancient heritage. Furthermore, Clac was never finished. There is still, to this day, significant
functionality missing. The plan was to implement a Forth-like language for programming the
calculator, but that has never been done. The entire concept should probably be revisited.

The documentation in the `docs` folder is also very old, incomplete, and outdated.

Now that I am retired and have more time to devote to projects like this, I am undertaking a major
effort to refactor the codebase and update the documentation. The goal is to make the code more
modern and readable, and to make the documentation more complete and up to date. I would also like,
after 30+ years, to finally finish Clac! This is a work in progress, and there is still a long way
to go.

Peter Chapin  
spicacality@kelseymountain.org  
