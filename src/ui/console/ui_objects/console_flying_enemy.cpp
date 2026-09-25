#include "console_flying_enemy.hpp"

using svr::ConsoleFlyingEnemy;

ConsoleFlyingEnemy::ConsoleFlyingEnemy(
    const Coord& top_left,
    const int width,
    const int height
) :
    FlyingEnemy(top_left, width, height),
    ConsoleUIObjectRectAdapter(top_left, width, height) {}

char ConsoleFlyingEnemy::get_brush() const noexcept {
    return 'f';
}