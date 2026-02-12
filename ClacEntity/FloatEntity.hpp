/*! \file    FloatEntity.hpp
 *  \brief   Interface to the Clac numeric type FloatEntity.
 *  \author  Peter Chapin <spicacality@kelseymountain.org>
 */

#ifndef FLOATENTITY_HPP
#define FLOATENTITY_HPP

#include "Entity.hpp"

namespace clac::entity {
    class FloatEntity : public Entity {
    public:
        // For building a FloatEntity from its primitive.
        FloatEntity(double number) noexcept;

        // Functions for maintaining a member of the Entity family.
        EntityType my_type() const noexcept override;
        std::string display() const override;
        Entity* duplicate() const override;

        // Unary operations.
        Entity* abs() const override;
        Entity* acos() const override;
        Entity* asin() const override;
        Entity* atan() const override;
        Entity* complex_conjugate() const override;
        Entity* cos() const override;
        Entity* exp() const override;
        Entity* exp10() const override;
        Entity* fractional_part() const override;
        Entity* imaginary_part() const override;
        Entity* integer_part() const override;
        Entity* inv() const override;
        Entity* ln() const override;
        Entity* log() const override;
        Entity* neg() const override;
        Entity* real_part() const override;
        Entity* sign() const override;
        Entity* sin() const override;
        Entity* sq() const override;
        Entity* sqrt() const override;
        Entity* tan() const override;

        // Conversion functions.
        Entity* to_complex() const override;
        Entity* to_float() const override;
        Entity* to_integer() const override;

        // Binary operations.
        Entity* divide(const Entity*) const override;
        Entity* minus(const Entity*) const override;
        Entity* multiply(const Entity*) const override;
        Entity* plus(const Entity*) const override;
        Entity* power(const Entity*) const override;

        // Relational operations.
        Entity* is_equal(const Entity*) const override;
        Entity* is_notequal(const Entity*) const override;
        Entity* is_less(const Entity*) const override;
        Entity* is_lessorequal(const Entity*) const override;
        Entity* is_greater(const Entity*) const override;
        Entity* is_greaterorequal(const Entity*) const override;

    private:
        double value;
    };
}

#endif
