/*! \file    clac.cpp
 *  \brief   Clac main program.
 *  \author  Peter Chapin <chapinp@proton.me> and Peter Nikolaidis
 */

#include <cstdarg>
#include <cstdlib>
#include <cstring>
#include <iostream>

// Scr library.
#include "debug.hpp"
#include "MessageWindow.hpp"
#include "scr.hpp"

// ClacEngine library.
#include "Global.hpp"

#include "ClacCommandWindow.hpp"
#include "DirectoryWindow.hpp"
#include "StackWindow.hpp"

using namespace std;

namespace {

    //! Adjusts the format of __DATE__.
    /*!
     * This function puts a comma after the day of the month and purges leading zeros or spaces
     * from the day of the month.
     *
     * \param standard_date The date in the format given by the __DATE__ macros.
     * \return A pointer to a statically allocated buffer (of size 13) holding the cleaned up
     * date.
     */
    char *adjust_date(const char *standard_date)
    {
        static char  buffer[13];
            char *buffer_pointer;

        // Make a working copy of the date as from the ANSI __DATE__ macro.
        strcpy( buffer, standard_date );

        // Open up space for the comma.
        for( buffer_pointer  = strchr( buffer, '\0' );
            buffer_pointer >= &buffer[6];
            buffer_pointer-- ) {
            *(buffer_pointer+1) = *buffer_pointer;
        }

        // Put the comma in.
        buffer[6] = ',';

        // If this is a date from 1 to 9, close up the extra space.
        if( buffer[4] == '0' || buffer[4] == ' ' ) {
            for( buffer_pointer = &buffer[4]; *buffer_pointer; buffer_pointer++ ) {
                *buffer_pointer = *( buffer_pointer + 1 );
            }
        }

        // Return are result.
        return buffer;
    }


    // These message descriptors define the appearance of the various kinds of message windows.
    scr::MessageWindowDescriptor message_descriptors[] = {
        // For scr::MESSAGE_WINDOW_MESSAGE
        { scr::WHITE, scr::SINGLE_LINE, scr::WHITE, NULL, scr::WHITE, scr::MESSAGE_WINDOW_ANY },

        // For scr::MESSAGE_WINDOW_PROMPT
        { scr::WHITE, scr::SINGLE_LINE, scr::WHITE, NULL, scr::WHITE, scr::MESSAGE_WINDOW_ANY },

        // For scr::MESSAGE_WINDOW_WARNING
        { scr::WHITE, scr::SINGLE_LINE, scr::WHITE, NULL, scr::WHITE, scr::MESSAGE_WINDOW_ANY },

        // For scr::MESSAGE_WINDOW_ERROR
        { scr::WHITE, scr::SINGLE_LINE, scr::WHITE, NULL, scr::WHITE, scr::MESSAGE_WINDOW_ANY },

        // For scr::MESSAGE_WINDOW_INT_ERROR
        { scr::WHITE, scr::SINGLE_LINE, scr::WHITE, NULL, scr::WHITE, scr::MESSAGE_WINDOW_ANY }
    };


    //! Class to perform setup and teardown operations.
    /*!
     * Only one instance of this class should be created. The constructor initializes the
     * underlying screen handling library, and the destructor shuts that library down. The point
     * of this class is to treat the screen as a resource that is managed by the RAI idiom. If
     * an exception is thrown that propagates to main, the destructor will still be called and
     * the screen will be shut down properly.
     */
    class SetUp {
    public:
        SetUp( bool use_debugger );
       ~SetUp( );
    private:
        bool debugging_on;
    };


    SetUp::SetUp( bool use_debugger ) : debugging_on( false )
    {
        // TODO: Reload the calculator state (if there's a saved one to be found).

        scr::initialize( );
        scr::refresh_on_key( true );
        scr::MessageWindow::set_descriptors( message_descriptors );

        // One problem with initializing debugging here is that if an exception is thrown
        // immediately (i.e., the user issues the "quit" command), the destructor of this class
        // doesn't run and the screen is left in a messy state. I don't think this will be an
        // issue in practice. If the debugging user moves to a breakpoint, this constructor will
        // have fully completed and the destructor will do its job.
        // TODO: Fix the problem described above.
        if( use_debugger ) {
            scr::initialize_debugging( DBG_TOP );
            debugging_on = true;
        }
    }


    SetUp::~SetUp( )
    {
        if( debugging_on ) {
            scr::terminate_debugging( );
        }
        scr::terminate( );

        // TODO: Save the calculator state.
        cout << "CLAC Version 0.10a  Compiled: " << adjust_date( __DATE__ ) << '\n'
            << "(C) Copyright 2023 by Peter Chapin and Peter Nikolaidis" << endl;
    }
}


//=====================================
//           Message Handling
//=====================================

//! Displays an error message.
/*!
 * This function is the master error message handler for all components of Clac. It is actually
 * declared in a low level header (support.hpp) in the Clac entity library. Any code that uses
 * Clac entities must provide an implementation of this function that is application specific.
 */
void error_message( const char *message, ... )
{
    va_list ap;
    char message_buffer[128 + 1];

    va_start( ap, message );    
    vsnprintf( message_buffer, 128 + 1, message, ap );
    scr::MessageWindow( message_buffer, scr::MESSAGE_WINDOW_ERROR );
}

/*!
 * This function is used to print information messages to the UI. Unlike the error message
 * function, it assumes the caller constructs the entire message. This choice was made on the
 * assumption that informational messages wouldn't normally need to print data values. That
 * assumption may need to be revisted at some point.
 *
 * As with `error_message`, any code that makes use of Clac entities must provide an
 * implementation of this function that is application specific.
 */
void info_message( const string &message )
{
    scr::MessageWindow( message.c_str( ), scr::MESSAGE_WINDOW_MESSAGE );
}


//==================================
//           Main Program
//==================================

int Main( int argc, char **argv )
{
    // The value of 'use_debugger' selects if the runtime debugging environment is active.
    bool use_debugger = false;

    // Command line analysis. Note that the windowing system is not yet running.
    // TODO: Improve and generalize the handling of the command line.
    for( int i = 1; i < argc; ++i ) {
        if( strcmp( argv[i], "-d" ) == 0 ) use_debugger = true;
    }

    // Initialize the program and start the windowing system.
    SetUp the_program( use_debugger );
    const int screen_rows = scr::number_of_rows( );
    const int screen_cols = scr::number_of_columns( );
    const int half_width  = screen_cols / 2;

    // Create the window manager.
    scr::Manager window_manager;

    // Create the windows in their initial positions and register them with the window manager.
    StackWindow stack_view(
        window_manager,  2,  2, half_width - 2, screen_rows - 5 );

    DirectoryWindow directory_view(
        window_manager,  2, half_width + 2, half_width - 2, screen_rows - 5 );

    ClacCommandWindow command_view(
        &window_manager, screen_rows - 1,  2, screen_cols - 2,  1 );

    // Initialize windows (the directory window is currently not implemented).
    stack_view.associate( &Global::the_stack( ) );
    command_view.set_prompt( "=> " );

    window_manager.input_loop( );

    // Clac always "succeeds" unless there is an unhandled exception (see below).
    return EXIT_SUCCESS;
}


//===================================
//           The Real Main
//===================================

int main( int argc, char **argv )
{
    // Set the default exit status in case an unhandled exception propagates through main.
    int return_value = EXIT_FAILURE;

    try {
        return_value = Main( argc, argv );
    }
    catch (...) {
        cerr << "\nPanic! Unhandled exception propagated through main()" << endl;
    }
    return return_value;
}
