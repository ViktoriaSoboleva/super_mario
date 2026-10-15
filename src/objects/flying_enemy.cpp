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
		min_x = top_left.x;
		max_x = top_left.x + 13;

}

svr::Rect FlyingEnemy::get_rect() const noexcept {
	return {top_left, width, height};
}

svr::Speed FlyingEnemy::get_speed() const noexcept {
	return {vspeed, hspeed};
}

void FlyingEnemy::process_horizontal_static_collision(Rect* obj) noexcept {
	
}

void FlyingEnemy::move_horizontally() noexcept { 
	top_left.x += hspeed;
	if (top_left.x <= min_x || top_left.x + width >= max_x) {
    	hspeed = -hspeed;
	}
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

void FlyingEnemy::move_vertically() noexcept {}

void FlyingEnemy::move_map_left() noexcept {
    top_left.x -= MapMovable::MAP_STEP;
    min_x -= MapMovable::MAP_STEP;
    max_x -= MapMovable::MAP_STEP;
}

void FlyingEnemy::move_map_right() noexcept {
    top_left.x += MapMovable::MAP_STEP;
    min_x += MapMovable::MAP_STEP;
    max_x += MapMovable::MAP_STEP;
}