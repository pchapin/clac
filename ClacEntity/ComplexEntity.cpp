/*! \file    ComplexEntity.cpp
 *  \brief   Implementation of the Clac numeric type ComplexEntity.
 *  \author  Peter Chapin <spicacality@kelseymountain.org>
 */

#include <cmath>
#include <complex>
#include <cstdio>
#include <sstream>
#include <string>

#include "DisplayState.hpp"
#include "Entities.hpp"
#include "support.hpp"

using namespace std;

namespace {

    // TODO: This is currently unused. Should it be?
    // Square root of -1.
    // const complex<double> j( 0.0, 1.0 );

}

namespace clac::entity {
    EntityType ComplexEntity::my_type() const noexcept
    {
        return COMPLEX;
    }

    string ComplexEntity::display() const
    {
        static char buffer[128 + 1]; // Array to hold the resulting string.
        const char* format_string;   // Pointer to a "printf style" format string.

        // Check the complex mode.
        if (display_state::get_complex_mode() == display_state::RECTANGULAR) {
            switch (display_state::get_display_mode()) {
            case display_state::FIXED:
                format_string = "(%.*f, %.*f)";
                break;

            case display_state::SCIENTIFIC:
                format_string = "(%.*E, %.*E)";
                break;

            default:
                format_string = "INTERNAL ERROR: Bad display mode";
                break;
            }
            snprintf(buffer, 128 + 1, format_string, display_state::get_decimal_count(), value.real(),
                     display_state::get_decimal_count(), value.imag());
        }

        // The complex mode must be POLAR.
        else {
            switch (display_state::get_display_mode()) {
            case display_state::FIXED:
                format_string = "(%.*f @ %.*f)";
                break;

            case display_state::SCIENTIFIC:
                format_string = "(%.*E @ %.*E)";
                break;

            default:
                format_string = "INTERNAL ERROR: Bad display mode";
                break;
            }
            snprintf(buffer, 128 + 1, format_string, display_state::get_decimal_count(), std::abs(value),
                     display_state::get_decimal_count(), from_radians(std::arg(value)));
        }
        return buffer;
    }

    Entity* ComplexEntity::duplicate() const
    {
        return new ComplexEntity(value);
    }

    //
    // Unary operations
    //

    Entity* ComplexEntity::abs() const
    {
        return new FloatEntity(std::abs(value));
    }

    Entity* ComplexEntity::complex_conjugate() const
    {
        return new ComplexEntity(std::conj(value));
    }

    Entity* ComplexEntity::cos() const
    {
        return new ComplexEntity(std::cos(value));
    }

    Entity* ComplexEntity::exp() const
    {
        return new ComplexEntity(std::exp(value));
    }

    Entity* ComplexEntity::exp10() const
    {
        return new ComplexEntity(std::pow(10.0, value));
    }

    Entity* ComplexEntity::imaginary_part() const
    {
        return new FloatEntity(value.imag());
    }

    Entity* ComplexEntity::inv() const
    {
        return new ComplexEntity(1.0 / value);
    }

    Entity* ComplexEntity::ln() const
    {
        // TODO: Implement me!
        throw "ComplexEntity::ln not implemented!";
        return nullptr;
    }

    Entity* ComplexEntity::log() const
    {
        // TODO: Implement me!
        throw "ComplexEntity::log not implemented!";
        return nullptr;
    }

    Entity* ComplexEntity::neg() const
    {
        return new ComplexEntity(-value);
    }

    Entity* ComplexEntity::real_part() const
    {
        return new FloatEntity(value.real());
    }

    Entity* ComplexEntity::sign() const
    {
        // TODO: Implement me!
        throw "ComplexEntity::sign not implemented!";
        return nullptr;
    }

    Entity* ComplexEntity::sin() const
    {
        return new ComplexEntity(std::sin(value));
    }

    Entity* ComplexEntity::sqrt() const
    {
        return new ComplexEntity(std::sqrt(value));
    }

    Entity* ComplexEntity::tan() const
    {
        return new ComplexEntity(std::tan(value));
    }

    //
    // Binary operations
    //

    Entity* ComplexEntity::divide(const Entity* R) const
    {
        const ComplexEntity* right = dynamic_cast<const ComplexEntity*>(R);
        return new ComplexEntity(value / right->value);
    }

    Entity* ComplexEntity::minus(const Entity* R) const
    {
        const ComplexEntity* right = dynamic_cast<const ComplexEntity*>(R);
        return new ComplexEntity(value - right->value);
    }

    Entity* ComplexEntity::multiply(const Entity* R) const
    {
        const ComplexEntity* right = dynamic_cast<const ComplexEntity*>(R);
        return new ComplexEntity(value * right->value);
    }

    Entity* ComplexEntity::plus(const Entity* R) const
    {
        const ComplexEntity* right = dynamic_cast<const ComplexEntity*>(R);
        return new ComplexEntity(value + right->value);
    }

    Entity* ComplexEntity::power(const Entity* R) const
    {
        // TODO: Implement me!
        throw "ComplexEntity::power not implemented!";
        return nullptr;
    }

    //
    // Conversions from ComplexEntity
    //

    Entity* ComplexEntity::to_complex() const
    {
        return duplicate();
    }
}
