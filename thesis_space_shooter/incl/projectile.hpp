#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP
#include "movable.hpp"

namespace spsh {
    class projectile : public movable {
    public:
        //TODO default param is temporary right now, might need fix
        using movable::movable;
    };
} // spsh

#endif //PROJECTILE_HPP
