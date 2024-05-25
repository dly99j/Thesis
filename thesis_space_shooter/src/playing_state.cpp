#include "../incl/playing_state.hpp"

namespace spsh {
    playing_state::playing_state(sf::RenderWindow &t_window, const map t_map)
        : m_map(t_map),
          m_time_of_last_asteroid(sf::Time::Zero),
          m_window(t_window),
          m_sound_player({
              sound_effect::player_rocket, sound_effect::player_hit,
              sound_effect::enemy_rocket, sound_effect::enemy_hit,
              sound_effect::button, sound_effect::powerup
          }) {
        m_music_player.play();
        set_map();

        if (!m_font.loadFromFile("../media/sansation.ttf")) {
            std::cerr << "error loading font\n";
            exit(errors::ASSET_LOAD_ERROR);
        }

        load_map_elements();
        set_background();

        m_asteroid_clock.restart();
        m_powerup_clock.restart();

        const auto window_width = static_cast<float>(m_window.getSize().x);
        const auto window_height = static_cast<float>(m_window.getSize().y);
        const auto player_width = m_player->get_reduced_texture_rect().width;
        const auto enemy_width = m_enemy->get_reduced_texture_rect().width;
        // auto player_height =
        // static_cast<float>(m_player.get_reduced_texture_rect().height);
        // TODO center correctly
        m_player->set_position({
            window_width / 2.0f - player_width / 2.0f,
            window_height - window_height / 10.0f
        });
        m_enemy->set_position(
            {window_width / 2.0f - enemy_width / 2.0f, window_height / 10.0f});
    }

