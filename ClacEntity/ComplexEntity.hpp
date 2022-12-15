/*! \file    ComplexEntity.hpp
 *  \brief   Interface to the clac numeric type ComplexEntity.
 *  \author  Peter Chapin <chapinp@proton.me>
 */

#ifndef COMPLEXENTITY_HPP
#define COMPLEXENTITY_HPP

#include <complex>
#include "Entity.hpp"

class ComplexEntity : public Entity {
public:

    // For building a ComplexEntity from its primitives.
    ComplexEntity( const std::complex< double > &number ) noexcept : value( number ) { }
    ComplexEntity( double real_part, double imaginary_part = 0.0) :
      value( real_part, imaginary_part ) { }

    // Functions for maintaining a member of the Entity family.
    EntityType my_type( ) const noexcept override;
    std::string display( ) const override;
    Entity *duplicate( ) const override;

    // Unary operations.
    Entity *abs( )               const override;
    Entity *complex_conjugate( ) const override;
    Entity *cos( )               const override;
    Entity *exp( )               const override;
    Entity *exp10( )             const override;
    Entity *imaginary_part( )    const override;
    Entity *inv( )               const override;
    Entity *ln( )                const override;
    Entity *log( )               const override;
    Entity *neg( )               const override;
    Entity *real_part( )         const override;
    Entity *sign( )              const override;
    Entity *sin( )               const override;
    Entity *sqrt( )              const override;
    Entity *tan( )               const override;

    // Conversion functions.
    Entity *to_complex( ) const;

    // Binary operations.
    Entity *divide   ( const Entity * ) const override;
    Entity *minus    ( const Entity * ) const override;
    Entity *multiply ( const Entity * ) const override;
    Entity *plus     ( const Entity * ) const override;
    Entity *power    ( const Entity * ) const override;

private:
    std::complex<double> value;
};

#endif
