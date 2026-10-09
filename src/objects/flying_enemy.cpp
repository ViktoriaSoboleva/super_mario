#include "flying_enemy.hpp"

using svr::FlyingEnemy;

FlyingEnemy::FlyingEnemy(
    const Coord& top_left,
    const int width,
    const int height
) : RectMapMovableAdapter(top_left, width, height) ,
    Movable(top_left, width, height,0,0){
        vspeed = 0;
	    hspeed = 0.2;

}

svr::Rect FlyingEnemy::get_rect() const noexcept {
	return {top_left, width, height};
}

svr::Speed FlyingEnemy::get_speed() const noexcept {
	return {vspeed, hspeed};
}

void FlyingEnemy::process_horizontal_static_collision(Rect* obj) noexcept {
	hspeed = -hspeed;
	move_horizontally();
}

void FlyingEnemy::process_mario_collision(Collisionable* mario) noexcept {
	if (mario->get_speed().v > 0 && mario->get_speed().v != V_ACCELERATION) {
		kill();
	} else {
		mario->kill();
	}
}

void FlyingEnemy::process_vertical_static_collision(Rect* obj) noexcept {
        
        vspeed = -vspeed;
    
}