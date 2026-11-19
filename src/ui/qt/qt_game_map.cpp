#include "qt_game_map.hpp"

#include <algorithm>
#include <array>

#include <QColor>
#include <QFont>
#include <QLinearGradient>
#include <QImage>
#include <QPaintEvent>
#include <QPainter>
#include <QPolygon>
#include <QString>

namespace {
	constexpr int TILE_SIZE = 16;
	constexpr int VIEW_WIDTH = 52;
	constexpr int HUD_HEIGHT = 48;

	QColor sprite_color(const char pixel) {
		switch (pixel) {
			case 'C': return QColor(65, 143, 205);
			case 'c': return QColor(34, 76, 129);
			case 'F': return QColor(255, 226, 171);
			case 'T': return QColor(235, 166, 112);
			case 'G': return QColor(73, 163, 62);
			case 'g': return QColor(39, 111, 51);
			case 'V': return QColor(145, 105, 183);
			case 'v': return QColor(80, 55, 116);
			case 'K': return QColor(55, 40, 43);
			case 'Y': return QColor(255, 210, 62);
			case 'O': return QColor(198, 104, 49);
			case 'W': return QColor(255, 255, 255);
			case 'N': return QColor(235, 92, 58);
			case 'n': return QColor(151, 53, 39);
			case 'A': return QColor(42, 190, 179);
			case 'a': return QColor(24, 103, 113);
			case 'E': return QColor(164, 210, 76);
			case 'e': return QColor(63, 119, 43);
			case 'D': return QColor(94, 47, 29);
			case 'L': return QColor(190, 111, 52);
			default: return Qt::transparent;
		}
	}

	QImage make_sprite(const std::array<const char*, 16>& pixels) {
		QImage image(TILE_SIZE, TILE_SIZE, QImage::Format_ARGB32);
		image.fill(Qt::transparent);
		for (int y = 0; y < TILE_SIZE; ++y) {
			for (int x = 0; x < TILE_SIZE && pixels[y][x] != '\0'; ++x) {
				if (pixels[y][x] != '.') {
					image.setPixelColor(x, y, sprite_color(pixels[y][x]));
				}
			}
		}
		return image;
	}

	QImage load_sprite(const QString& resource_path) {
		QImage image(resource_path);
		if (image.isNull()) {
			qFatal("Failed to load sprite resource: %s", qPrintable(resource_path));
		}
		return image;
	}

