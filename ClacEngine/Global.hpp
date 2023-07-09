/*! \file    Global.hpp
 *  \brief   This file contains the interface to clac's global state.
 *  \author  Peter Chapin <spicacality@kelseymountain.org>
 */

#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include "VeryLong.hpp"

#include "ClacStack.hpp"
#include "WordStream.hpp"

namespace Global {

    void set_bit_count( const spica::VeryLong &new_bit_count );

    MasterStream &word_source( );
    ClacStack    &the_stack( );
}

#endif
