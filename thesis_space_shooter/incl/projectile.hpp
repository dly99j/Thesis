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

    protected:
        projectile_type m_type;
    };
} // spsh

#endif //PROJECTILE_HPP
