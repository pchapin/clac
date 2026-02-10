/*! \file    support.cpp
 *  \brief   Definitions of various support functions.
 *  \author  Peter Chapin <spicacality@kelseymountain.org>
 */

#include <cctype>
#include <numbers>

#include "DisplayState.hpp"
#include "support.hpp"

using namespace std;

void underflow()
{
    throw "Stack Underflow";
}

Entity* type_mismatch(Entity*)
{
    error_message("Type Mismatch");
    return 0;
}

Entity* type_mismatch(Entity*, Entity*)
{
    error_message("Type Mismatch");
    return 0;
}

double to_radians(double number) noexcept
{
    switch (DisplayState::get_angle_mode()) {

    case DisplayState::DEG:
        return number * numbers::pi / 180.0;

    case DisplayState::RAD:
        return number;

    case DisplayState::GRAD:
        return number * numbers::pi / 200.0;
    }
    return number;
}

double from_radians(double number) noexcept
{
    switch (DisplayState::get_angle_mode()) {

    case DisplayState::DEG:
        return (number / numbers::pi) * 180.0;

    case DisplayState::RAD:
        return number;

    case DisplayState::GRAD:
        return (number / numbers::pi) * 200.0;
    }
    return number;
}

int stricmp(char* A, char* B) noexcept
{
    while (*A && *B) {
        if (toupper(*A) != toupper(*B))
            return 1;
        A++;
        B++;
    }
    if (*A == '\0' && *B == '\0')
        return 0;
    return 1;
}
