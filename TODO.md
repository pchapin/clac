TODO List
=========

This file contains a list of work items for Clac. Once the program has reached a certain level
of maturity, it may make sense to use the issues list on GitHub for TODO items. However, at this
stage of Clac's development, there will be many low-level, short-lived TODO items to think
about, or items that bear on the implementation of fundamental features. The issues list on
GitHub feels like the wrong place to manage such items.

Broadly speaking, here are some major TODO items:

+ Reasonable tests should be added (currently there are very few tests).
  
+ The documentation needs to be overhauled and updated.
  
+ The basic entity types need to be completed and checked.

+ The display( ) method of the entity types needs to be updated to honor the display state of
  the calculator.

+ Here is a list of additional operations and features that probably should be supported
  someday. Many of these items are taken directly from the HP-48 documentation.

    ! (factorial and/or gamma function)
    %
    %ch
    %t
    >rat
    alternate user interfaces (full screen or even graphical)
    beep
    debugging support
    commenting for scripts
    constants library
    d->r
    det (for matrices)
    directory operations
    dot and cross products
    engineering notation for integers
    hyperbolic functions (sinh, cosh, etc.). Or should these be implemented as scripts?
    logs of arbitrary base
    matrices
    pick stack level
    "please wait...". The idea is to print a message when a computation takes a long time.
    random number generation (0 to 1)
    relational tests (==, !=, <=, etc.)
    relocate purge & sto
    scripting capability
    shifts + rotates
    signed binaries
    size
    stack editing... (using a pop up window?)
    statistics + probability. Or should these be implemented as scripts?
    tags
    trace (for matrices)
    transpose (for matrices)
    type
    undo
    units support
    user input (for scripts)
