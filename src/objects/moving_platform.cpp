#include "moving_platform.hpp"

using biv::MovingPlatform;

MovingPlatform::MovingPlatform(
    const Coord& top_left,
    const int width,
    const int height,
    Mario* mario
) :
    Ship(top_left, width, height),
    Movable(top_left, width, height, 0, 0.2f),
    start_x(top_left.x),
    end_x(top_left.x + 30),
    mario(mario)
{}

void MovingPlatform::move_horizontally() noexcept {

    bool mario_on_platform =
        mario != nullptr &&
        mario->get_bottom() == get_top() &&
        mario->get_right() > get_left() &&
        mario->get_left() < get_right();

    if (get_x() >= end_x) {
        hspeed = -0.2f;
    }
    else if (get_x() <= start_x) {
        hspeed = 0.2f;
    }

    Movable::move_horizontally();

    if (mario_on_platform) {
        mario->move_horizontal_offset(hspeed);
    }
}

void MovingPlatform::move_vertically() noexcept {}

void MovingPlatform::move_map_left() noexcept {
    RectMapMovableAdapter::move_map_left();
    start_x -= MapMovable::MAP_STEP;
    end_x -= MapMovable::MAP_STEP;
}

void MovingPlatform::move_map_right() noexcept {
    RectMapMovableAdapter::move_map_right();
    start_x += MapMovable::MAP_STEP;
    end_x += MapMovable::MAP_STEP;
}