/*! \file    ListEntity.hpp
 *  \brief   Interface to the Clac numeric type ListEntity.
 *  \author  Peter Chapin <spicacality@kelseymountain.org>
 */

#ifndef LISTENTITY_HPP
#define LISTENTITY_HPP

#include "Entity.hpp"
#include <list>
#include <string>

class ListEntity : public Entity {
  public:
    ListEntity() noexcept
    {
    }
    ListEntity(const std::list<Entity*>& incoming) : value(incoming)
    {
    }
    ListEntity(const ListEntity&) = delete;
    ListEntity& operator=(const ListEntity&) = delete;
    ~ListEntity();

    EntityType my_type() const noexcept override;
    std::string display() const override;
    Entity* duplicate() const override;

    Entity* plus(const Entity*) const override;

  private:
    std::list<Entity*> value;
};

#endif
