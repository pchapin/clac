/*! \file    DirectoryEntity.hpp
 *  \brief   Interface to the Clac numeric type DirectoryEntity.
 *  \author  Peter Chapin <spicacality@kelseymountain.org>
 */

#ifndef DIRECTORYENTITY_HPP
#define DIRECTORYENTITY_HPP

#include "Entity.hpp"
#include <map>
#include <string>

class DirectoryEntity : public Entity {
  public:
    DirectoryEntity() noexcept
    {
    }
    DirectoryEntity(const DirectoryEntity&) = delete;
    DirectoryEntity& operator=(const DirectoryEntity&) = delete;
    virtual ~DirectoryEntity();

    EntityType my_type() const noexcept override;
    std::string display() const override;
    Entity* duplicate() const override;

  private:
    DirectoryEntity(const std::map<std::string, Entity*>& existing);
    std::map<std::string, Entity*> value;
};

#endif
