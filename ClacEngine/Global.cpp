/*! \file    Global.cpp
 *  \brief   This file contains the implementation of clac's global state.
 *  \author  Peter Chapin <spicacality@kelseymountain.org>
 */

#include "Global.hpp"

using namespace spica; // TODO: Remove this using directive.

namespace clac::global {

    // The global variables themselves.
    VeryLong current_bit_count;
    engine::MasterStream current_word_source;
    engine::ClacStack current_stack;

    // Accessor functions.
    void set_bit_count(const VeryLong& new_bit_count)
    {
        current_bit_count = new_bit_count;
    }

    engine::MasterStream& word_source()
    {
        return current_word_source;
    }

    engine::ClacStack& the_stack()
    {
        return current_stack;
    }

} // namespace global
