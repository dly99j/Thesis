#include "../incl/projectile.hpp"

namespace spsh {
    projectile::projectile(const direction t_direction, const float t_speed, const projectile_type t_type)
        : movable(t_direction, t_speed), m_type(t_type) {
    }

    auto projectile::get_type() const -> projectile_type {
        return m_type;
    }
} // spsh
