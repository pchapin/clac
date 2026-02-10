/*! \file    ProgramEntity.hpp
 *  \brief   Interface to the Clac numeric type ProgramEntity.
 *  \author  Peter Chapin <spicacality@kelseymountain.org>
 */

#ifndef PROGRAMENTITY_HPP
#define PROGRAMENTITY_HPP

#include "Entity.hpp"
#include <string>

class ProgramEntity : public Entity {
  public:
    ProgramEntity(const std::string& program) : value(program)
    {
    }

    EntityType my_type() const noexcept override;
    std::string display() const override;
    Entity* duplicate() const override;

  private:
    std::string value;
};

#endif
