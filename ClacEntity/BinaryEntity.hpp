/*! \file    BinaryEntity.hpp
 *  \brief   Interface to the clac numeric type BinaryEntity.
 *  \author  Peter Chapin <chapinp@proton.me>
*/

#ifndef BINARYENTITY_HPP
#define BINARYENTITY_HPP

#include <string>
#include "Entity.hpp"

class BinaryEntity : public Entity {
public:
    BinaryEntity( )  { value = 0UL; }
    BinaryEntity( unsigned long number ) { value = number; normalize( ); }

    EntityType my_type( ) const noexcept override;
    std::string display( ) const override;
    Entity *duplicate( ) const override;

    // Unary operations.
    Entity *abs( ) const override;
    Entity *acos( ) const override;
    Entity *asin( ) const override;
    Entity *atan( ) const override;
    Entity *complex_conjugate( ) const override;
    Entity *cos( ) const override;
    Entity *exp( ) const override;
    Entity *exp10( ) const override;
    Entity *fractional_part( ) const override;
    Entity *imaginary_part( ) const override;
    Entity *integer_part( ) const override;
    Entity *inv( ) const override;
    Entity *ln( ) const override;
    Entity *log( ) const override;
    Entity *logical_not( ) const override;
    Entity *neg( ) const override;

    // Binary operations.
    Entity *divide( const Entity * ) const override;
    Entity *logical_and( const Entity * ) const override;
    Entity *logical_or( const Entity * ) const override;
    Entity *logical_xor( const Entity * ) const override;
    Entity *minus( const Entity * ) const override;
    Entity *multiply( const Entity * ) const override;
    Entity *plus( const Entity * ) const override;

    // Conversions.
    Entity *to_binary( ) const override;
    Entity *to_complex( ) const override;
    Entity *to_float( ) const override;
    Entity *to_integer( ) const override;

private:
    unsigned long value;         // The bits themselves.

    void normalize( ) noexcept;  // Function to zero out most significant bits.
};

#endif
