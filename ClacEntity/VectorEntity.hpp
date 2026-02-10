/*! \file    VectorEntity.hpp
 *  \brief   Interface to the Clac numeric type VectorEntity.
 *  \author  Peter Chapin <spicacality@kelseymountain.org>
 */

#ifndef VECTORENTITY_HPP
#define VECTORENTITY_HPP

#include "Entity.hpp"
#include <string>
#include <vector>

class VectorEntity : public Entity {
  public:
    virtual ~VectorEntity();

    EntityType my_type() const noexcept override;
    std::string display() const override;
    Entity* duplicate() const override;

  private:
    std::vector<Entity*> value;
};

#endif
