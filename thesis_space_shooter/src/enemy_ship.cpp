#include "../incl/enemy_ship.hpp"

#include <cmath>
#include <iostream>

namespace spsh {
    enemy_ship::enemy_ship(direction t_direction, float t_speed, short t_lives)
        : ship_base(t_direction, t_speed, t_lives)
          , m_time_since_alive(sf::Time::Zero) {
        if (!m_texture.loadFromFile("../media/enemy_ship_one.png")) {
            std::cerr << "error loading player\n";
        }
        set_texture(m_texture);

        if (!m_bullet_texture.loadFromFile("../media/enemy_missile.png")) {
            std::cerr << "error loading bullet\n";
        }

        m_enemy_clock.restart();
    }

    auto enemy_ship::shoot(std::optional<sf::FloatRect> t_player_info) -> std::optional<projectile> {
        if (!t_player_info.has_value()) {
            std::cerr <<
                    "Possible developer error: enemy_ship::shoot param should have a value (might change in the future)\n";
            return std::nullopt;
        }
        if (!needs_to_shoot(t_player_info.value())) {
            return std::nullopt;
        }
        auto proj = projectile(direction::down, 2000.0f, projectile_type::rocket);
        proj.set_texture(m_bullet_texture);
        auto pos = this->get_position();
        pos.x += static_cast<float>(this->get_texture_size().x) / 2.0f
                - static_cast<float>(proj.get_texture_size().x)/ 2.0f;
        pos.y += this->get_texture_rect().height;
        proj.set_position(pos);
        return {proj};
    }

    auto enemy_ship::send_projectile_if_needed(sf::FloatRect t_player_rect)
        -> std::optional<projectile> {
        if (std::floor(m_enemy_clock.getElapsedTime().asSeconds()) <=
            std::floor(m_time_since_alive.asSeconds())) {
            return std::nullopt;
        }
        m_time_since_alive = m_enemy_clock.getElapsedTime();
        return shoot(t_player_rect);
    }

    auto enemy_ship::needs_to_shoot(sf::FloatRect t_player_rect) const -> bool {
        auto x_distance = std::abs(t_player_rect.left - get_texture_rect().left);
        if (x_distance < t_player_rect.width * 3) {
            return true;
        }
        return false;
    }
} // spsh
