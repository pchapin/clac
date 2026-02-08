
#include <memory>

// From SpicaCpp
#include "VeryLong.hpp"
#include "UnitTestManager.hpp"

// From Clac
#include "IntegerEntity.hpp"

// From Check
#include "u_tests.hpp"

using namespace std;

namespace {

    void constructor_test( )
    {
        UnitTestManager::UnitTest test( "constructor_test" );

        spica::VeryLong test_value( 1234567890 );
        unique_ptr<IntegerEntity> test_entity1{ new IntegerEntity( test_value ) };
        UNIT_CHECK( test_entity1->get_value( ) == test_value );
        UNIT_CHECK( test_entity1->my_type( ) == INTEGER );
        UNIT_CHECK( test_entity1->display( ) == "1234567890" );   // TODO: Exercise display( ) more?

        // Duplicate the entity and make sure the duplicate is correct.
        unique_ptr<Entity> test_entity2{ test_entity1->duplicate( ) };
        UNIT_CHECK( test_entity2->my_type( ) == INTEGER );
        UNIT_CHECK( test_entity2->display( ) == "1234567890" );
    }

}


bool IntegerEntity_tests( )
{
    constructor_test( );
    // TODO: Exercise the rest of the methods.
    return true;
}
