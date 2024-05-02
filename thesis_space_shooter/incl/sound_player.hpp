#ifndef SOUND_PLAYER_HPP
#define SOUND_PLAYER_HPP
#include <map>
#include <iostream>
#include <memory>
#include <utility>
#include <SFML/Audio.hpp>

#include "enums.hpp"
#include "config.hpp"

namespace spsh {

class sound_player {
public:
    sound_player() = default;

    explicit sound_player(std::initializer_list<sound_effect>);

    auto play(sound_effect) -> void;

private:
    auto loader(sound_effect) -> void;

    auto load_effect(sound_effect, const std::string&) -> void;

private:
    std::map<sound_effect, std::pair<sf::SoundBuffer, sf::Sound>> m_sounds;
};

} // spsh

#endif //SOUND_PLAYER_HPP
