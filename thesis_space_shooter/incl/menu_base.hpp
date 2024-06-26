#ifndef MENU_BASE_HPP
#define MENU_BASE_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include "config.hpp"

namespace spsh {
class menu_base {
   protected:
    explicit menu_base(sf::RenderWindow&);

    virtual ~menu_base() = default;

    auto virtual load_image() -> void = 0;

    auto virtual set_background() -> void final;

   protected:
    sf::RenderWindow& m_window;
    sf::Texture m_background_texture;
    sf::Sprite m_background_sprite;
};
}  // namespace spsh

#endif  //MENU_BASE_HPP
