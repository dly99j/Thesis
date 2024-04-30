#include "../incl/game.hpp"
#include "../incl/sound_player.hpp"

namespace spsh {
    game::game() : m_window(sf::VideoMode(1280, 960), "SpaceShooter", sf::Style::Close) {}
    auto game::run() -> void {
        spsh::sound_player s{spsh::sound_effect::enemy_hit};
        s.play(spsh::sound_effect::enemy_hit);
        s.play(spsh::sound_effect::enemy_fire);
        music_player<music::menu> mp;
        //mp.play();
        auto curr_map = map::first;
        while (m_window.isOpen()) {
            sf::Event event{};
            while (m_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    m_window.close();
                }

                main_menu mm(m_window);
                const auto result = mm.display();

                switch (result) {
                    case menu_result::play: {
                        mp.stop();
                        playing_state ps(m_window, curr_map);
                        ps.run();
                        mp.play();
                        break;
                    }
                    case menu_result::choose_map: {
                        choose_map_state cms(m_window);
                        curr_map = cms.display().value_or(curr_map);
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