	const QImage& sprite_image(const svr::QtSpriteKind kind) {
		static const QImage explorer = load_sprite(QStringLiteral(":/sprites/mario.png"));
		static const QImage moss_creature = load_sprite(QStringLiteral(":/sprites/enemy.png"));
		static const QImage flying_enemy = load_sprite(
			QStringLiteral(":/sprites/flying_enemy.png")
		);
		static const QImage stone_critter = make_sprite({
			"......DD......", "....DDLLDD....", "...DLLLLLLD...",
			"..DLLLLLLLLD..", ".DLLLLLLLLLLD.", "DLLLLLLLLLLLLD",
			"DLLLWWLLLLWWLLD", "DLLLWWLLLLWWLLD", "DLLLLLLLLLLLLD",
			".DLLLLLLLLLLD.", "..DLLLLLLLLD..", "...DLLLLLLD...",
			"...DDLLLLDD...", "..DD.LLLL.DD..", ".DD..LLLL..DD.",
			"DD...DDDD...DD."
		});
		static const QImage crystal = make_sprite({
			".......Y........", "......YYY.......", ".....YYYYY......",
			"....YYFFFFY.....", "...YYFFFFFFY....", "..YYFFFFFFFFY...",
			".YYFFFFFFFFFFY..", "YYYYFFFFFFFFYYY.", "YYYYFFFFFFFFYYY.",
			".YYFFFFFFFFFFY..", "..YYFFFFFFFFY...", "...YYFFFFFFY....",
			"....YYFFFFY.....", ".....YYYYY......", "......YYY.......",
			".......Y........"
		});
		static const QImage brick = make_sprite({
			"DDDDDDDDDDDDDDDD", "DLLLLLLLDDLLLLLD", "DLLLLLLLDDLLLLLD",
			"DLLLLLLDDLLLLLLD", "DLLLLLLLDDLLLLLD", "DLLLLLLLDDLLLLLD",
			"DDDDDDDDDDDDDDDD", "DLLLLLDDLLLLLLDD", "DLLLLLDDLLLLLLDD",
			"DLLLLLDDLLLLLLDD", "DLLLLLDDLLLLLLDD", "DLLLLLDDLLLLLLDD",
			"DDDDDDDDDDDDDDDD", "DLLLLLLLDDLLLLLD", "DLLLLLLLDDLLLLLD",
			"DDDDDDDDDDDDDDDD"
		});
		static const QImage power_block = make_sprite({
			"DDDDDDDDDDDDDDDD", "DLLLLLLLLLLLLLLD", "DLFFFFFFFFFFFFLD",
			"DLFFFFFFFFFFFFLD", "DLFFFFFYYFFFFFLD", "DLFFFFYYYYFFFFLD",
			"DLFFFYYYYYYFFFLD", "DLFFYYFFFFYYFFLD", "DLFFYYFFFFYYFFLD",
			"DLFFFYYYYYYFFFLD", "DLFFFFYYYYFFFFLD", "DLFFFFFYYFFFFFLD",
			"DLFFFFFFFFFFFFLD", "DLFFFFFFFFFFFFLD", "DLLLLLLLLLLLLLLD",
			"DDDDDDDDDDDDDDDD"
		});
		static const QImage grass = make_sprite({
			"GGGGGGGGGGGGGGGG", "GgGgGgGgGgGgGgGg", "DDDDDDDDDDDDDDDD",
			"DLLLLLLLLLLLLLLD", "DGGGGFFFFGGGGGGD", "DFFFFFFFFFFFFFFD",
			"DDDDDDDDDDDDDDDD", "DLLLLLLLDDLLLLLD", "DLLLLLLLDDLLLLLD",
			"DLGGGGGGDDGGGGGD", "DLGGGGGGDDGGGGGD", "DDDDDDDDDDDDDDDD",
			"DLLLLLLDDLLLLLLD", "DLLLLLLDDLLLLLLD", "DLLLLLLDDLLLLLLD",
			"DDDDDDDDDDDDDDDD"
		});
		static const QImage dirt = make_sprite({
			"DDDDDDDDDDDDDDDD", "DLLLLLLDDLLLLLLD", "DLLLLLLDDLLLLLLD",
			"DLLLLLLDDLLLLLLD", "DDDDDDDDDDDDDDDD", "DLLLLLLLLDDLLLLD",
			"DLLLLLLLDDLLLLLD", "DGGGGGGGGDDGGGGGD", "DGGGGGGGGDDGGGGGD",
			"DDDDDDDDDDDDDDDD", "DLLLLLLDDLLLLLLD", "DLLLLLLDDLLLLLLD",
			"DDDDDDDDDDDDDDDD", "DLLLLLLLLDDLLLLD", "DLLLLLLLDDLLLLLD",
			"DDDDDDDDDDDDDDDD"
		});
		static const QImage platform_top = make_sprite({
			"GGGGGGGGGGGGGGGG", "GgGgGgGgGgGgGgGg", "DDDDDDDDDDDDDDDD",
			"DLLLLLLLLLLLLLLD", "DLGGGGGGGGGGGGLD", "DLGGGGGGGGGGGGLD",
			"DLGGGGGGGGGGGGLD", "DDDDDDDDDDDDDDDD", "DLLLLLLDDLLLLLLD",
			"DLLLLLLDDLLLLLLD", "DGGGGGGDDGGGGGGD", "DGGGGGGDDGGGGGGD",
			"DDDDDDDDDDDDDDDD", "DLLLLLLDDLLLLLLD", "DLLLLLLDDLLLLLLD",
			"DDDDDDDDDDDDDDDD"
		});
		static const QImage platform_fill = make_sprite({
			"DDDDDDDDDDDDDDDD", "DLLLLLLDDLLLLLLD", "DLLLLLLDDLLLLLLD",
			"DLGGGGGDDGGGGGLD", "DLGGGGGDDGGGGGLD", "DDDDDDDDDDDDDDDD",
			"DLLLLLLDDLLLLLLD", "DLLLLLLDDLLLLLLD", "DGGGGGGDDGGGGGGD",
			"DGGGGGGDDGGGGGGD", "DDDDDDDDDDDDDDDD", "DLLLLLLDDLLLLLLD",
			"DLLLLLLDDLLLLLLD", "DGGGGGGDDGGGGGGD", "DGGGGGGDDGGGGGGD",
			"DDDDDDDDDDDDDDDD"
		});

		switch (kind) {
			case svr::QtSpriteKind::MARIO: return explorer;
			case svr::QtSpriteKind::ENEMY: return moss_creature;
			case svr::QtSpriteKind::FLYING_ENEMY: return flying_enemy;
			case svr::QtSpriteKind::JUMPING_ENEMY: return stone_critter;
			case svr::QtSpriteKind::MONEY: return crystal;
			case svr::QtSpriteKind::BRICK: return brick;
			case svr::QtSpriteKind::QUESTION: return power_block;
			case svr::QtSpriteKind::GROUND: return dirt;
			case svr::QtSpriteKind::PLATFORM: return platform_top;
			case svr::QtSpriteKind::PLATFORM_FILL: return platform_fill;
		}
		return brick;
	}

