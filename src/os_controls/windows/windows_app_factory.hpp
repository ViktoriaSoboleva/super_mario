#pragma once

#include "app_factory.hpp"

namespace svr {
	class WindowsAppFactory : public AppFactory {
		public:
			std::unique_ptr<KeyBoard> create_keyboard() override;
	};
}
