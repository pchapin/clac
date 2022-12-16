/*! \file    LabeledEntity.hpp
 *  \brief   Interface to the clac numeric type LabeledEntity.
 *  \author  Peter Chapin <chapinp@proton.me>
 */

#ifndef LABELEDENTITY_HPP
#define LABELEDENTITY_HPP

#include <string>
#include "Entity.hpp"

class LabeledEntity : public Entity {
public:
    LabeledEntity( Entity *thing, const std::string &name ) :
      object( thing ), label( name ) {}

    virtual ~LabeledEntity( ) { delete object; }

    EntityType  my_type( )   const noexcept override;
    std::string display( )   const override;
    Entity     *duplicate( ) const override;

private:
    Entity     *object;
    std::string label;
};

#endif