    auto playing_state::run() -> void {
        sf::Clock clock;
        auto time_since_update = sf::Time::Zero;

        while (m_window.isOpen()) {
            const auto delta_time = clock.restart();
            time_since_update += delta_time;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                m_music_player.pause();
                const auto quit = pause_game();
                if (quit) {
                    return;
                }
                m_music_player.play();
                clock.restart();
            }
            while (time_since_update > constants::frame_time) {
                time_since_update -= constants::frame_time;
                handle_events();
                update(delta_time);
            }
            detect_collision();
            if (handle_game_over()) {
                return;
            }
            render();
        }
    }

    auto playing_state::set_map() -> void {
        switch (m_map) {
            case map::first:
                m_player = std::make_unique<player_ship>(direction::stationary,
                                                         constants::firts_ship);
                m_enemy = std::make_unique<waypoint_enemy>(direction::stationary);
                break;
            case map::second:
                m_player = std::make_unique<player_ship>(direction::stationary,
                                                         constants::second_ship);
                m_enemy = std::make_unique<chasing_enemy>(direction::stationary);
                break;
            case map::third:
                m_player = std::make_unique<player_ship>(direction::stationary,
                                                         constants::third_ship);
                m_enemy = std::make_unique<avoiding_enemy>(direction::stationary);
                break;
            default:
                std::unreachable();
        }
    }

    auto playing_state::handle_events() -> void {
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

    auto playing_state::update(const sf::Time t_delta_time) -> void {
        move_player(t_delta_time);
        projectile_action(t_delta_time);
        powerup_action();
        enemy_action(t_delta_time);
    }

    auto playing_state::render() -> void {
        m_window.clear();
        m_window.draw(m_background_sprite);
        m_player->draw(m_window);
        m_enemy->draw(m_window);
        for (auto &&i: m_projectiles) {
            i.draw(m_window);
        }
        for (auto &&i: m_powerups) {
            i.draw(m_window);
        }
        m_window.draw(m_player->get_lifecounter_text());
        m_window.draw(m_player->get_ammo_text());
        m_window.display();
    }

    auto playing_state::pause_game() -> bool {
        m_sound_player.play(sound_effect::button);
        m_player->set_dierction(direction::stationary);
        auto [resume_button, quit_button] = draw_pause_game();
        while (m_window.isOpen()) {
            sf::Event e{};
            while (m_window.pollEvent(e)) {
                if (e.type == sf::Event::Closed) {
                    m_window.close();
                    return true;
                }
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                const auto mouse_pos = sf::Vector2f(sf::Mouse::getPosition(m_window));
                if (resume_button.getGlobalBounds().contains(mouse_pos)) {
                    sf::Event e{};
                    while (m_window.pollEvent(e)) {
                    }
                    m_sound_player.play(sound_effect::button);
                    return false;
                }
                if (quit_button.getGlobalBounds().contains(mouse_pos)) {
                    sf::Event e{};
                    while (m_window.pollEvent(e)) {
                    }
                    return true;
                }
            }
        }
        return true;
    }

    auto playing_state::draw_pause_game()
        -> std::pair<sf::RectangleShape, sf::RectangleShape> {
        sf::Text pause_text;
        pause_text.setFillColor(sf::Color::White);
        pause_text.setCharacterSize(60);
        pause_text.setString("Game paused");
        pause_text.setFont(m_font);
        sf::Vector2f pos;
        pos.x = (static_cast<float>(m_window.getSize().x) -
                 pause_text.getLocalBounds().width) /
                2.0f;
        pos.y = static_cast<float>(m_window.getSize().y) / 3.0f;
        pause_text.setPosition(pos);

        sf::RectangleShape resume_button({300.f, 80.f});
        sf::RectangleShape quit_button({300.f, 80.f});
        sf::Text resume_text, quit_text;
        resume_text.setFont(m_font);
        quit_text.setFont(m_font);
        resume_text.setString("Resume");
        quit_text.setString("Return to Main Menu");
        resume_text.setCharacterSize(20);
        quit_text.setCharacterSize(20);
        resume_button.setTexture(&m_btn);
        quit_button.setTexture(&m_btn);
        resume_text.setFillColor(sf::Color::White);
        quit_text.setFillColor(sf::Color::White);

        auto button_width = resume_button.getSize().x;
        auto button_height = resume_button.getSize().y;
        auto button_x =
                (static_cast<float>(m_window.getSize().x) - button_width) / 2.f;
        auto button_y = pos.y + 100.f;

        resume_button.setPosition(button_x, button_y);
        quit_button.setPosition(button_x, button_y + button_height + 30.f);
        resume_text.setPosition(
            button_x + (button_width - resume_text.getLocalBounds().width) / 2.f,
            button_y + (button_height - resume_text.getLocalBounds().height) / 2.f -
            5.f);
        quit_text.setPosition(
            button_x + (button_width - quit_text.getLocalBounds().width) / 2.f,
            button_y + button_height + 30.f +
            (button_height - quit_text.getLocalBounds().height) / 2.f - 5.f);

        //m_window.clear(sf::Color(30, 30, 30, 150)); // Semi-transparent black background
        sf::RectangleShape pause_overlay(
            static_cast<sf::Vector2f>(m_window.getSize()));
        pause_overlay.setFillColor(sf::Color(0, 0, 0, 128));
        m_window.draw(pause_overlay);
        m_window.draw(pause_text);
        m_window.draw(resume_button);
        m_window.draw(quit_button);
        m_window.draw(resume_text);
        m_window.draw(quit_text);
        m_window.display();

        return {resume_button, quit_button};
    }

    auto playing_state::set_background() -> void {
        switch (m_map) {
            case map::first: {
                if (!m_background_texture.loadFromFile("../media/bg0.jpg")) {
                    std::cerr << "error loading background!\n";
                    exit(errors::ASSET_LOAD_ERROR);
                }
                break;
            }
            case map::second: {
                if (!m_background_texture.loadFromFile("../media/bg1.jpg")) {
                    std::cerr << "error loading background!\n";
                    exit(errors::ASSET_LOAD_ERROR);
                }
                break;
            }
            case map::third: {
                if (!m_background_texture.loadFromFile("../media/bg2.jpg")) {
                    std::cerr << "error loading background!\n";
                    exit(errors::ASSET_LOAD_ERROR);
                }
                break;
            }
            default:
                std::unreachable();
        }
        m_background_sprite.setTexture(m_background_texture);
    }

    auto playing_state::load_map_elements() -> void {
        if (!m_asteroid_texture.loadFromFile("../media/asteroid.png")) {
            std::cerr << "error loading bullet\n";
            exit(errors::ASSET_LOAD_ERROR);
        }

        sf::Texture health_texture;
        if (!health_texture.loadFromFile("../media/add_health.png")) {
            std::cerr << "Error loading health power-up texture\n";
            exit(errors::ASSET_LOAD_ERROR);
        }
        m_powerup_textures[powerup_type::health] = health_texture;

        sf::Texture speed_texture;
        if (!speed_texture.loadFromFile("../media/add_speed.png")) {
            std::cerr << "Error loading speed power-up texture\n";
            exit(errors::ASSET_LOAD_ERROR);
        }
        m_powerup_textures[powerup_type::temporary_speed] = speed_texture;

        sf::Texture rocket_texture;
        if (!rocket_texture.loadFromFile("../media/add_ammo.png")) {
            std::cerr << "Error loading rocket power-up texture\n";
            exit(errors::ASSET_LOAD_ERROR);
        }
        m_powerup_textures[powerup_type::rocket] = rocket_texture;

        if (!m_btn.loadFromFile("../media/btn.png")) {
            std::cerr << "error loading button!\n";
            exit(errors::ASSET_LOAD_ERROR);
        }
    }

    auto playing_state::handle_input(const bool t_is_pressed) -> void {
        if (!t_is_pressed) {
            m_player->set_dierction(direction::stationary);
        }

        std::vector<direction> directions;
        auto final_direction = direction::stationary;

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

        const auto is_in_vec = [&directions](const direction d) {
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

        m_player->set_dierction(final_direction);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            if (auto &&proj = m_player->shoot(std::nullopt); proj.has_value()) {
                m_projectiles.push_back(std::move(proj.value()));
                m_sound_player.play(sound_effect::player_rocket);
            }
        }
    }

    auto playing_state::move_player(const sf::Time t_delta_time) -> void {
        const auto movement = m_player->calculate_move();

        if (m_player->is_off_map(
            std::make_unique<sf::Vector2u>(m_window.getSize()))) {
            m_player->put_back_on_map(
                std::make_unique<sf::Vector2u>(m_window.getSize()));
            return;
        }
        m_player->move(movement * t_delta_time.asSeconds());
    }

    auto playing_state::move_projectiles(const sf::Time t_delta_time) -> void {
        for (auto &&i: m_projectiles) {
            auto movement = i.calculate_move();
            i.move(movement * t_delta_time.asSeconds());
        }
        std::erase_if(m_projectiles,
                      [size = m_window.getSize()](const projectile &proj) {
                          return proj.is_off_map(std::make_unique<sf::Vector2u>(size));
                      });
    }

    auto playing_state::projectile_action(const sf::Time t_delta_time) -> void {
        move_projectiles(t_delta_time);
        send_asteroid_if_needed();
    }

    auto playing_state::powerup_action() -> void {
        spawn_powerup_if_needed();
        m_player->handle_speed_boost();
    }

    auto playing_state::enemy_action(const sf::Time t_delta_time) -> void {
        move_enemy(t_delta_time);
        send_enemy_projectile();
    }

    auto playing_state::move_enemy(sf::Time t_delta_time) -> void {
        switch (m_map) {
            case map::first:
                m_enemy->calculate_direction(m_window.getSize(), std::nullopt);
                break;
            case map::second:
                m_enemy->calculate_direction(m_window.getSize(),
                                             {m_player->get_texture_rect()});
                break;
            case map::third:
                m_enemy->calculate_direction(m_window.getSize(),
                                             get_closest_bullet_to_enemy());
                break;
            default:
                std::unreachable();
        }

        auto movement = m_enemy->calculate_move();

        if (m_enemy->is_off_map(std::make_unique<sf::Vector2u>(m_window.getSize()))) {
            m_enemy->put_back_on_map(
                std::make_unique<sf::Vector2u>(m_window.getSize()));
            return;
        }
        m_enemy->move(movement * t_delta_time.asSeconds());
    }

    auto playing_state::send_enemy_projectile() -> void {
        if (auto &&proj = m_enemy->send_projectile_if_needed(
                m_player->get_reduced_texture_rect());
            proj.has_value()) {
            m_projectiles.push_back(std::move(proj.value()));
            m_sound_player.play(sound_effect::enemy_rocket);
        }
    }

    auto playing_state::detect_collision() -> void {
        std::vector<projectile> collided_proj;
        std::vector<powerup> collided_pwu;
        for (auto &proj: m_projectiles) {
            if (m_player->get_reduced_texture_rect().intersects(
                proj.get_reduced_texture_rect())) {
                collided_proj.push_back(proj);
                m_player->decrease_life();
                m_sound_player.play(sound_effect::player_hit);
            } else if (m_enemy->get_reduced_texture_rect().intersects(
                           proj.get_texture_rect()) &&
                       proj.get_type() == projectile_type::rocket) {
                collided_proj.push_back(proj);
                m_enemy->decrease_life();
                m_sound_player.play(sound_effect::enemy_hit);
            }
        }
        for (auto &pwu: m_powerups) {
            if (m_player->get_texture_rect().intersects(
                pwu.get_reduced_texture_rect())) {
                collided_pwu.push_back(pwu);
                pwu.apply_effect(m_player);
                m_sound_player.play(sound_effect::powerup);
            }
        }
        if (!collided_proj.empty() || !collided_pwu.empty()) {
            handle_collision(collided_proj, collided_pwu);
        }
    }

    auto playing_state::handle_collision(std::vector<projectile> &t_proj,
                                         std::vector<powerup> &t_pwu) -> void {
        std::erase_if(m_projectiles, [&t_proj](const projectile &proj) {
            return std::find(t_proj.begin(), t_proj.end(), proj) != t_proj.end();
        });
        std::erase_if(m_powerups, [&t_pwu](const powerup &pwu) {
            return std::find(t_pwu.begin(), t_pwu.end(), pwu) != t_pwu.end();
        });
    }

    auto playing_state::handle_lifetime() const -> game_state {
        if (!m_player->is_alive()) {
            return game_state::lost;
        }
        if (!m_enemy->is_alive()) {
            return game_state::won;
        }
        return game_state::playing;
    }

    auto playing_state::handle_game_over() -> bool {
        auto state = handle_lifetime();
        if (state == game_state::playing) {
            return false;
        }
        auto main_menu_button = draw_game_over(state);
        while (m_window.isOpen()) {
            sf::Event e{};
            while (m_window.pollEvent(e)) {
                if (e.type == sf::Event::Closed) {
                    m_window.close();
                    return true;
                }
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (const auto mouse_pos = sf::Vector2f(sf::Mouse::getPosition(m_window));
                    main_menu_button.getGlobalBounds().contains(mouse_pos)) {
                    sf::Event e{};
                    while (m_window.pollEvent(e)) {
                    }
                    return true;
                }
            }
        }
        return true;
    }

    auto playing_state::draw_game_over(game_state t_state) -> sf::RectangleShape {
        render();
        sf::Text game_over_text;
        game_over_text.setFillColor(sf::Color::White);
        game_over_text.setCharacterSize(60);
        if (t_state == game_state::lost) {
            game_over_text.setString("Game Over! You Lost");
        } else if (t_state == game_state::won) {
            game_over_text.setString("Congratulations! You Won");
        } else {
            std::cerr << "Fatal error! draw_game_over called when the game is not over";
            exit(errors::BAD_FUNCTION_CALL);
        }
        game_over_text.setFont(m_font);
        sf::Vector2f pos;
        pos.x = (static_cast<float>(m_window.getSize().x) -
                 game_over_text.getLocalBounds().width) /
                2.0f;
        pos.y = static_cast<float>(m_window.getSize().y) / 3.0f;
        game_over_text.setPosition(pos);

        sf::RectangleShape main_menu_button({300.f, 80.f});
        sf::Text main_menu_text;
        main_menu_text.setFont(m_font);
        main_menu_text.setString("Return to Main Menu");
        main_menu_text.setCharacterSize(20);
        main_menu_button.setTexture(&m_btn);
        main_menu_text.setFillColor(sf::Color::White);

        auto button_width = main_menu_button.getSize().x;
        auto button_height = main_menu_button.getSize().y;
        auto button_x =
                (static_cast<float>(m_window.getSize().x) - button_width) / 2.f;
        auto button_y = pos.y + 100.f;

        main_menu_button.setPosition(button_x, button_y);
        main_menu_text.setPosition(
            button_x + (button_width - main_menu_text.getLocalBounds().width) / 2.f,
            button_y +
            (button_height - main_menu_text.getLocalBounds().height) / 2.f - 5.f);

        sf::RectangleShape game_over_overlay(
            static_cast<sf::Vector2f>(m_window.getSize()));
        game_over_overlay.setFillColor(sf::Color(0, 0, 0, 128));
        m_window.draw(game_over_overlay);
        m_window.draw(game_over_text);
        m_window.draw(main_menu_button);
        m_window.draw(main_menu_text);
        m_window.display();

        return main_menu_button;
    }

    auto playing_state::get_closest_bullet_to_enemy()
        -> std::optional<sf::FloatRect> {
        auto distance_sq = [this](const projectile &p) {
            return std::pow(this->m_enemy->get_position().x - p.get_position().x, 2) +
                   std::pow(this->m_enemy->get_position().y - p.get_position().y, 2);
        };
        if (m_projectiles.empty()) {
            return std::nullopt;
        }
        std::optional<projectile> closest = std::nullopt;
        for (const auto &i: m_projectiles) {
            if (i.get_type() == projectile_type::asteroid) {
                continue;
            }
            if (i.get_direction() == direction::down) {
                continue;
            }
            if (!closest.has_value()) {
                closest = i;
            } else if (distance_sq(i) < distance_sq(closest.value())) {
                closest = i;
            }
        }

        if (closest.has_value()) {
            return closest.value().get_reduced_texture_rect();
        }
        return std::nullopt;
    }

    auto playing_state::send_asteroid_if_needed() -> void {
        if (std::floor(m_asteroid_clock.getElapsedTime().asSeconds()) <=
            std::floor(m_time_of_last_asteroid.asSeconds())) {
            return;
        }
        m_time_of_last_asteroid = m_asteroid_clock.getElapsedTime();
        projectile generated(direction::down, 2000.0f, projectile_type::asteroid);
        generated.set_texture(m_asteroid_texture);
        generated.set_position(
            {generate_random_coords(m_asteroid_texture.getSize()).x, 0.0f});
        m_projectiles.push_back(generated);
    }

    auto playing_state::spawn_powerup_if_needed() -> void {
        if (m_powerups.size() > 5)
            return;
        if (const auto pwu = powerup::generate_powerup(
                generate_random_coords(
                    m_powerup_textures[powerup_type::temporary_speed].getSize()),
                m_powerup_clock, m_powerup_textures);
            pwu.has_value()) {
            m_powerups.push_back(pwu.value());
        }
    }

    auto playing_state::generate_random_coords(const sf::Vector2u t_size) const
        -> sf::Vector2f {
        std::random_device random_device;
        std::mt19937 random_engine(random_device());
        std::uniform_real_distribution<float> dist_x(
            0.0f,
            static_cast<float>(m_window.getSize().x) - static_cast<float>(t_size.x));
        std::uniform_real_distribution<float> dist_y(
            0.0f,
            static_cast<float>(m_window.getSize().y) - static_cast<float>(t_size.y));

        return {dist_x(random_engine), dist_y(random_engine)};
    }
} // namespace spsh
