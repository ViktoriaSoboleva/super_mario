#include "qt_keyboard.hpp"

#include <QApplication>
#include <QEvent>
#include <QKeyEvent>
#include <QEventLoop>

using svr::QtKeyboard;
using svr::UserInput;

QtKeyboard::QtKeyboard(QApplication* application)
	: QObject(), application(application) {
	this->application->installEventFilter(this);
}

QtKeyboard::~QtKeyboard() {
	application->removeEventFilter(this);
}

UserInput QtKeyboard::get_user_input() {
	application->processEvents(QEventLoop::AllEvents, 1);
	if (!enabled) {
		return UserInput::NO_INPUT;
	}
	if (exit_requested || pressed_keys.contains(Qt::Key_Q)
		|| pressed_keys.contains(Qt::Key_Escape)) {
		return UserInput::EXIT;
	}
	if (pressed_keys.contains(Qt::Key_Space)
		|| pressed_keys.contains(Qt::Key_Up)) {
		return UserInput::MARIO_JUMP;
	}
	if (pressed_keys.contains(Qt::Key_A)
		|| pressed_keys.contains(Qt::Key_Left)) {
		return UserInput::MAP_RIGHT;
	}
	if (pressed_keys.contains(Qt::Key_D)
		|| pressed_keys.contains(Qt::Key_Right)) {
		return UserInput::MAP_LEFT;
	}
	return UserInput::NO_INPUT;
}

void QtKeyboard::off() {
	enabled = false;
	pressed_keys.clear();
}

void QtKeyboard::on() {
	enabled = true;
	pressed_keys.clear();
}

bool QtKeyboard::eventFilter(QObject* watched, QEvent* event) {
	if (enabled && event->type() == QEvent::KeyPress) {
		const auto* key_event = static_cast<QKeyEvent*>(event);
		if (!key_event->isAutoRepeat()) {
			pressed_keys.insert(key_event->key());
		}
	} else if (enabled && event->type() == QEvent::KeyRelease) {
		const auto* key_event = static_cast<QKeyEvent*>(event);
		if (!key_event->isAutoRepeat()) {
			pressed_keys.remove(key_event->key());
		}
	} else if (enabled && event->type() == QEvent::Close) {
		exit_requested = true;
	}
	return QObject::eventFilter(watched, event);
}
