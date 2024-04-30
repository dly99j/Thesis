#include "../incl/menu_base.hpp"

namespace spsh {
    menu_base::menu_base(sf::RenderWindow &t_window) : m_window(t_window) {
        set_background();
    }

    auto menu_base::set_background() -> void {
        if (!m_background_texture.loadFromFile("../media/bg_menu.jpg")) {
            std::cerr << "error loading background! (bg_menu)\n";
            exit(errors::ASSET_LOAD_ERROR);
        }
        m_background_sprite.setTexture(m_background_texture);
    }
} // spsh