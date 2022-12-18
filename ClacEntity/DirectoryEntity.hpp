/*! \file    DirectoryEntity.hpp
 *  \brief   Interface to the clac numeric type DirectoryEntity.
 *  \author  Peter Chapin <chapinp@proton.me>
 */

#ifndef DIRECTORYENTITY_HPP
#define DIRECTORYENTITY_HPP

#include <string>
#include <map>
#include "Entity.hpp"

class DirectoryEntity : public Entity {
public:
    DirectoryEntity( ) noexcept { }
    DirectoryEntity( const DirectoryEntity & ) = delete;
    DirectoryEntity &operator=( const DirectoryEntity & ) = delete;
    virtual ~DirectoryEntity( );

    EntityType my_type( ) const noexcept override;
    std::string display( ) const override;
    Entity *duplicate( ) const override;

private:
    DirectoryEntity( const std::map<std::string, Entity *> &existing );
    std::map<std::string, Entity *> value;
};

#endif
