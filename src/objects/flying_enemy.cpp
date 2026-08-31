#include "flying_enemy.hpp"

using biv::FlyingEnemy;

FlyingEnemy::FlyingEnemy(
    const Coord& top_left,
    const int width,
    const int height
) : Enemy(top_left, width, height) {
    hspeed = 0;
    vspeed = 0.2;
}

void FlyingEnemy::process_vertical_static_collision(Rect* obj) noexcept {
    vspeed = -vspeed;
}