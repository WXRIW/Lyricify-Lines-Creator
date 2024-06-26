/************************************************************************
 * Filename:    WindowPreviewLyrics.h
 * Description: 预览歌词窗体方法定义
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#pragma once

#include <cmath>
#include <fstream>
#include <math.h>
#include <string>
#include <Windows.h>
#include "CommonDefine.h"
#include "FileHelper.h"
#include "FontHelper.h"
#include "Lyrics.h"
#include "LyricsHelper.h"
#include "MusicPlayer.h"
#include "StringHelper.h"
#include "TaskHelper.h"
#include "WindowHelper.h"

namespace WindowPreviewLyrics
{
	/// <summary>
	/// 显示预览歌词窗体
	/// </summary>
	/// <param name="DPI_Scale">DPI 缩放比</param>
	/// <param name="rect">父窗口区域，不传入则随机位置</param>
	/// <param name="hParent">父窗口句柄</param>
	void Show(std::vector<Lyricify::Lyrics> lyricsList, double DPI_Scale = 1, RECT rect = { -1, -1, -1, -1 }, HWND hParent = (HWND)nullptr);

	/// <summary>
	/// 预览歌词窗体是否正在显示
	/// </summary>
	bool IsOpened();
}
