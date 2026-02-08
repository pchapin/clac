
#include <memory>

// From SpicaCpp
#include "UnitTestManager.hpp"

// From Clac
#include "FloatEntity.hpp"

// From Check
#include "u_tests.hpp"

using namespace std;

namespace {

    void constructor_test( )
    {
        UnitTestManager::UnitTest test( "constructor_test" );

        double test_value( 3.14159 );
        unique_ptr<FloatEntity> test_entity1{ new FloatEntity( test_value ) };
        //UNIT_CHECK( test_entity1->get_value( ) == test_value );
        UNIT_CHECK( test_entity1->my_type( ) == FLOAT );
        UNIT_CHECK( test_entity1->display( ) == "3.142" );   // TODO: Exercise display( ) more?

        // Duplicate the entity and make sure the duplicate is correct.
        unique_ptr<Entity> test_entity2{ test_entity1->duplicate( ) };
        UNIT_CHECK( test_entity2->my_type( ) == FLOAT );
        UNIT_CHECK( test_entity2->display( ) == "3.142" );
    }

}


bool FloatEntity_tests( )
{
    constructor_test( );
    // TODO: Exercise the rest of the methods.
    return true;
}
