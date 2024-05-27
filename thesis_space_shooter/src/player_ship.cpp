#include <utility>

#include "../incl/player_ship.hpp"

#include <iostream>
#include <SFML/Graphics/Texture.hpp>

namespace spsh {
    player_ship::player_ship(const direction t_direction, const player_details &t_player_details)
        : ship_base(t_direction, t_player_details.speed, t_player_details.lives), m_bullet_speed(t_player_details.bullet_speed),
          m_is_boost_active(false), m_boosted_speed(t_player_details.boost_multiplier * t_player_details.speed),
          m_original_speed(t_player_details.speed),
          m_speed_boost_duration(sf::seconds(t_player_details.boost_duration)) {
        switch (t_player_details.current_map) {
            case map::first: {
                if (!m_texture.loadFromFile("../media/ship0.png")) {
                    std::cerr << "error loading player\n";
                    exit(errors::ASSET_LOAD_ERROR);
                }
                break;
            }
            case map::second: {
                if (!m_texture.loadFromFile("../media/ship1.png")) {
                    std::cerr << "error loading player\n";
                    exit(errors::ASSET_LOAD_ERROR);
                }
                break;
            }
            case map::third: {
                if (!m_texture.loadFromFile("../media/ship2.png")) {
                    std::cerr << "error loading player\n";
                    exit(errors::ASSET_LOAD_ERROR);
                }
                break;
            }
        }
        set_texture(m_texture);

        if (!m_font.loadFromFile("../media/sansation.ttf")) {
            std::cerr << "error loading font\n";
            exit(errors::ASSET_LOAD_ERROR);
        }

        if (!m_bullet_texture.loadFromFile("../media/player_missile.png")) {
            std::cerr << "error loading bullet\n";
            exit(errors::ASSET_LOAD_ERROR);
        }

        setup_lifecounter_text();
        setup_ammo_text();

        for (std::size_t i = 0; i < t_player_details.bullets; ++i) {
            m_bullets.emplace(direction::up, m_bullet_speed, projectile_type::rocket);
        }
    }

    auto player_ship::shoot(const std::optional<sf::FloatRect> t_nothing) -> std::optional<projectile> {
        if (t_nothing.has_value()) {
            std::cerr << "Fatal developer error: player_ship::shoot should never receive a param value\n";
            exit(errors::OPTIONAL_ERROR);
        }
        if (m_bullets.empty()) {
            return std::nullopt;
        }
        auto &&proj = std::move(m_bullets.back());
        proj.set_texture(m_bullet_texture);
        m_bullets.pop();
        auto pos = this->get_position();
        pos.x += static_cast<float>(this->get_texture_size().x) / 2.0f - static_cast<float>(proj.get_texture_size().x) /
                2.0f;
        pos.y -= this->get_reduced_texture_rect().height / 2.0f;
        proj.set_position(pos);
        return {std::move(proj)};
    }

    auto player_ship::add_ammo(const short t_amount) -> void {
        for (short i = 0; i < t_amount; ++i) {
            m_bullets.emplace(direction::up, m_bullet_speed, projectile_type::rocket);
        }
    }

    auto player_ship::start_speed_boost() -> void {
        m_speed_boost_timer.restart();
        set_speed(m_boosted_speed);
        m_is_boost_active = true;
    }

    auto player_ship::handle_speed_boost() -> void {
        if (m_speed_boost_timer.getElapsedTime() < m_speed_boost_duration && m_is_boost_active) {
            return;
        }
        set_speed(m_original_speed);
        m_is_boost_active = false;
    }

    auto player_ship::get_lifecounter_text() -> sf::Text {
        update_lifecounter_text();
        return m_lifecounter_text;
    }

    auto player_ship::get_ammo_text() -> sf::Text {
        update_ammo_text();
        return m_ammo_text;
    }

    auto player_ship::setup_lifecounter_text() -> void {
        m_lifecounter_text.setFont(m_font);
        m_lifecounter_text.setPosition(10.0f, 10.0f);
        m_lifecounter_text.setCharacterSize(16);
    }

    auto player_ship::setup_ammo_text() -> void {
        m_ammo_text.setFont(m_font);
        m_ammo_text.setPosition(10.0f, 30.0f);
        m_ammo_text.setCharacterSize(16);
    }

    auto player_ship::update_lifecounter_text() -> void {
        m_lifecounter_text.setString(std::to_string(m_lives) + " lives");
    }

    auto player_ship::update_ammo_text() -> void {
        m_ammo_text.setString(std::to_string(m_bullets.size()) + " rockets");
    }
} // spsh
