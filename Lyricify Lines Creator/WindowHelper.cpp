/************************************************************************
 * Filename:    WindowHelper.cpp
 * Description: 窗口帮助类实现
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#include "WindowHelper.h"

void WindowHelper::EnableMinimizeButton(HWND hWnd, bool enable)
{
    LONG style = GetWindowLong(hWnd, GWL_STYLE);
    if (enable)
    {
        style |= WS_MINIMIZEBOX;
    }
    else
    {
        style &= ~WS_MINIMIZEBOX;
    }
    SetWindowLong(hWnd, GWL_STYLE, style);
    SetWindowPos(hWnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}
