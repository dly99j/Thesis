#include "../incl/game.hpp"

#include <filesystem>
#include <iostream>

namespace spsh {
    game::game()
        : m_window(sf::VideoMode(640, 480), "SpaceShooter", sf::Style::Close)
          , m_player_texture()
          , m_projectile_texture()
          , m_player(direction::stationary, 5000.0f) {
        if (!m_player_texture.loadFromFile("../media/eagle.png")) {
            std::cerr << "error loading player\n";
        }
        if (!m_projectile_texture.loadFromFile("../media/basic_red_dot.png")) {
            std::cerr << "error loading bullet\n";
        }

        m_player.set_texture(m_player_texture);
        m_player.set_position(100.0f, 100.0f);
    }

    auto game::run() -> void {
        sf::Clock clock;
        auto time_since_update = sf::Time::Zero;

        while (m_window.isOpen()) {
            auto delta_time = clock.restart();
            time_since_update += delta_time;
            while (time_since_update > c_frame_time) {
                time_since_update -= c_frame_time;
                handle_events();
                update(delta_time);
            }
            render();
        }
    }

    auto game::handle_events() -> void {
        sf::Event event{};
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) {
                handle_input(event.key.code, true);
            } else if (event.type == sf::Event::KeyReleased) {
                handle_input(event.key.code, false);
            } else if (event.type == sf::Event::Closed) {
                m_window.close();
            } //TODO else error handling(?)
        }
    }

    auto game::update(sf::Time t_delta_time) -> void {
        move_player(t_delta_time);
        move_projectiles(t_delta_time);
    }

    auto game::render() -> void {
        m_window.clear();
        m_player.draw(m_window);
        for (auto&& i : m_projectiles) {
            i.draw(m_window);
        }
        m_window.display();
    }

    auto game::handle_input(sf::Keyboard::Key t_key, bool t_is_pressed) -> void {
        if (!t_is_pressed) {
            m_player.set_dierction(direction::stationary);
        } else if (t_key == sf::Keyboard::W) {
            m_player.set_dierction(direction::up);
        } else if (t_key == sf::Keyboard::D) {
            m_player.set_dierction(direction::right);
        } else if (t_key == sf::Keyboard::S) {
            m_player.set_dierction(direction::down);
        } else if (t_key == sf::Keyboard::A) {
            m_player.set_dierction(direction::left);
        } else if (t_key == sf::Keyboard::Space) {
            auto&& proj = m_player.shoot();
            if (proj.has_value()) {
                proj.value().set_texture(m_projectile_texture);
                m_projectiles.push_back(proj.value());
            }
        }
    }

    auto game::move_player(sf::Time t_delta_time) -> void {
        sf::Vector2f movement;
        if (m_player.get_direction() == direction::up) {
            movement.y -= m_player.get_speed();
        } else if (m_player.get_direction() == direction::right) {
            movement.x += m_player.get_speed();
        } else if (m_player.get_direction() == direction::down) {
            movement.y += m_player.get_speed();
        } else if (m_player.get_direction() == direction::left) {
            movement.x -= m_player.get_speed();
        } else if (m_player.get_direction() == direction::stationary) {
            //TODO what do i do with this?
            movement.x += 0.0f;
        } //TODO else error handling(?)
        m_player.move(movement * t_delta_time.asSeconds());
    }

    auto game::move_projectiles(sf::Time t_delta_time) -> void {
        for (auto&& i : m_projectiles) {
            sf::Vector2f movement;
            if (i.get_direction() == direction::up) {
                movement.y -= i.get_speed();
            } else if (i.get_direction() == direction::right) {
                movement.x += i.get_speed();
            } else if (i.get_direction() == direction::down) {
                movement.y += i.get_speed();
            } else if (i.get_direction() == direction::left) {
                movement.x -= i.get_speed();
            } else if (i.get_direction() == direction::stationary) {
                //TODO what do i do with this?
                movement.x += 0.0f;
            } //TODO else error handling(?)
            i.move(movement * t_delta_time.asSeconds());
        }
    }
} // spsh
