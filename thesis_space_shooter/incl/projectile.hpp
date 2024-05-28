#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP
#include <SFML/Graphics.hpp>
#include "enums.hpp"
#include "movable.hpp"
#include "sound_player.hpp"

namespace spsh {
class projectile : public movable {
   public:
    projectile(direction, float, projectile_type);

    [[nodiscard]]
    auto get_type() const -> projectile_type;

   protected:
    projectile_type m_type;
};
}  // namespace spsh

#endif  //PROJECTILE_HPP
