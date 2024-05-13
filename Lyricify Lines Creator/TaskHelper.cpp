#include "TaskHelper.h"

std::future<void> TaskHelper::Delay(int milliseconds) {
	return std::async(std::launch::async, [=]() {
		std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
		});
}
