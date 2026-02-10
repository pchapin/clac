/*! \file    ProgramEntity.cpp
 *  \brief   Implementation of the Clac numeric type ProgramEntity.
 *  \author  Peter Chapin <spicacality@kelseymountain.org>
 */

#include "Entities.hpp"

EntityType ProgramEntity::my_type() const noexcept
{
    return PROGRAM;
}

std::string ProgramEntity::display() const
{
    return "ProgramEntity::display( ) not implemented!";
}

Entity* ProgramEntity::duplicate() const
{
    return new ProgramEntity(value);
}
