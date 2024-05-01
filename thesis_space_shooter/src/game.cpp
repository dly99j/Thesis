#include "../incl/game.hpp"

namespace spsh {
    game::game() : m_window(sf::VideoMode(1280, 960), "SpaceShooter", sf::Style::Close),
                   m_sound_player({sound_effect::button}){}
    auto game::run() -> void {
        m_music_player.play();
        auto curr_map = map::first;
        while (m_window.isOpen()) {
            sf::Event event{};
            while (m_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    m_window.close();
                }

                main_menu mm(m_window);
                const auto result = mm.display();
                m_sound_player.play(sound_effect::button);

                switch (result) {
                    case menu_result::play: {
                        m_music_player.stop();
                        playing_state ps(m_window, curr_map);
                        ps.run();
                        //Has to be played here because the playing state instance ceases to exist
                        m_sound_player.play(sound_effect::button);
                        m_music_player.play();
                        break;
                    }
                    case menu_result::choose_map: {
                        choose_map_state cms(m_window);
                        if (auto opt_map = cms.display(); opt_map.has_value()) {
                            m_sound_player.play(sound_effect::button);
                            curr_map = opt_map.value();
                        }
                        break;
                    }
                    case menu_result::quit:
                        m_window.close();
                        break;
                    default:
                        std::unreachable();
                }
            }
        }
    }
} // namespace spsh
