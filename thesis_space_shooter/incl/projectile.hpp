#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP
#include <SFML/Graphics.hpp>
#include "movable.hpp"

namespace spsh {

    enum class projectile_type {
        asteroid, rocket
    };

    class projectile : public movable {
    public:
        projectile(direction, float, projectile_type);

        [[nodiscard]]
        auto get_type() const -> projectile_type;

    private:
        static sf::Texture m_projectile_texture;
        projectile_type m_type;
    };
} // spsh

#endif //PROJECTILE_HPP
