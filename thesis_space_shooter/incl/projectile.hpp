#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP
#include <SFML/Graphics.hpp>
#include "movable.hpp"

namespace spsh {
    class projectile : public movable {
    public:
        //TODO default param is temporary right now, might need fix
        projectile(direction, float);

    private:
        static sf::Texture m_projectile_texture;
    };
} // spsh

#endif //PROJECTILE_HPP
