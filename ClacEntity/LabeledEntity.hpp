/*! \file    LabeledEntity.hpp
 *  \brief   Interface to the Clac numeric type LabeledEntity.
 *  \author  Peter Chapin <spicacality@kelseymountain.org>
 */

#ifndef LABELEDENTITY_HPP
#define LABELEDENTITY_HPP

#include <string>
#include "Entity.hpp"

class LabeledEntity : public Entity {
public:
    LabeledEntity( Entity *thing, const std::string &name ) :
      object( thing ), label( name ) {}
    LabeledEntity( const LabeledEntity & ) = delete;
    LabeledEntity &operator=( const LabeledEntity & ) = delete;
    virtual ~LabeledEntity( ) { delete object; }

    EntityType  my_type( )   const noexcept override;
    std::string display( )   const override;
    Entity     *duplicate( ) const override;

private:
    Entity     *object;
    std::string label;
};

#endif
