/************************************************************************
 * Filename:    TaskHelper.cpp
 * Description: 任务帮助类实现
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#include "TaskHelper.h"

std::future<void> TaskHelper::Delay(int milliseconds) {
	return std::async(std::launch::async, [=]() {
		std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
		});
}
