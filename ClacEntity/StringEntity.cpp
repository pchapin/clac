/*! \file    StringEntity.cpp
 *  \brief   Implementation of the Clac numeric type StringEntity.
 *  \author  Peter Chapin <spicacality@kelseymountain.org>
 */

#include "Entities.hpp"

using namespace std;

EntityType StringEntity::my_type( ) const noexcept
{
    return STRING;
}


string StringEntity::display( ) const
{
    return value;
}


Entity *StringEntity::duplicate( ) const
{
    return new StringEntity( value );
}


Entity *StringEntity::plus( const Entity *R ) const
{
    const StringEntity *right = dynamic_cast<const StringEntity *>( R );
    return new StringEntity( value + right->value );
}


//
// Conversions from StringEntity
//

Entity *StringEntity::to_string( ) const
{
    return duplicate( );
}
