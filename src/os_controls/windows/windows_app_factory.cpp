#include "windows_app_factory.hpp"

#include "windows_keyboard.hpp"

std::unique_ptr<svr::KeyBoard> svr::WindowsAppFactory::create_keyboard() {
	return std::make_unique<WindowsKeyBoard>();
}
