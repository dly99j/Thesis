#include "../incl/enemy_ship.hpp"

#include <cmath>
#include <iostream>

namespace spsh {
    enemy_ship::enemy_ship(direction t_direction, float t_speed, short t_lives)
    : ship_base(t_direction, t_speed, t_lives) {
        if (!m_texture.loadFromFile("../media/eagle_rotated.png")) {
            std::cerr << "error loading player\n";
        }
        set_texture(m_texture);

        if(!m_bullet_texture.loadFromFile("../media/basic_yellow_dot.png")) {
            std::cerr << "error loading bullet\n";
        }

        m_enemy_clock.restart();
    }

    auto enemy_ship::shoot() -> std::optional<projectile> {
        auto proj = projectile(direction::down, 2000.0f, projectile_type::rocket);
        proj.set_texture(m_bullet_texture);
        auto pos = this->get_position();
        pos.x += static_cast<float>(this->get_texture_size().x) / 4.0f; //TODO this is ugly as fuck but it works
        //pos.y -= static_cast<float>(proj.get_texture_size().y);
        proj.set_position(pos);
        return {proj};
    }

    auto enemy_ship::send_projectile_if_needed() -> std::optional<projectile> {
        if (std::floor(m_enemy_clock.getElapsedTime().asSeconds()) <=
            std::floor(m_time_since_alive.asSeconds())) {
            return {};
            }
        return shoot();
    }
} // spsh