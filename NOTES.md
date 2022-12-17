
General Comments
================

Clac is in a state of disarray. A lot of work will need to be done on it before it is reasonably
well organized again. Here is the current state of the program:

Clac is intended to have three parts

+ The entity library. This is a library of calculator entity types. It is intended to be
  independent of the rest of Clac and easily incorporated into other programs.

+ The execution engine. This does the actual calculations. As with the entity library, the
  execution engine is intended to be easily incorporated into other programs. This allows other
  applications to use Clac as an internal calculator or even as an internal numeric scripting
  language.

+ The user interface. This gives a nice, generic interface to the execution engine. In the
  current implementation the UI is a very simple, console-oriented interface. It prints a
  prompt, accepts a line of Clac command words, does computations, and outputs the state of
  Clac's stack before printing a new prompt. More glamourous user interfaces can easily be
  imagined and would be welcome additions to Clac.

Right now the entity library source is in the ClacEntity folder and the execution engine is in
the ClacEngine folder. The files related to the UI are in the top level directory. Documentation
is in the doc directory.

The original vision for Clac was to include a scripting language based on Forth (because of
Clac's stack-oriented nature). At the time of this writing, the scripting language is entirely
unimplemented. If it were mature, however, a number of computational features could potentially
be implemented as a library of standard scripts. This would reduce the mathematical part of Clac
to a core of basic numeric types with their primitive operations.

Notes, Bugs
===========

+ There are "TODO" lists for each source file in the comment header of that file and sprinkled
  in comments throughout the file. There is also a TODO.md file that contains items with broader
  scope (whose resolution might impact multiple files). TODO items of a strategic nature may
  also be found in the issues list on GitHub, although until Clac is more mature we don't plan
  to make much use of the GitHub issues list.
  
  If you are looking for something useful to do, just review the various TODO lists until you
  find something that looks interesting to you. We recommend that you make use of whatever TODO
  searching functionality your editor or IDE has to generate a list of TODO items.
  