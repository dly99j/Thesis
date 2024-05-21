#ifndef MUSIC_PLAYER_HPP
#define MUSIC_PLAYER_HPP

#include <map>
#include <iostream>
#include <memory>
#include <utility>

#include "enums.hpp"
#include "config.hpp"
#include <SFML/Audio.hpp>


namespace spsh {

template <music>
class music_player {
public:
    music_player();

    auto play() -> void;

    auto pause() -> void;

    auto stop() -> void;

private:
    auto load() -> void;

private:
    sf::Music m_music;
};

template<music type>
music_player<type>::music_player() {
    load();
    m_music.setVolume(constants::music_volume);
}

template<music type>
auto music_player<type>::load() -> void {
    switch (type) {
        case music::menu: {
            if (!m_music.openFromFile("../media/menu_music.ogg")) {
                std::cerr << "error loading menu music\n";
                exit(errors::ASSET_LOAD_ERROR);
            }
            m_music.setLoop(true);
            break;
        }
        case music::game: {
            if (!m_music.openFromFile("../media/ingame_music.ogg")) {
                std::cerr << "error loading in game music\n";
                exit(errors::ASSET_LOAD_ERROR);
            }
            m_music.setLoop(true);
            break;
        }
        default:
            std::unreachable();
    }
}

template<music type>
auto music_player<type>::play() -> void {
    m_music.play();
}

template<music type>
auto music_player<type>::pause() -> void {
    m_music.pause();
}

template<music type>
auto music_player<type>::stop() -> void {
    m_music.stop();
}
} // spsh

#endif //MUSIC_PLAYER_HPP
