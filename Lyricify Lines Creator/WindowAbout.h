#pragma once

#include <thread>
#include "CommonDefine.h"

class WindowAbout
{
private:
	/// <summary>
	/// 打开窗口
	/// </summary>
	/// <param name="isOpened">窗口是否已经关闭</param>
	/// <param name="DPI_Scale">DPI 缩放比</param>
	/// <param name="rect">父窗口区域，不传入则随机位置</param>
	static void OpenWindow(bool* isOpened, double DPI_Scale, RECT rect = { -1, -1, -1, -1 });

public:
	/// <summary>
	/// 显示关于窗体
	/// </summary>
	/// <param name="DPI_Scale">DPI 缩放比</param>
	/// <param name="rect">父窗口区域，不传入则随机位置</param>
	static void Show(double DPI_Scale = 1, RECT rect = { -1, -1, -1, -1 });
};