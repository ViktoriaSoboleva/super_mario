#pragma once

#include <memory>

#include "keyboard.hpp"

namespace svr {
	class AppFactory {
		public:
			virtual ~AppFactory() = default;
			virtual std::unique_ptr<KeyBoard> create_keyboard() = 0;
	};
}
