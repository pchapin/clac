/*! \file    ClacCommandWindow.cpp
 *  \brief   Implementation of the ClacCommandWindow class.
 *  \author  Peter Chapin <chapinp@proton.me>
 */

#include "ClacCommandWindow.hpp"
#include "Global.hpp"
#include "WordStream.hpp"

// TODO: Fix this hack. [Move process_words and all associated code to this file?]
extern bool process_words( );

bool ClacCommandWindow::process_keystroke( int &key_code )
{
    // If the user hasn't hit Enter, they is editing the command.
    if( key_code != scr::K_RETURN )
        return scr::CommandWindow::process_keystroke( key_code );

    // Push the command text onto the master stream as a string of Clac command words.
    StringStream *words = new StringStream( command_text );
    Global::word_source( ).push( words );
    if( process_words( ) == false ) {
        key_code = scr::K_ESC;
        return false;
    }

    // Prepare the command window for another command line.
    command_text.erase( );
    cursor_offset = 0;
    return true;
}
