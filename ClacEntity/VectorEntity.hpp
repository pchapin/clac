/*! \file    VectorEntity.hpp
 *  \brief   Interface to the clac numeric type VectorEntity.
 *  \author  Peter Chapin <chapinp@proton.me>
 */

#ifndef VECTORENTITY_HPP
#define VECTORENTITY_HPP

#include <string>
#include <vector>
#include "Entity.hpp"

class VectorEntity : public Entity {
public:
    virtual ~VectorEntity( );
    
    EntityType  my_type( )   const noexcept override;
    std::string display( )   const override;
    Entity     *duplicate( ) const override;

private:
    std::vector<Entity *> value;
};

#endif
