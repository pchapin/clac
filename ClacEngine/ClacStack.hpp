/*! \file    ClacStack.cpp
 *  \brief   This file contains the interface to class ClacStack.
 *  \author  Peter Chapin <spicacality@kelseymountain.org>
 */

#ifndef CLACSTACK_HPP
#define CLACSTACK_HPP

#include "Entity.hpp"
#include "VeryLong.hpp"

/*! A class holding a stack of Entity values used during computations.
 *
 * Instances of this class hold (pointers to) Entity values of various types in a stack-like
 * structure. Methods are provided for various stack manipulations to support the stack
 * management commands used by Clac. Currently Clac instantiates only a single object of this
 * type to hold command parameters. Multiple Clac stacks could potentially be created to support
 * additional features in a future version of Clac. However, the life cycle methods would need
 * to be implemented first.
 * 
 * Note that the first level of the stack (the "top" of the stack) is level zero. Stack index
 * values are represented using VeryLong because those values typically come from entities on
 * the parameter stack. It is recognized, however, that the type VeryLong is extreme overkill
 * and potentially inefficient to use in this way.
 * 
 * \todo Currently ClacStack objects are limited to holding at most 100 Entity values. This
 * limitation should be lifted in the future. It is expected that recursive Clac scripts might
 * need a lot of parameter stack space.
 */
class ClacStack {
private:
    enum { STACK_SIZE = 100 };

    // TODO: Modify this class to allow a stack of arbitrary size.
    Entity *data[STACK_SIZE];

public:
    //! Initialize the ClacStack to an empty state.
    ClacStack( );

    //! Delete all objects in the ClacStack before cleaning up the stack itself.
   ~ClacStack( );

    // Disable the other life cycle methods (for now).
    ClacStack( const ClacStack & ) = delete;
    ClacStack &operator=( const ClacStack & ) = delete;

    //! Push an Entity onto the stack (that is, stack level zero). Return false on error.
    bool push( Entity *item );

    //! Pop and remove the entity from stack level zero. Return nullptr if the stack is empty.
    Entity *pop( );

    //! Get a copy of an entity from the stack. Return nullptr if index out of bounds.
    Entity *get( const VeryLong &index );

    //! Put a copy of the argument into stack level zero. The old object, if present, is deleted.
    void put( Entity *new_object );

    //! Drop everything off the stack.
    void clear( );

    //! Delete level 0 of the stack.
    void drop( );

    // TODO: Implement ClacStack::dup.
    //! Make a copy of the entity at 'level' and push it onto level 0. Return false on error.
    bool dup( const VeryLong &level = 0 );

    //! Return the total height of the stack.
    size_t height( );

    //! Rotates the top 'count' levels "down" (meaning toward lower level numbers).
    void roll_down( const VeryLong &count );

    //! Rotates the top 'count' levels "up" (meaning toward higher level numbers).
    void roll_up( const VeryLong &count );

    //! Equivalent to "3 roll_up".
    void rotate( );

    //! Exchange stack levels 0 and 1.
    void swap( );
};

#endif

