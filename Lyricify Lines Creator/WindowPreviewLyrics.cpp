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
	}

	/// <summary>
	/// 刷新 UI (画布内容)
	/// </summary>
	static void RefreshUI()
	{
		if (IsInDrawAtWndProcPaint || IsInRefreshUI) return;
		IsInRefreshUI = true;

		CanvasMain->Clear(true, BACKGROUND_COLOR);
		DrawAtWndProcPaint();
		Window->Redraw();

		IsInRefreshUI = false;
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
		// ButtonPlayPause->Create();

		hiex::init_end(wnd.GetHandle());
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
