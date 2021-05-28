/*! \file    u_tests.cpp
    \brief   Main unit test driver program for the Clac system.
    \author  Peter C. Chapin <chapinp@acm.org>
*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "u_tests.hpp"
#include "UnitTestManager.hpp"

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

    UnitTestManager::register_test( VeryLong_tests, "VeryLong" );

    UnitTestManager::execute_tests( *output, "Clac Unit Tests" );
    return UnitTestManager::test_status( );
}

