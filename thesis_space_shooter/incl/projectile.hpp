#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP
#include <SFML/Graphics.hpp>
#include "movable.hpp"
#include "enums.hpp"
#include "sound_player.hpp"

namespace spsh {

    class projectile : public movable {
    public:
        projectile(direction, float, projectile_type);

        [[nodiscard]]
        auto get_type() const -> projectile_type;

        auto set_sound() -> void;

        auto play_sound() -> void;

    protected:
        projectile_type m_type;
        sound_player m_sound_player;
    };
} // spsh

#endif //PROJECTILE_HPP
