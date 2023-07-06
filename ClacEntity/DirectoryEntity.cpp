/*! \file    DirectoryEntity.cpp
 *  \brief   Implementation of the Clac numeric type DirectoryEntity.
 *  \author  Peter Chapin <spicacality@kelseymountain.org>
 */

#include "Entities.hpp"

using namespace std;

DirectoryEntity::DirectoryEntity( const map< string, Entity * > &existing )
{
    map<string, Entity *>::const_iterator p;

    try {
        for( p = existing.begin( ); p != existing.end( ); ++p ) {
            Entity *dup = p->second->duplicate( );
            value[p->first] = dup;
        }
    }
    catch( ... ) {
        for( p = value.begin( ); p != value.end( ); ++p ) {
            delete p->second;
        }
        throw;
    }
}

DirectoryEntity::~DirectoryEntity( )
{
    map<string, Entity *>::iterator p;
    
    for( p = value.begin( ); p != value.end( ); ++p ) {
        delete p->second;
    }
}

EntityType DirectoryEntity::my_type( ) const noexcept
{
    return DIRECTORY;
}

string DirectoryEntity::display( ) const
{
    return "DirectoryEntity::display( ) not implemented!";
}

Entity *DirectoryEntity::duplicate( ) const
{
    return new DirectoryEntity( value );
}
