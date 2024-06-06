/************************************************************************
 * Filename:    WindowPreviewLyrics.cpp
 * Description: 预览歌词窗体实现
 * Author:      XY Wang, TL Chen, JZ Zhang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#include "WindowPreviewLyrics.h"

namespace WindowPreviewLyrics
{
	const int WINDOW_WIDTH = 500;
	const int WINDOW_HEIGHT = 500;
	const int MIN_WINDOW_WIDTH = 500;
	const int MIN_WINDOW_HEIGHT = 400;

	bool IsInRefreshUI = false;
	bool IsInDrawAtWndProcPaint = false;
	bool isOpened = false;
	double DPI_Scale = 1;

	hiex::Window* Window;
	hiex::Canvas* CanvasMain;
	hiex::SysButton* ButtonPlayPause;
	std::vector<Lyricify::Lyrics> LyricsList;

	/// <summary>
	/// 动画缓动函数，由 Lyricify 提供
	/// </summary>
	static double FuncEase(double x)
	{
		x = x * 0.9793195;
		auto a = -10.55 * std::pow(x, 7) + 42.76 * std::pow(x, 6) - 73.36 * std::pow(x, 5) + 70.9 * std::pow(x, 4) - 41.89 * std::pow(x, 3) + 12.98 * std::pow(x, 2) + 0.1638 * x;
		return a / 1.0041521796874393;
	}

	/// <summary>
	/// 绘制画布
	/// </summary>
	static void DrawAtWndProcPaint(bool ignoreInRefreshUI = false)
	{
		if (IsInDrawAtWndProcPaint || IsInRefreshUI && !ignoreInRefreshUI) return;
		IsInDrawAtWndProcPaint = true;

		int w = CanvasMain->GetWidth() / DPI_Scale;
		int h = CanvasMain->GetHeight() / DPI_Scale;

		CanvasMain->SetBkColor(BACKGROUND_COLOR);

		// TODO: 这里写画板（歌词部分）应该怎么画

		int index = 0;
		const int SCROLL_DURATION = 600;
		const int LINE_HEIGHT = 42;
		int currentTime = MusicPlayer::GetCurrentPositionMs();

		// 找到当前播放歌词的索引index
		for (int i = LyricsList.size() - 1; i >= 0; i--)
		{
			if (currentTime >= LyricsList[i].StartTime - SCROLL_DURATION)
			{
				index = i;
				break;
			}
		}

		// 计算当前歌词播放百分比，并以此为标准进行相应滚动
		// 分别绘制已播放歌词（两句）、正在播放歌词、即将播放歌词

		auto current = LyricsList[index].StartTime - currentTime;
		auto progress = (double)current / SCROLL_DURATION;
		if (progress < 0)
		{
			progress = 0;
		}
		if (progress > 1)
		{
			progress = 1;
		}

		auto realProgress = progress;
		progress = 1 - FuncEase(1 - progress);

		/* 已播放歌词 */
		// 颜色设置为灰色
		// 默认字体大小22
		int fontSize = 22;
		setfont(fontSize * sqrt((double)w * h / WINDOW_HEIGHT / WINDOW_WIDTH), 0, SettingsHelper::Settings.GetFont(), 0, 0, FW_DONTCARE, false, false, false);
		CanvasMain->SetTextColor(GRAY);

		// 默认顶部高度70
		int HEAD = 70;
		auto lineHeight = LINE_HEIGHT * sqrt((double)w * h / WINDOW_HEIGHT / WINDOW_WIDTH);

		// 总行数
		int rownum = (h - HEAD) / lineHeight;
		if (rownum % 2 == 0)
		{
			rownum -= 1;
		}
		int headSpace = HEAD;

		// 行高
		lineHeight = (double)(h - HEAD) / rownum;

		for (int i = rownum / 2; i > 0; i--)
		{
			// 判断歌词是否存在
			if (index - i >= 0)
			{
				// 设置字体颜色渐变，黑—>灰
				// 设置字体大小随窗口大小变化而变化
				if (i == 1)
				{
					// 当前播放歌词播放完字体由大到小变化
					setfont(fontSize * sqrt((double)w * h / WINDOW_HEIGHT / WINDOW_WIDTH) + 6 * sqrt((double)w * h / WINDOW_HEIGHT / WINDOW_WIDTH) * progress, 0, SettingsHelper::Settings.GetFont(), 0, 0, FW_DONTCARE, false, false, false);
					// 当前播放歌词播放完颜色由黑变灰渐变
					CanvasMain->SetTextColor(RGB(127 * (1 - realProgress), 127 * (1 - realProgress), 127 * (1 - realProgress)));
				}
				else
				{
					setfont(fontSize * sqrt((double)w * h / WINDOW_HEIGHT / WINDOW_WIDTH), 0, SettingsHelper::Settings.GetFont(), 0, 0, FW_DONTCARE, false, false, false);
					CanvasMain->SetTextColor(GRAY);
				}
				RECT rect = { MARGIN_HORIZONTAL,
					(LONG)(headSpace + (lineHeight * progress) + lineHeight * (rownum / 2 - i)),
					w - MARGIN_HORIZONTAL,
					(LONG(headSpace + (lineHeight * progress) + lineHeight + lineHeight * (rownum / 2 - i))) };
				CanvasMain->CenterText(LyricsList[static_cast<std::vector<Lyricify::Lyrics, std::allocator<Lyricify::Lyrics>>::size_type>(index) - i].Text.c_str(), rect);
			}
		}

		/* 当前播放歌词 */
		// 当前歌词开始播放颜色由灰变黑渐变
		CanvasMain->SetTextColor(RGB(127 * realProgress, 127 * realProgress, 127 * realProgress));
		// 当前歌词开始播放字体由小到大变化
		setfont(fontSize * sqrt((double)w * h / WINDOW_HEIGHT / WINDOW_WIDTH) + 6 * sqrt((double)w * h / WINDOW_HEIGHT / WINDOW_WIDTH) * (1 - progress), 0, SettingsHelper::Settings.GetFont(), 0, 0, FW_DONTCARE, false, false, false);
		RECT r = { MARGIN_HORIZONTAL,
			(LONG)(headSpace + (lineHeight * progress) + lineHeight * (rownum - 1) / 2),
			w - MARGIN_HORIZONTAL ,
			(LONG(headSpace + (lineHeight * progress) + lineHeight + lineHeight * (rownum - 1) / 2)) };
		CanvasMain->CenterText(LyricsList[index].Text.c_str(), r);

		// 即将播放歌词 字体颜色为灰色
		// 依据窗口高度绘制相应数量歌词
		setfont(fontSize * sqrt((double)w * h / WINDOW_HEIGHT / WINDOW_WIDTH), 0, SettingsHelper::Settings.GetFont(), 0, 0, FW_DONTCARE, false, false, false);

		for (int i = 1; i <= rownum / 2; i++)
		{
			CanvasMain->SetTextColor(GRAY);

			if ((unsigned long long)index + i < LyricsList.size())
			{
				RECT rect = { MARGIN_HORIZONTAL,
					(LONG)(headSpace + (lineHeight * progress) + lineHeight * (rownum / 2 + i)),
					w - MARGIN_HORIZONTAL,
					(LONG)(headSpace + (lineHeight * progress) + lineHeight + lineHeight * (rownum / 2 + i)) };

				CanvasMain->CenterText(LyricsList[static_cast<std::vector<Lyricify::Lyrics, std::allocator<Lyricify::Lyrics>>::size_type>(index) + i].Text.c_str(), rect);
			}
		}

		/* 绘制进度条 */
		// 在进度条左标明已播放时长 
		// 在进度条左标明总播放时长

		// 顶部高度45
		auto top = 45;

		// 当前播放进度
		auto progress1 = MusicPlayer::GetCurrentPositionMs();

		// 获取时间
		auto timeStr = StringHelper::TimeMsToString(progress1 == -1 ? 0 : progress1);
		// 设置时间输出格式
		auto timeStr1 = timeStr.substr(0, timeStr.length() - 1);
		// 计算左右距离
		auto left = MARGIN_HORIZONTAL + (timeStr.length() == 7 ? 76 : 86);
		auto right = w - MARGIN_HORIZONTAL - BUTTON_WIDTH - CONTROL_PADDING_HORIZONTAL;
		double percent = progress1 == -1 ? 0 : (double)progress1 / MusicPlayer::GetTotalDurationMs();
		auto width = right - left;

		// 总时长
		auto progress2 = MusicPlayer::GetTotalDurationMs();
		// 获取时间
		auto timeTotalStr = StringHelper::TimeMsToString(progress2);
		// 设置时间输出格式
		auto timeTotalStr1 = timeTotalStr.substr(0, timeTotalStr.length() - 1);

		setfont(DEFAULT_CANVAS_FONTSIZE, 0, L"Consolas");
		CanvasMain->OutTextXY(MARGIN_HORIZONTAL, top, (StringHelper::StringToWstring(timeStr1)).c_str());
		CanvasMain->OutTextXY(right + 20, top, (StringHelper::StringToWstring(timeTotalStr1).c_str()));

		CanvasMain->GP_SetLineWidth(3);
		CanvasMain->GP_Line(left, top + 11, right, top + 11, true, RGB(0xBF, 0xBF, 0xBF));
		CanvasMain->GP_Line(left, top + 11, right - width * (1 - percent), top + 11, true, RGB(0x7F, 0x7F, 0x7F));
		CanvasMain->GP_SetLineWidth(1);

		IsInDrawAtWndProcPaint = false;
	}

	/// <summary>
	/// 刷新 UI (画布内容)
	/// </summary>
	static void RefreshUI()
	{
		if (IsInDrawAtWndProcPaint || IsInRefreshUI) return;

		IsInRefreshUI = true;

		CanvasMain->Clear(true, BACKGROUND_COLOR);
		DrawAtWndProcPaint(true);
		Window->Redraw();

		IsInRefreshUI = false;
	}

	static void ButtonPlayPause_Click()
	{
		if (MusicPlayer::IsPlaying())
		{
			MusicPlayer::Pause();
			ButtonPlayPause->SetText(L"播放");
		}
		else
		{
			MusicPlayer::SetPlaybackSpeed(); // 重置播放速度到 1.0x
			MusicPlayer::Play();
			ButtonPlayPause->SetText(L"暂停");

			std::thread([]()
				{
					static bool IsRefreshThreadRunning = false;
					if (IsRefreshThreadRunning) return;

					IsRefreshThreadRunning = true;

					std::wstring audio = MusicPlayer::CurrentAudioPath;
					while (audio == MusicPlayer::CurrentAudioPath && MusicPlayer::IsPlaying())
					{
						if (true) //!WindowAbout::IsOpened() && !WindowPreviewOutput::IsOpened()) // 关于被打开时，不再刷新进度，防止渲染错乱
						{
							RefreshUI();
						}
						TaskHelper::Delay(10).wait();
					}
					if (!MusicPlayer::IsPlaying())
					{
						ButtonPlayPause->SetText(L"播放");
					}

					IsRefreshThreadRunning = false;
				}).detach();
		}
	}

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_PAINT:
			DrawAtWndProcPaint();
			break;

		case WM_SIZE:
		{
			CanvasMain->Clear(true, BACKGROUND_COLOR);

			int w = CanvasMain->GetWidth() / DPI_Scale;
			int h = CanvasMain->GetHeight() / DPI_Scale;

			// TODO: 这里写窗口大小改变后进行对控件（如按钮）调整位置和尺寸
			ButtonPlayPause->Move(w / 2 - BUTTON_WIDTH / 2, 10);

			break;
		}

		case WM_GETMINMAXINFO:
		{
			MINMAXINFO* pmmi = (MINMAXINFO*)lParam;
			pmmi->ptMinTrackSize.x = MIN_WINDOW_WIDTH * DPI_Scale;
			pmmi->ptMinTrackSize.y = MIN_WINDOW_HEIGHT * DPI_Scale;
			return 0;
		}

		default:
			return HIWINDOW_DEFAULT_PROC;
			break;
		}

		return 0;
	}

	static void OpenWindow(double scale, std::vector<Lyricify::Lyrics> lyricsList, RECT rect, HWND hParent = (HWND)nullptr)
	{
		isOpened = true;
		DPI_Scale = scale;
		LyricsList = lyricsList;

		/* 这一段是临时内容，用于方便开发 */

		//try
		//{
		//	// 加载一段歌词 用于测试
		//	TCHAR exePath[MAX_PATH];
		//	GetModuleFileName(NULL, exePath, MAX_PATH);
		//	auto filePath = StringHelper::GetDirectoryFromPath(exePath) + L"\\Lyrics.txt";
		//	auto lyricsRaw = StringHelper::StringToWstring(FileHelper::ReadAllText(filePath));
		//	auto lyrics = Lyricify::LyricsHelper::ParseLyricsFromLyricifyLinesString(lyricsRaw);
		//	LyricsList = lyrics;

		//	// 加载对应歌曲
		//	MusicPlayer::Load(StringHelper::GetDirectoryFromPath(exePath) + L"\\Audio.mp3");
		//}
		//catch (...)
		//{
		//	MessageBox(NULL, L"加载歌词或歌曲失败！\n请确保 Audio.mp3 和 Lyrics.txt 存在且可用。", L"加载失败", MB_OK);
		//}

		/* 临时内容结束 */

		hiex::Window wnd;
		hiex::Canvas canvas;
		hiex::SysButton buttonPlayPause;
		Window = &wnd;
		CanvasMain = &canvas;
		ButtonPlayPause = &buttonPlayPause;
		if (rect.left != -1 && rect.right != -1 && rect.top != -1 && rect.bottom != -1)
		{
			int left = (rect.left + rect.right - WINDOW_WIDTH * DPI_Scale) / 2;
			int top = (rect.top + rect.bottom - WINDOW_HEIGHT * DPI_Scale) / 2;
			wnd.PreSetPos(left, top);
		}
		wnd.InitWindow(WINDOW_WIDTH * DPI_Scale, WINDOW_HEIGHT * DPI_Scale, EW_NORMAL, GetStringFromKey("String.Window.PreviewLyrics").c_str(), nullptr, hParent);
		if (hParent != (HWND)nullptr) WindowHelper::EnableMinimizeButton(wnd.GetHandle(), false);

		wnd.BindCanvas(&canvas);
		wnd.SetProcFunc(WndProc);
		setfont(20, 0, SettingsHelper::Settings.GetFont(), 0, 0, 0, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);
		setaspectratio(DPI_Scale, DPI_Scale);

		// TODO: 按钮的创建

		int w = CanvasMain->GetWidth() / DPI_Scale;
		int h = CanvasMain->GetHeight() / DPI_Scale;

		ButtonPlayPause->Create(Window->GetHandle(), w / 2 - 40, 10, BUTTON_WIDTH, BUTTON_HEIGHT, L"播放");
		ButtonPlayPause->RegisterMessage(ButtonPlayPause_Click);
		ButtonPlayPause->SetFont(DEFAULT_BUTTON_FONTSIZE, 0, SettingsHelper::Settings.GetFont());

		wnd.Redraw();
		TaskHelper::Delay(10).wait();

		if (SettingsHelper::Settings.IsPreviewLyricsOpenMaximize)
		{
			// 最大化窗口
			PostMessage(wnd.GetHandle(), WM_SYSCOMMAND, SC_MAXIMIZE, 0);
		}

		hiex::init_end(wnd.GetHandle());
		MusicPlayer::Pause();
		if (hParent != (HWND)nullptr) BringWindowToTop(hParent); // 让主窗体显示于最上方
		isOpened = false;
	}

	void Show(std::vector<Lyricify::Lyrics> lyricsList, double DPI_Scale, RECT rect, HWND hParent)
	{
		if (!isOpened)
		{
			std::thread(OpenWindow, DPI_Scale, lyricsList, rect, hParent).detach();
		}
	}

	bool IsOpened()
	{
		return isOpened;
	}
}
