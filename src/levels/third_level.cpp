#include "third_level.hpp"
using biv::ThirdLevel;
ThirdLevel::ThirdLevel(UIFactory* ui_factory) : GameLevel(ui_factory) { init_data(); }
bool ThirdLevel::is_final() const noexcept { return true; }
biv::GameLevel* ThirdLevel::get_next() { return next; }
void ThirdLevel::init_data() { ui_factory->create_mario({39, 10}, 3, 3);
ui_factory->create_ship({20, 25}, 170, 2);


ui_factory->create_ship({195, 20}, 12, 7);
}