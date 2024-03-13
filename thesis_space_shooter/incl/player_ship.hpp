#ifndef PLAYER_SHIP_HPP
#define PLAYER_SHIP_HPP
#include <optional>
#include <queue>
#include <SFML/Graphics/Text.hpp>

#include "projectile.hpp"
#include "ship_base.hpp"

namespace spsh {
    class player_ship : public ship_base {
    public:
        //TODO default param is temporary right now, might need fix
        explicit player_ship(direction, float, short = 3, std::queue<projectile>  = {}, std::size_t = 10);

        [[nodiscard]]
        auto shoot(std::optional<sf::FloatRect>) -> std::optional<projectile> override;

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
        sf::Font m_font;
        sf::Text m_lifecounter_text;
        sf::Text m_ammo_text;

        std::queue<projectile> m_bullets;
    };
} // spsh

#endif //PLAYER_SHIP_HPP
