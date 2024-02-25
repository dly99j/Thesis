#ifndef PLAYER_SHIP_HPP
#define PLAYER_SHIP_HPP
#include <optional>
#include <queue>

#include "movable.hpp"
#include "projectile.hpp"

namespace spsh {
    class player_ship : public movable {
    public:
        //TODO default param is temporary right now, might need fix
        explicit player_ship(direction, float, std::queue<projectile> = {});

        [[nodiscard]]
        auto shoot() -> std::optional<projectile>;

        auto put_back_on_map(const std::unique_ptr<sf::Vector2u>& t_window_size) -> void;

        auto decrease_life(short = 1) -> void;

        auto is_alive() const -> bool;

    private:
        std::queue<projectile> m_bullets;
        short m_lives;
    };
} // spsh

#endif //PLAYER_SHIP_HPP
