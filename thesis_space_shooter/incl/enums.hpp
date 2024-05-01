#ifndef ENUMS_HPP
#define ENUMS_HPP

namespace spsh {
    enum class direction {
        up,
        up_right,
        right,
        down_right,
        down,
        down_left,
        left,
        up_left,
        stationary
    };

    enum class powerup_type {
        health,
        rocket,
        temporary_speed
    };

    enum class projectile_type {
        asteroid,
        rocket
    };

    enum class map {
        first,
        second,
        third
    };

    enum class game_state {
        playing,
        won,
        lost
    };

    enum class menu_result {
        play,
        choose_map,
        quit
    };

    enum class music {
        menu,
        game
    };

    enum class sound_effect {
        player_rocket,
        enemy_rocket,
        player_hit,
        enemy_hit,
        button,
        powerup
    };
}

#endif //ENUMS_HPP