	void draw_cloud(QPainter& painter, const int x, const int y) {
		const QColor shadow(123, 191, 212);
		const QColor cloud(244, 255, 246);
		painter.fillRect(x + 16, y + 8, 32, 8, shadow);
		painter.fillRect(x + 8, y + 16, 48, 8, shadow);
		painter.fillRect(x, y + 24, 64, 8, shadow);
		painter.fillRect(x + 8, y + 32, 48, 8, shadow);
		painter.fillRect(x + 16, y, 32, 8, cloud);
		painter.fillRect(x + 8, y + 8, 48, 8, cloud);
		painter.fillRect(x, y + 16, 64, 8, cloud);
		painter.fillRect(x + 8, y + 24, 48, 8, cloud);
	}

	void draw_hill(QPainter& painter, const int x, const int base, const int width) {
		QPolygon hill;
		hill << QPoint(x, base) << QPoint(x + width / 2, base - 96)
			<< QPoint(x + width, base);
		painter.setPen(Qt::NoPen);
		painter.setBrush(QColor(68, 173, 133));
		painter.drawPolygon(hill);

		QPolygon highlight;
		highlight << QPoint(x + width / 5, base - 14)
			<< QPoint(x + width / 2, base - 96)
			<< QPoint(x + width * 4 / 5, base - 14)
			<< QPoint(x + width / 2, base - 35);
		painter.setBrush(QColor(118, 209, 147));
		painter.drawPolygon(highlight);
	}

	void draw_plant(QPainter& painter, const int x, const int ground) {
		painter.fillRect(x + 12, ground - 42, 4, 30, QColor(39, 133, 100));
		painter.fillRect(x + 2, ground - 30, 12, 6, QColor(75, 188, 120));
		painter.fillRect(x + 14, ground - 36, 12, 6, QColor(75, 188, 120));
		painter.fillRect(x + 6, ground - 50, 16, 8, QColor(255, 213, 105));
		painter.fillRect(x + 10, ground - 54, 8, 16, QColor(255, 239, 166));
		painter.fillRect(x + 12, ground - 48, 4, 8, QColor(232, 144, 82));
	}

	void draw_character_sprite(
		QPainter& painter,
		const QRectF& bounds,
		const QImage& image
	) {
		QSizeF size(image.size());
		size.scale(bounds.size(), Qt::KeepAspectRatio);
		const QRectF target(
			bounds.left() + (bounds.width() - size.width()) / 2,
			bounds.bottom() - size.height(),
			size.width(),
			size.height()
		);
		painter.drawImage(target, image);
	}

