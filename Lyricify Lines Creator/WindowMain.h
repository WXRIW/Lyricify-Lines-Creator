#pragma once

#include <functional>
#include "CommonDefine.h"
#include "LyricsHelper.h"
#include "FileHelper.h"
#include "resource.h"
#include "WindowAbout.h"

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

	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void Show(double scale = 1);
};

