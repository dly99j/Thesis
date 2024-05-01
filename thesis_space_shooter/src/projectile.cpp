#include "../incl/projectile.hpp"

#include <iostream>

namespace spsh {

    projectile::projectile(direction t_direction, float t_speed, projectile_type t_type)
        : movable(t_direction, t_speed), m_type(t_type) {
    }

    auto projectile::get_type() const -> projectile_type {
        return m_type;
    }

    auto projectile::set_sound() -> void {
        if (m_type == projectile_type::rocket) {
            if (m_direction == direction::down) {
                m_sound_player = sound_player{sound_effect::enemy_rocket};
            } else if (m_direction == direction::up) {
                m_sound_player = sound_player{sound_effect::player_rocket};
            }
        }
    }

    auto projectile::play_sound() -> void {
        if (m_type == projectile_type::rocket) {
            if (m_direction == direction::down) {
                m_sound_player.play(sound_effect::enemy_rocket);
            } else if (m_direction == direction::up) {
                m_sound_player.play(sound_effect::player_rocket);
            }
        }
    }
} // spsh
