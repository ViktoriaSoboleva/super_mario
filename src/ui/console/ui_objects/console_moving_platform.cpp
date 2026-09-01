#include "console_moving_platform.hpp"

using biv::ConsoleMovingPlatform;

ConsoleMovingPlatform::ConsoleMovingPlatform(
    const Coord& top_left,
    const int width,
    const int height,
    Mario* mario
) :
    MovingPlatform(top_left, width, height, mario),
    ConsoleUIObjectRectAdapter(top_left, width, height)
{}

char ConsoleMovingPlatform::get_brush() const noexcept {
    return '=';
}