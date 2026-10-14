#include "moving_platform.hpp"

using svr::MovingPlatform;

MovingPlatform::MovingPlatform(
    const Coord& top_left,
    const int width,
    const int height
)
    : Ship(top_left, width, height),
      Movable(top_left, width, height, 0, 0.2f),
      start_x(top_left.x),
      end_x(top_left.x + 30)
{}

void MovingPlatform::move_horizontally() noexcept {
    if (get_x() >= end_x) {
        hspeed = -0.2f;
    }
    else if (get_x() <= start_x) {
        hspeed = 0.2f;
    }

Movable::move_horizontally();
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