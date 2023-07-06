/*! \file    ClacCommandWindow.hpp
 *  \brief   Definition of the ClacCommandWindow class.
 *  \author  Peter Chapin <spicacality@kelseymountain.org>
 */

#ifndef CLACCOMMANDWINDOW_H
#define CLACCOMMANDWINDOW_H

#include "CommandWindow.hpp"

class ClacCommandWindow : public scr::CommandWindow {
public:
    ClacCommandWindow( scr::Manager *my_manager, int row, int column, int width, int height ) :
      scr::CommandWindow( my_manager, row, column, width, height )
      { }

    //! Process Clac commands.
    /*!
     * Normal keystrokes are passed to `scr::CommandWindow` for handling. When a K_RETURN is
     * seen, this method executes the given command string and does not return until all
     * processing is complete.
     */
    bool process_keystroke( int &key_code ) override;
};

#endif
