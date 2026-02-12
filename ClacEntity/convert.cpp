/*! \file    convert.cpp
 *  \brief   Type conversion functions.
 *  \author  Peter Chapin <spicacality@kelseymountain.org>
 */

#include <cmath>

#include "convert.hpp"
#include "Entities.hpp"

using namespace std;

//
// The follow array defines the automatic conversions done when operands of differing types meet
// in a binary expression. This array must be symmetric about the diagonal.
//
//
// FINISH ME! (When all the necessary conversion functions are defined).
#define E &Entity

namespace clac::entity {
    Entity *( Entity::*convert_table[type_count][type_count] )( ) const = {
        //           Bin            Cpx            Dir      Flt            Int            Lbl      Lst      Mat      Prg      Rat             Str           Vec
        /* Bin */  { E::to_binary,  E::to_complex, nullptr, E::to_float,   E::to_integer, nullptr, nullptr, nullptr, nullptr, nullptr,        nullptr,      nullptr },
        /* Cpx */  { E::to_complex, E::to_complex, nullptr, E::to_complex, nullptr,       nullptr, nullptr, nullptr, nullptr, nullptr,        nullptr,      nullptr },
        /* Dir */  { nullptr,       nullptr,       nullptr, nullptr,       nullptr,       nullptr, nullptr, nullptr, nullptr, nullptr,        nullptr,      nullptr },
        /* Flt */  { E::to_float,   E::to_complex, nullptr, E::to_float,   E::to_float,   nullptr, nullptr, nullptr, nullptr, E::to_float,    nullptr,      nullptr },
        /* Int */  { E::to_integer, nullptr,       nullptr, E::to_float,   E::to_integer, nullptr, nullptr, nullptr, nullptr, nullptr,        nullptr,      nullptr },
        /* Lbl */  { nullptr,       nullptr,       nullptr, nullptr,       nullptr,       nullptr, nullptr, nullptr, nullptr, nullptr,        nullptr,      nullptr },
        /* Lst */  { nullptr,       nullptr,       nullptr, nullptr,       nullptr,       nullptr, nullptr, nullptr, nullptr, nullptr,        nullptr,      nullptr },
        /* Mat */  { nullptr,       nullptr,       nullptr, nullptr,       nullptr,       nullptr, nullptr, nullptr, nullptr, nullptr,        nullptr,      nullptr },
        /* Prg */  { nullptr,       nullptr,       nullptr, nullptr,       nullptr,       nullptr, nullptr, nullptr, nullptr, nullptr,        nullptr,      nullptr },
        /* Rat */  { nullptr,       nullptr,       nullptr, E::to_float,   nullptr,       nullptr, nullptr, nullptr, nullptr, E::to_rational, nullptr,      nullptr },
        /* Str */  { nullptr,       nullptr,       nullptr, nullptr,       nullptr,       nullptr, nullptr, nullptr, nullptr, nullptr,        E::to_string, nullptr },
        /* Vec */  { nullptr,       nullptr,       nullptr, nullptr,       nullptr,       nullptr, nullptr, nullptr, nullptr, nullptr,        nullptr,      nullptr }
    };
}
