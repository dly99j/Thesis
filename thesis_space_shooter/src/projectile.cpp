#include "../incl/projectile.hpp"

#include <iostream>

namespace spsh {

    sf::Texture projectile::m_projectile_texture;

    projectile::projectile(direction t_direction, float t_speed) : movable(t_direction, t_speed) {
        if (!m_projectile_texture.loadFromFile("../media/basic_red_dot.png")) {
            std::cerr << "error loading bullet\n";
        }
        set_texture(m_projectile_texture);
    }
} // spsh
