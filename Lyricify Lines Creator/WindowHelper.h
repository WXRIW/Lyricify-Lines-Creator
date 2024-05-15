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
