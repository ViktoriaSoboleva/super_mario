#pragma once

#include "enemy.hpp"

namespace biv {

class FlyingEnemy : public Enemy {

public:
    FlyingEnemy(const Coord& top_left, const int width, const int height);

    void process_vertical_static_collision(Rect* obj) noexcept override;
};

}