/*! \file    ListEntity.cpp
 *  \brief   Implementation of the Clac numeric type ListEntity.
 *  \author  Peter Chapin <spicacality@kelseymountain.org>
 */

#include <memory>
#include "Entities.hpp"

using namespace std;

ListEntity::~ListEntity( )
{
    list<Entity *>::iterator p;
    for( p = value.begin( ); p != value.end( ); ++p ) {
        delete *p;
    }
}

EntityType ListEntity::my_type( ) const noexcept
{
    return LIST;
}

string ListEntity::display( ) const
{
    string workspace = "{ ";
    list<Entity *>::const_iterator p;

    for( p = value.begin( ); p != value.end( ); ++p ) {
        workspace.append( ( *p )->display( ) );
        workspace.append( " " );
    }

    workspace.append( "}" );
    return workspace;
}


Entity *ListEntity::duplicate( ) const
{
    list<Entity *> new_value;
    list<Entity *>::const_iterator p;

    for( p = value.begin( ); p != value.end( ); ++p ) {

        // If (*p)->duplicate() throws, new_value will be destroyed but the already duplicated
        // objects won't be. This must be fixed eventually.
        //
        new_value.push_back( ( *p )->duplicate( ) );
    }

    // This involves copying the list (of pointers) which is time consuming. There is also a
    // problem here if creating the new ListEntity throws.
    //
    return new ListEntity( new_value );
}


Entity *ListEntity::plus( const Entity *R ) const
{
    const ListEntity *right = dynamic_cast< const ListEntity * >( R );
    list<Entity *>::const_iterator p;

    unique_ptr<ListEntity> new_list( new ListEntity( value ) );
    for( p = right->value.begin( ); p != right->value.end( ); ++p ) {
        new_list->value.push_back( *p );
    }

    return new_list.release( );
}