	void draw_hud(QPainter& painter, const int width, const int collected_gems) {
		painter.fillRect(0, 0, width, HUD_HEIGHT, QColor(25, 42, 67, 230));
		painter.fillRect(0, HUD_HEIGHT - 3, width, 3, QColor(93, 220, 197));

		QFont title_font(QStringLiteral("Consolas"), 11, QFont::Bold);
		QFont label_font(QStringLiteral("Consolas"), 8, QFont::Bold);
		painter.setFont(title_font);
		painter.setPen(QColor(150, 239, 230));
		painter.drawText(16, 20, QStringLiteral("PIXEL QUEST"));
		painter.setPen(QColor(255, 255, 255));
		painter.drawText(16, 37, QStringLiteral("ADVENTURE"));

		const int gem_x = width - 122;
		painter.setPen(QColor(183, 199, 222));
		painter.setFont(label_font);
		painter.drawText(gem_x, 17, QStringLiteral("COINS"));
		painter.fillRect(gem_x, 24, 10, 10, QColor(255, 211, 92));
		painter.fillRect(gem_x + 3, 21, 4, 16, QColor(255, 239, 166));
		painter.setPen(Qt::white);
		painter.setFont(title_font);
		painter.drawText(gem_x + 18, 35, QStringLiteral("%1").arg(collected_gems, 2, 10, QLatin1Char('0')));

		painter.setPen(QColor(183, 199, 222));
		painter.setFont(label_font);
		painter.drawText(width / 2 - 25, 17, QStringLiteral("WORLD"));
		painter.setPen(Qt::white);
		painter.setFont(title_font);
		painter.drawText(width / 2 - 18, 37, QStringLiteral("1 - 1"));
	}
}

using svr::QtGameMap;

QtGameMap::QtGameMap(const int height, const int width)
	: QWidget(), GameMap(height, width) {
	setWindowTitle(QStringLiteral("Pixel Quest - Platformer"));
	setFixedSize(std::min(width, VIEW_WIDTH) * TILE_SIZE, height * TILE_SIZE);
	setFocusPolicy(Qt::StrongFocus);
	QWidget::show();
	activateWindow();
	setFocus(Qt::OtherFocusReason);
}

void QtGameMap::add_obj(
	Rect* object,
	const QtSpriteKind sprite,
	const Collisionable* active_state
) {
	objects.push_back({object, sprite, active_state});
}

void QtGameMap::clear() noexcept {
	update();
}

void QtGameMap::remove_obj(Rect* object) {
	objects.erase(
		std::remove_if(
			objects.begin(),
			objects.end(),
			[object](const Drawable& drawable) { return drawable.rect == object; }
		),
		objects.end()
	);
}

void QtGameMap::refresh() noexcept {
	update();
}

void QtGameMap::remove_objs() {
	objects.clear();
}

void QtGameMap::show() const noexcept {
	const_cast<QtGameMap*>(this)->repaint();
}

