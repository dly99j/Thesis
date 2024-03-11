#ifndef GAME_HPP
#define GAME_HPP
#include <memory>
#include <SFML/Graphics.hpp>
#include <vector>

#include "enemy_ship.hpp"
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

        auto handle_input(bool) -> void;

        auto move_player(sf::Time) -> void;

        auto move_projectiles(sf::Time) -> void;

        auto move_enemy(sf::Time) -> void;

        auto detect_collision() -> void;

        auto handle_collision(std::vector<projectile>&) -> void;

        auto handle_lifetime() -> void;

        auto send_asteroid_if_needed() -> void;

        [[nodiscard]]
        auto generate_asteroid_x() const -> float;

    private:
        const sf::Time c_frame_time = sf::seconds(1.0f / 300.0f);
        sf::Time m_time_since_startup;
        sf::Clock m_global_clock; //TODO better name?

        sf::RenderWindow m_window;
        sf::Texture m_asteroid_texture;

        player_ship m_player;
        enemy_ship m_enemy;
        std::vector<projectile> m_projectiles;
    };
} // spsh

#endif //GAME_HPP
