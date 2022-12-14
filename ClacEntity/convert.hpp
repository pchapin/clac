/*! \file    convert.hpp
 *  \brief   Interface to the entity conversion table.
 *  \author  Peter Chapin <chapinp@proton.me>
 */

#ifndef CONVERT_HPP
#define CONVERT_HPP

#include "Entity.hpp"

const int type_count = 12;

extern Entity *( Entity::*convert_table[type_count][type_count] )( ) const;

#endif
