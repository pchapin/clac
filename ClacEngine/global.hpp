/*! \file    global.hpp
 *  \brief   This file contains the interface to clac's global state.
 *  \author  Peter Chapin <chapinp@proton.me>
 */

#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include "VeryLong.hpp"

#include "ClacStack.hpp"
#include "WordStream.hpp"

namespace global {

    void set_bit_count( const VeryLong &new_bit_count );

    MasterStream &word_source( );
    ClacStack    &the_stack( );
}

#endif
