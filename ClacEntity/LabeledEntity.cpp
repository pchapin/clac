/*! \file    LabeledEntity.cpp
 *  \brief   Implementation of the Clac numeric type LabeledEntity.
 *  \author  Peter Chapin <spicacality@kelseymountain.org>
 */

#include "Entities.hpp"

namespace clac::entity {
    EntityType LabeledEntity::my_type() const noexcept
    {
        return LABELED;
    }

    std::string LabeledEntity::display() const
    {
        std::string result(label);
        result.append(": ");
        result.append(object->display());
        return result;
    }

    Entity* LabeledEntity::duplicate() const
    {
        Entity* new_object = object->duplicate();
        return new LabeledEntity(new_object, label);
    }
}
