#include <utility>

#include "../incl/player_ship.hpp"

namespace spsh {
    player_ship::player_ship(direction t_direction, float t_speed, std::queue<projectile> t_bullets)
    : movable(t_direction, t_speed), m_bullets(std::move(t_bullets)) {
        //TODO ONLY FOR TESTING PURPOSES!!!!!!
        m_bullets.emplace(direction::up, 6000.0f);
        m_bullets.emplace(direction::up, 6000.0f);
        m_bullets.emplace(direction::up, 6000.0f);
        m_bullets.emplace(direction::up, 6000.0f);
        m_bullets.emplace(direction::up, 6000.0f);
        m_bullets.emplace(direction::up, 6000.0f);
        m_bullets.emplace(direction::up, 6000.0f);
        m_bullets.emplace(direction::up, 6000.0f);
        m_bullets.emplace(direction::up, 6000.0f);
        m_bullets.emplace(direction::up, 6000.0f);
        m_bullets.emplace(direction::up, 6000.0f);
    }

    auto player_ship::shoot() -> std::optional<projectile> {

        if (m_bullets.empty()) {
            return {};
        }
        auto proj = m_bullets.back();
        m_bullets.pop(); //TODO nicer solution that requires no copy?
        proj.set_position(this->get_position());
        return {proj};
    }
} // spsh
