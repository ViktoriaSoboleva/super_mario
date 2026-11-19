#pragma once

#include <QApplication>

#include "app_factory.hpp"

namespace svr {
	class QtAppFactory : public AppFactory {
		private:
			QApplication* application;

		public:
			explicit QtAppFactory(QApplication* application);
			std::unique_ptr<KeyBoard> create_keyboard() override;
	};
}
