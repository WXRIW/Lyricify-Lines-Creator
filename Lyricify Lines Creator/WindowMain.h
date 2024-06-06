/************************************************************************
 * Filename:    WindowMain.h
 * Description: 主窗体方法定义
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#pragma once

#include <functional>
#include <iostream>
#include "CommonDefine.h"
#include "LyricsHelper.h"
#include "FileHelper.h"
#include "resource.h"
#include "WindowAbout.h"
#include "WindowPreviewLyrics.h"
#include "WindowPreviewOutput.h"
#include "WindowSettings.h"
#include "MusicPlayer.h"
#include "TaskHelper.h"
#include "ProcedureHelper.h"

#pragma comment(lib, "imm32.lib")

namespace WindowMain
{
	void AddWindowControls(HWND);
	void ResizeMoveControls();
	void DrawLabelControls();
	void DrawPlaybackArea();
	void DrawAtWndProcPaint(bool ignoreInRefreshUI);
	void RefreshUI();

	void ButtonChooseAudio_Click();
	void ButtonChooseRawLyrics_Click();
	void ButtonOutputPath_Click();
	void ButtonPlayPause_Click();
	void ButtonAbout_Click();
	void ButtonSettings_Click();
	void ButtonViewOutput_Click();
	void ButtonPreview_Click();
	void ButtonRestart_Click();
	void ButtonStart_Click();

	std::wstring GetOutputFullpath();
	int GetCurrentLineIndex();
	Lyricify::Lyrics* GetCurrentLine(int index = -1);
	std::wstring GetCurrentLineString(int index = -2);
	std::vector<std::wstring> GetComingLinesString(int index = -2, size_t maxSize = -1);

	void KeyboardEvents(WPARAM wParam);
	RECT GetWindowRect();
	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void Show(double scale = 1);
};
