#include "../incl/waypoint_enemy.hpp"

namespace spsh {
waypoint_enemy::waypoint_enemy(const direction t_direction, const float t_speed,
                               const short t_lives)
    : enemy_ship(t_direction, t_speed, t_lives), m_need_new_gen(true) {
    if (!m_texture.loadFromFile("../media/eship0.png")) {
        std::cerr << "error loading player\n";
        exit(errors::ASSET_LOAD_ERROR);
    }
    set_texture(m_texture);
}

auto waypoint_enemy::generate_new_waypoint(
    const sf::Vector2u t_screen_dimensions) -> void {
    const auto width = static_cast<float>(t_screen_dimensions.x);
    const auto height = static_cast<float>(t_screen_dimensions.y);

    std::uniform_real_distribution width_dist(0.0f, width);
    std::uniform_real_distribution height_dist(0.0f, height / 3.0f);
    const auto rand_x = width_dist(m_gen);
    const auto rand_y = height_dist(m_gen);

    m_waypoint = {rand_x, rand_y};
}

auto waypoint_enemy::is_close_to_waypoint() const -> bool {
    constexpr auto half_dim = 50.0f;
    constexpr auto dim = half_dim * 2.0f;
    const auto rect_left = m_waypoint.x - half_dim;
    const auto rect_top = m_waypoint.y - half_dim;

    if (const sf::FloatRect square(rect_left, rect_top, dim, dim);
        square.intersects(get_texture_rect())) {
        return true;
    }
    return false;
}

auto waypoint_enemy::calculate_direction(
    const sf::Vector2u t_screen_dimensions,
    const std::optional<sf::FloatRect> t_player_rect) -> void {
    if (t_player_rect.has_value()) {
        std::cerr << "Fatal developer error! This can't have value!\n";
        std::cerr << "waypoint_enemy::calculate_dierction\n";
        exit(errors::OPTIONAL_ERROR);
    }

    if (m_need_new_gen) {
        generate_new_waypoint(t_screen_dimensions);
        m_need_new_gen = false;
    }
    if (is_close_to_waypoint()) {
        generate_new_waypoint(t_screen_dimensions);
    }

    const auto& position = get_position();
    const auto width_difference = std::abs(position.x - m_waypoint.x);
    const auto height_difference = std::abs(position.y - m_waypoint.y);
    constexpr auto critical_diff = 2.0f;

    const auto enemy_to_the_right = [&position, this]() {
        return position.x > m_waypoint.x;
    };
    const auto enemy_lower = [&position, this]() {
        return position.y > m_waypoint.y;
    };

    if (width_difference > critical_diff * height_difference) {
        if (enemy_to_the_right()) {
            set_direction(direction::left);
        } else {
            set_direction(direction::right);
        }
    } else if (height_difference > critical_diff * width_difference) {
        if (enemy_lower()) {
            set_direction(direction::up);
        } else {
            set_direction(direction::down);
        }
    } else {
        if (enemy_to_the_right() && enemy_lower()) {
            set_direction(direction::up_left);
        } else if (!enemy_to_the_right() && enemy_lower()) {
            set_direction(direction::up_right);
        } else if (enemy_to_the_right() && !enemy_lower()) {
            set_direction(direction::down_left);
        } else {
            set_direction(direction::down_right);
        }
    }
}
}  // namespace spsh
