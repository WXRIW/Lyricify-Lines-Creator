/************************************************************************
 * Filename:    WindowPreviewOutput.h
 * Description: 预览输出窗体方法定义
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
#include "StringHelper.h"
#include "WindowHelper.h"

namespace WindowPreviewOutput
{
	/// <summary>
	/// 显示预览输出窗体
	/// </summary>
	/// <param name="DPI_Scale">DPI 缩放比</param>
	/// <param name="rect">父窗口区域，不传入则随机位置</param>
	/// <param name="hParent">父窗口句柄</param>
	void Show(std::wstring filePath, std::wstring fileContent, double DPI_Scale = 1, RECT rect = { -1, -1, -1, -1 }, HWND hParent = (HWND)nullptr);

	/// <summary>
	/// 预览输出窗体是否正在显示
	/// </summary>
	bool IsOpened();
}
