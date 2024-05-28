#ifndef CONFIG_HPP
#define CONFIG_HPP
#include <cstddef>
#include "enums.hpp"

namespace spsh {
    struct player_details {
        float speed;
        short lives;
        std::size_t bullets;
        float bullet_speed;
        float boost_multiplier;
        float boost_duration;
        map current_map;
    };

    namespace constants {
        constexpr player_details first_ship{350.0f, 5, 10, 600.0f, 2.0f, 10.0f, map::first};
        constexpr player_details second_ship{300.0f, 6, 5, 600.0f, 2.5f, 8.0f, map::second};
        constexpr player_details third_ship{350.0f, 6, 15, 600.0f, 3.0f, 7.0f, map::third};

        constexpr float chasing_enemy_speed = 250.0f;
        constexpr short chasing_enemy_lives = 10;

        constexpr float avoiding_enemy_speed = 225.0f;
        constexpr short avoiding_enemy_lives = 11;

        constexpr float waypoint_enemy_speed = 200.0f;
        constexpr short waypoint_enemy_lives = 12;

        constexpr float enemy_bullet_speed = 600.0f;
        constexpr float asteroid_speed = 600.0f;

        constexpr float pwu_spawn_interval = 2.0f;
        constexpr float change_direction_interval = 3.0f;
        constexpr float music_volume = 30.0f;
        const sf::Time frame_time = sf::seconds(1.0f / 240.0f);
    }

    namespace errors {
        constexpr int ASSET_LOAD_ERROR = 1;
        constexpr int OPTIONAL_ERROR = 2;
        constexpr int BAD_FUNCTION_CALL = 3;
        constexpr int SOUND_ERROR = 4;
    }
} //SPSH
#endif //CONFIG_HPP
