#ifndef MOVABLE_HPP
#define MOVABLE_HPP
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
//#include "player_ship.hpp"
#include "enums.hpp"

namespace spsh {

    class movable {
    public:
        explicit movable(direction, float);

        virtual ~movable();

        [[nodiscard]]
        auto operator==(const movable& other) const -> bool;

        [[nodiscard]]
        auto get_speed() const -> float;

        auto set_speed(float) -> void;

        [[nodiscard]]
        auto get_direction() const -> direction;

        [[nodiscard]]
        auto get_position() const -> sf::Vector2f;

        [[nodiscard]]
        auto get_reduced_texture_rect() const -> sf::FloatRect;

        [[nodiscard]]
        auto get_texture_rect() const -> sf::FloatRect;

        auto get_texture_size() const -> sf::Vector2u;

        auto set_dierction(direction) -> void;

        auto set_texture(sf::Texture&) -> void;

        auto set_position(sf::Vector2f) -> void;

        virtual auto draw(sf::RenderTarget&) -> void;

        auto calculate_move() const -> sf::Vector2f;

        auto move(sf::Vector2f) -> void;

        [[nodiscard]]
        auto is_off_map(const std::unique_ptr<sf::Vector2u>& t_window_size) const -> bool;

    protected:
        //auto virtual load_resources() -> void = 0;

    protected:
        sf::Sprite m_sprite;
        direction m_direction;
        float m_speed;
    };
} // spsh

#endif //MOVABLE_HPP
