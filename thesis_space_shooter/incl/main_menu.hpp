#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "enums.hpp"
#include "menu_base.hpp"
#include "config.hpp"

namespace spsh {

    class main_menu : public menu_base {
    public:
        explicit main_menu(sf::RenderWindow &);

        auto load_image() -> void final;

        [[nodiscard]]
        auto display() const -> menu_result;

    private:
        sf::Texture m_btn;
    };
} // namespace spsh

#endif // MAIN_MENU_HPP
