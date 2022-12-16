/*! \file    VectorEntity.cpp
 *  \brief   Implementation of the clac numeric type VectorEntity.
 *  \author  Peter Chapin <chapinp@proton.me>
 */

#include "Entities.hpp"

using namespace std;

VectorEntity::~VectorEntity( )
{
    vector<Entity *>::iterator p;

    for( p = value.begin( ); p != value.end( ); ++p ) {
        delete *p;
    }
}

EntityType VectorEntity::my_type( ) const noexcept
{
    return VECTOR;
}


string VectorEntity::display( ) const
{
    return "VectorEntity::display( ) not implemented!";
}


Entity *VectorEntity::duplicate( ) const
{
    throw Error("VectorEntity::duplicate( ) not implemented!");
}

