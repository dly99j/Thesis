#include "../incl/movable.hpp"

#include <iostream>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace spsh {
    movable::movable(direction t_direction, float t_speed)
        : m_texture(), m_direction(t_direction), m_speed(t_speed) {
    }

    movable::~movable() = default;

    auto movable::operator==(const movable& other) const -> bool {
        return this->get_direction() == other.get_direction() &&
               this->get_speed() == other.get_speed() &&
               this->get_texture_rect() == other.get_texture_rect() &&
               this->get_position() == other.get_position();
    }

    auto movable::get_speed() const -> float {
        return m_speed;
    }

    auto movable::get_direction() const -> direction {
        return m_direction;
    }

    auto movable::get_position() const -> sf::Vector2f {
        return m_texture.getPosition();
    }

    //TODO we should probably make the rect smaller
    auto movable::get_texture_rect() const -> sf::FloatRect {
        const auto& [top, left] = get_position();
        const auto& rect = m_texture.getTextureRect();
        const auto& width = static_cast<float>(rect.width);
        const auto& height = static_cast<float>(rect.width);
        return {left - width/4.0f, top - height/4.0f, width/2.0f, height/4.0f*3.0f};
    }

    auto movable::get_texture_size() const -> sf::Vector2u {
        return m_texture.getTexture()->getSize();
    }

    auto movable::set_dierction(direction t_direction) -> void {
        m_direction = t_direction;
    }

    auto movable::set_texture(sf::Texture& t_texture) -> void {
        m_texture.setTexture(t_texture);
    }

    auto movable::set_position(sf::Vector2f t_position) -> void {
        m_texture.setPosition(t_position);
    }

    auto movable::draw(sf::RenderTarget& t_target) -> void {
        t_target.draw(m_texture);
    }

    auto movable::move(sf::Vector2f t_movement) -> void {
        m_texture.move(t_movement);
    }

    auto movable::is_off_map(const std::unique_ptr<sf::Vector2u>& t_window_size) const -> bool {
        auto [x, y] = get_position();
        if (x < 0.0f || y < 0.0f) {
            return true;
        }
        if (x + static_cast<float>(get_texture_size().x) > static_cast<float>(t_window_size->x) ||
            y + static_cast<float>(get_texture_size().y) > static_cast<float>(t_window_size->y)) {
            return true;
        }
        return false;
    }
} // spsh
