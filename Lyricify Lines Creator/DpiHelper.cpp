/************************************************************************
 * Filename:    DpiHelper.cpp
 * Description: DPI 帮助方法实现
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#include "DpiHelper.h"
#include <Windows.h>

void EnableDpiAwareness()
{
	HMODULE hShcore = LoadLibrary(L"Shcore.dll");
	if (hShcore != NULL)
	{
		typedef HRESULT(WINAPI* LPFNSPDPIA)(PROCESS_DPI_AWARENESS);
		LPFNSPDPIA lSetProcessDpiAwareness = (LPFNSPDPIA)GetProcAddress(hShcore, "SetProcessDpiAwareness");
		if (lSetProcessDpiAwareness != NULL)
		{
			HRESULT hr = lSetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
			if (!SUCCEEDED(hr)) SetProcessDPIAware();
		}
		else SetProcessDPIAware();

		FreeLibrary(hShcore);
	}
	else SetProcessDPIAware();
}

int GetDpi()
{
	// 仅可用于 Windows 10 1607
	/*HWND hwnd = GetDesktopWindow();
	return GetDpiForWindow(hwnd);*/

    return (int)(GetDpiScale() * 96);
}

double GetDpiScale()
{
    // 获取窗口当前显示的监视器
    // 使用桌面的句柄.
    HWND hWnd = GetDesktopWindow();
    HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

    // 获取监视器逻辑宽度与高度
    MONITORINFOEX miex;
    miex.cbSize = sizeof(miex);
    GetMonitorInfo(hMonitor, &miex);
    int cxLogical = (miex.rcMonitor.right - miex.rcMonitor.left);
    int cyLogical = (miex.rcMonitor.bottom - miex.rcMonitor.top);

    // 获取监视器物理宽度与高度
    DEVMODE dm;
    dm.dmSize = sizeof(dm);
    dm.dmDriverExtra = 0;
    EnumDisplaySettings(miex.szDevice, ENUM_CURRENT_SETTINGS, &dm);
    int cxPhysical = dm.dmPelsWidth;
    int cyPhysical = dm.dmPelsHeight;

    // 缩放比例计算  实际上使用任何一个即可
    double horzScale = ((double)cxPhysical / (double)cxLogical);
    double vertScale = ((double)cyPhysical / (double)cyLogical);
    return horzScale;
}