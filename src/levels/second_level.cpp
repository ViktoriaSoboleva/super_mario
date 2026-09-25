#include "second_level.hpp"

using biv::SecondLevel;

SecondLevel::SecondLevel(UIFactory* ui_factory) : GameLevel(ui_factory) {
	init_data();
}

bool SecondLevel::is_final() const noexcept {
	return true;
}

biv::GameLevel* SecondLevel::get_next() {
	return next;
}

// ----------------------------------------------------------------------------
// 									PROTECTED
// ----------------------------------------------------------------------------
void SecondLevel::init_data() {
	ui_factory->create_mario({39, 10}, 3, 3);
	
	ui_factory->create_ship({20, 25}, 35, 2);

	ui_factory->create_ship({60, 20}, 12, 7);
	ui_factory->create_ship({82, 25}, 18, 2);
	
	ui_factory->create_ship({150, 25}, 35, 2);

	ui_factory->create_box({45, 17}, 8, 2);
	ui_factory->create_full_box({86, 17}, 6, 3);

	ui_factory->create_box({135, 13}, 10, 2);
	ui_factory->create_full_box({160, 18}, 6, 3);

	ui_factory->create_moving_platform({100, 18}, 12, 2);

	ui_factory->create_ship({195, 20}, 12, 7);

	ui_factory->create_enemy({30, 5}, 3, 2);
	ui_factory->create_enemy({88, 5}, 3, 2);
	ui_factory->create_enemy({155, 5}, 3, 2);

	ui_factory->create_flying_enemy({75, 8}, 3, 2);

	ui_factory->create_jumping_enemy({125, 10}, 3, 2);
	ui_factory->create_jumping_enemy({170, 10}, 3, 2);
}
