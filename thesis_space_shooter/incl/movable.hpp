#ifndef MOVABLE_HPP
#define MOVABLE_HPP
#include <SFML/Graphics/Sprite.hpp>

namespace spsh {
    enum class direction {
        up, right, down, left, stationary
    };

    class movable {
    public:
        explicit movable(direction, float);

        virtual ~movable();

        [[nodiscard]]
        auto get_speed() const -> const float;

        [[nodiscard]]
        auto get_direction() const -> const direction;

        [[nodiscard]]
        auto get_position() const -> const sf::Vector2f;

        auto set_dierction(direction) -> void;

        auto set_texture(sf::Texture&) -> void;

        //TODO remove float variant possibly?
        auto set_position(float, float) -> void;

        //TODO copy vs reference?
        auto set_position(sf::Vector2f) -> void;

        virtual auto draw(sf::RenderTarget&) -> void;

        auto move(sf::Vector2f) -> void;
    private:
        sf::Sprite m_object;
        spsh::direction m_direction;
        const float m_speed;
    };
} // spsh

#endif //MOVABLE_HPP
