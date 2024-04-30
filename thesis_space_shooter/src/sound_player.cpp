#include "../incl/sound_player.hpp"

namespace spsh {
    sound_player::sound_player(const std::initializer_list<sound_effect> t_sounds) {
        for (const auto sound : t_sounds) {
            loader(sound);
        }
    }

    auto sound_player::play(const sound_effect t_sound) -> void {
        if (!m_sounds.contains(t_sound)) {
            std::cerr << "error: instance of sound_player tried to play a sound it doesn't have\n";
            return;
        }

        m_sounds[t_sound].second->play();
        std::clog << m_sounds[t_sound].second->getStatus() << " play() \n";
    }

    auto sound_player::loader(const sound_effect t_sound) -> void {
        switch (t_sound) {
            case sound_effect::player_fire:
                load(t_sound, "../media/audio/player_fire.wav");
            break;
            case sound_effect::player_hit:
                load(t_sound, "../media/audio/player_hit.wav");
                break;
            case sound_effect::enemy_fire:
                load(t_sound, "../media/audio/enemy_fire.wav");
                break;
            case sound_effect::enemy_hit:
                load(t_sound, "../media/audio/enemy_hit.wav");
                break;
            case sound_effect::button:
                load(t_sound, "../media/audio/button.wav");
                break;
            case sound_effect::powerup:
                load(t_sound, "../media/audio/powerup.wav");
                break;
            default:
                std::unreachable();
        }
    }

    auto sound_player::load(const sound_effect t_sound, const std::string& t_path) -> void {
        sf::SoundBuffer sound_buf;
        if (!sound_buf.loadFromFile(t_path)) {
            std::cerr << "error: sound_effect couldn't be loaded\n";
            exit(errors::SOUND_ERROR);
        }
        sf::Sound sound;
        m_sounds[t_sound] = std::move(std::make_pair(std::make_unique<sf::SoundBuffer>(sound_buf), std::make_unique<sf::Sound>(sound)));
        m_sounds[t_sound].second->setBuffer(*m_sounds[t_sound].first);
    }
} // spsh