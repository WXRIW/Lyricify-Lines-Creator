/************************************************************************
 * Filename:    WindowHelper.h
 * Description: 窗口帮助类定义
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#pragma once

#include <Windows.h>

class WindowHelper
{
public:
    /// <summary>
    /// 启用窗口的最小化按钮
    /// </summary>
    /// <param name="hWnd">窗口句柄</param>
    /// <param name="enable">是否启用</param>
    static void EnableMinimizeButton(HWND hWnd, bool enable);
};
