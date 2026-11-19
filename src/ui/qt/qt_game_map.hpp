#pragma once

#include <vector>

#include <QWidget>

#include "collisionable.hpp"
#include "game_map.hpp"
#include "rect.hpp"

class QPaintEvent;

namespace svr {
	enum class QtSpriteKind {
		MARIO,
		ENEMY,
		FLYING_ENEMY,
		JUMPING_ENEMY,
		MONEY,
		BRICK,
		QUESTION,
		GROUND,
		PLATFORM,
		PLATFORM_FILL
	};

	class QtGameMap : public QWidget, public GameMap {
		private:
			struct Drawable {
				Rect* rect;
				QtSpriteKind sprite;
				const Collisionable* active_state;
			};

			std::vector<Drawable> objects;

		public:
			QtGameMap(int height, int width);

			void add_obj(
				Rect* object,
				QtSpriteKind sprite,
				const Collisionable* active_state = nullptr
			);
			void clear() noexcept override;
			void refresh() noexcept override;
			void remove_obj(Rect* object);
			void remove_objs() override;
			void show() const noexcept override;

		protected:
			void paintEvent(QPaintEvent* event) override;
	};
}
