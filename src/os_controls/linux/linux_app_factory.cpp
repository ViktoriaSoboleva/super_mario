#include "linux_app_factory.hpp"

#include "linux_keyboard.hpp"

std::unique_ptr<svr::KeyBoard> svr::LinuxAppFactory::create_keyboard() {
	return std::make_unique<LinuxKeyboard>();
}
