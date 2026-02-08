/*! \file    u_tests.cpp
 *  \brief   Main unit test driver program for the Clac system.
 *  \author  Peter Chapin <spicacality@kelseymountain.org>
 */

#include <cstdarg>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "u_tests.hpp"
#include "UnitTestManager.hpp"

using namespace std;

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

    va_start( ap, message );
    char message_buffer[128 + 1];
    vsnprintf( message_buffer, 128 + 1, message, ap );
    cout << message_buffer << endl;
}

/*!
 * This function is used to print information messages to the UI. Unlike the error message
 * function, it assumes the caller constructs the entire message. This choice was made on the
 * assumption that informational messages wouldn't normally need to print data values. That
 * assumption may need to be revisted at some point.
 *
 * As with error_message, any code that makes use of Clac entities must provide an
 * implementation of this function that is application specific.
 */
void info_message( const string &message )
{
    cout << message << endl;
}

int main( int argc, char **argv )
{
    std::ostream *output = &std::cout;
    std::ofstream output_file;

    if( argc == 2 ) {
        output_file.open( argv[1] );
        if( !output_file ) {
            std::cerr << "Unable to open " << argv[1] << " for output!\n";
            return EXIT_FAILURE;
        }
        output = &output_file;
    }

    UnitTestManager::register_suite( IntegerEntity_tests, "IntegerEntity" );
    UnitTestManager::register_suite( FloatEntity_tests,   "FloatEntity"   );

    UnitTestManager::execute_suites( *output, "Clac Unit Tests" );
    return UnitTestManager::test_status( );
}

