#include "../incl/game.hpp"

#include <cmath>
#include <filesystem>
#include <iostream>
#include <random>

namespace spsh {
    game::game()
        : m_time_since_startup(sf::Time::Zero)
          , m_window(sf::VideoMode(640, 480), "SpaceShooter", sf::Style::Close)
          , m_player(direction::stationary, 1000.0f) {


        if (!m_asteroid_texture.loadFromFile("../media/basic_blue_dot.png")) {
            std::cerr << "error loading bullet\n";
        }

        m_global_clock.restart();

        auto window_width = static_cast<float>(m_window.getSize().x);
        auto window_height = static_cast<float>(m_window.getSize().y);
        //TODO center correctly
        m_player.set_position({window_width / 2.0f, window_height - window_height / 10.0f});
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
            detect_collision();
            handle_lifetime();
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
        send_asteroid_if_needed();
    }

    auto game::render() -> void {
        m_window.clear();
        m_player.draw(m_window);
        for (auto&& i: m_projectiles) {
            i.draw(m_window);
        }
        m_window.draw(m_player.get_lifecounter_text());
        m_window.draw(m_player.get_ammo_text());
        m_window.display();
    }

    //TODO completely rewrite if I want it to go diagonally
    // https://en.sfml-dev.org/forums/index.php?topic=22285.0
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
                m_projectiles.push_back(proj.value());
            }
        }
    }

    auto game::move_player(sf::Time t_delta_time) -> void {
        sf::Vector2f movement;
        //auto move_up = [&](){movement.y -= m_player.get_speed();};
        //auto move_right = [&](){movement.x += m_player.get_speed();};
        //auto move_down = [&](){movement.y += m_player.get_speed();};
        //auto move_left = [&](){movement.x -= m_player.get_speed();};
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

        if (m_player.is_off_map(std::make_unique<sf::Vector2u>(m_window.getSize()))) {
            m_player.put_back_on_map(std::make_unique<sf::Vector2u>(m_window.getSize()));
            return;
        }
        m_player.move(movement * t_delta_time.asSeconds());
    }

    auto game::move_projectiles(sf::Time t_delta_time) -> void {
        for (auto&& i: m_projectiles) {
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
            //(void) std::ranges::remove_if(m_projectiles, [size = m_window.getSize()](const projectile& proj) {
            //    return proj.is_off_map(std::make_unique<sf::Vector2u>(size));
            //});
            //TODO ranges version above is much nicer, but doesn't work. why??
            for (auto it = m_projectiles.begin(); it != m_projectiles.end(); ++it) {
                if (it->is_off_map(std::make_unique<sf::Vector2u>(m_window.getSize()))) {
                    it = m_projectiles.erase(it);
                    --it;
                }
            }
        }
    }

    auto game::detect_collision() -> void {
        std::vector<projectile> collided;
        for (auto& proj : m_projectiles) {
            if (m_player.get_texture_rect().intersects(proj.get_texture_rect())) {
                std::clog << m_player.get_texture_rect().top << "  " << m_player.get_texture_rect().left << std::endl;
                std::clog << proj.get_texture_rect().top - proj.get_texture_rect().height << "  " << proj.get_texture_rect().left - proj.get_texture_rect().width << std::endl;
                collided.push_back(proj);
                m_player.decrease_life();
            }
        }
        if (!collided.empty()) {
            std::clog << "coll\n";
            handle_collision(collided);
        }
    }

    auto game::handle_collision(std::vector<projectile>& t_proj) -> void {
        //(void) std::ranges::remove_if(m_projectiles, [&t_proj](const projectile& proj) {
        //    //return std::find(t_proj.begin(), t_proj.end(), proj) != t_proj.end();
        //});
        //TODO ranges version above is much nicer, but doesn't work. why??
        for (auto it = m_projectiles.begin(); it != m_projectiles.end(); ++it) {
            if (std::find(t_proj.begin(), t_proj.end(), *it) != t_proj.end()) {
                it = m_projectiles.erase(it);
                --it;
            }
        }
    }

    auto game::handle_lifetime() -> void {
        if (m_player.is_alive()) {
            return;
        }
        exit(1);
    }

    auto game::send_asteroid_if_needed() -> void {
        if (std::floor(m_global_clock.getElapsedTime().asSeconds()) <=
            std::floor(m_time_since_startup.asSeconds())) {
            return;
        }
        m_time_since_startup = m_global_clock.getElapsedTime();
        projectile ast(direction::down, 2000.0f);
        ast.set_texture(m_asteroid_texture);
        ast.set_position({generate_asteroid_x(), 0.0f});
        m_projectiles.push_back(ast);
    }

    auto game::generate_asteroid_x() const -> float {
        std::random_device random_device;
        std::mt19937 random_engine(random_device());
        std::uniform_real_distribution<float>
            dist(0.0f, static_cast<float>(m_window.getSize().x) - static_cast<float>(m_asteroid_texture.getSize().x));

        return dist(random_engine);
    }
} // spsh
