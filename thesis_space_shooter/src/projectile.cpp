#include "../incl/projectile.hpp"

#include <iostream>

namespace spsh {
    sf::Texture projectile::m_projectile_texture;

    projectile::projectile(direction t_direction, float t_speed, projectile_type t_type)
        : movable(t_direction, t_speed), m_type(t_type) {
    }

    auto projectile::get_type() const -> projectile_type {
        return m_type;
    }
} // spsh
