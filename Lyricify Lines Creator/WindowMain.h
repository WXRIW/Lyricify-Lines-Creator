#pragma once

#include <functional>
#include "CommonDefine.h"
#include "LyricsHelper.h"
#include "FileHelper.h"
#include "resource.h"
#include "WindowAbout.h"
#include "MusicPlayer.h"
#include "TaskHelper.h"

#pragma warning(disable: 4244) // 禁用转换精度损失的 warning

namespace WindowMain
{
	void AddWindowControls(HWND);
	void ResizeMoveControls();
	void DrawLabelControls();
	void DrawPlaybackArea();
	void DrawAtWndProcPaint();

	void ButtonChooseAudio_Click();
	void ButtonChooseRawLyrics_Click();
	void ButtonOutputPath_Click();
	void ButtonPlayPause_Click();
	void ButtonAbout_Click();
	void ButtonViewOutput_Click();
	void ButtonPreview_Click();
	void ButtonRestart_Click();
	void ButtonStart_Click();

	RECT GetWindowRect();
	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void Show(double scale = 1);
};

