/*! \file    DisplayState.hpp
 *  \brief   Interface to clac's display state variables.
 *  \author  Peter Chapin <chapinp@proton.me>
 *
 * Namespace DisplayState is a wrapper around all of clac's display state variables. Such
 * variables specify how certain objects are to be displayed. Having all the display state
 * variables in one place like this makes it easier to keep track of them.
 *
 * This namespace manages access to the display state variables and forces them to be referred
 * to using only the provided getters and setters. This helps to organize them. 
 */

#ifndef DISPLAYSTATE_HPP
#define DISPLAYSTATE_HPP

namespace DisplayState {

    // The following types define the legal values for certain objects below.
    enum AngleModeType   { RAD, DEG, GRAD };
    enum BaseType        { DECIMAL, BINARY, HEX, OCTAL };
    enum ComplexModeType { RECTANGULAR, POLAR };
    enum FloatModeType   { FIXED, SCIENTIFIC, ENGINEERING };

    // The following methods allow access to the display state variables.
    AngleModeType   get_angle_mode( )    noexcept;
    BaseType        get_base( )          noexcept;
    ComplexModeType get_complex_mode( )  noexcept;
    int             get_decimal_count( ) noexcept;
    FloatModeType   get_display_mode( )  noexcept;

    // The following methods allow modifications to the display state variables.
    void set_angle_mode    (AngleModeType   new_mode ) noexcept;
    void set_base          (BaseType        new_base ) noexcept;
    void set_complex_mode  (ComplexModeType new_mode ) noexcept;
    void set_decimal_count (int             number   ) noexcept;
    void set_display_mode  (FloatModeType   new_mode ) noexcept;
}

#endif
