#ifndef PLAYING_STATE
#define PLAYING_STATE
#include <SFML/Graphics.hpp>
#include <chrono>
#include <memory>
#include <thread>
#include <vector>

#include <cmath>
#include <filesystem>
#include <iostream>
#include <random>

#include "avoiding_enemy.hpp"
#include "chasing_enemy.hpp"
#include "enums.hpp"
#include "music_player.hpp"
#include "player_ship.hpp"
#include "powerup.hpp"
#include "sound_player.hpp"
#include "waypoint_enemy.hpp"

using namespace std::chrono_literals;

namespace spsh {
    class playing_state {
    public:
        playing_state(sf::RenderWindow &, map);

        auto run() -> void;

    private:
        auto set_map() -> void;

        auto handle_events() -> void;

        auto update(sf::Time) -> void;

        auto render() -> void;

        [[nodiscard]] auto pause_game() -> bool;

        [[nodiscard]] auto draw_pause_game()
            -> std::pair<sf::RectangleShape, sf::RectangleShape>;

        auto set_background() -> void;

        auto load_map_elements() -> void;

        auto handle_input(bool) -> void;

        auto move_player(sf::Time) -> void;

        auto move_projectiles(sf::Time) -> void;

        auto projectile_action(sf::Time) -> void;

        auto powerup_action() -> void;

        auto enemy_action(sf::Time) -> void;

        auto move_enemy(sf::Time) -> void;

        auto send_enemy_projectile() -> void;

        auto detect_collision() -> void;

        auto handle_collision(std::vector<projectile> &, std::vector<powerup> &)
            -> void;

        [[nodiscard]] auto handle_lifetime() const -> game_state;

        [[nodiscard]] auto handle_game_over() -> bool;

        auto draw_game_over(game_state) -> sf::RectangleShape;

        auto get_closest_bullet_to_enemy() -> std::optional<sf::FloatRect>;

        auto send_asteroid_if_needed() -> void;

        auto spawn_powerup_if_needed() -> void;

        [[nodiscard]] auto generate_random_coords(sf::Vector2u) const -> sf::Vector2f;

    private:
        map m_map;
        const sf::Time c_frame_time = sf::seconds(1.0f / 240.0f);
        sf::Time m_time_of_last_asteroid;
        sf::Clock m_asteroid_clock;
        sf::Clock m_powerup_clock;

        sf::RenderWindow &m_window;
        sf::Sprite m_background_sprite;
        sf::Texture m_asteroid_texture;
        sf::Texture m_background_texture;
        sf::Texture m_btn;
        sf::Font m_font;

        std::map<powerup_type, sf::Texture> m_powerup_textures;

        std::unique_ptr<player_ship> m_player;
        std::unique_ptr<enemy_ship> m_enemy;
        std::vector<projectile> m_projectiles;
        std::vector<powerup> m_powerups;

        music_player<music::game> m_music_player;
        sound_player m_sound_player;
    };
} // namespace spsh

#endif  // PLAYING_STATE
