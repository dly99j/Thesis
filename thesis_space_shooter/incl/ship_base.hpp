#ifndef SHIP_BASE_HPP
#define SHIP_BASE_HPP
#include "movable.hpp"
#include "projectile.hpp"
#include "sound_player.hpp"

namespace spsh {
    class ship_base : public movable {
    public:
        explicit ship_base(direction, float, short);

        virtual ~ship_base() = default;

        [[nodiscard]]
        auto virtual shoot(std::optional<sf::FloatRect>) -> std::optional<projectile> = 0;

        auto virtual put_back_on_map(const std::unique_ptr<sf::Vector2u> &) -> void final;

        auto decrease_life(short = 1) -> void;

        auto increase_life(short = 1) -> void;

        [[nodiscard]]
        auto get_lives() const -> short;

        [[nodiscard]]
        auto is_alive() const -> bool;

    protected:
        sf::Texture m_texture;
        short m_lives;
    };
} // spsh

#endif //SHIP_BASE_HPP