void QtGameMap::paintEvent(QPaintEvent* event) {
	Q_UNUSED(event);
	QPainter painter(this);
	painter.setRenderHint(QPainter::SmoothPixmapTransform, false);
	QLinearGradient sky(0, 0, 0, QWidget::height());
	sky.setColorAt(0.0, QColor(83, 163, 247));
	sky.setColorAt(0.62, QColor(135, 205, 250));
	sky.setColorAt(1.0, QColor(215, 239, 251));
	painter.fillRect(rect(), sky);

	const auto mario = std::find_if(
		objects.cbegin(),
		objects.cend(),
		[](const Drawable& drawable) { return drawable.sprite == QtSpriteKind::MARIO; }
	);
	const float camera_x = mario == objects.cend()
		? 0.0f
		: mario->rect->get_x() - VIEW_WIDTH * 0.42f;

	const int screen_width = QWidget::width();
	const int far_camera_x = static_cast<int>(camera_x * 0.22f * TILE_SIZE);
	const int near_camera_x = static_cast<int>(camera_x * 0.48f * TILE_SIZE);
	draw_hill(painter, 64 - far_camera_x, 395, 230);
	draw_hill(painter, 390 - far_camera_x, 395, 270);
	draw_hill(painter, 760 - far_camera_x, 395, 240);
	draw_hill(painter, 200 - near_camera_x, 405, 130);
	draw_hill(painter, 620 - near_camera_x, 405, 170);
	for (const int world_x : {4, 28, 55, 82, 110, 139, 168, 195}) {
		const int x = (world_x - static_cast<int>(camera_x * 0.68f)) * TILE_SIZE;
		draw_cloud(painter, x, 82 + (world_x % 3) * 28);
	}
	for (const int world_x : {11, 42, 72, 101, 133, 164, 190}) {
		const int x = (world_x - static_cast<int>(camera_x)) * TILE_SIZE;
		draw_plant(painter, x, 430);
	}

	const int water_top = (GameMap::height - 3) * TILE_SIZE;
	painter.fillRect(0, water_top, screen_width, QWidget::height() - water_top,
		QColor(44, 153, 183));
	for (int y = water_top + 8; y < QWidget::height(); y += 16) {
		for (int x = (y / 8 % 2) * 16; x < screen_width; x += 64) {
			painter.fillRect(x, y, 24, 2, QColor(139, 222, 220));
		}
	}

	int collected_gems = 0;
	for (const Drawable& object : objects) {
		if (object.active_state != nullptr
			&& !object.active_state->is_active()) {
			if (object.sprite == QtSpriteKind::MONEY) {
				++collected_gems;
			}
			continue;
		}

		const Rect& model_rect = *object.rect;
		const int left = model_rect.get_left();
		const int top = model_rect.get_top();
		const int columns = model_rect.get_right() - left;
		const int rows = model_rect.get_bottom() - top;
		const float screen_left = (model_rect.get_x() - camera_x) * TILE_SIZE;
		if (screen_left + columns * TILE_SIZE < 0
			|| screen_left >= screen_width
			|| (top + rows) * TILE_SIZE < 0
			|| top * TILE_SIZE >= QWidget::height()) {
			continue;
		}
		const QRectF target(
			screen_left,
			model_rect.get_y() * TILE_SIZE,
			columns * TILE_SIZE,
			rows * TILE_SIZE
		);

		if (object.sprite == QtSpriteKind::MARIO
			|| object.sprite == QtSpriteKind::ENEMY
			|| object.sprite == QtSpriteKind::FLYING_ENEMY
			|| object.sprite == QtSpriteKind::JUMPING_ENEMY
			|| object.sprite == QtSpriteKind::MONEY) {
			if (object.sprite == QtSpriteKind::MARIO) {
				painter.fillRect(
					QRectF(target.x() + 8, target.bottom() - 3, target.width() - 16, 5),
					QColor(30, 63, 69, 60)
				);
			}
			draw_character_sprite(painter, target, sprite_image(object.sprite));
			continue;
		}

		const bool used_power_block =
			object.sprite == QtSpriteKind::QUESTION
				&& object.active_state != nullptr
				&& !object.active_state->is_active();
		const QtSpriteKind tile_sprite = used_power_block
			? QtSpriteKind::BRICK : object.sprite;
		for (int row = 0; row < rows; ++row) {
			for (int column = 0; column < columns; ++column) {
				QtSpriteKind tile = tile_sprite;
				if (tile_sprite == QtSpriteKind::GROUND && row == 0) {
					tile = QtSpriteKind::PLATFORM;
				} else if (tile_sprite == QtSpriteKind::PLATFORM && row == 0) {
					tile = QtSpriteKind::PLATFORM;
				} else if (tile_sprite == QtSpriteKind::PLATFORM) {
					tile = QtSpriteKind::PLATFORM_FILL;
				} else if (tile_sprite == QtSpriteKind::QUESTION && row > 0) {
					tile = QtSpriteKind::BRICK;
				}
				const QPointF tile_position(
					screen_left + column * TILE_SIZE,
					(top + row) * TILE_SIZE
				);
				painter.drawImage(tile_position, sprite_image(tile));
				if (tile_sprite == QtSpriteKind::QUESTION && row == 0) {
					painter.setPen(QColor(94, 47, 29));
					painter.setFont(QFont(QStringLiteral("Consolas"), 12, QFont::Bold));
					painter.drawText(
						QRectF(tile_position.x(), tile_position.y() - 1, TILE_SIZE, TILE_SIZE + 2),
						Qt::AlignCenter,
						QStringLiteral("?")
					);
				}
			}
		}
	}
	draw_hud(painter, screen_width, collected_gems);
}
