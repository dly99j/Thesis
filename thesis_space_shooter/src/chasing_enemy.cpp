#include "../incl/chasing_enemy.hpp"

namespace spsh {
    chasing_enemy::chasing_enemy(direction t_direction, float t_speed, short t_lives)
        : enemy_ship(t_direction, t_speed, t_lives) {
        if (!m_texture.loadFromFile("../media/eship1.png")) {
            std::cerr << "error loading player\n";
            exit(errors::ASSET_LOAD_ERROR);
        }
        set_texture(m_texture);
        m_direction_timer.restart();
    }

    auto chasing_enemy::change_random_direction() -> bool {
        if (m_direction_timer.getElapsedTime().asSeconds() > constants::change_direction_interval) {
            m_direction_timer.restart();
            return true;
        }
        return false;
    }

    auto chasing_enemy::calculate_direction(const sf::Vector2u t_screen_dimensions,
                                            const std::optional<sf::FloatRect> t_player_rect) -> void {
        if (!t_player_rect.has_value()) {
            std::cerr << "Fatal developer error! This has to have value!\n";
            std::cerr << "chasing_enemy::calculate_dierction\n";
            exit(errors::OPTIONAL_ERROR);
        }
        const auto player_width = t_player_rect.value().width / 4.0f;
        const auto player_middle_x = t_player_rect.value().left + t_player_rect.value().width / 2.0f;
        const auto enemy_middle_x = get_reduced_texture_rect().left + get_reduced_texture_rect().width / 2.0f;
        auto delta = static_cast<float>(t_screen_dimensions.x) / 7.0f;
        delta = delta < player_width ? delta : player_width;
        if (const auto curr_delta = std::abs(enemy_middle_x - player_middle_x); curr_delta < delta) {
            set_dierction(direction::stationary);
        } else {
            if (change_random_direction()) {
                const auto rand = m_dist(m_gen);
                if (enemy_middle_x > player_middle_x) {
                    if (rand < 4) {
                        set_dierction(direction::up_left);
                    } else if (rand > 6) {
                        set_dierction(direction::down_left);
                    } else {
                        set_dierction(direction::left);
                    }
                } else {
                    if (rand < 4) {
                        set_dierction(direction::up_right);
                    } else if (rand > 6) {
                        set_dierction(direction::down_right);
                    } else {
                        set_dierction(direction::right);
                    }
                }
            } else {
                const auto pos_top = get_reduced_texture_rect().top;
                const auto pos_bot = get_reduced_texture_rect().top + get_reduced_texture_rect().height;
                if (enemy_middle_x > player_middle_x) {
                    if ((get_direction() == direction::up_left || get_direction() == direction::up_right)
                        && pos_top > 5.0f) {
                        set_dierction(direction::up_left);
                    } else if ((get_direction() == direction::down_left || get_direction() == direction::down_right)
                        && pos_bot < static_cast<float>(t_screen_dimensions.y) / 3.0f) {
                        set_dierction(direction::down_left);
                    } else {
                        set_dierction(direction::left);
                    }
                } else {
                    if ((get_direction() == direction::up_left || get_direction() == direction::up_right)
                        && pos_top > 5.0f) {
                        set_dierction(direction::up_right);
                    } else if ((get_direction() == direction::down_left || get_direction() == direction::down_right)
                        && pos_bot < static_cast<float>(t_screen_dimensions.y) / 3.0f) {
                        set_dierction(direction::down_right);
                    } else {
                        set_dierction(direction::right);
                    }
                }
            }
        }
    }
} // spsh
