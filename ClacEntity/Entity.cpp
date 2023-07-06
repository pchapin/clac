/*! \file    Entity.cpp
 *  \brief   Implementation of the abstract base class Entity.
 *  \author  Peter Chapin <spicacality@kelseymountain.org>
 *
 * The functions in this file provide default behavior for the operations that an Entity classes
 * doesn't wish to provide. These functions mostly just produce errors by throwing an
 * appropriate exception.
 */

#include "Entity.hpp"

Entity::~Entity( )
{
    return;
}

//
// Unary operations.
//

Entity *Entity::abs( ) const
{
    throw Error( "Unable to take absolute value of object" );
    return nullptr;
}

Entity *Entity::acos( ) const
{
    throw Error( "Unable to take arccosine of object" );
    return nullptr;
}

Entity *Entity::asin( ) const
{
    throw Error( "Unable to take arcsine of object" );
    return nullptr;
}

Entity *Entity::atan( ) const
{
    throw Error( "Unable to take arctangent of object" );
    return nullptr;
}

Entity *Entity::complex_conjugate( ) const
{
    throw Error( "Unable to take complex conjugate of object" );
    return nullptr;
}

Entity *Entity::cos( ) const
{
    throw Error( "Unable to take cosine of object" );
    return nullptr;
}

Entity *Entity::exp( ) const
{
    throw Error( "Unable to exponentiate object" );
    return nullptr;
}

Entity *Entity::exp10( ) const
{
    throw Error( "Unable to exponentiate object" );
    return nullptr;
}

Entity *Entity::fractional_part( ) const
{
    throw Error( "Object has no fractional part" );
    return nullptr;
}

Entity *Entity::imaginary_part( ) const
{
    throw Error( "Object has no imaginary part" );
    return nullptr;
}

Entity *Entity::integer_part( ) const
{
    throw Error( "Object has no integer part" );
    return nullptr;
}

Entity *Entity::inv( ) const
{
    throw Error( "Unable to invert object" );
    return nullptr;
}

Entity *Entity::ln( ) const
{
    throw Error( "Unable to take natural logarithm of object" );
    return nullptr;
}

Entity *Entity::log( ) const
{
    throw Error( "Unable to take logarithm of object" );
    return nullptr;
}

Entity *Entity::logical_not( ) const
{
    throw Error( "Unable to logically negate object" );
    return nullptr;
}

Entity *Entity::neg( ) const
{
    throw Error( "Unable to negate object" );
    return nullptr;
}

Entity *Entity::real_part( ) const
{
    throw Error( "Object has no real part" );
    return nullptr;
}

Entity *Entity::rotate_left( ) const
{
    throw Error( "Unable to rotate object to the left" );
    return nullptr;
}

Entity *Entity::rotate_right( ) const
{
    throw Error( "Unable to rotate object to the right" );
    return nullptr;
}

Entity *Entity::shift_left( ) const
{
    throw Error( "Unable to shift object to the left" );
    return nullptr;
}

Entity *Entity::shift_right( ) const
{
    throw Error( "Unable to shift object to the right" );
    return nullptr;
}

Entity *Entity::sign( ) const
{
    throw Error( "Unable to find sign of object" );
    return nullptr;
}

Entity *Entity::sin( ) const
{
    throw Error( "Unable to take sine of object" );
    return nullptr;
}

Entity *Entity::sq( ) const
{
    throw Error( "Unable to square object" );
    return nullptr;
}

Entity *Entity::sqrt( ) const
{
    throw Error( "Unable to take square root of object" );
    return nullptr;
}

Entity *Entity::tan( ) const
{
    throw Error( "Unable to take tangent of object" );
    return nullptr;
}

Entity *Entity::transpose( ) const
{
    throw Error( "Unable to transpose object" );
    return nullptr;
}

//
// Conversion Functions.
//

Entity *Entity::to_binary( ) const
{
    throw Error( "Unable to convert object to a binary" );
    return nullptr;
}

Entity *Entity::to_complex( ) const
{
    throw Error( "Unable to convert object to a complex" );
    return nullptr;
}

