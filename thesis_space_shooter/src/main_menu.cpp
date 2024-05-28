#include "../incl/main_menu.hpp"

namespace spsh {
main_menu::main_menu(sf::RenderWindow& t_window) : menu_base(t_window) {
    load_image();
}

auto main_menu::load_image() -> void {
    if (!m_btn.loadFromFile("../media/btn.png")) {
        std::cerr << "error loading button!\n";
        exit(errors::ASSET_LOAD_ERROR);
    }
}

auto main_menu::display() const -> menu_result {
    sf::Font font;
    if (!font.loadFromFile("../media/sansation.ttf")) {
        std::cerr << "Failed to load font file" << std::endl;
        exit(errors::ASSET_LOAD_ERROR);
    }

    sf::Text title("Main Menu", font, 60);
    title.setFillColor(sf::Color::White);
    title.setStyle(sf::Text::Bold);
    title.setPosition((static_cast<float>(m_window.getSize().x) -
                       title.getGlobalBounds().width) /
                          2.f,
                      100.f);

    sf::RectangleShape play_button({300.f, 120.f});
    sf::RectangleShape choose_map_button({300.f, 120.f});
    sf::RectangleShape quit_button({300.f, 120.f});

    play_button.setTexture(&m_btn);
    choose_map_button.setTexture(&m_btn);
    quit_button.setTexture(&m_btn);

    play_button.setPosition(
        (static_cast<float>(m_window.getSize().x) - play_button.getSize().x) /
            2.f,
        250.f);
    choose_map_button.setPosition((static_cast<float>(m_window.getSize().x) -
                                   choose_map_button.getSize().x) /
                                      2.f,
                                  400.f);
    quit_button.setPosition(
        (static_cast<float>(m_window.getSize().x) - quit_button.getSize().x) /
            2.f,
        550.f);

    sf::Text play_text("Start Game", font, 30);
    play_text.setFillColor(sf::Color::White);
    play_text.setPosition(
        play_button.getPosition().x +
            (play_button.getSize().x - play_text.getGlobalBounds().width) / 2.f,
        play_button.getPosition().y +
            (play_button.getSize().y - play_text.getGlobalBounds().height) /
                2.f -
            5.f);

    sf::Text choose_map_text("Choose Map", font, 30);
    choose_map_text.setFillColor(sf::Color::White);
    choose_map_text.setPosition(choose_map_button.getPosition().x +
                                    (choose_map_button.getSize().x -
                                     choose_map_text.getGlobalBounds().width) /
                                        2.f,
                                choose_map_button.getPosition().y +
                                    (choose_map_button.getSize().y -
                                     choose_map_text.getGlobalBounds().height) /
                                        2.f -
                                    5.f);

    sf::Text quit_text("Quit", font, 30);
    quit_text.setFillColor(sf::Color::White);
    quit_text.setPosition(
        quit_button.getPosition().x +
            (quit_button.getSize().x - quit_text.getGlobalBounds().width) / 2.f,
        quit_button.getPosition().y +
            (quit_button.getSize().y - quit_text.getGlobalBounds().height) /
                2.f -
            5.f);

    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window.close();
                return menu_result::quit;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mouse_pos =
                    m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
                if (play_button.getGlobalBounds().contains(mouse_pos)) {
                    return menu_result::play;
                }
                if (choose_map_button.getGlobalBounds().contains(mouse_pos)) {
                    return menu_result::choose_map;
                }
                if (quit_button.getGlobalBounds().contains(mouse_pos)) {
                    return menu_result::quit;
                }
            }
        }

        m_window.clear(sf::Color(30, 30, 30));
        m_window.draw(m_background_sprite);
        m_window.draw(title);
        m_window.draw(play_button);
        m_window.draw(choose_map_button);
        m_window.draw(quit_button);
        m_window.draw(play_text);
        m_window.draw(choose_map_text);
        m_window.draw(quit_text);
        m_window.display();
    }

    return menu_result::quit;
}
}  // namespace spsh
