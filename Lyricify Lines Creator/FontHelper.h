/************************************************************************
 * Filename:    FontHelper.h
 * Description: 字体帮助类定义
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#pragma once

#include <string>
#include <Windows.h>

class FontHelper
{
public:
	/// <summary>
	/// 获取文本的实际渲染尺寸
	/// </summary>
	/// <param name="text">文本字符串</param>
	/// <param name="fontName">字体名</param>
	/// <param name="fontSize">字号</param>
	/// <param name="dpiScale">DPI 缩放比</param>
	/// <param name="fontWeight">字重</param>
	/// <param name="italic">斜体</param>
	/// <param name="underline">下划线</param>
	/// <param name="strikeout">删除线</param>
	/// <returns>文本的实际渲染尺寸</returns>
	static SIZE CalculateTextSize(const wchar_t* text, const wchar_t* fontName, int fontSize, int dpiScale = 1, int fontWeight = FW_DONTCARE, bool italic = false, bool underline = false, bool strikeout = false);
};
