#include "../incl/movable.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace spsh {
    movable::movable(direction t_direction, float t_speed)
        : m_object(), m_direction(t_direction), m_speed(t_speed) {
    }

    movable::~movable() = default;

    auto movable::get_speed() const -> const float {
        return m_speed;
    }

    auto movable::get_direction() const -> const direction {
        return m_direction;
    }

    auto movable::get_position() const -> const sf::Vector2f {
        return m_object.getPosition();
    }

    auto movable::set_dierction(direction t_direction) -> void {
        m_direction = t_direction;
    }

    auto movable::set_texture(sf::Texture& t_texture) -> void {
        m_object.setTexture(t_texture);
    }

    auto movable::set_position(float t_x, float t_y) -> void {
        m_object.setPosition(t_x, t_y);
    }

    auto movable::set_position(sf::Vector2f t_position) -> void {
        m_object.setPosition(t_position);
    }

    auto movable::draw(sf::RenderTarget& t_target) -> void {
        t_target.draw(m_object);
    }

    auto movable::move(sf::Vector2f t_movement) -> void {
        m_object.move(t_movement);
    }
} // spsh
