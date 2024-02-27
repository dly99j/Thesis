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
        auto player_width = static_cast<float>(m_player.get_texture_rect().width);
        //dauto player_height = static_cast<float>(m_player.get_texture_rect().height);
        //TODO center correctly
        m_player.set_position({window_width / 2.0f - player_width / 2.0f, window_height - window_height / 10.0f});
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
                handle_input(true);
            } else if (event.type == sf::Event::KeyReleased) {
                handle_input(false);
            } else if (event.type == sf::Event::Closed) {
                m_window.close();
            }
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

    auto game::handle_input(bool t_is_pressed) -> void {
        if (!t_is_pressed) {
            m_player.set_dierction(direction::stationary);
        }

        std::vector<direction> directions;
        direction final_direction = direction::stationary;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            directions.push_back(direction::up);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            directions.push_back(direction::left);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            directions.push_back(direction::down);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            directions.push_back(direction::right);
        }

        auto is_in_vec = [&directions](direction d) {
            return std::ranges::find(directions, d) != directions.end();
        };

        auto up_down_pressed = [&is_in_vec]() {
            if (is_in_vec(direction::up) && is_in_vec(direction::down)) {
                return true;
            }
            return false;
        };

        auto left_right_pressed = [&is_in_vec]() {
            if (is_in_vec(direction::left) && is_in_vec(direction::right)) {
                return true;
            }
            return false;
        };


        if (directions.size() == 1) {
            final_direction = directions[0];
        } else if (directions.size() == 2) {
            if (up_down_pressed() || left_right_pressed()) {
                final_direction = direction::stationary;
            } else if (is_in_vec(direction::up) && is_in_vec(direction::left)) {
                final_direction = direction::up_left;
            } else if (is_in_vec(direction::up) && is_in_vec(direction::right)) {
                final_direction = direction::up_right;
            } else if (is_in_vec(direction::down) && is_in_vec(direction::left)) {
                final_direction = direction::down_left;
            } else if (is_in_vec(direction::down) && is_in_vec(direction::right)) {
                final_direction = direction::down_right;
            }
        } else if (directions.size() == 3) {
            if (up_down_pressed()) {
                if (is_in_vec(direction::left)) {
                    final_direction = direction::left;
                } else if (is_in_vec(direction::right)) {
                    final_direction = direction::right;
                }
            } else if (left_right_pressed()) {
                if (is_in_vec(direction::up)) {
                    final_direction = direction::up;
                } else if (is_in_vec(direction::down)) {
                    final_direction = direction::down;
                }
            }
        } else {
            final_direction = direction::stationary;
        }

        m_player.set_dierction(final_direction);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            auto&& proj = m_player.shoot();
            if (proj.has_value()) {
                m_projectiles.push_back(proj.value());
            }
        }
    }

    auto game::move_player(sf::Time t_delta_time) -> void {
        sf::Vector2f movement;

        //TODO is readability worth so many fn calls??
        //optimalization? does it eliminate fn calls and object creations?
        auto move_up = [&]() { movement.y -= m_player.get_speed(); };
        auto move_right = [&]() { movement.x += m_player.get_speed(); };
        auto move_down = [&]() { movement.y += m_player.get_speed(); };
        auto move_left = [&]() { movement.x -= m_player.get_speed(); };
        if (m_player.get_direction() == direction::up) {
            move_up();
        } else if (m_player.get_direction() == direction::right) {
            move_right();
        } else if (m_player.get_direction() == direction::down) {
            move_down();
        } else if (m_player.get_direction() == direction::left) {
            move_left();
        } else if (m_player.get_direction() == direction::up_left) {
            move_up();
            move_left();
        } else if (m_player.get_direction() == direction::up_right) {
            move_up();
            move_right();
        } else if (m_player.get_direction() == direction::down_left) {
            move_down();
            move_left();
        } else if (m_player.get_direction() == direction::down_right) {
            move_down();
            move_right();
        }

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
            }
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
        for (auto& proj: m_projectiles) {
            if (m_player.get_texture_rect().intersects(proj.get_texture_rect())) {
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
                dist(0.0f, static_cast<float>(m_window.getSize().x) - static_cast<float>(m_asteroid_texture.getSize().
                               x));

        return dist(random_engine);
    }
} // spsh
