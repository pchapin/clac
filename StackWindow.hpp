/*! \file    StackWindow.hpp
 *  \brief   Definition of the StackWindow class.
 *  \author  Peter Chapin <chapinp@proton.me>
 *
 * Objects of this class manage the display of a Stack object.
 */

#ifndef STACKWINDOW_HPP
#define STACKWINDOW_HPP

// The Scr library.
#include "ImageBuffer.hpp"
#include "Manager.hpp"
#include "Window.hpp"

#include "ClacStack.hpp"

class StackWindow : public scr::Window {
public:
    // Be sure there is no association initially.
    StackWindow( scr::Manager &M, int R, int C, int W, int H ) :
        scr::Window( &M, R, C, W, H ), the_stack( nullptr )
        { }

    // Associate this window with a stack object.
    void associate( ClacStack *object )
        { the_stack = object; }

    virtual scr::ImageBuffer *get_image( ) override;

private:
    ClacStack *the_stack;
};

#endif
