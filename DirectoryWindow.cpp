/*! \file    DirectoryWindow.cpp
 *  \brief   Implementation of the DirectoryWindow class.
 *  \author  Peter Chapin <chapinp@proton.me>
 */

#include <cstdio>

// The Scr library
#include "scr.hpp"

#include "LabeledEntity.hpp"
#include "DirectoryWindow.hpp"

using namespace std;

scr::ImageBuffer *DirectoryWindow::get_image( )
{
    // TODO: Implement me.
    image.clear( );
    image.copy( "DirectoryWindow::get_image not implemented",
                1,
                1,
                image.get_width( ),
                scr::WHITE );
    return &image;
}
