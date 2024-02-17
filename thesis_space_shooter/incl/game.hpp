#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "player_ship.hpp"

namespace spsh {

    class game {
    public:
        game();

        auto run() -> void;

    private: /*functions*/
        auto handle_events() -> void;

        auto update(sf::Time) -> void;

        auto render() -> void;

        auto handle_input(sf::Keyboard::Key, bool) -> void;

        auto move_player(sf::Time) -> void;
        auto move_projectiles(sf::Time) -> void;

    private: /*variables*/
        const sf::Time c_frame_time = sf::seconds(1.0f / 60.0f);

        sf::RenderWindow m_window;
        sf::Texture m_player_texture;
        sf::Texture m_projectile_texture;

        player_ship m_player;
        std::vector<projectile> m_projectiles;
    };
} // spsh

#endif //GAME_HPP
