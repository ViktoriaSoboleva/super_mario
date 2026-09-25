#pragma once

#include "enemy.hpp"

namespace svr {

class JumpingEnemy : public Enemy {
public:
    JumpingEnemy(
        const Coord& top_left,
        const int width,
        const int height
    );

    void process_vertical_static_collision(Rect* obj) noexcept override;
};

}