#ifndef CHOOSE_MAP_STATE_HPP
#define CHOOSE_MAP_STATE_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility>
#include "config.hpp"
#include "enums.hpp"
#include "menu_base.hpp"

namespace spsh {
class choose_map_state : public menu_base {
   public:
    explicit choose_map_state(sf::RenderWindow&);

    auto load_image() -> void final;

    [[nodiscard]]
    auto display() -> std::optional<map>;

   private:
    sf::Texture m_bg0, m_bg1, m_bg2;
    sf::RectangleShape m_map0_button, m_map1_button, m_map2_button;
};
}  // namespace spsh

#endif  //CHOOSE_MAP_STATE_HPP
