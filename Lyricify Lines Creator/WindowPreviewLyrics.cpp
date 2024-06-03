#include "WindowPreviewLyrics.h"

namespace WindowPreviewLyrics
{
	const int WINDOW_WIDTH = 400;
	const int WINDOW_HEIGHT = 500;
	const int MIN_WINDOW_WIDTH = 300;
	const int MIN_WINDOW_HEIGHT = 300;

	bool IsInRefreshUI = false;
	bool IsInDrawAtWndProcPaint = false;
	bool isOpened = false;
	hiex::Window* Window;
	hiex::Canvas* CanvasMain;
	hiex::SysButton* ButtonPlayPause;
	std::vector<Lyricify::Lyrics> LyricsList;
	double DPI_Scale = 1;

	static double FuncEase(double x)
	{
		x = x * 0.9793195;
		auto a = -10.55 * std::pow(x, 7) + 42.76 * std::pow(x, 6) - 73.36 * std::pow(x, 5) + 70.9 * std::pow(x, 4) - 41.89 * std::pow(x, 3) + 12.98 * std::pow(x, 2) + 0.1638 * x;
		return a / 1.0041521796874393;
	}

	/// <summary>
	/// 绘制画布
	/// </summary>
	/// <param name="ignoreInRefreshUI"></param>
	static void DrawAtWndProcPaint(bool ignoreInRefreshUI = false)
	{
		if (IsInDrawAtWndProcPaint || IsInRefreshUI && !ignoreInRefreshUI) return;
		IsInDrawAtWndProcPaint = true;

		int w = CanvasMain->GetWidth() / DPI_Scale;
		int h = CanvasMain->GetHeight() / DPI_Scale;

		CanvasMain->SetBkColor(BACKGROUND_COLOR);

		// TODO: 这里写画板（歌词部分）应该怎么画
		// CanvasMain->OutTextXY();

		// 计算文字尺寸可以用 FontHelper::CalculateTextSize();
		
		// 设置画板字号
		setfont(18, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, false, false);

		// 设置画板颜色
		//CanvasMain->SetTextColor(RGB(0, 0, 0));

		//std::wstring lyrics = L"uk vbruk g wabk awbi biu nvw我我我我我 nvi n";
		//auto index = lyrics.find_last_of(' ');
		//auto newLyrics = lyrics.substr(0, index); // 左边的

		//auto leftLyrics = lyrics.substr(newLyrics.size()); // 剩下的

		int index = 0;
		const int SCROLL_DURATION = 600;
		const int LINE_HEIGHT = 50;
		int currentTime = MusicPlayer::GetCurrentPositionMs();
		for (int i = LyricsList.size() - 1; i >= 0; i--)
		{
			if (currentTime >= LyricsList[i].StartTime - SCROLL_DURATION)
			{
				index = i;
				break;
			}
		}
		auto current = LyricsList[index].StartTime - currentTime;
		auto progress = (double)current / SCROLL_DURATION;
		if (progress < 0) progress = 0;
		if (progress > 1) progress = 1;
		progress = 1 - FuncEase(1 - progress);
		setfont(18 + 6 * (1 - progress), 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, false, false);
		CanvasMain->CenterText(LyricsList[index].Text.c_str(), { MARGIN_HORIZONTAL, 100 + (long)(LINE_HEIGHT * progress),w - MARGIN_HORIZONTAL,100 + (long)(LINE_HEIGHT * progress) + LINE_HEIGHT });
		setfont(18, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, false, false);
		for (int i = 1; i < 8; i++)
		{
			CanvasMain->CenterText(LyricsList[index + i].Text.c_str(), { MARGIN_HORIZONTAL, 100 + (long)(LINE_HEIGHT * progress) + LINE_HEIGHT * i,w - MARGIN_HORIZONTAL,100 + (long)(LINE_HEIGHT * progress) + LINE_HEIGHT + LINE_HEIGHT * i });
		}

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

	void ButtonPlayPause_Click()
	{
		if (MusicPlayer::IsPlaying())
		{
			MusicPlayer::Pause();
			ButtonPlayPause->SetText(L"播放");
		}
		else
		{
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
			// ButtonPlayPause->Move();

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

		try
		{
			// 加载一段歌词 用于测试
			TCHAR exePath[MAX_PATH];
			GetModuleFileName(NULL, exePath, MAX_PATH);
			auto filePath = StringHelper::GetDirectoryFromPath(exePath) + L"\\Lyrics.txt";
			auto lyricsRaw = StringHelper::StringToWstring(FileHelper::ReadAllText(filePath));
			auto lyrics = Lyricify::LyricsHelper::ParseLyricsFromLyricifyLinesString(lyricsRaw);
			LyricsList = lyrics;

			// 加载对应歌曲
			MusicPlayer::Load(StringHelper::GetDirectoryFromPath(exePath) + L"\\Audio.mp3");
		}
		catch (...)
		{
			MessageBox(NULL, L"加载歌词或歌曲失败！\n请确保 Audio.mp3 和 Lyrics.txt 存在且可用。", L"加载失败", MB_OK);
		}

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
		wnd.InitWindow(WINDOW_WIDTH * DPI_Scale, WINDOW_HEIGHT * DPI_Scale, EW_NORMAL, L"输出预览", nullptr, hParent);
		if (hParent != (HWND)nullptr) WindowHelper::EnableMinimizeButton(wnd.GetHandle(), false);

		wnd.BindCanvas(&canvas);
		wnd.SetProcFunc(WndProc);
		setfont(20, 0, DEFAULT_FONT, 0, 0, 0, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);
		setaspectratio(DPI_Scale, DPI_Scale);

		// TODO: 按钮的创建
		ButtonPlayPause->Create(Window->GetHandle(), 20, 20, BUTTON_WIDTH, BUTTON_HEIGHT, L"播放");
		ButtonPlayPause->RegisterMessage(ButtonPlayPause_Click);

		wnd.Redraw();
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
