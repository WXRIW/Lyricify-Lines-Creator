/************************************************************************
 * Filename:    WindowSettings.cpp
 * Description: 设置窗体实现
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#include "WindowSettings.h"

namespace WindowSettings
{
	const int WINDOW_WIDTH = 350;
	const int WINDOW_HEIGHT = 215;

	const int LABEL_ADDHEIGHT = 2;
	const int LINE_HEIGHT = 32;
	const int CONTROL_HEIGHT = 21;

	bool isOpened = false;
	double DPI_Scale = 1;

	hiex::Window* Window;
	hiex::Canvas* CanvasMain;
	hiex::SysStatic* LabelLanguage;
	hiex::SysComboBox* ComboBoxLanguage;
	hiex::SysStatic* LabelLyricsOutputFormat;
	hiex::SysComboBox* ComboBoxLyricsOutputFormat;
	hiex::SysStatic* LabelDeviceLatency;
	hiex::SysEdit* TextBoxDeviceLatency;
	hiex::SysStatic* LabelKeyboardLatency;
	hiex::SysEdit* TextBoxKeyboardLatency;
	hiex::SysStatic* LabelPreviewLyricsMaximize;
	hiex::SysCheckBox* CheckBoxPreviewLyricsMaximize;
	hiex::SysButton* ButtonSave;
	hiex::SysButton* ButtonCancel;

	static std::wstring LyricsFormats[] =
	{
		L"Lyricify Lines",
		L"LRC",
	};

	static std::wstring LanguageList[] =
	{
		L"English (English)",
		L"简体中文 (Simplified Chinese)",
		L"繁體中文 (Traditional Chinese)",
		L"Français (French)",
		L"Pусский (Russian)",
	};

	static const size_t LanguageCount = sizeof(LanguageList) / sizeof(LanguageList[0]);

	static int GetLanguageIndex(const std::wstring& language)
	{
		for (size_t i = 0; i < LanguageCount; ++i)
		{
			if (LanguageList[i] == language)
			{
				return static_cast<int>(i);
			}
		}
		return -1;
	}

	static Languages GetLanguageEnum(int index)
	{
		if (index >= 0 && index < static_cast<int>(LanguageCount))
		{
			return static_cast<Languages>(index);
		}
		return Languages::ZH_HANS;
	}

	static void SettingsValueChange()
	{
		if (LanguageList[(int)SettingsHelper::Settings.Language] != ComboBoxLanguage->GetText()
			|| SettingsHelper::Settings.IsOutputLrc != (ComboBoxLyricsOutputFormat->GetText() == L"LRC")
			|| std::to_wstring(SettingsHelper::Settings.DeviceLatencyMs) != (TextBoxDeviceLatency->GetText())
			|| std::to_wstring(SettingsHelper::Settings.KeyboardLatencyMs) != (TextBoxKeyboardLatency->GetText())
			|| SettingsHelper::Settings.IsPreviewLyricsOpenMaximize != CheckBoxPreviewLyricsMaximize->IsChecked())
		{
			ButtonSave->Enable(true);
		}
		else
		{
			ButtonSave->Enable(false);
		}
	}

	static void ComboBoxLanguage_Selected(int nSel, std::wstring wstrSelText)
	{
		SettingsValueChange();
	}

	static void ComboBoxLyricsOutputFormat_Selected(int nSel, std::wstring wstrSelText)
	{
		SettingsValueChange();
	}

	static void TextBoxDeviceLatency_TextChanged(std::wstring wstrText)
	{
		if (!StringHelper::IsNumeric(wstrText))
		{
			if (wstrText.empty())
			{
				TextBoxDeviceLatency->SetText(L"0");
			}
			else
			{
				TextBoxDeviceLatency->SetText(std::to_wstring(SettingsHelper::Settings.DeviceLatencyMs));
				MessageBox(Window->GetHandle(), GetStringFromKey("String.Window.Settings.InvalidLatencyValue").c_str(), GetStringFromKey("String.Window.Settings.ErrorInput").c_str(), MB_ICONINFORMATION | MB_OK);
			}
		}
		SettingsValueChange();
	}

	static void TextBoxKeyboardLatency_TextChanged(std::wstring wstrText)
	{
		if (!StringHelper::IsNumeric(wstrText))
		{
			if (wstrText.empty())
			{
				TextBoxKeyboardLatency->SetText(L"0");
			}
			else
			{
				TextBoxKeyboardLatency->SetText(std::to_wstring(SettingsHelper::Settings.KeyboardLatencyMs));
				MessageBox(Window->GetHandle(), GetStringFromKey("String.Window.Settings.InvalidLatencyValue").c_str(), GetStringFromKey("String.Window.Settings.ErrorInput").c_str(), MB_ICONINFORMATION | MB_OK);
			}
		}
		SettingsValueChange();
	}

	static void CheckBoxPreviewLyricsMaximize_Checked(bool checked)
	{
		SettingsValueChange();
	}

	static void ButtonSave_Click()
	{
		SettingsHelper::Settings.Language = GetLanguageEnum(GetLanguageIndex(ComboBoxLanguage->GetText()));
		SettingsHelper::Settings.IsOutputLrc = ComboBoxLyricsOutputFormat->GetText() == L"LRC";
		SettingsHelper::Settings.DeviceLatencyMs = std::stoi(TextBoxDeviceLatency->GetText());
		SettingsHelper::Settings.KeyboardLatencyMs = std::stoi(TextBoxKeyboardLatency->GetText());
		SettingsHelper::Settings.IsPreviewLyricsOpenMaximize = CheckBoxPreviewLyricsMaximize->IsChecked();
		SettingsHelper::SaveSettings();

		SendMessage(Window->GetHandle(), WM_CLOSE, 0, 0);
	}

	static void ButtonCancel_Click()
	{
		SendMessage(Window->GetHandle(), WM_CLOSE, 0, 0);
	}

	static void OpenWindow(double scale, RECT rect, HWND hParent = (HWND)nullptr)
	{
		isOpened = true;
		DPI_Scale = scale;

		hiex::Window wnd;
		hiex::Canvas canvas;
		hiex::SysStatic labelLanguage;
		hiex::SysComboBox comboBoxLanguage;
		hiex::SysStatic labelLyricsOutputFormat;
		hiex::SysComboBox comboBoxLyricsOutputFormat;
		hiex::SysStatic labelDeviceLatency;
		hiex::SysEdit textBoxDeviceLatency;
		hiex::SysStatic labelKeyboardLatency;
		hiex::SysEdit textBoxKeyboardLatency;
		hiex::SysStatic labelPreviewLyricsMaximize;
		hiex::SysCheckBox checkBoxPreviewLyricsMaximize;
		hiex::SysButton buttonSave;
		hiex::SysButton buttonCancel;

		Window = &wnd;
		CanvasMain = &canvas;
		LabelLanguage = &labelLanguage;
		ComboBoxLanguage = &comboBoxLanguage;
		LabelLyricsOutputFormat = &labelLyricsOutputFormat;
		ComboBoxLyricsOutputFormat = &comboBoxLyricsOutputFormat;
		LabelDeviceLatency = &labelDeviceLatency;
		TextBoxDeviceLatency = &textBoxDeviceLatency;
		LabelKeyboardLatency = &labelKeyboardLatency;
		TextBoxKeyboardLatency = &textBoxKeyboardLatency;
		LabelPreviewLyricsMaximize = &labelPreviewLyricsMaximize;
		CheckBoxPreviewLyricsMaximize = &checkBoxPreviewLyricsMaximize;
		ButtonSave = &buttonSave;
		ButtonCancel = &buttonCancel;

		if (rect.left != -1 && rect.right != -1 && rect.top != -1 && rect.bottom != -1)
		{
			int left = (rect.left + rect.right - WINDOW_WIDTH * DPI_Scale) / 2;
			int top = (rect.top + rect.bottom - WINDOW_HEIGHT * DPI_Scale) / 2;
			Window->PreSetPos(left, top);
		}
		Window->InitWindow(WINDOW_WIDTH * DPI_Scale, WINDOW_HEIGHT * DPI_Scale, EW_NORMAL, GetStringFromKey("String.Window.Settings").c_str(), nullptr, hParent);
		DisableResizing(Window->GetHandle(), true);
		WindowHelper::EnableMinimizeButton(Window->GetHandle(), false);
		Window->BindCanvas(CanvasMain);
		setfont(20, 0, DEFAULT_FONT, 0, 0, 0, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);
		setaspectratio(DPI_Scale, DPI_Scale);

		auto hwnd = Window->GetHandle();
		int w = CanvasMain->GetWidth() / DPI_Scale;
		int h = CanvasMain->GetHeight() / DPI_Scale;
		int top = MARGIN_VERTICAL;
		int FONTSIZE = 18 - 2 * (DPI_Scale - 1);

		// 为语言优化 Label 宽度
		auto LEFT_LABEL_WIDTH = 0;
		auto padding = 35;
		auto size = FontHelper::CalculateTextSize(GetStringFromKey("String.Window.Settings.Language").c_str(), DEFAULT_FONT, FONTSIZE).cx;
		if (size + padding > LEFT_LABEL_WIDTH) LEFT_LABEL_WIDTH = size + padding;
		size = FontHelper::CalculateTextSize(GetStringFromKey("String.Window.Settings.LyricsOutputFormat").c_str(), DEFAULT_FONT, FONTSIZE).cx;
		if (size + padding > LEFT_LABEL_WIDTH) LEFT_LABEL_WIDTH = size + padding;
		size = FontHelper::CalculateTextSize(GetStringFromKey("String.Window.Settings.DeviceLatency").c_str(), DEFAULT_FONT, FONTSIZE).cx;
		if (size + padding > LEFT_LABEL_WIDTH) LEFT_LABEL_WIDTH = size + padding;
		size = FontHelper::CalculateTextSize(GetStringFromKey("String.Window.Settings.KeyboardLatency").c_str(), DEFAULT_FONT, FONTSIZE).cx;
		if (size + padding > LEFT_LABEL_WIDTH) LEFT_LABEL_WIDTH = size + padding;
		size = FontHelper::CalculateTextSize(GetStringFromKey("String.Window.Settings.PreviewLyricsMaximize").c_str(), DEFAULT_FONT, FONTSIZE).cx;
		if (size + padding > LEFT_LABEL_WIDTH) LEFT_LABEL_WIDTH = size + padding;

		LabelLanguage->Create(hwnd, MARGIN_HORIZONTAL, top + LABEL_ADDHEIGHT, LEFT_LABEL_WIDTH, CONTROL_HEIGHT, GetStringFromKey("String.Window.Settings.Language").c_str());
		ComboBoxLanguage->PreSetStyle({ false, false, false });
		ComboBoxLanguage->Create(hwnd, MARGIN_HORIZONTAL + LEFT_LABEL_WIDTH, top, w - MARGIN_HORIZONTAL * 2 - LEFT_LABEL_WIDTH, CONTROL_HEIGHT);
		for (auto& item : LanguageList) ComboBoxLanguage->AddString(item);
		ComboBoxLanguage->SelectString(LanguageList[(int)SettingsHelper::Settings.Language]);
		ComboBoxLanguage->RegisterSelMessage(ComboBoxLanguage_Selected);
		top += LINE_HEIGHT;

		LabelLyricsOutputFormat->Create(hwnd, MARGIN_HORIZONTAL, top + LABEL_ADDHEIGHT, LEFT_LABEL_WIDTH, CONTROL_HEIGHT, GetStringFromKey("String.Window.Settings.LyricsOutputFormat").c_str());
		ComboBoxLyricsOutputFormat->PreSetStyle({ false, false, false });
		ComboBoxLyricsOutputFormat->Create(hwnd, MARGIN_HORIZONTAL + LEFT_LABEL_WIDTH, top, w - MARGIN_HORIZONTAL * 2 - LEFT_LABEL_WIDTH, CONTROL_HEIGHT);
		for (auto& item : LyricsFormats) ComboBoxLyricsOutputFormat->AddString(item);
		ComboBoxLyricsOutputFormat->SelectString(LyricsFormats[SettingsHelper::Settings.IsOutputLrc ? 1 : 0]);
		ComboBoxLyricsOutputFormat->RegisterSelMessage(ComboBoxLyricsOutputFormat_Selected);
		top += LINE_HEIGHT;

		LabelDeviceLatency->Create(hwnd, MARGIN_HORIZONTAL, top + LABEL_ADDHEIGHT, LEFT_LABEL_WIDTH, CONTROL_HEIGHT, GetStringFromKey("String.Window.Settings.DeviceLatency").c_str());
		TextBoxDeviceLatency->Create(hwnd, MARGIN_HORIZONTAL + LEFT_LABEL_WIDTH, top, w - MARGIN_HORIZONTAL * 2 - LEFT_LABEL_WIDTH, CONTROL_HEIGHT, std::to_wstring(SettingsHelper::Settings.DeviceLatencyMs));
		TextBoxDeviceLatency->RegisterMessage(TextBoxDeviceLatency_TextChanged);
		top += LINE_HEIGHT;

		LabelKeyboardLatency->Create(hwnd, MARGIN_HORIZONTAL, top + LABEL_ADDHEIGHT, LEFT_LABEL_WIDTH, CONTROL_HEIGHT, GetStringFromKey("String.Window.Settings.KeyboardLatency").c_str());
		TextBoxKeyboardLatency->Create(hwnd, MARGIN_HORIZONTAL + LEFT_LABEL_WIDTH, top, w - MARGIN_HORIZONTAL * 2 - LEFT_LABEL_WIDTH, CONTROL_HEIGHT, std::to_wstring(SettingsHelper::Settings.KeyboardLatencyMs));
		TextBoxKeyboardLatency->RegisterMessage(TextBoxKeyboardLatency_TextChanged);
		top += LINE_HEIGHT;

		LabelPreviewLyricsMaximize->Create(hwnd, MARGIN_HORIZONTAL, top + LABEL_ADDHEIGHT, LEFT_LABEL_WIDTH, CONTROL_HEIGHT, GetStringFromKey("String.Window.Settings.PreviewLyricsMaximize").c_str());
		CheckBoxPreviewLyricsMaximize->Create(hwnd, MARGIN_HORIZONTAL + LEFT_LABEL_WIDTH, top, w - MARGIN_HORIZONTAL * 2 - LEFT_LABEL_WIDTH, CONTROL_HEIGHT);
		CheckBoxPreviewLyricsMaximize->Check(SettingsHelper::Settings.IsPreviewLyricsOpenMaximize);
		CheckBoxPreviewLyricsMaximize->RegisterMessage(CheckBoxPreviewLyricsMaximize_Checked);
		top += LINE_HEIGHT;

		ButtonSave->Create(hwnd, w - MARGIN_HORIZONTAL - BUTTON_WIDTH * 2 - CONTROL_PADDING_HORIZONTAL, h - MARGIN_VERTICAL - BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT, GetStringFromKey("String.Window.Settings.Save").c_str());
		ButtonSave->Enable(false);
		ButtonSave->RegisterMessage(ButtonSave_Click);
		ButtonCancel->Create(hwnd, w - MARGIN_HORIZONTAL - BUTTON_WIDTH, h - MARGIN_VERTICAL - BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT, GetStringFromKey("String.Window.Settings.Cancel").c_str());
		ButtonCancel->RegisterMessage(ButtonCancel_Click);

		LabelLanguage->SetFont(FONTSIZE, 0, DEFAULT_FONT);
		ComboBoxLanguage->SetFont(FONTSIZE, 0, DEFAULT_FONT);
		LabelLyricsOutputFormat->SetFont(FONTSIZE, 0, DEFAULT_FONT);
		ComboBoxLyricsOutputFormat->SetFont(FONTSIZE, 0, DEFAULT_FONT);
		LabelDeviceLatency->SetFont(FONTSIZE, 0, DEFAULT_FONT);
		TextBoxDeviceLatency->SetFont(FONTSIZE, 0, DEFAULT_FONT);
		LabelKeyboardLatency->SetFont(FONTSIZE, 0, DEFAULT_FONT);
		TextBoxKeyboardLatency->SetFont(FONTSIZE, 0, DEFAULT_FONT);
		LabelPreviewLyricsMaximize->SetFont(FONTSIZE, 0, DEFAULT_FONT);
		CheckBoxPreviewLyricsMaximize->SetFont(FONTSIZE, 0, DEFAULT_FONT);
		ButtonSave->SetFont(FONTSIZE, 0, DEFAULT_FONT);
		ButtonCancel->SetFont(FONTSIZE, 0, DEFAULT_FONT);

		hiex::init_end(Window->GetHandle());
		if (hParent != (HWND)nullptr) BringWindowToTop(hParent); // 让主窗体显示于最上方
		isOpened = false;
	}

	void Show(double DPI_Scale, RECT rect, HWND hParent)
	{
		if (!isOpened)
		{
			std::thread(OpenWindow, DPI_Scale, rect, hParent).detach();
		}
	}

	bool IsOpened()
	{
		return isOpened;
	}
}
