#ifndef MOVABLE_HPP
#define MOVABLE_HPP
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace spsh {
    enum class direction {
        up, up_right, right, down_right, down, down_left, left, up_left, stationary
    };

    //Stores the position and the texture size of the player
    using player_info = std::pair<sf::Vector2f, sf::FloatRect>;

    class movable {
    public:
        explicit movable(direction, float);

        virtual ~movable();

        [[nodiscard]]
        auto operator==(const movable& other) const -> bool;

        [[nodiscard]]
        auto get_speed() const -> float;

        [[nodiscard]]
        auto get_direction() const -> direction;

        [[nodiscard]]
        auto get_position() const -> sf::Vector2f;

        [[nodiscard]]
        auto get_texture_rect() const -> sf::FloatRect;

        auto get_texture_size() const -> sf::Vector2u;

        auto set_dierction(direction) -> void;

        auto set_texture(sf::Texture&) -> void;

        //TODO copy vs reference?
        auto set_position(sf::Vector2f) -> void;

        virtual auto draw(sf::RenderTarget&) -> void;

        auto calculate_move() const -> sf::Vector2f;

        auto move(sf::Vector2f) -> void;

        [[nodiscard]]
        auto is_off_map(const std::unique_ptr<sf::Vector2u>& t_window_size) const -> bool;

    private:
        sf::Sprite m_sprite;
        direction m_direction;
        //TODO this was originally const but remove_if needs assignment operator. fix? or is it good as non const?
        float m_speed;
    };
} // spsh

#endif //MOVABLE_HPP