Entity *Entity::to_directory( ) const
{
    throw Error( "Unable to convert object to a directory" );
    return nullptr;
}

Entity *Entity::to_float( ) const
{
    throw Error( "Unable to convert object to a float" );
    return nullptr;
}

Entity *Entity::to_integer( ) const
{
    throw Error( "Unable to convert object to an integer" );
    return nullptr;
}

Entity *Entity::to_labeled( ) const
{
    throw Error( "Unable to convert object to a labeled object" );
    return nullptr;
}

Entity *Entity::to_list( ) const
{
    throw Error( "Unable to convert object to a list" );
    return nullptr;
}

Entity *Entity::to_matrix( ) const
{
    throw Error( "Unable to convert object to a matrix" );
    return nullptr;
}

Entity *Entity::to_program( ) const
{
    throw Error( "Unable to convert object to a program" );
    return nullptr;
}

Entity *Entity::to_rational( ) const
{
    throw Error( "Unable to convert object to a rational number" );
    return nullptr;
}

Entity *Entity::to_string( ) const
{
    throw Error( "Unable to convert object to a string" );
    return nullptr;
}

Entity *Entity::to_vector( ) const
{
    throw Error( "Unable to convert object to a vector" );
    return nullptr;
}

//
// Binary operations.
//

Entity *Entity::cross( const Entity * ) const
{
    throw Error( "Unable to take cross product of these objects" );
    return nullptr;
}

Entity *Entity::divide( const Entity * ) const
{
    throw Error( "Unable to divide these objects" );
    return nullptr;
}

Entity *Entity::dot( const Entity * ) const
{
    throw Error( "Unable to take dot product of these objects" );
    return nullptr;
}

Entity *Entity::logical_and( const Entity * ) const
{
    throw Error( "Unable to logically AND these objects" );
    return nullptr;
}

Entity *Entity::logical_or( const Entity * ) const
{
    throw Error( "Unable to logically OR these objects" );
    return nullptr;
}

Entity *Entity::logical_xor( const Entity * ) const
{
    throw Error( "Unable to logically exclusive OR these objects" );
    return nullptr;
}

Entity *Entity::minus( const Entity * ) const
{
    throw Error( "Unable to subtract these objects" );
    return nullptr;
}

Entity *Entity::modulo( const Entity * ) const
{
    throw Error( "Unable to modulo these objects" );
    return nullptr;
}

Entity *Entity::multiply( const Entity * ) const
{
    throw Error( "Unable to multiply these objects" );
    return nullptr;
}

Entity *Entity::plus( const Entity * ) const
{
    throw Error( "Unable to add these objects" );
    return nullptr;
}

Entity *Entity::power( const Entity * ) const
{
    throw Error( "Unable to exponentiate these objects" );
    return nullptr;
}

//
// Relational operations.
//

Entity *Entity::is_equal( const Entity * ) const
{
    throw Error( "Unable to compare these objects" );
    return nullptr;
}

Entity *Entity::is_notequal( const Entity * ) const
{
    throw Error( "Unable to compare these objects" );
    return nullptr;
}

Entity *Entity::is_less( const Entity * ) const
{
    throw Error( "Unable to compare these objects" );
    return nullptr;
}

Entity *Entity::is_lessorequal( const Entity * ) const
{
    throw Error( "Unable to compare these objects" );
    return nullptr;
}

Entity *Entity::is_greater( const Entity * ) const
{
    throw Error( "Unable to compare these objects" );
    return nullptr;
}

Entity *Entity::is_greaterorequal( const Entity * ) const
{
    throw Error( "Unable to compare these objects" );
    return nullptr;
}

//
// File operations.
//

// This should be made abstract eventually. Doing so now will cause problems for Entity classes
// that have not yet gotten around to implementing it.
//
long Entity::file_size( ) const noexcept
{
    return 0;
}

void Entity::write( std::ofstream & ) const
{
    throw Error( "Unable to write object to a file" );
}

// This function is static and will eventually have to be fleshed out (and probably moved to a
// different file in order to handle all the entity types.
//
Entity *Entity::read( std::ifstream & )
{
    throw Error( "Unable to read files" );
    return nullptr;
}
