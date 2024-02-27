#ifndef PLAYER_SHIP_HPP
#define PLAYER_SHIP_HPP
#include <optional>
#include <queue>
#include <SFML/Graphics/Text.hpp>

#include "movable.hpp"
#include "projectile.hpp"

namespace spsh {
    class player_ship : public movable {
    public:
        //TODO default param is temporary right now, might need fix
        explicit player_ship(direction, float, std::queue<projectile> = {}, short = 3, std::size_t = 10);

        [[nodiscard]]
        auto shoot() -> std::optional<projectile>;

        auto put_back_on_map(const std::unique_ptr<sf::Vector2u>& t_window_size) -> void;

        auto decrease_life(short = 1) -> void;

        [[nodiscard]]
        auto get_lives() const -> short;

        [[nodiscard]]
        auto is_alive() const -> bool;

        [[nodiscard]]
        auto get_lifecounter_text() -> sf::Text;

        [[nodiscard]]
        auto get_ammo_text() -> sf::Text;

    private:
        auto setup_lifecounter_text() -> void;

        auto setup_ammo_text() -> void;

        auto update_lifecounter_text() -> void;

        auto update_ammo_text() -> void;

    private:
        sf::Texture m_player_texture;
        sf::Font m_font;
        sf::Text m_lifecounter_text;
        sf::Text m_ammo_text;

        std::queue<projectile> m_bullets;
        short m_lives;
    };
} // spsh

#endif //PLAYER_SHIP_HPP
