#ifndef POWERUP_HPP
#define POWERUP_HPP
#include "movable.hpp"
#include "player_ship.hpp"
#include "enums.hpp"
#include <random>
#include <cmath>
#include <utility>
#include <iostream>

namespace spsh {

    class powerup : public movable {
    public:
        explicit powerup(powerup_type t_type);

        auto apply_effect(const std::unique_ptr<player_ship> &) const -> void;

        auto static generate_powerup(sf::Vector2f, sf::Clock &,
                                     std::map<powerup_type, sf::Texture> &) -> std::optional<powerup>;

    private:
        auto static generate_object(powerup_type, sf::Vector2f, std::map<powerup_type, sf::Texture> &) -> powerup;

    private:
        powerup_type m_type;
    };
} // namespace spsh

#endif // POWERUP_HPP
