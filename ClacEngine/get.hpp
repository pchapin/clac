/*! \file    get.hpp
 *  \brief   This file contains the declaration of a function that reads entites from the input.
 *  \author  Peter Chapin <chapinp@proton.me>
 */

#ifndef GET_HPP
#define GET_HPP

#include "Entity.hpp"
#include "WordStream.hpp"

/*!
 * This function returns a pointer to a dynamically allocated entity. It extracts words from the
 * given word source, as necessary, to create an appropriate entity. If it encounters an error
 * it returns nullptr.
 */
Entity *get_entity( WordStream &word_source );

#endif
