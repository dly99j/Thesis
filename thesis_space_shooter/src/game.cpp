#include "../incl/game.hpp"

#include <cmath>
#include <filesystem>
#include <iostream>
#include <random>

#include "../incl/avoiding_enemy.hpp"

namespace spsh {
    game::game()
        : m_time_since_startup(sf::Time::Zero)
          , m_window(sf::VideoMode(1280, 960), "SpaceShooter", sf::Style::Close)
          , m_player(direction::stationary, 1000.0f)
          , m_enemy(std::make_unique<avoiding_enemy>(direction::stationary)) {
        if (!m_asteroid_texture.loadFromFile("../media/asteroid.png")) {
            std::cerr << "error loading bullet\n";
        }
        set_background();

        m_global_clock.restart();

        auto window_width = static_cast<float>(m_window.getSize().x);
        auto window_height = static_cast<float>(m_window.getSize().y);
        auto player_width = m_player.get_texture_rect().width;
        auto enemy_width = m_enemy->get_texture_rect().width;
        //auto player_height = static_cast<float>(m_player.get_texture_rect().height);
        //TODO center correctly
        m_player.set_position({window_width / 2.0f - player_width / 2.0f, window_height - window_height / 10.0f});
        m_enemy->set_position({window_width / 2.0f - enemy_width / 2.0f, window_height / 10.0f});
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
        projectile_action(t_delta_time);
        enemy_action(t_delta_time);
    }

    auto game::render() -> void {
        m_window.clear();
        m_window.draw(m_background_sprite);
        m_player.draw(m_window);
        m_enemy->draw(m_window);
        for (auto&& i: m_projectiles) {
            i.draw(m_window);
        }
        m_window.draw(m_player.get_lifecounter_text());
        m_window.draw(m_player.get_ammo_text());
        m_window.display();
    }

    auto game::set_background() -> void {
        if (!m_background_texture.loadFromFile("../media/bg.jpg")) {
            std::cerr << "error loading background!\n";
        }
        //auto [x, y] = m_background_texture.getSize();
        m_background_sprite.setTexture(m_background_texture);
        //m_background_sprite.setOrigin(static_cast<float>(x) / 2.0f, static_cast<float>(y) / 2.0f);
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

        const auto is_in_vec = [&directions](direction d) {
            return std::ranges::find(directions, d) != directions.end();
        };

        const auto up_down_pressed = [&is_in_vec]() {
            if (is_in_vec(direction::up) && is_in_vec(direction::down)) {
                return true;
            }
            return false;
        };

        const auto left_right_pressed = [&is_in_vec]() {
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
            auto&& proj = m_player.shoot(std::nullopt);
            if (proj.has_value()) {
                m_projectiles.push_back(proj.value());
            }
        }
    }

    //TODO refactor to ship_base/player_ship
    auto game::move_player(sf::Time t_delta_time) -> void {
        auto movement = m_player.calculate_move();

        if (m_player.is_off_map(std::make_unique<sf::Vector2u>(m_window.getSize()))) {
            m_player.put_back_on_map(std::make_unique<sf::Vector2u>(m_window.getSize()));
            return;
        }
        m_player.move(movement * t_delta_time.asSeconds());
    }

    auto game::move_projectiles(sf::Time t_delta_time) -> void {
        for (auto&& i: m_projectiles) {
            auto movement = i.calculate_move();
            i.move(movement * t_delta_time.asSeconds());
        }
        std::erase_if(m_projectiles, [size = m_window.getSize()](const projectile& proj) {
            return proj.is_off_map(std::make_unique<sf::Vector2u>(size));
        });;
        /*
         *i leave this here just in case something breaks
        for (auto it = m_projectiles.begin(); it != m_projectiles.end(); ++it) {
            if (it->is_off_map(std::make_unique<sf::Vector2u>(m_window.getSize()))) {
                it = m_projectiles.erase(it);
                --it;
            }
        }
        */
    }

    auto game::projectile_action(sf::Time t_delta_time) -> void {
        move_projectiles(t_delta_time);
        send_asteroid_if_needed();
    }

    auto game::enemy_action(sf::Time t_delta_time) -> void {
        move_enemy(t_delta_time);
        send_enemy_projectile();
    }

    auto game::move_enemy(sf::Time t_delta_time) -> void {
        m_enemy->calculate_direction(m_player.get_texture_rect(), m_window.getSize());
        auto movement = m_enemy->calculate_move();

        if (m_enemy->is_off_map(std::make_unique<sf::Vector2u>(m_window.getSize()))) {
            m_enemy->put_back_on_map(std::make_unique<sf::Vector2u>(m_window.getSize()));
            return;
        }
        m_enemy->move(movement * t_delta_time.asSeconds());
    }

    auto game::send_enemy_projectile() -> void {
        auto proj = m_enemy->send_projectile_if_needed(m_player.get_texture_rect());
        if (proj.has_value()) {
            m_projectiles.push_back(proj.value());
        }
    }

    auto game::detect_collision() -> void {
        std::vector<projectile> collided;
        for (auto& proj: m_projectiles) {
            if (m_player.get_texture_rect().intersects(proj.get_texture_rect())) {
                collided.push_back(proj);
                m_player.decrease_life();
            }
            //TODO increase enemy texture rect
            else if (m_enemy->get_texture_rect().intersects(proj.get_texture_rect()) &&
                     proj.get_type() == projectile_type::rocket) {
                collided.push_back(proj);
                m_enemy->decrease_life();
            }
        }
        if (!collided.empty()) {
            handle_collision(collided);
        }
    }

    auto game::handle_collision(std::vector<projectile>& t_proj) -> void {
        std::erase_if(m_projectiles, [&t_proj](const projectile& proj) {
            return std::find(t_proj.begin(), t_proj.end(), proj) != t_proj.end();
        });
    }

    auto game::handle_lifetime() -> void {
        if (!m_player.is_alive()) {
            exit(1);
        }
        if (!m_enemy->is_alive()) {
            exit(2);
        }
    }

    auto game::send_asteroid_if_needed() -> void {
        if (std::floor(m_global_clock.getElapsedTime().asSeconds()) <=
            std::floor(m_time_since_startup.asSeconds())) {
            return;
        }
        m_time_since_startup = m_global_clock.getElapsedTime();
        projectile ast(direction::down, 2000.0f, projectile_type::asteroid);
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
