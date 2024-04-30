#ifndef GAME_HPP
#define GAME_HPP

#include "playing_state.hpp"
#include "main_menu.hpp"
#include "choose_map_state.hpp"
#include "music_player.hpp"


namespace spsh {
    class game {
    public:
        game();

        auto run() -> void;

    private:
        sf::RenderWindow m_window;
    };
} // namespace spsh

#endif // GAME_HPP
