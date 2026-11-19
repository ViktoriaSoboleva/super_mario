#pragma once

#include <memory>
#include <vector>

#include "box.hpp"
#include "enemy.hpp"
#include "flying_enemy.hpp"
#include "full_box.hpp"
#include "jumping_enemy.hpp"
#include "mario.hpp"
#include "money.hpp"
#include "moving_platform.hpp"
#include "qt_game_map.hpp"
#include "ship.hpp"
#include "ui_factory.hpp"

namespace svr {
	class QtUIFactory : public UIFactory {
		private:
			std::unique_ptr<QtGameMap> game_map;
			std::vector<std::unique_ptr<Box>> boxes;
			std::vector<std::unique_ptr<FullBox>> full_boxes;
			std::vector<std::unique_ptr<Ship>> ships;
			std::unique_ptr<Mario> mario;
			std::vector<std::unique_ptr<Enemy>> enemies;
			std::vector<std::unique_ptr<FlyingEnemy>> flying_enemies;
			std::vector<std::unique_ptr<JumpingEnemy>> jumping_enemies;
			std::vector<std::unique_ptr<MovingPlatform>> moving_platforms;
			std::vector<std::unique_ptr<Money>> moneys;

			void add_drawable(
				Rect* object,
				QtSpriteKind sprite,
				const Collisionable* active_state = nullptr
			);

		public:
			explicit QtUIFactory(Game* game);

			void clear_data() override;
			void create_box(const Coord& top_left, int width, int height) override;
			void create_enemy(const Coord& top_left, int width, int height) override;
			void create_flying_enemy(const Coord& top_left, int width, int height) override;
			void create_jumping_enemy(const Coord& top_left, int width, int height) override;
			void create_full_box(const Coord& top_left, int width, int height) override;
			void create_mario(const Coord& top_left, int width, int height) override;
			void create_money(const Coord& top_left, int width, int height) override;
			void create_ship(const Coord& top_left, int width, int height) override;
			void create_moving_platform(
				const Coord& top_left, int width, int height
			) override;
			GameMap* get_game_map(int height, int width) override;
			Mario* get_mario() override;
	};
}
