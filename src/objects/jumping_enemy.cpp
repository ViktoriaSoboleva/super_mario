#include "jumping_enemy.hpp"

using svr::JumpingEnemy;

JumpingEnemy::JumpingEnemy(
    const Coord& top_left,
    const int width,
    const int height
) : RectMapMovableAdapter(top_left, width, height) ,
    Movable(top_left, width, height,0,0){
	    hspeed = 0;
        jump();

}

svr::Rect JumpingEnemy::get_rect() const noexcept {
	return {top_left, width, height};
}

svr::Speed JumpingEnemy::get_speed() const noexcept {
	return {vspeed, hspeed};
}

void JumpingEnemy::process_horizontal_static_collision(Rect* obj) noexcept {
	hspeed = -hspeed;
	move_horizontally();
}

void JumpingEnemy::process_mario_collision(Collisionable* mario) noexcept {
	if (mario->get_speed().v > 0 && mario->get_speed().v != V_ACCELERATION) {
		kill();
	} else {
		mario->kill();
	}
}
void JumpingEnemy::process_vertical_static_collision(Rect* obj) noexcept {
    if (vspeed > 0) {
        top_left.y = obj->get_top() - height;
        vspeed = JUMP_SPEED;
    } else if (vspeed < 0) {
        top_left.y = obj->get_bottom();
        vspeed = 0;
    }
}