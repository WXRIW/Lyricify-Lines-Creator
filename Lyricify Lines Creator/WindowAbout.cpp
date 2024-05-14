#include "WindowAbout.h"

void WindowAbout::Show(double DPI_Scale, RECT rect)
{
	static bool IsOpened = false;

	if (!IsOpened)
	{
		std::thread(OpenWindow, &IsOpened, DPI_Scale, rect).detach();
	}
}

void WindowAbout::OpenWindow(bool* isOpened, double DPI_Scale, RECT rect)
{
	*isOpened = true;
	const int WIDTH = 360;
	const int HEIGHT = 355;

	hiex::Window wnd;
	if (rect.left != -1 && rect.right != -1 && rect.top != -1 && rect.bottom != -1)
	{
		int left = (rect.left + rect.right) / 2 - WIDTH * DPI_Scale / 2;
		int top = (rect.top + rect.bottom) / 2 - HEIGHT * DPI_Scale / 2;
		wnd.PreSetPos(left, top);
	}
	wnd.InitWindow(WIDTH * DPI_Scale, HEIGHT * DPI_Scale, EW_NORMAL, L"关于");
	DisableResizing(wnd.GetHandle(), true);
	SetWindowPos(wnd.GetHandle(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); // Topmost

	hiex::Canvas canvas;
	wnd.BindCanvas(&canvas);
	setfont(20, 0, DEFAULT_FONT, 0, 0, 0, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);
	setaspectratio(DPI_Scale, DPI_Scale);
	int w = canvas.GetWidth() / DPI_Scale;
	int top = 0;

	canvas.SetTextColor(BLACK);
	setfont(24, 0, DEFAULT_FONT, 0, 0, FW_BOLD, false, false, false);
	canvas.CenterText(L"Lyricify Lines Creator", { 0, 20, w, 45 });
	canvas.SetTextColor(GRAY);
	setfont(16, 0, L"Consolas", 0, 0, FW_DONTCARE, false, false, false);
	canvas.CenterText((std::wstring(L"Version ") + std::wstring(VERSION)).c_str(), {0, 50, w, 70});

	top += 85;
	canvas.SetTextColor(BLACK);
	setfont(18, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, false, false);
	canvas.CenterText(L"开发者", { 0, top, w, top + 20 }); top += 26;
	canvas.SetTextColor(GRAY);
	setfont(16, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, false, false);
	canvas.CenterText(L"Xiaoyang Wang", { 0, top, w, top + 20 }); top += 20;
	canvas.CenterText(L"Tianle Chen", { 0, top, w, top + 20 }); top += 20;
	canvas.CenterText(L"Runze Zhang", { 0, top, w, top + 20 }); top += 20;

	top += 20;
	canvas.SetTextColor(BLACK);
	setfont(18, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, false, false);
	canvas.CenterText(L"第三方协议", { 0, top, w, top + 20 }); top += 26;
	canvas.SetTextColor(GRAY);
	setfont(16, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, false, false);
	canvas.CenterText(L"HiEasyX (MIT 协议)", { 0, top, w, top + 20 }); top += 20;
	setfont(12, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, true, false);
	canvas.CenterText(L"https://github.com/zouhuidong/HiEasyX/blob/main/LICENSE", { 0, top, w, top + 15 }); top += 22;
	setfont(16, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, false, false);
	canvas.CenterText(L"EasyX", { 0, top, w, top + 20 }); top += 20;
	setfont(12, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, true, false);
	canvas.CenterText(L"https://easyx.cn/copyright", { 0, top, w, top + 15 }); top += 22;
	setfont(16, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, false, false);
	canvas.CenterText(L"irrKlang", { 0, top, w, top + 20 }); top += 20;
	setfont(12, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, true, false);
	canvas.CenterText(L"https://www.ambiera.com/irrklang/license.html", { 0, top, w, top + 15 }); top += 22;

	wnd.Redraw();
	hiex::init_end(wnd.GetHandle());
	*isOpened = false;
}