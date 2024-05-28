#include "../incl/avoiding_enemy.hpp"

namespace spsh {
avoiding_enemy::avoiding_enemy(const direction t_direction, const float t_speed,
                               const short t_lives)
    : enemy_ship(t_direction, t_speed, t_lives) {
    if (!m_texture.loadFromFile("../media/eship2.png")) {
        std::cerr << "error loading avoiding_enemy texture\n";
        exit(errors::ASSET_LOAD_ERROR);
    }
    set_texture(m_texture);

    m_is_going_left = m_dist(m_gen) < 5;
    m_is_going_diagonally = m_dist(m_gen) < 5;
    m_is_going_upwards = m_dist(m_gen) < 5;

    m_direction_timer.restart();
}

auto avoiding_enemy::change_random_direction() -> void {
    if (m_direction_timer.getElapsedTime().asSeconds() >
        constants::change_direction_interval) {
        m_direction_timer.restart();
        if (m_dist(m_gen) < 7) {
            m_is_going_diagonally = true;
        } else {
            m_is_going_diagonally = false;
        }

        if (m_dist(m_gen) < 5) {
            m_is_going_upwards = true;
        } else {
            m_is_going_upwards = false;
        }
    }
}

auto avoiding_enemy::left_right_switch(const sf::Vector2u t_screen_dimensions)
    -> void {
    if (m_is_going_left && get_position().x < 20.0f) {
        m_is_going_left = false;
    }
    if (!m_is_going_left &&
        get_position().x + get_texture_rect().width >
            static_cast<float>(t_screen_dimensions.x) - 20.0f) {
        m_is_going_left = true;
    }
}

auto avoiding_enemy::is_bullet_close(
    const sf::Vector2u t_screen_dimensions,
    const std::optional<sf::FloatRect>& t_closest_bullet) const -> bool {
    if (!t_closest_bullet.has_value()) {
        return false;
    }
    const auto bullet_middle_x =
        t_closest_bullet.value().left + t_closest_bullet.value().width / 2.0f;
    const auto bullet_middle_y =
        t_closest_bullet.value().top + t_closest_bullet.value().height / 2.0f;
    const auto enemy_middle_x = get_reduced_texture_rect().left +
                                get_reduced_texture_rect().width / 2.0f;
    const auto enemy_middle_y = get_reduced_texture_rect().top +
                                get_reduced_texture_rect().height / 2.0f;
    const auto delta = static_cast<float>(t_screen_dimensions.x) / 4.5f;

    const auto distance_sq = std::pow(bullet_middle_x - enemy_middle_x, 2) +
                             std::pow(bullet_middle_y - enemy_middle_y, 2);
    return distance_sq < std::pow(delta, 2);
}

auto avoiding_enemy::calculate_direction(
    const sf::Vector2u t_screen_dimensions,
    const std::optional<sf::FloatRect> t_closest_bullet) -> void {
    left_right_switch(t_screen_dimensions);
    change_random_direction();

    if (is_bullet_close(t_screen_dimensions, t_closest_bullet)) {
        const auto bullet_middle_x = t_closest_bullet.value().left +
                                     t_closest_bullet.value().width / 2.0f;
        const auto enemy_middle_x = get_reduced_texture_rect().left +
                                    get_reduced_texture_rect().width / 2.0f;
        if (bullet_middle_x < enemy_middle_x && m_is_going_left) {
            set_direction(direction::right);
        } else if (bullet_middle_x >= enemy_middle_x && !m_is_going_left) {
            set_direction(direction::left);
        }
    } else if (m_is_going_left) {
        if (m_is_going_diagonally) {
            if (m_is_going_upwards) {
                const auto pos_top = get_reduced_texture_rect().top;
                if (pos_top < 5.0f) {
                    m_is_going_upwards = false;
                    m_is_going_diagonally = false;
                    set_direction(direction::left);
                } else {
                    set_direction(direction::up_left);
                }
            } else {
                const auto pos_bot = get_reduced_texture_rect().top +
                                     get_reduced_texture_rect().height;
                if (pos_bot >
                    static_cast<float>(t_screen_dimensions.y) / 3.0f) {
                    m_is_going_diagonally = false;
                    set_direction(direction::left);
                } else {
                    set_direction(direction::down_left);
                }
            }
        } else {
            set_direction(direction::left);
        }
    } else {
        if (m_is_going_diagonally) {
            if (m_is_going_upwards) {
                const auto pos_top = get_reduced_texture_rect().top;
                if (pos_top < 5.0f) {
                    m_is_going_upwards = false;
                    m_is_going_diagonally = false;
                    set_direction(direction::right);
                } else {
                    set_direction(direction::up_right);
                }
            } else {
                const auto pos_bot = get_reduced_texture_rect().top +
                                     get_reduced_texture_rect().height;
                if (pos_bot >
                    static_cast<float>(t_screen_dimensions.y) / 3.0f) {
                    m_is_going_diagonally = false;
                    set_direction(direction::right);
                } else {
                    set_direction(direction::down_right);
                }
            }
        } else {
            set_direction(direction::right);
        }
    }
}
}  // namespace spsh
