#include <utility>

#include "../incl/player_ship.hpp"

#include <iostream>
#include <SFML/Graphics/Texture.hpp>

namespace spsh {
    player_ship::player_ship(direction t_direction, float t_speed, short t_lives,
                             std::queue<projectile> t_bullets, std::size_t t_init_ammo_cnt)
        : ship_base(t_direction, t_speed, t_lives), m_bullets(std::move(t_bullets)) {
        if (!m_texture.loadFromFile("../media/eagle.png")) {
            std::cerr << "error loading player\n";
        }
        set_texture(m_texture);

        if (!m_font.loadFromFile("../media/sansation.ttf")) {
            std::cerr << "error loading font\n";
        }

        setup_lifecounter_text();
        setup_ammo_text();

        //TODO only for testing purposes
        for (std::size_t i = 0; i < t_init_ammo_cnt; ++i) {
            m_bullets.emplace(direction::up, 2000.0f, projectile_type::rocket);
        }
    }

    auto player_ship::shoot(std::optional<sf::FloatRect> t_nothing) -> std::optional<projectile> {
        if (t_nothing.has_value()) {
            std::cerr << "Fatal developer error: player_ship::shoot should never recive a param value\n";
            exit(3);
        }
        if (m_bullets.empty()) {
            return std::nullopt;
        }
        auto proj = m_bullets.back();
        m_bullets.pop(); //TODO nicer solution that requires no copy?
        auto pos = this->get_position();
        pos.x += static_cast<float>(this->get_texture_size().x) / 4.0f; //TODO this is ugly as fuck but it works
        pos.y -= static_cast<float>(proj.get_texture_size().y);
        proj.set_position(pos);
        return {proj};
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
