/*! \file    ProgramEntity.hpp
 *  \brief   Interface to the clac numeric type ProgramEntity.
 *  \author  Peter Chapin <chapinp@proton.me>
 */

#ifndef PROGRAMENTITY_HPP
#define PROGRAMENTITY_HPP

#include <string>
#include "Entity.hpp"

class ProgramEntity : public Entity {
public:
    ProgramEntity( const std::string &program ) : value( program )
      { }

    EntityType  my_type( )   const noexcept override;
    std::string display( )   const override;
    Entity     *duplicate( ) const override;

private:
    std::string value;
};

#endif
