/*! \file    MatrixEntity.cpp
 *  \brief   Implementation of the clac numeric type MatrixEntity.
 *  \author  Peter Chapin <chapinp@proton.me>
 */

#include "Entities.hpp"

using namespace std;

MatrixEntity::~MatrixEntity( )
{
    vector<row_type>::iterator p1;
    vector<Entity *>::iterator p2;

    for( p1 = value.begin( ); p1 != value.end( ); ++p1 ) {
        for( p2 = p1->begin( ); p2 != p1->end( ); ++p2 ) {
            delete *p2;
        }
    }
}

EntityType MatrixEntity::my_type( ) const
{
    return MATRIX;
}

string MatrixEntity::display( ) const
{
    return "MatrixEntity::display( ) not implemented!";
}

Entity *MatrixEntity::duplicate() const
{
    throw Error("MatrixEntity::duplicate( ) not implemented!");
}
