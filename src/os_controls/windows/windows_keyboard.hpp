#pragma once

#include "keyboard.hpp"

namespace svr {
	class WindowsKeyBoard : public KeyBoard {
		public:
			UserInput get_user_input() override;
			void on() override;
			void off() override;
	};
}
