#include <thread>
#include <memory>

#ifdef QT_UI
	#include <QApplication>
	#include "qt_app_factory.hpp"
	#include "qt_ui_factory.hpp"
#else
#include "console_ui_factory.hpp"
#endif
#include "first_level.hpp"
#include "game.hpp"
#include "game_level.hpp"
#include "game_map.hpp"
#include "keyboard.hpp"
#include "mario.hpp"
#include "os_control_settings.hpp"
#include "ui_factory.hpp"

#if defined(WINDOWS_CONSOLE)
	#include "windows_app_factory.hpp"
	#include "windows_control_settings.hpp"
#elif defined(LINUX_CONSOLE)
	#include "linux_app_factory.hpp"
	#include "linux_control_settings.hpp"
	#include "ncurses.h"
#endif

int main(int argc, char* argv[]) {
#ifdef QT_UI
	QApplication application(argc, argv);
#endif
	const int map_height = 30;
	const int map_weight = 200;
	auto frame_delay = std::chrono::milliseconds(0);
	
	svr::OSControlSettings* control_settings = nullptr;
	std::unique_ptr<svr::AppFactory> app_factory;
#ifdef QT_UI
	app_factory = std::make_unique<svr::QtAppFactory>(&application);
	frame_delay = std::chrono::milliseconds(16);
#elif defined(WINDOWS_CONSOLE)
		app_factory = std::make_unique<svr::WindowsAppFactory>();
		control_settings = new svr::WindowsControlSettings();
		frame_delay = std::chrono::milliseconds(10);
#elif defined(LINUX_CONSOLE)
		app_factory = std::make_unique<svr::LinuxAppFactory>();
		control_settings = new svr::LinuxControlSettings(map_height, map_weight);
		frame_delay = std::chrono::milliseconds(50);
#endif

	std::unique_ptr<svr::KeyBoard> keyboard = app_factory->create_keyboard();
	
	if (control_settings != nullptr) {
		control_settings->init();
	}
	keyboard->on();
	
	svr::Game game;
#ifdef QT_UI
	svr::QtUIFactory qt_ui_factory(&game);
	svr::UIFactory* ui_factory = &qt_ui_factory;
#else
	svr::UIFactory* ui_factory = new svr::ConsoleUIFactory(&game);
#endif
	svr::GameMap* game_map = ui_factory->get_game_map(map_height, map_weight);
	svr::GameLevel* game_level = new svr::FirstLevel(ui_factory);
	svr::Mario* mario = ui_factory->get_mario();
	
	svr::UserInput user_input;
	do {
		user_input = keyboard->get_user_input();
		switch (user_input) {
			case svr::UserInput::MAP_LEFT:
				mario->move_map_left();
				if (!game.check_static_collisions(mario)) {
					game.move_map_left();
				}
				mario->move_map_right();
				break;
			case svr::UserInput::MAP_RIGHT:
				mario->move_map_right();
				if (!game.check_static_collisions(mario)) {
					game.move_map_right();
				}
				mario->move_map_left();
				break;
			case svr::UserInput::MARIO_JUMP:
				mario->jump();
				break;
			case svr::UserInput::EXIT:
				game.finish();
				break;
		}
		
		game.move_objs_horizontally();
		game.check_horizontally_static_collisions();
		
		game.move_objs_vertically();
		game.check_mario_collision();
		game.check_vertically_static_collisions();

		game.check_mario_on_platform();
		
		if (
			game_map->is_below_map(mario->get_top())
			|| !mario->is_active()
		) {
			keyboard->off();
			keyboard->on();
			game_level->restart();
			mario = ui_factory->get_mario();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		
		if (game.is_level_end()) {
			if (!game_level->is_final()) {
				game_level = game_level->get_next();
				mario = ui_factory->get_mario();
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				keyboard->off();
				keyboard->on();
				game.start_level();
			} else {
				game.finish();
			}
		}
		
		game_map->refresh();
		if (control_settings != nullptr) {
			control_settings->set_cursor_start_position();
		}
		game_map->show();
		std::this_thread::sleep_for(frame_delay);
	} while (
		!game.is_finished()
	);
	
}
