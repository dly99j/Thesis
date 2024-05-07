#include "../incl/choose_map_state.hpp"

namespace spsh {
    choose_map_state::choose_map_state(sf::RenderWindow &t_window) : menu_base(t_window)
                                                                     , m_map0_button({320.f, 240.f}),
                                                                     m_map1_button({320.f, 240.f}),
                                                                     m_map2_button({320.f, 240.f}) {
        load_image();
    }

    auto choose_map_state::load_image() -> void {
        if (!m_bg0.loadFromFile("../media/bg0_small.jpg")) {
            std::cerr << "error loading map1 button!\n";
            exit(errors::ASSET_LOAD_ERROR);
        }
        if (!m_bg1.loadFromFile("../media/bg1_small.jpg")) {
            std::cerr << "error loading map2 button!\n";
            exit(errors::ASSET_LOAD_ERROR);
        }
        if (!m_bg2.loadFromFile("../media/bg2_small.jpg")) {
            std::cerr << "error loading map3 button!\n";
            exit(errors::ASSET_LOAD_ERROR);
        }
    }

    auto choose_map_state::display() -> std::optional<map> {
        sf::Font font;
        if (!font.loadFromFile("../media/sansation.ttf")) {
            std::cerr << "Failed to load font file" << std::endl;
            exit(errors::ASSET_LOAD_ERROR);
        }

        sf::Text title("Choose a Map", font, 60);
        title.setFillColor(sf::Color::White);
        title.setStyle(sf::Text::Bold);
        title.setPosition((static_cast<float>(m_window.getSize().x) - title.getGlobalBounds().width) / 2.f, 50.f);

        m_map0_button.setTexture(&m_bg0);
        m_map1_button.setTexture(&m_bg1);
        m_map2_button.setTexture(&m_bg2);

        m_map0_button.setOutlineThickness(5.0f);
        m_map1_button.setOutlineThickness(5.0f);
        m_map2_button.setOutlineThickness(5.0f);

        m_map0_button.setPosition((static_cast<float>(m_window.getSize().x) - m_map0_button.getSize().x) / 2.f, 180.f);
        m_map1_button.setPosition((static_cast<float>(m_window.getSize().x) - m_map1_button.getSize().x) / 2.f, 440.f);
        m_map2_button.setPosition((static_cast<float>(m_window.getSize().x) - m_map2_button.getSize().x) / 2.f, 700.f);

        sf::Text map0_text("Fisrt Map", font, 30);
        map0_text.setFillColor(sf::Color::White);
        map0_text.setPosition(
            m_map0_button.getPosition().x + (m_map0_button.getSize().x - map0_text.getGlobalBounds().width) / 2.f,
            m_map0_button.getPosition().y + (m_map0_button.getSize().y - map0_text.getGlobalBounds().height) / 2.f -
            5.f);

        sf::Text map1_text("Second Map", font, 30);
        map1_text.setFillColor(sf::Color::White);
        map1_text.setPosition(
            m_map1_button.getPosition().x + (
                m_map1_button.getSize().x - map1_text.getGlobalBounds().width) / 2.f,
            m_map1_button.getPosition().y + (
                m_map1_button.getSize().y - map1_text.getGlobalBounds().height) / 2.f - 5.f);

        sf::Text map2_text("Third Map", font, 30);
        map2_text.setFillColor(sf::Color::White);
        map2_text.setPosition(
            m_map2_button.getPosition().x + (m_map2_button.getSize().x - map2_text.getGlobalBounds().width) / 2.f,
            m_map2_button.getPosition().y + (m_map2_button.getSize().y - map2_text.getGlobalBounds().height) / 2.f -
            5.f);

        while (m_window.isOpen()) {
            sf::Event event{};
            while (m_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    m_window.close();
                    return map::first;
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    return std::nullopt;
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2f mouse_pos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
                    if (m_map0_button.getGlobalBounds().contains(mouse_pos)) {
                        return map::first;
                    }
                    if (m_map1_button.getGlobalBounds().contains(mouse_pos)) {
                        return map::second;
                    }
                    if (m_map2_button.getGlobalBounds().contains(mouse_pos)) {
                        return map::third;
                    }
                }
            }

            m_window.clear(sf::Color(30, 30, 30));
            m_window.draw(m_background_sprite);
            m_window.draw(title);
            m_window.draw(m_map0_button);
            m_window.draw(m_map1_button);
            m_window.draw(m_map2_button);
            m_window.draw(map0_text);
            m_window.draw(map1_text);
            m_window.draw(map2_text);
            m_window.display();
        }
        std::unreachable();
    }
} // spsh
