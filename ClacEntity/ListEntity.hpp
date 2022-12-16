/*! \file    ListEntity.hpp
 *  \brief   Interface to the clac numeric type ListEntity.
 *  \author  Peter Chapin <chapinp@proton.me>
 */

#ifndef LISTENTITY_HPP
#define LISTENTITY_HPP

#include <list>
#include <string>
#include "Entity.hpp"

class ListEntity : public Entity {
public:
    ListEntity( ) { }
    ListEntity( const std::list<Entity *> &incoming ) : value( incoming ) { }
   ~ListEntity( );

    EntityType  my_type( )   const noexcept override;
    std::string display( )   const override;
    Entity     *duplicate( ) const override;

    virtual Entity *plus( const Entity * ) const override;

private:
    std::list<Entity *> value;
};

#endif
