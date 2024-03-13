//
// Created by htamas on 2024.03.12..
//

#include "../incl/avoiding_enemy.hpp"

namespace spsh {
    avoiding_enemy::avoiding_enemy(direction t_direction, float t_speed, short t_lives)
        : enemy_ship(t_direction, t_speed, t_lives) {
    }

    auto avoiding_enemy::calculate_direction(sf::FloatRect t_player_rect, sf::Vector2u t_screen_dimensions) -> void {
        //gets the middle point of the texture on the x axis
        auto player_width = t_player_rect.width / 1.4f;
        auto player_middle_x = t_player_rect.left + (t_player_rect.width / 2.0f);
        auto enemy_middle_x = get_texture_rect().left + (get_texture_rect().width / 2);
        auto delta = static_cast<float>(t_screen_dimensions.x) / 6.0f;
        delta = delta < player_width ? delta : player_width;
        auto curr_delta = std::abs(enemy_middle_x - player_middle_x);
        if (curr_delta < delta) {
            set_dierction(direction::stationary);
        } else {
            if (enemy_middle_x > player_middle_x) {
                set_dierction(direction::left);
            } else {
                set_dierction(direction::right);
            }
        }
    }

} // spsh
