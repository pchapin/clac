/*! \file    global.cpp
 *  \brief   This file contains the implementation of clac's global state.
 *  \author  Peter Chapin <chapinp@proton.me>
*/

#include "global.hpp"

namespace global {

    // The global variables themselves.
    VeryLong      current_bit_count;
    MasterStream  current_word_source;
    ClacStack     current_stack;

    // Accessor functions.
    void set_bit_count( const VeryLong &new_bit_count )
        { current_bit_count = new_bit_count; }

    MasterStream &word_source( )
        { return current_word_source; }

    ClacStack &the_stack( )
        { return current_stack; }

}
