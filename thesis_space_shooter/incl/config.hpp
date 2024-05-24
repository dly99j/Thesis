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
        constexpr player_details firts_ship{1000.0f, 5, 10, 2000.0f, 2.0f, 10.0f, map::first};
        constexpr player_details second_ship{800.0f, 6, 20, 1500.0f, 2.5f, 8.0f, map::second};
        constexpr player_details third_ship{1000.0f, 6, 15, 2500.0f, 3.0f, 1.0f, map::third};

        constexpr auto pwu_spawn_interval = 2.0f;
        constexpr auto change_direction_interval = 3.0f;
        constexpr auto music_volume = 30.0f;
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
