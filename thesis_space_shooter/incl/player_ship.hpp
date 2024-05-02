#ifndef PLAYER_SHIP_HPP
#define PLAYER_SHIP_HPP
#include <SFML/Graphics/Text.hpp>
#include <optional>
#include <queue>

#include "projectile.hpp"
#include "ship_base.hpp"
#include "config.hpp"

namespace spsh {

class player_ship : public ship_base {
public:
  explicit player_ship(direction, const player_details&);

  [[nodiscard]] auto shoot(std::optional<sf::FloatRect>)
      -> std::optional<projectile> override;

  auto add_ammo(short = 3) -> void;

  auto start_speed_boost() -> void;

  auto handle_speed_boost() -> void;

  [[nodiscard]] auto get_lifecounter_text() -> sf::Text;

  [[nodiscard]] auto get_ammo_text() -> sf::Text;

private:
  auto setup_lifecounter_text() -> void;

  auto setup_ammo_text() -> void;

  auto update_lifecounter_text() -> void;

  auto update_ammo_text() -> void;

private:
  sf::Font m_font;
  sf::Text m_lifecounter_text;
  sf::Text m_ammo_text;
  sf::Texture m_bullet_texture;

  bool m_is_boost_active;
  sf::Clock m_speed_boost_timer;
  float m_boosted_speed;
  float m_original_speed;
  sf::Time m_speed_boost_duration;

  std::queue<projectile> m_bullets;
};
} // namespace spsh

#endif // PLAYER_SHIP_HPP
