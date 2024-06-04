/************************************************************************
 * Filename:    WindowSettings.h
 * Description: 设置窗体方法定义
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#pragma once

#include <fstream>
#include <string>
#include <Windows.h>
#include "CommonDefine.h"
#include "FontHelper.h"
#include "StringHelper.h"
#include "WindowHelper.h"

namespace WindowSettings
{
	/// <summary>
	/// 显示设置窗体
	/// </summary>
	/// <param name="DPI_Scale">DPI 缩放比</param>
	/// <param name="rect">父窗口区域，不传入则随机位置</param>
	/// <param name="hParent">父窗口句柄</param>
	void Show(double DPI_Scale = 1, RECT rect = { -1, -1, -1, -1 }, HWND hParent = (HWND)nullptr);

	/// <summary>
	/// 关于窗体是否正在显示
	/// </summary>
	bool IsOpened();
}
