/************************************************************************
 * Filename:    TaskHelper.h
 * Description: 任务帮助类定义
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#pragma once

#include <chrono>
#include <future>
#include <thread>

class TaskHelper
{
public:
	/// <summary>
	/// 不阻塞的暂停指定毫秒数
	/// 用法: Delay(ms).wait();
	/// </summary>
	/// <param name="milliseconds">要暂停的毫秒数</param>
	static std::future<void> Delay(int milliseconds);
};
