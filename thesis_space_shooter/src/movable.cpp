#include "../incl/movable.hpp"

#include <forward_list>
#include <iostream>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace spsh {
    movable::movable(const direction t_direction, const float t_speed)
        : m_direction(t_direction), m_speed(t_speed) {
    }

    movable::~movable() = default;

    auto movable::operator==(const movable &other) const -> bool {
        return this->get_direction() == other.get_direction() &&
               this->get_speed() == other.get_speed() &&
               this->get_reduced_texture_rect() == other.get_reduced_texture_rect() &&
               this->get_position() == other.get_position();
    }

    auto movable::get_speed() const -> float {
        return m_speed;
    }

    auto movable::set_speed(const float t_speed) -> void {
        m_speed = t_speed;
    }

    auto movable::get_direction() const -> direction {
        return m_direction;
    }

    auto movable::get_position() const -> sf::Vector2f {
        return m_sprite.getPosition();
    }

    //TODO we should probably make the rect smaller
    auto movable::get_reduced_texture_rect() const -> sf::FloatRect {
        const auto &[left, top] = get_position();
        const auto &rect = m_sprite.getTextureRect();
        const auto &width = static_cast<float>(rect.width);
        const auto &height = static_cast<float>(rect.height);
        //return {left - width / 4.0f, top - height / 1.0f, width / 2.0f, height / 4.0f * 3.0f};
        //if (dynamic_cast<const spsh::player_ship*>(this) != nullptr) {
        //    return {left + width / 4.0f, top / 4.0f, width / 2.0f, height * 0.75f};
        //}
        return {left + width / 4.0f, top, width / 2.0f, height * 0.8f};
    }

    auto movable::get_texture_rect() const -> sf::FloatRect {
        const auto &[left, top] = get_position();
        const auto &rect = m_sprite.getTextureRect();
        //const auto& left = static_cast<float>(rect.left);
        //const auto& top = static_cast<float>(rect.top);
        const auto &width = static_cast<float>(rect.width);
        const auto &height = static_cast<float>(rect.height);
        return {left, top, width, height};
    }

    auto movable::get_texture_size() const -> sf::Vector2u {
        return m_sprite.getTexture()->getSize();
    }

    auto movable::set_dierction(const direction t_direction) -> void {
        m_direction = t_direction;
    }

    auto movable::set_texture(const sf::Texture &t_texture) -> void {
        m_sprite.setTexture(t_texture);
    }

    auto movable::set_position(const sf::Vector2f t_position) -> void {
        m_sprite.setPosition(t_position);
    }

    auto movable::draw(sf::RenderTarget &t_target) -> void {
        t_target.draw(m_sprite);
        //auto&& s = sf::RectangleShape({get_reduced_texture_rect().width, get_reduced_texture_rect().height});
        //s.setPosition(get_reduced_texture_rect().left, get_reduced_texture_rect().top);
        //s.setFillColor(sf::Color::White);
        //t_target.draw(s);
    }

    auto movable::calculate_move() const -> sf::Vector2f {
        sf::Vector2f movement;
        constexpr float sqrt_two = 1.41421f;

        const auto move_up = [&](const bool is_diag) {
            is_diag ? movement.y -= get_speed() / sqrt_two : movement.y -= get_speed();
        };
        const auto move_right = [&](const bool is_diag) {
            is_diag ? movement.x += get_speed() / sqrt_two : movement.x += get_speed();
        };
        const auto move_down = [&](const bool is_diag) {
            is_diag ? movement.y += get_speed() / sqrt_two : movement.y += get_speed();
        };
        const auto move_left = [&](const bool is_diag) {
            is_diag ? movement.x -= get_speed() / sqrt_two : movement.x -= get_speed();
        };

        if (get_direction() == direction::up) {
            move_up(false);
        } else if (get_direction() == direction::right) {
            move_right(false);
        } else if (get_direction() == direction::down) {
            move_down(false);
        } else if (get_direction() == direction::left) {
            move_left(false);
        } else if (get_direction() == direction::up_left) {
            move_up(true);
            move_left(true);
        } else if (get_direction() == direction::up_right) {
            move_up(true);
            move_right(true);
        } else if (get_direction() == direction::down_left) {
            move_down(true);
            move_left(true);
        } else if (get_direction() == direction::down_right) {
            move_down(true);
            move_right(true);
        }
        return movement;
    }

    auto movable::move(const sf::Vector2f t_movement) -> void {
        m_sprite.move(t_movement);
    }

    auto movable::is_off_map(const std::unique_ptr<sf::Vector2u> &t_window_size) const -> bool {
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
