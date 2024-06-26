#ifndef GAME_HPP
#define GAME_HPP

#include "choose_map_state.hpp"
#include "main_menu.hpp"
#include "music_player.hpp"
#include "playing_state.hpp"

namespace spsh {
class game {
   public:
    game();

    auto run() -> void;

   private:
    sf::RenderWindow m_window;

    music_player<music::menu> m_music_player;
    sound_player m_sound_player;
};
}  // namespace spsh

#endif  // GAME_HPP
