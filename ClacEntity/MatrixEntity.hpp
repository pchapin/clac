/*! \file    MatrixEntity.hpp
 *  \brief   Interface to the clac numeric type MatrixEntity.
 *  \author  Peter Chapin <chapinp@proton.me>
 */

#ifndef MATRIXENTITY_HPP
#define MATRIXENTITY_HPP

#include <string>
#include <vector>
#include "Entity.hpp"

class MatrixEntity : public Entity {
public:
    ~MatrixEntity( );

    EntityType  my_type( )   const noexcept override;
    std::string display( )   const override;
    Entity     *duplicate( ) const override;

private:

    // It would probably make sense to create a separate matrix type with overloaded operators,
    // etc (as was done for rational and integer, and then just make the private part of a
    // matrix an instance of that type.
    // 
    typedef std::vector<Entity *> row_type;
    std::vector<row_type> value;
};

#endif
