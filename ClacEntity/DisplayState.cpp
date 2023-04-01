/*! \file    DisplayState.cpp
 *  \brief   Implementation of clac's display state variables.
 *  \author  Peter Chapin <chapinp@proton.me>
 */

#include "DisplayState.hpp"

namespace {

    // Definitions of display state variables, with initial defaults.
    DisplayState::AngleModeType   angle_mode    = DisplayState::DEG;
    DisplayState::BaseType        bit_base      = DisplayState::HEX;
    DisplayState::ComplexModeType complex_mode  = DisplayState::RECTANGULAR;
    int                           decimal_count = 3;
    DisplayState::FloatModeType   display_mode  = DisplayState::FIXED;

}


namespace DisplayState {

    // Setters
    // -------

    void set_angle_mode( AngleModeType new_mode )     noexcept { angle_mode = new_mode;   }
    void set_base( BaseType new_base )                noexcept { bit_base = new_base;     }
    void set_complex_mode( ComplexModeType new_mode ) noexcept { complex_mode = new_mode; }
    void set_decimal_count( int number )              noexcept { decimal_count = number;  }
    void set_display_mode( FloatModeType new_mode )   noexcept { display_mode = new_mode; }


    // Getters
    // -------

    AngleModeType   get_angle_mode( )    noexcept { return angle_mode;    }
    BaseType        get_base( )          noexcept { return bit_base;      }
    ComplexModeType get_complex_mode( )  noexcept { return complex_mode;  }
    int             get_decimal_count( ) noexcept { return decimal_count; }
    FloatModeType   get_display_mode( )  noexcept { return display_mode;  }

}