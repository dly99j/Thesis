#include <utility>

#include "../incl/player_ship.hpp"

#include <iostream>
#include <SFML/Graphics/Texture.hpp>

namespace spsh {
    player_ship::player_ship(direction t_direction, float t_speed,
        std::queue<projectile> t_bullets, short t_lives, std::size_t t_init_ammo_cnt)
        : movable(t_direction, t_speed), m_bullets(std::move(t_bullets)), m_lives(t_lives) {

        if (!m_player_texture.loadFromFile("../media/eagle.png")) {
            std::cerr << "error loading player\n";
        }
        set_texture(m_player_texture);

        if (!m_font.loadFromFile("../media/sansation.ttf")) {
            std::cerr << "error loading font\n";
        }

        setup_lifecounter_text();
        setup_ammo_text();

        //TODO only for testing purposes
        for (std::size_t i = 0; i < t_init_ammo_cnt; ++i) {
            m_bullets.emplace(direction::up, 2000.0f);
        }
    }

    auto player_ship::shoot() -> std::optional<projectile> {
        if (m_bullets.empty()) {
            return {};
        }
        auto proj = m_bullets.back();
        m_bullets.pop(); //TODO nicer solution that requires no copy?
        auto pos = this->get_position();
        std::clog << pos.x << "   " << pos.y << std::endl;
        pos.x += static_cast<float>(this->get_texture_size().x) / 4.0f; //TODO this is ugly as fuck but it works
        pos.y -= static_cast<float>(proj.get_texture_size().y);
        proj.set_position(pos);
        return {proj};
    }

    auto player_ship::put_back_on_map(const std::unique_ptr<sf::Vector2u>& t_window_size) -> void {
        if (!is_off_map(t_window_size)) {
            return;
        }

        const auto window_x = static_cast<float>(t_window_size->x);
        const auto window_y = static_cast<float>(t_window_size->y);
        const auto texture_x = static_cast<float>(get_texture_size().x);
        const auto texture_y = static_cast<float>(get_texture_size().y);

        if (get_position().x < 0.0f) {
            set_position({0.0f, get_position().y});
        }
        if (get_position().y < 0.0f) {
            set_position({get_position().x, 0.0f});
        }
        if (get_position().x + texture_x > window_x) {
            set_position({window_x - texture_x, get_position().y});
        }
        if (get_position().y + texture_y > window_y) {
            set_position({get_position().x, window_y - texture_y});
        }
    }

    auto player_ship::decrease_life(short t_decrease_by) -> void {
        m_lives -= t_decrease_by;
    }

    auto player_ship::get_lives() const -> short {
        return m_lives;
    }

    auto player_ship::is_alive() const -> bool {
        return m_lives > 0;
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
