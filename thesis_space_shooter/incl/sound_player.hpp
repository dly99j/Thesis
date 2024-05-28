#ifndef SOUND_PLAYER_HPP
#define SOUND_PLAYER_HPP
#include <SFML/Audio.hpp>
#include <iostream>
#include <map>
#include <memory>
#include <utility>

#include "config.hpp"
#include "enums.hpp"

namespace spsh {
class sound_player {
   public:
    sound_player() = default;

    sound_player(std::initializer_list<sound_effect>);

    auto play(sound_effect) -> void;

   private:
    auto loader(sound_effect) -> void;

    auto load_effect(sound_effect, const std::string&) -> void;

   private:
    std::map<sound_effect, std::pair<sf::SoundBuffer, sf::Sound> > m_sounds;
};
}  // namespace spsh

#endif  //SOUND_PLAYER_HPP
