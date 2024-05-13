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
