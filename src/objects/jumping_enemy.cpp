#include "jumping_enemy.hpp"

using biv::JumpingEnemy;

JumpingEnemy::JumpingEnemy(
    const Coord& top_left,
    const int width,
    const int height
) : Enemy(top_left, width, height) {
    hspeed = 0;
    jump();
}

void JumpingEnemy::process_vertical_static_collision(Rect* obj) noexcept {
    Enemy::process_vertical_static_collision(obj);

    if (vspeed == 0) {
        jump();
    }
}