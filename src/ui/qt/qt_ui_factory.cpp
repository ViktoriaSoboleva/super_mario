#include "qt_ui_factory.hpp"

#include <stdexcept>
#include <utility>

using svr::QtUIFactory;

QtUIFactory::QtUIFactory(Game* game) : UIFactory(game) {}

void QtUIFactory::add_drawable(
	Rect* object,
	const QtSpriteKind sprite,
	const Collisionable* active_state
) {
	if (game_map == nullptr) {
		throw std::logic_error("Qt game map must be created before level objects");
	}
	game_map->add_obj(object, sprite, active_state);
}

void QtUIFactory::clear_data() {
	game->remove_objs();
	if (game_map != nullptr) {
		game_map->remove_objs();
	}

	mario.reset();
	boxes.clear();
	full_boxes.clear();
	ships.clear();
	enemies.clear();
	flying_enemies.clear();
	jumping_enemies.clear();
	moving_platforms.clear();
	moneys.clear();
}

void QtUIFactory::create_box(
	const Coord& top_left, const int width, const int height
) {
	auto box = std::make_unique<Box>(top_left, width, height);
	Box* raw_box = box.get();
	boxes.push_back(std::move(box));
	game->add_map_movable(raw_box);
	game->add_static_obj(raw_box);
	add_drawable(static_cast<Rect*>(raw_box), QtSpriteKind::BRICK);
}

void QtUIFactory::create_enemy(
	const Coord& top_left, const int width, const int height
) {
	auto enemy = std::make_unique<Enemy>(top_left, width, height);
	Enemy* raw_enemy = enemy.get();
	enemies.push_back(std::move(enemy));
	game->add_map_movable(raw_enemy);
	game->add_movable(raw_enemy);
	game->add_collisionable(raw_enemy);
	add_drawable(
		static_cast<Rect*>(raw_enemy),
		QtSpriteKind::ENEMY,
		static_cast<const Collisionable*>(raw_enemy)
	);
}

void QtUIFactory::create_flying_enemy(
	const Coord& top_left, const int width, const int height
) {
	auto enemy = std::make_unique<FlyingEnemy>(top_left, width, height);
	FlyingEnemy* raw_enemy = enemy.get();
	flying_enemies.push_back(std::move(enemy));
	game->add_map_movable(raw_enemy);
	game->add_movable(raw_enemy);
	game->add_collisionable(raw_enemy);
	add_drawable(
		static_cast<Rect*>(raw_enemy),
		QtSpriteKind::FLYING_ENEMY,
		static_cast<const Collisionable*>(raw_enemy)
	);
}

void QtUIFactory::create_jumping_enemy(
	const Coord& top_left, const int width, const int height
) {
	auto enemy = std::make_unique<JumpingEnemy>(top_left, width, height);
	JumpingEnemy* raw_enemy = enemy.get();
	jumping_enemies.push_back(std::move(enemy));
	game->add_map_movable(raw_enemy);
	game->add_movable(raw_enemy);
	game->add_collisionable(raw_enemy);
	add_drawable(
		static_cast<Rect*>(raw_enemy),
		QtSpriteKind::JUMPING_ENEMY,
		static_cast<const Collisionable*>(raw_enemy)
	);
}

void QtUIFactory::create_full_box(
	const Coord& top_left, const int width, const int height
) {
	auto box = std::make_unique<FullBox>(top_left, width, height, this);
	FullBox* raw_box = box.get();
	full_boxes.push_back(std::move(box));
	game->add_collisionable(raw_box);
	game->add_map_movable(raw_box);
	game->add_static_obj(raw_box);
	add_drawable(
		static_cast<Rect*>(raw_box),
		QtSpriteKind::QUESTION,
		static_cast<const Collisionable*>(raw_box)
	);
}

void QtUIFactory::create_mario(
	const Coord& top_left, const int width, const int height
) {
	if (mario != nullptr) {
		game->remove_collisionable(mario.get());
		game->remove_movable(mario.get());
		game_map->remove_obj(static_cast<Rect*>(mario.get()));
		game->remove_mario();
	}

	mario = std::make_unique<Mario>(top_left, width, height);
	game->add_collisionable(mario.get());
	game->add_movable(mario.get());
	game->add_mario(mario.get());
	add_drawable(static_cast<Rect*>(mario.get()), QtSpriteKind::MARIO);
}

void QtUIFactory::create_money(
	const Coord& top_left, const int width, const int height
) {
	auto money = std::make_unique<Money>(top_left, width, height);
	Money* raw_money = money.get();
	moneys.push_back(std::move(money));
	game->add_map_movable(raw_money);
	game->add_movable(raw_money);
	game->add_collisionable(raw_money);
	add_drawable(
		static_cast<Rect*>(raw_money),
		QtSpriteKind::MONEY,
		static_cast<const Collisionable*>(raw_money)
	);
}

void QtUIFactory::create_ship(
	const Coord& top_left, const int width, const int height
) {
	auto ship = std::make_unique<Ship>(top_left, width, height);
	Ship* raw_ship = ship.get();
	ships.push_back(std::move(ship));
	game->add_map_movable(raw_ship);
	game->add_static_obj(raw_ship);
	add_drawable(static_cast<Rect*>(raw_ship), QtSpriteKind::GROUND);
}

void QtUIFactory::create_moving_platform(
	const Coord& top_left, const int width, const int height
) {
	auto platform = std::make_unique<MovingPlatform>(top_left, width, height);
	MovingPlatform* raw_platform = platform.get();
	moving_platforms.push_back(std::move(platform));
	game->add_map_movable(raw_platform);
	game->add_moving_platform(raw_platform);
	game->add_static_obj(raw_platform);
	add_drawable(static_cast<Rect*>(raw_platform), QtSpriteKind::PLATFORM);
}

svr::GameMap* QtUIFactory::get_game_map(const int height, const int width) {
	if (game_map == nullptr) {
		game_map = std::make_unique<QtGameMap>(height, width);
	}
	return game_map.get();
}

svr::Mario* QtUIFactory::get_mario() {
	return mario.get();
}
