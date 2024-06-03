/************************************************************************
 * Filename:    main.cpp
 * Description: 程序入口点
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#include <fstream>
#include <vector>
#include <string>

#include "DpiHelper.h" // 须优先引用，其中定义了系统要求常量
#include "CommonDefine.h"
#include "WindowMain.h"

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"") // 不显示控制台

double DPI_Scale = 1;

int main()
{
	if (ENABLE_HIGHDPI)
	{
		// 高 DPI 支持
		DPI_Scale = GetDpiScale(); // 必须先获取，在设置 DPI Aware 后这个值将变为 1
		EnableDpiAwareness();

		hiex::SysControlBase::DPI_Scale = DPI_Scale;
	}

	hiex::SetCustomIcon(MAKEINTRESOURCE(IDI_ICON1), MAKEINTRESOURCE(IDI_ICON1));
	WindowMain::Show(DPI_Scale);

	closegraph();
	return 0;
}
