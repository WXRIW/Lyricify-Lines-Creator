#include "WindowAbout.h"

void WindowAbout::Show(double DPI_Scale)
{
	static bool IsOpened = false;

	if (!IsOpened)
	{
		IsOpened = true;
		std::thread(OpenWindow, &IsOpened, DPI_Scale).detach();
	}
}

void WindowAbout::OpenWindow(bool* isOpened, double DPI_Scale)
{
	hiex::Window wnd(360 * DPI_Scale, 300 * DPI_Scale, EW_NORMAL, L"关于");
	DisableResizing(wnd.GetHandle(), true);
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
	setfont(16, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, false, false);
	canvas.CenterText(L"Version 0.1-alpha", { 0, 50, w, 70 });

	top += 85;
	canvas.SetTextColor(BLACK);
	setfont(18, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, false, false);
	canvas.CenterText(L"开发者", { 0, top, w, top + 20 }); top += 20;
	canvas.SetTextColor(GRAY);
	setfont(16, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, false, false);
	canvas.CenterText(L"Xiaoyang Wang", { 0, top, w, top + 20 }); top += 20;
	canvas.CenterText(L"Tianle Chen", { 0, top, w, top + 20 }); top += 20;
	canvas.CenterText(L"Runze Zhang", { 0, top, w, top + 20 }); top += 20;

	top += 15;
	canvas.SetTextColor(BLACK);
	setfont(18, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, false, false);
	canvas.CenterText(L"第三方协议", { 0, top, w, top + 20 }); top += 20;
	canvas.SetTextColor(GRAY);
	setfont(16, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, false, false);
	canvas.CenterText(L"HiEasyX (MIT 协议)", { 0, top, w, top + 20 }); top += 20;
	setfont(12, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, true, false);
	canvas.CenterText(L"https://github.com/zouhuidong/HiEasyX", { 0, top, w, top + 15 }); top += 22;
	setfont(16, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, false, false);
	canvas.CenterText(L"irrKlang (非商用)", { 0, top, w, top + 20 }); top += 20;
	setfont(12, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, true, false);
	canvas.CenterText(L"https://www.ambiera.com/irrklang/license.html", { 0, top, w, top + 15 }); top += 22;

	wnd.Redraw();
	hiex::init_end(wnd.GetHandle());
	*isOpened = false;
}