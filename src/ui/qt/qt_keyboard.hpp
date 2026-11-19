#pragma once

#include <QSet>
#include <QObject>

#include "keyboard.hpp"

class QApplication;
class QEvent;

namespace svr {
	class QtKeyboard : public QObject, public KeyBoard {
		private:
			QApplication* application;
			QSet<int> pressed_keys;
			bool enabled = false;
			bool exit_requested = false;

		public:
			explicit QtKeyboard(QApplication* application);
			~QtKeyboard() override;

			UserInput get_user_input() override;
			void off() override;
			void on() override;

		protected:
			bool eventFilter(QObject* watched, QEvent* event) override;
	};
}
