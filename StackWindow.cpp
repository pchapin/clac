/*! \file    StackWindow.cpp
 *  \brief   Implementation of the StackWindow class.
 *  \author  Peter Chapin <spicacality@kelseymountain.org>
 */

#include <cstdio>
#include <cstdlib>
#include <map>
#include <sstream>

// The Scr library.
#include "scr.hpp"

#include "Entity.hpp"
#include "StackWindow.hpp"

using namespace std;

namespace {
 
    // Map entity types to names for the UI.
    map<EntityType, string> type_abbreviation = {
        { BINARY,  "BIN" }, { COMPLEX,  "CPX" }, { DIRECTORY, "DIR" }, { FLOAT,  "FLT" },
        { INTEGER, "INT" }, { LABELED,  "LBL" }, { LIST,      "LST" }, { MATRIX, "MAT" },
        { PROGRAM, "PGM" }, { RATIONAL, "RAT" }, { STRING,    "STR" }, { VECTOR, "VEC" }
    };

}


scr::ImageBuffer *StackWindow::get_image( )
{
    char number_buffer[16];

    image.clear( );
    for( int i = 0; i < image.get_height( ); ++i ) {
        int item_number = image.get_height( ) - (i + 1);

        // Get the right stack level number and print it into the window.
        int count = snprintf( number_buffer, 16, "%2d: ", item_number );
        image.copy( number_buffer, i + 1, 1, image.get_width( ), scr::WHITE );

        Entity *thing = the_stack->get( item_number );

        // If the object exists, print it in the window.
        stringstream formatter;
        if( thing == nullptr ) {
            formatter << "--- : ";
        }
        else {
            formatter << type_abbreviation[thing->my_type( )] << " : " << thing->display( );
        }
        image.copy( formatter.str( ).c_str( ),
                    i + 1,
                    count + 1,
                    image.get_width( ) - count,
                    scr::WHITE );
    }
    return &image;
}
