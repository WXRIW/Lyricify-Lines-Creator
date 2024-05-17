#include "WindowPreviewOutput.h"

namespace WindowPreviewOutput
{
	const int WINDOW_WIDTH = 400;
	const int WINDOW_HEIGHT = 500;
	const int MIN_WINDOW_WIDTH = 300;
	const int MIN_WINDOW_HEIGHT = 300;

	bool isOpened = false;
	hiex::Window* Window;
	hiex::Canvas* CanvasMain;
	hiex::SysEdit* TextBoxOutput;
	hiex::SysButton* ButtonSave;
	double DPI_Scale = 1;
	std::wstring FilePath;
	std::wstring FileContent;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_SIZE:
		{
			CanvasMain->Clear(true, BACKGROUND_COLOR);

			int w = CanvasMain->GetWidth() / DPI_Scale;
			int h = CanvasMain->GetHeight() / DPI_Scale;

			TextBoxOutput->Resize(w - MARGIN_HORIZONTAL * 2, h - MARGIN_VERTICAL * 2 - BUTTON_HEIGHT - 10);
			ButtonSave->Move(w - MARGIN_HORIZONTAL - BUTTON_WIDTH, h - MARGIN_VERTICAL - BUTTON_HEIGHT);

			break;
		}
		case WM_COMMAND:
			if (HIWORD(wParam) == EN_CHANGE && (HWND)lParam == TextBoxOutput->GetHandle())
			{
				auto text = TextBoxOutput->GetText();
				text = StringHelper::Replace(text, L"\r\n", L"\n");
				ButtonSave->Enable(text != FileContent);
			}
			break;


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

	static void OpenWindow(std::wstring filePath, std::wstring fileContent, double scale, RECT rect, HWND hParent = (HWND)nullptr)
	{
		isOpened = true;
		DPI_Scale = scale;
		FilePath = filePath;
		FileContent = fileContent;

		hiex::Window wnd;
		hiex::Canvas canvas;
		hiex::SysEdit textBoxOutput;
		hiex::SysButton buttonSave;
		Window = &wnd;
		CanvasMain = &canvas;
		TextBoxOutput = &textBoxOutput;
		ButtonSave = &buttonSave;
		if (rect.left != -1 && rect.right != -1 && rect.top != -1 && rect.bottom != -1)
		{
			int left = (rect.left + rect.right - WINDOW_WIDTH * DPI_Scale) / 2;
			int top = (rect.top + rect.bottom - WINDOW_HEIGHT * DPI_Scale) / 2;
			wnd.PreSetPos(left, top);
		}
		wnd.InitWindow(WINDOW_WIDTH * DPI_Scale, WINDOW_HEIGHT * DPI_Scale, EW_NORMAL, L"输出预览", nullptr, hParent);
		WindowHelper::EnableMinimizeButton(wnd.GetHandle(), false);

		wnd.BindCanvas(&canvas);
		wnd.SetProcFunc(WndProc);
		setfont(20, 0, DEFAULT_FONT, 0, 0, 0, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);
		setaspectratio(DPI_Scale, DPI_Scale);

		int w = CanvasMain->GetWidth() / DPI_Scale;
		int h = CanvasMain->GetHeight() / DPI_Scale;

		TextBoxOutput->PreSetStyle({ true, false, true });
		TextBoxOutput->Create(wnd.GetHandle(), MARGIN_HORIZONTAL, MARGIN_VERTICAL, w - MARGIN_HORIZONTAL * 2, h - MARGIN_VERTICAL * 2 - BUTTON_HEIGHT - 10, StringHelper::Replace(FileContent, L"\n", L"\r\n"));
		TextBoxOutput->SetFont(18, 0, DEFAULT_FONT);

		ButtonSave->Create(wnd.GetHandle(), w - MARGIN_HORIZONTAL - BUTTON_WIDTH, h - MARGIN_VERTICAL - BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT, L"保存");
		ButtonSave->Enable(false);
		ButtonSave->SetFont(DEFAULT_BUTTON_FONTSIZE, 0, DEFAULT_FONT);
		ButtonSave->RegisterMessage([]()
			{
				std::wofstream outFile(FilePath);
				if (!outFile)
				{
					MessageBox(Window->GetHandle(), L"保存失败，无法写入文件！", L"保存失败", MB_OK | MB_ICONWARNING);
					return;
				}
				else
				{
					auto text = TextBoxOutput->GetText();
					text = StringHelper::Replace(text, L"\r\n", L"\n");
					outFile << text;
					outFile.close();
					MessageBox(Window->GetHandle(), L"保存成功！", L"保存成功", MB_OK);
					ButtonSave->Enable(false);
					FileContent = text;
				}
			});

		hiex::init_end(wnd.GetHandle());
		if (hParent != (HWND)nullptr) BringWindowToTop(hParent); // 让主窗体显示于最上方
		isOpened = false;
	}

	void Show(std::wstring filePath, std::wstring fileContent, double DPI_Scale, RECT rect, HWND hParent)
	{
		if (!isOpened)
		{
			std::thread(OpenWindow, filePath, fileContent, DPI_Scale, rect, hParent).detach();
		}
	}

	bool IsOpened()
	{
		return isOpened;
	}
}
