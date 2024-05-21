#include "../incl/powerup.hpp"

namespace spsh {
    powerup::powerup(const powerup_type t_type)
        : movable(direction::stationary, 0.0f), m_type(t_type) {
    }

    auto powerup::apply_effect(const std::unique_ptr<player_ship> &t_ship) const -> void {
        switch (m_type) {
            case powerup_type::health:
                t_ship->increase_life();
                break;
            case powerup_type::rocket:
                t_ship->add_ammo();
                break;
            case powerup_type::temporary_speed:
                t_ship->start_speed_boost();
                break;
            default:
                std::cerr << "this is unreachable in powerup::apply_effect\n";
                std::unreachable();
        }
    }

    auto powerup::generate_powerup(const sf::Vector2f t_pos, sf::Clock &t_powerup_clock,
                                   std::map<powerup_type, sf::Texture> &t_textures)
        -> std::optional<powerup> {
        if (std::floor(t_powerup_clock.getElapsedTime().asSeconds()) <= constants::pwu_spawn_interval) {
            return std::nullopt;
        }
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, 2);
        const auto rand = dist(gen);
        powerup_type pt;

        switch (rand) {
            case 0:
                pt = powerup_type::health;
                break;
            case 1:
                pt = powerup_type::rocket;
                break;
            case 2:
                pt = powerup_type::temporary_speed;
                break;
            default:
                std::cerr << "this is unreachable in powerup::generate_powerup\n";
                std::unreachable();
        }

        t_powerup_clock.restart();
        auto generated = generate_object(pt, t_pos, t_textures);
        return {generated};
    }

    //TODO why is it called m_type in the param list
    auto powerup::generate_object(const powerup_type m_type, const sf::Vector2f t_pos,
                                  std::map<powerup_type, sf::Texture> &t_textures) -> powerup {
        switch (m_type) {
            case powerup_type::health: {
                auto health = powerup(powerup_type::health); //random generated variety
                health.set_texture(t_textures[powerup_type::health]);
                health.set_position(t_pos);
                return health;
            }
            case powerup_type::rocket: {
                auto rocket = powerup(powerup_type::rocket); //random generated variety
                rocket.set_texture(t_textures[powerup_type::rocket]);
                rocket.set_position(t_pos);
                return rocket;
            }
            case powerup_type::temporary_speed: {
                auto temporary_speed = powerup(powerup_type::temporary_speed); //random generated variety
                temporary_speed.set_texture(t_textures[powerup_type::temporary_speed]);
                temporary_speed.set_position(t_pos);
                return temporary_speed;
            }
            default:
                std::cerr << "this is unreachable in powerup::generate_object\n";
                std::unreachable();
        }
    }
} // namespace spsh
