#include "qt_app_factory.hpp"

#include "qt_keyboard.hpp"

svr::QtAppFactory::QtAppFactory(QApplication* application)
	: application(application) {}

std::unique_ptr<svr::KeyBoard> svr::QtAppFactory::create_keyboard() {
	return std::make_unique<QtKeyboard>(application);
}
