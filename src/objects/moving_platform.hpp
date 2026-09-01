#pragma once

#include "ship.hpp"
#include "movable.hpp"
#include "mario.hpp"

namespace biv {

class MovingPlatform :
    public Ship,
    public Movable {

private:
    float start_x;
    float end_x;
    Mario* mario;

public:
    MovingPlatform(
        const Coord& top_left,
        const int width,
        const int height,
        Mario* mario
    );

    void move_horizontally() noexcept override;
    void move_vertically() noexcept override;

    void move_map_left() noexcept override;
    void move_map_right() noexcept override;
};


}