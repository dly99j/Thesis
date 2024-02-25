#include <utility>

#include "../incl/player_ship.hpp"

#include <iostream>
#include <SFML/Graphics/Texture.hpp>

namespace spsh {
    player_ship::player_ship(direction t_direction, float t_speed, std::queue<projectile> t_bullets)
        : movable(t_direction, t_speed), m_bullets(std::move(t_bullets)) {
        //TODO only for testing purposes
        /*
        m_bullets.emplace(direction::up, 2000.0f);
        m_bullets.emplace(direction::up, 2000.0f);
        m_bullets.emplace(direction::up, 2000.0f);
        m_bullets.emplace(direction::up, 2000.0f);
        m_bullets.emplace(direction::up, 2000.0f);
        m_bullets.emplace(direction::up, 2000.0f);
        m_bullets.emplace(direction::up, 2000.0f);
        m_bullets.emplace(direction::up, 2000.0f);
        m_bullets.emplace(direction::up, 2000.0f);
        m_bullets.emplace(direction::up, 2000.0f);
        */
    }

    auto player_ship::shoot() -> std::optional<projectile> {
        if (m_bullets.empty()) {
            return {};
        }
        auto proj = m_bullets.back();
        m_bullets.pop(); //TODO nicer solution that requires no copy?
        auto pos = this->get_position();
        pos.x += static_cast<float>(this->get_texture_size().x) / 4.0f; //TODO this is ugly as fuck but it works
        proj.set_position(pos);
        return {proj};
    }

    auto player_ship::put_back_on_map(const std::unique_ptr<sf::Vector2u>& t_window_size) -> void {
        if (!is_off_map(t_window_size)) {
            return;
        }

        const auto window_x = static_cast<float>(t_window_size->x);
        const auto window_y = static_cast<float>(t_window_size->y);
        const auto texture_x = static_cast<float>(get_texture_size().x);
        const auto texture_y = static_cast<float>(get_texture_size().y);

        if (get_position().x < 0.0f) {
            set_position({0.0f, get_position().y});
        }
        if (get_position().y < 0.0f) {
            set_position({get_position().x, 0.0f});
        }
        if (get_position().x + texture_x > window_x) {
            set_position({window_x - texture_x, get_position().y});
        }
        if (get_position().y + texture_y > window_y) {
            set_position({get_position().x, window_y - texture_y});
        }
    }
} // spsh
