/*! \file    StringEntity.hpp
 *  \brief   Interface to the clac numeric type StringEntity.
 *  \author  Peter Chapin <chapinp@proton.me>
 */

#ifndef STRINGENTITY_HPP
#define STRINGENTITY_HPP

#include <string>
#include "Entity.hpp"

class StringEntity : public Entity {
public:
    StringEntity( ) { }
    StringEntity( const std::string &incoming ) : value( incoming ) { }

    // It might be nice to do without this at some point.
    std::string get_value( )
      { return value; }

    EntityType  my_type( )   const noexcept override;
    std::string display( )   const override;
    Entity     *duplicate( ) const override;

    // Conversion functions.
    Entity *to_string( ) const override;

    // Binary operations.
    Entity *plus( const Entity * ) const override;

private:
    std::string value;
};

#endif
