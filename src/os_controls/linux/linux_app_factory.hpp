#pragma once

#include "app_factory.hpp"

namespace svr {
	class LinuxAppFactory : public AppFactory {
		public:
			std::unique_ptr<KeyBoard> create_keyboard() override;
	};
}
