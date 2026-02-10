/*! \file    support.hpp
 *  \brief   Declarations of various support functions.
 *  \author  Peter Chapin <spicacality@kelseymountain.org>
 */

#ifndef SUPPORT_HPP
#define SUPPORT_HPP

#include "Entity.hpp"
#include <string>

void error_message(const char*, ...);
void info_message(const std::string& message);
void underflow();
Entity* type_mismatch(Entity*);
Entity* type_mismatch(Entity*, Entity*);

double to_radians(double) noexcept;
double from_radians(double) noexcept;

// These functions are not standard, but they are common. We are implementing them ourselves to
// ensure they are available.
//
int stricmp(char*, char*) noexcept;

#endif
