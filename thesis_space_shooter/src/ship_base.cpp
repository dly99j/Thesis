#include "../incl/ship_base.hpp"

namespace spsh {
    ship_base::ship_base(direction t_direction, float t_speed, short t_lives)
    : movable(t_direction, t_speed), m_lives(t_lives){
    }

    auto ship_base::put_back_on_map(const std::unique_ptr<sf::Vector2u>& t_window_size) -> void {
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

    auto ship_base::decrease_life(short t_decrease_by) -> void {
        m_lives -= t_decrease_by;
    }

    auto ship_base::increase_life(short t_increase_by) -> void {
        m_lives += t_increase_by;
    }

    auto ship_base::get_lives() const -> short {
        return m_lives;
    }

    auto ship_base::is_alive() const -> bool {
        return m_lives > 0;
    }
} // spsh