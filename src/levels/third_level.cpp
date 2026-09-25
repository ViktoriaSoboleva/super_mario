#include "third_level.hpp"
using biv::ThirdLevel;
ThirdLevel::ThirdLevel(UIFactory* ui_factory) : GameLevel(ui_factory) { init_data(); }
bool ThirdLevel::is_final() const noexcept { return true; }
biv::GameLevel* ThirdLevel::get_next() { return next; }
void ThirdLevel::init_data() 
{ 
    ui_factory->create_mario({39, 10}, 3, 3);

    ui_factory->create_ship({20, 25}, 30, 2);

    ui_factory->create_ship({62, 22}, 10, 5);

    ui_factory->create_ship({90, 25}, 12, 2);

    ui_factory->create_ship({122, 19}, 12, 8);

    ui_factory->create_ship({158, 25}, 14, 2);

    ui_factory->create_ship({185, 22}, 14, 5);


    ui_factory->create_box({38, 17}, 8, 2);
    ui_factory->create_full_box({48, 14}, 5, 3);

    ui_factory->create_box({95, 16}, 7, 2);
    ui_factory->create_full_box({128, 11}, 5, 3);


    ui_factory->create_moving_platform({70, 17}, 10, 2);
    ui_factory->create_moving_platform({138, 16}, 10, 2);

    ui_factory->create_ship({205, 20}, 12, 7);

    ui_factory->create_enemy({28, 5}, 3, 2);
    ui_factory->create_enemy({93, 5}, 3, 2);
    ui_factory->create_enemy({162, 5}, 3, 2);
    ui_factory->create_enemy({188, 5}, 3, 2);

    ui_factory->create_flying_enemy({55, 8}, 3, 2);
    ui_factory->create_flying_enemy({108, 7}, 3, 2);
    ui_factory->create_flying_enemy({175, 8}, 3, 2);

    ui_factory->create_jumping_enemy({65, 10}, 3, 2);
    ui_factory->create_jumping_enemy({126, 8}, 3, 2);
    ui_factory->create_jumping_enemy({165, 10}, 3, 2);

}