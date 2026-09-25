#include "console_ship.hpp"

using svr::ConsoleShip;

ConsoleShip::ConsoleShip(const Coord& top_left, const int width, const int height) 
	: Ship(top_left, width, height) {}

char ConsoleShip::get_brush() const noexcept {
	return '#';
}
