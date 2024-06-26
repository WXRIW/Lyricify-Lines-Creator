/************************************************************************
 * Filename:    WindowMain.cpp
 * Description: 主窗体实现
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#include "WindowMain.h"

namespace WindowMain
{

#pragma region Variable Definitions

	double DPI_Scale = 1;

	// 顶部区域左侧 Label 的宽度，后期本地化时在这里更改尺寸
	int TOP_LEFT_LABEL_MAX_WIDTH = 65;

	bool IsInRefreshUI = false;
	bool IsInDrawAtWndProcPaint = false;
	bool IsMaking = false;
	std::vector<Lyricify::Lyrics> LyricsList;

	float PlaybackSpeed = 1;

#pragma endregion

#pragma region Control Definitions

	hiex::Window wnd;

	// 顶部区域

	hiex::Canvas CanvasMain;

	hiex::SysEdit TextBoxChooseAudio;
	hiex::SysEdit TextBoxChooseRawLyrics;
	hiex::SysEdit TextBoxOutputPath;

	hiex::SysButton ButtonChooseAudio;
	hiex::SysButton ButtonChooseRawLyrics;
	hiex::SysButton ButtonOutputPath;

	// 播放区域

	hiex::SysButton ButtonPlayPause;
	hiex::SysComboBox ComboBoxPlaybackSpeed;

	// 底部区域

	hiex::SysButton ButtonAbout;
	hiex::SysButton ButtonSettings;
	hiex::SysButton ButtonViewOutput;
	hiex::SysButton ButtonPreview;
	hiex::SysButton ButtonRestart;
	hiex::SysButton ButtonStart;

#pragma endregion

#pragma region Button Clicks & Keyboard Events

	void ButtonChooseAudio_Click()
	{
		auto path = FileHelper::SelectFile(GetStringFromKey("String.Window.Main.SelectAudioDialogTitle").c_str(), GetStringFromKey("String.Window.Main.SelectAudioDialogFilter").c_str());
		if (!path.empty())
		{
			TextBoxChooseAudio.SetText(path);

			if (!MusicPlayer::Load(path))
			{
				MessageBox(wnd.GetHandle(), GetStringFromKey("String.Window.Main.AudioLoadFailed").c_str(), GetStringFromKey("String.Window.Main.AudioLoadFailed").c_str(), MB_OK | MB_ICONWARNING);
			}
		}
	}

	void ButtonChooseRawLyrics_Click()
	{
		auto path = FileHelper::SelectFile(GetStringFromKey("String.Window.Main.SelectLyricsDialogTitle").c_str(), GetStringFromKey("String.Window.Main.SelectLyricsDialogFilter").c_str());
		if (!path.empty())
		{
			TextBoxChooseRawLyrics.SetText(path);

			auto stringLines = Lyricify::LyricsHelper::ReadTextToLines(TextBoxChooseRawLyrics.GetText());
			if (stringLines.size() == 0)
			{
				MessageBox(wnd.GetHandle(), GetStringFromKey("String.Window.Main.EmptyOrErrorText").c_str(), GetStringFromKey("String.Window.Main.EmptyOrErrorText").c_str(), MB_OK | MB_ICONWARNING);
				return;
			}

			// 加载歌词文本
			LyricsList = Lyricify::LyricsHelper::GetLyricsFromLines(stringLines);

			// 加载到 UI 中
			RefreshUI();
		}
	}

	void ButtonOutputPath_Click()
	{
		auto path = FileHelper::SelectFolder(GetStringFromKey("String.Window.Main.OutputPathDialogTitle").c_str());
		if (!path.empty())
		{
			TextBoxOutputPath.SetText(path);
		}
	}

	void ButtonPlayPause_Click()
	{
		if (MusicPlayer::IsPlaying())
		{
			MusicPlayer::Pause();
			ButtonPlayPause.SetText(GetStringFromKey("String.Window.Main.Play").c_str());
		}
		else
		{
			if (MusicPlayer::CurrentAudioPath.empty() && !TextBoxChooseAudio.GetText().empty()
				|| MusicPlayer::CurrentAudioPath != TextBoxChooseAudio.GetText())
			{
				// 没有加载音频，或音频变更时，需要重新加载
				if (!MusicPlayer::Load(TextBoxChooseAudio.GetText()))
				{
					MessageBox(wnd.GetHandle(), GetStringFromKey("String.Window.Main.AudioLoadFailed").c_str(), GetStringFromKey("String.Window.Main.AudioLoadFailed").c_str(), MB_OK | MB_ICONWARNING);
				}
			}

			MusicPlayer::SetPlaybackSpeed(PlaybackSpeed);
			MusicPlayer::Play();
			ButtonPlayPause.SetText(GetStringFromKey("String.Window.Main.Pause").c_str());

			std::thread([]()
				{
					static bool IsRefreshThreadRunning = false;
					if (IsRefreshThreadRunning) return;
					IsRefreshThreadRunning = true;

					std::wstring audio = MusicPlayer::CurrentAudioPath;
					while (audio == MusicPlayer::CurrentAudioPath && MusicPlayer::IsPlaying())
					{
						// 关于被打开时，不再刷新进度，防止渲染错乱
						if (!WindowAbout::IsOpened()
							&& !WindowSettings::IsOpened()
							&& !WindowPreviewOutput::IsOpened()
							&& !WindowPreviewLyrics::IsOpened())
						{
							RefreshUI();
						}
						TaskHelper::Delay(25).wait();
					}
					if (!MusicPlayer::IsPlaying())
					{
						ButtonPlayPause.SetText(GetStringFromKey("String.Window.Main.Play").c_str());
					}

					IsRefreshThreadRunning = false;
				}).detach();
		}
	}

	static void ComboBoxPlaybackSpeed_Selected(int nSel, std::wstring wstrSelText)
	{
		double value = 1.0;
		try
		{
			if (!wstrSelText.empty() && wstrSelText.back() == L'x')
			{
				std::wstring trimmedStr = wstrSelText.substr(0, wstrSelText.size() - 1);
				value = std::stof(trimmedStr);
			}
			else
			{
				// 如果字符串不以 'x' 结尾，直接转换
				value = std::stof(wstrSelText);
			}
		}
		catch (...) {}

		PlaybackSpeed = value;
		MusicPlayer::SetPlaybackSpeed(value);
	}

	void ButtonAbout_Click()
	{
		WindowAbout::Show(DPI_Scale, GetWindowRect(), wnd.GetHandle());
	}

	void ButtonSettings_Click()
	{
		WindowSettings::Show(DPI_Scale, GetWindowRect(), wnd.GetHandle());
	}

	void ButtonViewOutput_Click()
	{
		auto fileContent = SettingsHelper::Settings.IsOutputLrc
			? Lyricify::LyricsHelper::GenerateLrcFromLyricsList(LyricsList)
			: Lyricify::LyricsHelper::GenerateLyricifyLinesFromLyricsList(LyricsList);
		if (fileContent.empty())
		{
			MessageBox(wnd.GetHandle(), GetStringFromKey("String.Window.Main.NoOutputToView").c_str(), GetStringFromKey("String.Window.Main.NoOutputToView").c_str(), MB_OK | MB_ICONINFORMATION);
			return;
		}
		auto filePath = GetOutputFullpath();
		WindowPreviewOutput::Show(filePath, fileContent, DPI_Scale, GetWindowRect(), wnd.GetHandle());
	}

	void ButtonPreview_Click()
	{
		auto fileContent = Lyricify::LyricsHelper::GenerateLyricifyLinesFromLyricsList(LyricsList);
		if (fileContent.empty())
		{
			MessageBox(wnd.GetHandle(), GetStringFromKey("String.Window.Main.NoPreviewToView").c_str(), GetStringFromKey("String.Window.Main.NoPreviewToView").c_str(), MB_OK | MB_ICONINFORMATION);
			return;
		}
		MusicPlayer::SeekTo(0); // 进度归零
		WindowPreviewLyrics::Show(Lyricify::LyricsHelper::ParseLyricsFromLyricifyLinesString(fileContent), DPI_Scale, GetWindowRect());
	}

	void ButtonRestart_Click()
	{
		// 清空歌词的时间信息，并返回头部

		// 如果音频变化，需要重新加载
		if (MusicPlayer::CurrentAudioPath != TextBoxChooseAudio.GetText())
		{
			if (!MusicPlayer::Load(TextBoxChooseAudio.GetText()))
			{
				MessageBox(wnd.GetHandle(), GetStringFromKey("String.Window.Main.AudioLoadFailed").c_str(), GetStringFromKey("String.Window.Main.AudioLoadFailed").c_str(), MB_OK | MB_ICONWARNING);
				return;
			}
		}
		else
		{
			MusicPlayer::SeekTo(0);
		}

		// 清空歌词信息 (直接重新加载)
		auto stringLines = Lyricify::LyricsHelper::ReadTextToLines(TextBoxChooseRawLyrics.GetText());
		if (stringLines.size() == 0)
		{
			MessageBox(wnd.GetHandle(), GetStringFromKey("String.Window.Main.EmptyOrErrorText").c_str(), GetStringFromKey("String.Window.Main.EmptyOrErrorText").c_str(), MB_OK | MB_ICONWARNING);
			return;
		}
		LyricsList = Lyricify::LyricsHelper::GetLyricsFromLines(stringLines);

		if (!MusicPlayer::IsPlaying()) RefreshUI();
	}

	void ButtonStart_Click()
	{
		if (!IsMaking)
		{
			// 开始制作
			// 检查配置状态
			if (TextBoxChooseAudio.GetTextLength() == 0)
			{
				MessageBox(wnd.GetHandle(), GetStringFromKey("String.Window.Main.NoAudioSelected").c_str(), GetStringFromKey("String.Window.Main.NoAudioSelected").c_str(), MB_OK | MB_ICONWARNING);
				return;
			}
			if (MusicPlayer::CurrentAudioPath != TextBoxChooseAudio.GetText() && !MusicPlayer::Load(TextBoxChooseAudio.GetText()))
			{
				MessageBox(wnd.GetHandle(), GetStringFromKey("String.Window.Main.AudioLoadFailed").c_str(), GetStringFromKey("String.Window.Main.AudioLoadFailed").c_str(), MB_OK | MB_ICONWARNING);
				return;
			}
			if (TextBoxChooseRawLyrics.GetTextLength() == 0)
			{
				MessageBox(wnd.GetHandle(), GetStringFromKey("String.Window.Main.NoLyricsSelected").c_str(), GetStringFromKey("String.Window.Main.NoLyricsSelected").c_str(), MB_OK | MB_ICONWARNING);
				return;
			}
			auto stringLines = Lyricify::LyricsHelper::ReadTextToLines(TextBoxChooseRawLyrics.GetText());
			if (stringLines.size() == 0)
			{
				MessageBox(wnd.GetHandle(), GetStringFromKey("String.Window.Main.EmptyOrErrorText").c_str(), GetStringFromKey("String.Window.Main.EmptyOrErrorText").c_str(), MB_OK | MB_ICONWARNING);
				return;
			}

			// 加载歌词文本
			LyricsList = Lyricify::LyricsHelper::GetLyricsFromLines(stringLines);

			// 开始播放音频
			if (!MusicPlayer::IsPlaying())
			{
				ButtonPlayPause_Click();
			}

			// 更新按钮状态
			ButtonRestart.Enable(true);
			ButtonStart.SetText(GetStringFromKey("String.Window.Main.SaveLyrics").c_str());
		}
		else
		{
			// 保存歌词
			// 暂停播放音频
			if (MusicPlayer::IsPlaying())
			{
				ButtonPlayPause_Click();
			}

			// 保存至文件
			auto lyricifyLinesString = SettingsHelper::Settings.IsOutputLrc
				? Lyricify::LyricsHelper::GenerateLrcFromLyricsList(LyricsList)
				: Lyricify::LyricsHelper::GenerateLyricifyLinesFromLyricsList(LyricsList);
			if (lyricifyLinesString.empty())
			{
				MessageBox(wnd.GetHandle(), GetStringFromKey("String.Window.Main.NoLyricsToSave").c_str(), GetStringFromKey("String.Window.Main.NoLyricsToSave").c_str(), MB_OK | MB_ICONWARNING);
				return;
			}
			else
			{
				std::wofstream outFile(GetOutputFullpath());
				if (!outFile)
				{
					MessageBox(wnd.GetHandle(), GetStringFromKey("String.Window.Main.OutputSaveFailed").c_str(), GetStringFromKey("String.Window.Main.SaveFailedTitle").c_str(), MB_OK | MB_ICONWARNING);
					return;
				}
				else
				{
					outFile << lyricifyLinesString;
					outFile.close();
				}
			}

			// 更新按钮状态
			ButtonRestart.Enable(false);
			ButtonStart.SetText(GetStringFromKey("String.Window.Main.Start").c_str());
		}
		IsMaking = !IsMaking;
	}

	void KeyboardEvents(WPARAM wParam)
	{
		switch (wParam)
		{
		case VK_SPACE:
			ButtonPlayPause_Click();
			break;

		case 'B':
			MusicPlayer::SeekBack(3000);
			if (!MusicPlayer::IsPlaying()) RefreshUI();
			break;

		case 'N':
			MusicPlayer::SeekForward(3000);
			if (!MusicPlayer::IsPlaying()) RefreshUI();
			break;

		case 'M':
			MusicPlayer::SeekForward(10000);
			if (!MusicPlayer::IsPlaying()) RefreshUI();
			break;

		case 'C':
			MusicPlayer::SeekForward(30000);
			if (!MusicPlayer::IsPlaying()) RefreshUI();
			break;

		case 'R':
			MusicPlayer::SeekTo(0);
			if (!MusicPlayer::IsPlaying()) RefreshUI();
			break;

		case VK_UP: // 为当前行 (下一行) 标记起始时间
		{
			if (!IsMaking) break;
			auto index = GetCurrentLineIndex();
			if (index < (int)LyricsList.size() - 1)
			{
				auto line = GetCurrentLine(index + 1);
				if (line != nullptr)
				{
					line->StartTime = MusicPlayer::GetCurrentPositionMs() - SettingsHelper::Settings.TotalLatencyMs();
				}
			}
			else if (index == (int)LyricsList.size() - 1)
			{
				auto line = GetCurrentLine(index);
				if (line != nullptr && line->EndTime == -1)
				{
					line->EndTime = MusicPlayer::GetCurrentPositionMs() - SettingsHelper::Settings.TotalLatencyMs();
				}
			}
			if (!MusicPlayer::IsPlaying()) RefreshUI();
			break;
		}

		case VK_RIGHT: // 为当前行标记结束时间
		{
			if (!IsMaking) break;
			auto line = GetCurrentLine();
			if (line != nullptr && line->EndTime == -1)
			{
				line->EndTime = MusicPlayer::GetCurrentPositionMs() - SettingsHelper::Settings.TotalLatencyMs();
			}
			if (!MusicPlayer::IsPlaying()) RefreshUI();
			break;
		}

		case VK_LEFT: // 为上一行标记结束时间
		{
			if (!IsMaking) break;
			auto index = GetCurrentLineIndex();
			if (index - 1 >= 0)
			{
				auto line = GetCurrentLine(index - 1);
				if (line != nullptr && line->EndTime == -1)
				{
					line->EndTime = MusicPlayer::GetCurrentPositionMs() - SettingsHelper::Settings.TotalLatencyMs();
				}
				if (!MusicPlayer::IsPlaying()) RefreshUI();
			}
			break;
		}

		case VK_DOWN: // 删去当前行的其实时间，如果有结束时间，则优先删除
		{
			if (!IsMaking) break;
			auto index = GetCurrentLineIndex();
			auto line = GetCurrentLine(index);
			if (line != nullptr)
			{
				if (line->EndTime != -1)
				{
					MusicPlayer::SeekTo(line->EndTime);
					line->EndTime = -1;
				}
				else
				{
					MusicPlayer::SeekTo(line->StartTime);
					line->StartTime = -1;
				}
			}
			if (!MusicPlayer::IsPlaying()) RefreshUI();
			break;
		}

		default:
			break;
		}
	}

#pragma endregion

#pragma region Sizes (Init & Resize)

	/// <summary>
	/// 添加主窗体的控件
	/// </summary>
	/// <param name="hwnd">传入主窗体的句柄</param>
	void AddWindowControls(HWND hwnd)
	{
		int left, top;
		int w = CanvasMain.GetWidth() / DPI_Scale;
		int h = CanvasMain.GetHeight() / DPI_Scale;
		int tempBtnWidth = BUTTON_WIDTH;
		int tempLabelWidth = TOP_LEFT_LABEL_MAX_WIDTH;

		if (SettingsHelper::Settings.IsNeedTextCalc())
		{
			auto textSize = FontHelper::CalculateTextSize(GetStringFromKey("String.Window.Main.SelectAudio").c_str(), SettingsHelper::Settings.GetFont(), DEFAULT_CANVAS_FONTSIZE).cx;
			if (textSize + 5 > tempLabelWidth) tempLabelWidth = textSize + 5;
			textSize = FontHelper::CalculateTextSize(GetStringFromKey("String.Window.Main.SelectLyrics").c_str(), SettingsHelper::Settings.GetFont(), DEFAULT_CANVAS_FONTSIZE).cx;
			if (textSize + 5 > tempLabelWidth) tempLabelWidth = textSize + 5;
			textSize = FontHelper::CalculateTextSize(GetStringFromKey("String.Window.Main.OutputPath").c_str(), SettingsHelper::Settings.GetFont(), DEFAULT_CANVAS_FONTSIZE).cx;
			if (textSize + 5 > tempLabelWidth) tempLabelWidth = textSize + 5;

			textSize = FontHelper::CalculateTextSize(GetStringFromKey("String.Window.Main.ImportAudio").c_str(), SettingsHelper::Settings.GetFont(), DEFAULT_BUTTON_FONTSIZE).cx;
			if (textSize + 30 > tempBtnWidth) tempBtnWidth = textSize + 30;
			textSize = FontHelper::CalculateTextSize(GetStringFromKey("String.Window.Main.ImportLyrics").c_str(), SettingsHelper::Settings.GetFont(), DEFAULT_BUTTON_FONTSIZE).cx;
			if (textSize + 30 > tempBtnWidth) tempBtnWidth = textSize + 30;
			textSize = FontHelper::CalculateTextSize(GetStringFromKey("String.Window.Main.SelectPath").c_str(), SettingsHelper::Settings.GetFont(), DEFAULT_BUTTON_FONTSIZE).cx;
			if (textSize + 30 > tempBtnWidth) tempBtnWidth = textSize + 30;
		}

#pragma region 顶部区域

		DrawLabelControls();

		left = MARGIN_HORIZONTAL + tempLabelWidth + CONTROL_PADDING_HORIZONTAL;
		auto width = w - (MARGIN_HORIZONTAL * 2 + tempLabelWidth + tempBtnWidth + CONTROL_PADDING_HORIZONTAL * 2);
		TextBoxChooseAudio.Create(hwnd, left, MARGIN_VERTICAL, width, CONTROL_HEIGHT);
		TextBoxChooseRawLyrics.Create(hwnd, left, MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL, width, CONTROL_HEIGHT);
		TextBoxOutputPath.Create(hwnd, left, MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL * 2, width, CONTROL_HEIGHT);

		left = w - MARGIN_HORIZONTAL - tempBtnWidth;
		ButtonChooseAudio.Create(hwnd, left, BUTTON_HEIGHT_OFFSET + MARGIN_VERTICAL, tempBtnWidth, BUTTON_HEIGHT, GetStringFromKey("String.Window.Main.ImportAudio").c_str());
		ButtonChooseRawLyrics.Create(hwnd, left, BUTTON_HEIGHT_OFFSET + MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL, tempBtnWidth, BUTTON_HEIGHT, GetStringFromKey("String.Window.Main.ImportLyrics").c_str());
		ButtonOutputPath.Create(hwnd, left, BUTTON_HEIGHT_OFFSET + MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL * 2, tempBtnWidth, BUTTON_HEIGHT, GetStringFromKey("String.Window.Main.SelectPath").c_str());

#pragma endregion

#pragma region 播放区域

		left = w - MARGIN_HORIZONTAL - BUTTON_WIDTH;
		top = MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL * 3 + 25;
		ComboBoxPlaybackSpeed.PreSetStyle({ false, false, false });
		ButtonPlayPause.Create(hwnd, left, BUTTON_HEIGHT_OFFSET + top, BUTTON_WIDTH, BUTTON_HEIGHT, GetStringFromKey("String.Window.Main.Play").c_str());
		ComboBoxPlaybackSpeed.Create(hwnd, left, BUTTON_HEIGHT_OFFSET + top + CONTROL_PADDING_VERTICAL, BUTTON_WIDTH, BUTTON_HEIGHT);
		ComboBoxPlaybackSpeed.AddString(L"0.25x");
		ComboBoxPlaybackSpeed.AddString(L"0.5x");
		ComboBoxPlaybackSpeed.AddString(L"0.75x");
		ComboBoxPlaybackSpeed.AddString(L"1.0x");
		ComboBoxPlaybackSpeed.AddString(L"1.25x");
		ComboBoxPlaybackSpeed.AddString(L"1.5x");
		ComboBoxPlaybackSpeed.AddString(L"2.0x");
		ComboBoxPlaybackSpeed.SelectString(L"1.0x");

#pragma endregion

#pragma region 底部区域

		auto widthAccu = 0;
		top = h - MARGIN_VERTICAL - BUTTON_HEIGHT;
		tempBtnWidth = BUTTON_WIDTH;
		if (SettingsHelper::Settings.IsNeedTextCalc())
		{
			auto textSize = FontHelper::CalculateTextSize(GetStringFromKey("String.Window.Main.About").c_str(), SettingsHelper::Settings.GetFont(), DEFAULT_BUTTON_FONTSIZE).cx;
			if (textSize + 30 > tempBtnWidth) tempBtnWidth = textSize + 30;
		}
		ButtonAbout.Create(hwnd, MARGIN_HORIZONTAL, top, tempBtnWidth, BUTTON_HEIGHT, GetStringFromKey("String.Window.Main.About").c_str());
		widthAccu += tempBtnWidth;

		tempBtnWidth = BUTTON_WIDTH;
		if (SettingsHelper::Settings.IsNeedTextCalc())
		{
			auto textSize = FontHelper::CalculateTextSize(GetStringFromKey("String.Window.Main.Settings").c_str(), SettingsHelper::Settings.GetFont(), DEFAULT_BUTTON_FONTSIZE).cx;
			if (textSize + 30 > tempBtnWidth) tempBtnWidth = textSize + 30;
		}
		ButtonSettings.Create(hwnd, MARGIN_HORIZONTAL + widthAccu + CONTROL_PADDING_HORIZONTAL, top, tempBtnWidth, BUTTON_HEIGHT, GetStringFromKey("String.Window.Main.Settings").c_str());
		widthAccu += tempBtnWidth;

		widthAccu = 0;
		tempBtnWidth = BUTTON_WIDTH;
		if (SettingsHelper::Settings.IsNeedTextCalc())
		{
			auto textSize = FontHelper::CalculateTextSize(GetStringFromKey("String.Window.Main.Start").c_str(), SettingsHelper::Settings.GetFont(), DEFAULT_BUTTON_FONTSIZE).cx;
			if (textSize + 30 > tempBtnWidth) tempBtnWidth = textSize + 30;
		}
		widthAccu += tempBtnWidth;
		ButtonStart.Create(hwnd, w - MARGIN_HORIZONTAL - widthAccu, top, tempBtnWidth, BUTTON_HEIGHT, GetStringFromKey("String.Window.Main.Start").c_str());

		tempBtnWidth = BUTTON_WIDTH;
		if (SettingsHelper::Settings.IsNeedTextCalc())
		{
			auto textSize = FontHelper::CalculateTextSize(GetStringFromKey("String.Window.Main.Restart").c_str(), SettingsHelper::Settings.GetFont(), DEFAULT_BUTTON_FONTSIZE).cx;
			if (textSize + 30 > tempBtnWidth) tempBtnWidth = textSize + 30;
		}
		widthAccu += tempBtnWidth;
		ButtonRestart.Create(hwnd, w - MARGIN_HORIZONTAL - widthAccu - CONTROL_PADDING_HORIZONTAL, top, tempBtnWidth, BUTTON_HEIGHT, GetStringFromKey("String.Window.Main.Restart").c_str());

		tempBtnWidth = BUTTON_WIDTH;
		if (SettingsHelper::Settings.IsNeedTextCalc())
		{
			auto textSize = FontHelper::CalculateTextSize(GetStringFromKey("String.Window.Main.Preview").c_str(), SettingsHelper::Settings.GetFont(), DEFAULT_BUTTON_FONTSIZE).cx;
			if (textSize + 30 > tempBtnWidth) tempBtnWidth = textSize + 30;
		}
		widthAccu += tempBtnWidth;
		ButtonPreview.Create(hwnd, w - MARGIN_HORIZONTAL - widthAccu - CONTROL_PADDING_HORIZONTAL * 4, top, tempBtnWidth, BUTTON_HEIGHT, GetStringFromKey("String.Window.Main.Preview").c_str());

		tempBtnWidth = BUTTON_WIDTH;
		if (SettingsHelper::Settings.IsNeedTextCalc())
		{
			auto textSize = FontHelper::CalculateTextSize(GetStringFromKey("String.Window.Main.ViewOutput").c_str(), SettingsHelper::Settings.GetFont(), DEFAULT_BUTTON_FONTSIZE).cx;
			if (textSize + 30 > tempBtnWidth) tempBtnWidth = textSize + 30;
		}
		widthAccu += tempBtnWidth;
		ButtonViewOutput.Create(hwnd, w - MARGIN_HORIZONTAL - widthAccu - CONTROL_PADDING_HORIZONTAL * 5, top, tempBtnWidth, BUTTON_HEIGHT, GetStringFromKey("String.Window.Main.ViewOutput").c_str());

#pragma endregion

		// 设置字体
		TextBoxChooseAudio.SetFont(DEFAULT_TEXTBOX_FONTSIZE, 0, SettingsHelper::Settings.GetFont());
		TextBoxChooseRawLyrics.SetFont(DEFAULT_TEXTBOX_FONTSIZE, 0, SettingsHelper::Settings.GetFont());
		TextBoxOutputPath.SetFont(DEFAULT_TEXTBOX_FONTSIZE, 0, SettingsHelper::Settings.GetFont());
		ButtonChooseAudio.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, SettingsHelper::Settings.GetFont());
		ButtonChooseRawLyrics.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, SettingsHelper::Settings.GetFont());
		ButtonOutputPath.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, SettingsHelper::Settings.GetFont());
		ButtonPlayPause.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, SettingsHelper::Settings.GetFont());
		ComboBoxPlaybackSpeed.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, SettingsHelper::Settings.GetFont());
		ButtonAbout.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, SettingsHelper::Settings.GetFont());
		ButtonSettings.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, SettingsHelper::Settings.GetFont());
		ButtonViewOutput.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, SettingsHelper::Settings.GetFont());
		ButtonPreview.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, SettingsHelper::Settings.GetFont());
		ButtonRestart.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, SettingsHelper::Settings.GetFont());
		ButtonStart.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, SettingsHelper::Settings.GetFont());

		// 注册点击消息
		ButtonChooseAudio.RegisterMessage(ButtonChooseAudio_Click);
		ButtonChooseRawLyrics.RegisterMessage(ButtonChooseRawLyrics_Click);
		ButtonOutputPath.RegisterMessage(ButtonOutputPath_Click);
		ButtonPlayPause.RegisterMessage(ButtonPlayPause_Click);
		ComboBoxPlaybackSpeed.RegisterSelMessage(ComboBoxPlaybackSpeed_Selected);
		ButtonAbout.RegisterMessage(ButtonAbout_Click);
		ButtonSettings.RegisterMessage(ButtonSettings_Click);
		ButtonViewOutput.RegisterMessage(ButtonViewOutput_Click);
		ButtonPreview.RegisterMessage(ButtonPreview_Click);
		ButtonRestart.RegisterMessage(ButtonRestart_Click);
		ButtonStart.RegisterMessage(ButtonStart_Click);

		// 控件回调穿透
		ProcedureHelper::TransKeyMsgToParent(ButtonChooseAudio.GetHandle(), WndProc);
		ProcedureHelper::TransKeyMsgToParent(ButtonChooseRawLyrics.GetHandle(), WndProc);
		ProcedureHelper::TransKeyMsgToParent(ButtonOutputPath.GetHandle(), WndProc);
		ProcedureHelper::TransKeyMsgToParent(ButtonPlayPause.GetHandle(), WndProc);
		ProcedureHelper::TransKeyMsgToParent(ButtonAbout.GetHandle(), WndProc);
		ProcedureHelper::TransKeyMsgToParent(ButtonSettings.GetHandle(), WndProc);
		ProcedureHelper::TransKeyMsgToParent(ButtonViewOutput.GetHandle(), WndProc);
		ProcedureHelper::TransKeyMsgToParent(ButtonPreview.GetHandle(), WndProc);
		ProcedureHelper::TransKeyMsgToParent(ButtonRestart.GetHandle(), WndProc);
		ProcedureHelper::TransKeyMsgToParent(ButtonStart.GetHandle(), WndProc);

		// 禁用部分按钮
		ButtonRestart.Enable(false);
	}

	/// <summary>
	/// 窗口大小改变时调用的方法，用于控件位置和尺寸自适应
	/// </summary>
	void ResizeMoveControls()
	{
		int left, top;
		int w = CanvasMain.GetWidth() / DPI_Scale;
		int h = CanvasMain.GetHeight() / DPI_Scale;
		int tempBtnWidth = BUTTON_WIDTH;
		int tempLabelWidth = TOP_LEFT_LABEL_MAX_WIDTH;

		if (SettingsHelper::Settings.IsNeedTextCalc())
		{
			auto textSize = FontHelper::CalculateTextSize(GetStringFromKey("String.Window.Main.SelectAudio").c_str(), SettingsHelper::Settings.GetFont(), DEFAULT_CANVAS_FONTSIZE).cx;
			if (textSize + 5 > tempLabelWidth) tempLabelWidth = textSize + 5;
			textSize = FontHelper::CalculateTextSize(GetStringFromKey("String.Window.Main.SelectLyrics").c_str(), SettingsHelper::Settings.GetFont(), DEFAULT_CANVAS_FONTSIZE).cx;
			if (textSize + 5 > tempLabelWidth) tempLabelWidth = textSize + 5;
			textSize = FontHelper::CalculateTextSize(GetStringFromKey("String.Window.Main.OutputPath").c_str(), SettingsHelper::Settings.GetFont(), DEFAULT_CANVAS_FONTSIZE).cx;
			if (textSize + 5 > tempLabelWidth) tempLabelWidth = textSize + 5;

			textSize = FontHelper::CalculateTextSize(GetStringFromKey("String.Window.Main.ImportAudio").c_str(), SettingsHelper::Settings.GetFont(), DEFAULT_BUTTON_FONTSIZE).cx;
			if (textSize + 30 > tempBtnWidth) tempBtnWidth = textSize + 30;
			textSize = FontHelper::CalculateTextSize(GetStringFromKey("String.Window.Main.ImportLyrics").c_str(), SettingsHelper::Settings.GetFont(), DEFAULT_BUTTON_FONTSIZE).cx;
			if (textSize + 30 > tempBtnWidth) tempBtnWidth = textSize + 30;
			textSize = FontHelper::CalculateTextSize(GetStringFromKey("String.Window.Main.SelectPath").c_str(), SettingsHelper::Settings.GetFont(), DEFAULT_BUTTON_FONTSIZE).cx;
			if (textSize + 30 > tempBtnWidth) tempBtnWidth = textSize + 30;
		}

#pragma region 顶部区域

		// 因 HiEasyX 的一些问题，Resize 后边框将变粗
		auto width = w - (MARGIN_HORIZONTAL * 2 + tempLabelWidth + tempBtnWidth + CONTROL_PADDING_HORIZONTAL * 2);
		TextBoxChooseAudio.Resize(width, CONTROL_HEIGHT);
		TextBoxChooseRawLyrics.Resize(width, CONTROL_HEIGHT);
		TextBoxOutputPath.Resize(width, CONTROL_HEIGHT);

		left = w - MARGIN_HORIZONTAL - tempBtnWidth;
		ButtonChooseAudio.Move(left, BUTTON_HEIGHT_OFFSET + MARGIN_VERTICAL);
		ButtonChooseRawLyrics.Move(left, BUTTON_HEIGHT_OFFSET + MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL);
		ButtonOutputPath.Move(left, BUTTON_HEIGHT_OFFSET + MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL * 2);

#pragma endregion

#pragma region 播放区域

		left = w - MARGIN_HORIZONTAL - BUTTON_WIDTH;
		top = MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL * 3 + 25;
		ButtonPlayPause.Move(left, BUTTON_HEIGHT_OFFSET + top);
		ComboBoxPlaybackSpeed.Move(left, BUTTON_HEIGHT_OFFSET + top + CONTROL_PADDING_VERTICAL);

#pragma endregion

#pragma region 底部区域

		auto widthAccu = 0;
		top = h - MARGIN_VERTICAL - BUTTON_HEIGHT;
		tempBtnWidth = BUTTON_WIDTH;
		if (SettingsHelper::Settings.IsNeedTextCalc())
		{
			auto textSize = FontHelper::CalculateTextSize(GetStringFromKey("String.Window.Main.About").c_str(), SettingsHelper::Settings.GetFont(), DEFAULT_BUTTON_FONTSIZE).cx;
			if (textSize + 30 > tempBtnWidth) tempBtnWidth = textSize + 30;
		}
		widthAccu += tempBtnWidth;
		ButtonAbout.Move(MARGIN_HORIZONTAL, top);
		ButtonSettings.Move(MARGIN_HORIZONTAL + widthAccu + CONTROL_PADDING_HORIZONTAL, top);

		widthAccu = 0;
		tempBtnWidth = BUTTON_WIDTH;
		if (SettingsHelper::Settings.IsNeedTextCalc())
		{
			auto textSize = FontHelper::CalculateTextSize(GetStringFromKey("String.Window.Main.Start").c_str(), SettingsHelper::Settings.GetFont(), DEFAULT_BUTTON_FONTSIZE).cx;
			if (textSize + 30 > tempBtnWidth) tempBtnWidth = textSize + 30;
		}
		widthAccu += tempBtnWidth;
		ButtonStart.Move(w - MARGIN_HORIZONTAL - widthAccu, top);

		tempBtnWidth = BUTTON_WIDTH;
		if (SettingsHelper::Settings.IsNeedTextCalc())
		{
			auto textSize = FontHelper::CalculateTextSize(GetStringFromKey("String.Window.Main.Restart").c_str(), SettingsHelper::Settings.GetFont(), DEFAULT_BUTTON_FONTSIZE).cx;
			if (textSize + 30 > tempBtnWidth) tempBtnWidth = textSize + 30;
		}
		widthAccu += tempBtnWidth;
		ButtonRestart.Move(w - MARGIN_HORIZONTAL - widthAccu - CONTROL_PADDING_HORIZONTAL, top);

		tempBtnWidth = BUTTON_WIDTH;
		if (SettingsHelper::Settings.IsNeedTextCalc())
		{
			auto textSize = FontHelper::CalculateTextSize(GetStringFromKey("String.Window.Main.Preview").c_str(), SettingsHelper::Settings.GetFont(), DEFAULT_BUTTON_FONTSIZE).cx;
			if (textSize + 30 > tempBtnWidth) tempBtnWidth = textSize + 30;
		}
		widthAccu += tempBtnWidth;
		ButtonPreview.Move(w - MARGIN_HORIZONTAL - widthAccu - CONTROL_PADDING_HORIZONTAL * 4, top);

		tempBtnWidth = BUTTON_WIDTH;
		if (SettingsHelper::Settings.IsNeedTextCalc())
		{
			auto textSize = FontHelper::CalculateTextSize(GetStringFromKey("String.Window.Main.ViewOutput").c_str(), SettingsHelper::Settings.GetFont(), DEFAULT_BUTTON_FONTSIZE).cx;
			if (textSize + 30 > tempBtnWidth) tempBtnWidth = textSize + 30;
		}
		widthAccu += tempBtnWidth;
		ButtonViewOutput.Move(w - MARGIN_HORIZONTAL - widthAccu - CONTROL_PADDING_HORIZONTAL * 5, top);

#pragma endregion
	}

#pragma endregion

#pragma region Canvas Drawing

	/// <summary>
	/// 更新 UI
	/// </summary>
	void RefreshUI()
	{
		if (IsInDrawAtWndProcPaint || IsInRefreshUI) return;
		IsInRefreshUI = true;

		CanvasMain.Clear(true, BACKGROUND_COLOR);
		DrawAtWndProcPaint(true);
		wnd.Redraw();

		IsInRefreshUI = false;
	}

	/// <summary>
	/// 在 Canvas 中绘制文本 (实现 Label 控件效果)
	/// </summary>
	void DrawLabelControls()
	{
		CanvasMain.OutTextXY(MARGIN_HORIZONTAL, 1 + MARGIN_VERTICAL, GetStringFromKey("String.Window.Main.SelectAudio").c_str());
		CanvasMain.OutTextXY(MARGIN_HORIZONTAL, 1 + MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL, GetStringFromKey("String.Window.Main.SelectLyrics").c_str());
		CanvasMain.OutTextXY(MARGIN_HORIZONTAL, 1 + MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL * 2, GetStringFromKey("String.Window.Main.OutputPath").c_str());
	}

	/// <summary>
	/// 绘制播放区域
	/// </summary>
	void DrawPlaybackArea()
	{
		auto top = MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL * 3 + 25;

		int w = CanvasMain.GetWidth() / DPI_Scale;
		int h = CanvasMain.GetHeight() / DPI_Scale;

#pragma region 音频区域

		// 当前时间
		auto progress = MusicPlayer::GetCurrentPositionMs();
		auto timeStr = StringHelper::TimeMsToString(progress == -1 ? 0 : progress);
		timeStr = timeStr.substr(0, timeStr.length() - 1);
		setfont(DEFAULT_CANVAS_FONTSIZE, 0, L"Consolas");
		CanvasMain.OutTextXY(MARGIN_HORIZONTAL, top, (StringHelper::StringToWstring(timeStr)).c_str());

		// 进度条
		auto left = MARGIN_HORIZONTAL + (timeStr.length() == 7 ? 76 : 86);
		auto right = w - MARGIN_HORIZONTAL - BUTTON_WIDTH - CONTROL_PADDING_HORIZONTAL;
		double percent = progress == -1 ? 0 : (double)progress / MusicPlayer::GetTotalDurationMs();
		auto width = right - left;
		CanvasMain.GP_SetLineWidth(3);
		CanvasMain.GP_Line(left, top + 11, right, top + 11, true, RGB(0xBF, 0xBF, 0xBF));
		CanvasMain.GP_Line(left, top + 11, right - width * (1 - percent), top + 11, true, RGB(0x7F, 0x7F, 0x7F));
		CanvasMain.GP_SetLineWidth(1); // 还原

#pragma endregion

#pragma region 歌词区域

		setfont(DEFAULT_CANVAS_FONTSIZE, 0, SettingsHelper::Settings.GetFont(), 0, 0, FW_BOLD, false, false, false);
		CanvasMain.OutTextXY(MARGIN_HORIZONTAL, top + LYRICS_PADDING_VERTICAL, GetStringFromKey("String.Window.Main.PreviousLine").c_str());
		CanvasMain.OutTextXY(MARGIN_HORIZONTAL, top + LYRICS_PADDING_VERTICAL * 2, GetStringFromKey("String.Window.Main.CurrentLine").c_str());
		CanvasMain.OutTextXY(MARGIN_HORIZONTAL, top + LYRICS_PADDING_VERTICAL * 3, GetStringFromKey("String.Window.Main.NextLine").c_str());

		// 还原字体设置
		setfont(DEFAULT_CANVAS_FONTSIZE, 0, SettingsHelper::Settings.GetFont(), 0, 0, FW_DONTCARE, false, false, false);

		// 绘制歌词文本
		// 可通过剩余高度 判断绘制多行歌词
		width = 66;
		if (SettingsHelper::Settings.IsNeedTextCalc())
		{
			auto textSize = FontHelper::CalculateTextSize(GetStringFromKey("String.Window.Main.PreviousLine").c_str(), SettingsHelper::Settings.GetFont(), DEFAULT_CANVAS_FONTSIZE).cx;
			if (textSize + 18 > width) width = textSize + 18;
			textSize = FontHelper::CalculateTextSize(GetStringFromKey("String.Window.Main.PreviousLine").c_str(), SettingsHelper::Settings.GetFont(), DEFAULT_CANVAS_FONTSIZE).cx;
			if (textSize + 18 > width) width = textSize + 18;
			textSize = FontHelper::CalculateTextSize(GetStringFromKey("String.Window.Main.NextLine").c_str(), SettingsHelper::Settings.GetFont(), DEFAULT_CANVAS_FONTSIZE).cx;
			if (textSize + 18 > width) width = textSize + 18;
		}
		left = MARGIN_HORIZONTAL + width;
		auto currentIndex = GetCurrentLineIndex();
		auto currentLine = GetCurrentLine(currentIndex);
		auto isCurrentLineHasEndTime = false;

		// 画上一行
		if (currentIndex - 1 >= 0)
		{
			auto previousLine = GetCurrentLine(currentIndex - 1);
			if (previousLine != nullptr)
			{
				CanvasMain.SetTextColor(previousLine->EndTime == -1 ? FOREGROUND_COLOR : RGB(0x7F, 0x7F, 0x7F));
				CanvasMain.OutTextXY(left, top + LYRICS_PADDING_VERTICAL, previousLine->Text.c_str());
			}
		}

		// 画当前行
		if (currentLine != nullptr && currentLine->EndTime != -1)
		{
			CanvasMain.SetTextColor(RGB(0x7F, 0x7F, 0x7F));
		}
		else
		{
			CanvasMain.SetTextColor(FOREGROUND_COLOR);
		}
		CanvasMain.OutTextXY(left, top + LYRICS_PADDING_VERTICAL * 2, GetCurrentLineString(currentIndex).c_str());

		// 画后续行
		auto lyricsHeight = h - BUTTON_HEIGHT - MARGIN_VERTICAL - 10 - LYRICS_PADDING_VERTICAL * 4 - top;
		auto linesAvailable = lyricsHeight / LYRICS_PADDING_VERTICAL - 1;
		linesAvailable = linesAvailable < 1 ? 1 : linesAvailable;
		auto comingLines = GetComingLinesString(currentIndex, linesAvailable);
		CanvasMain.SetTextColor(RGB(0x7F, 0x7F, 0x7F));
		for (size_t i = 0; i < comingLines.size(); i++)
		{
			CanvasMain.OutTextXY(left, top + LYRICS_PADDING_VERTICAL * (i + 3), comingLines[i].c_str());
		}

#pragma endregion

#pragma region 提示区域

		const std::vector<std::wstring> Notices =
		{
			GetStringFromKey("String.Window.Main.NoticeLineStart"),
			GetStringFromKey("String.Window.Main.NoticeCurrentLineEnd"),
			GetStringFromKey("String.Window.Main.NoticePreviousLineEnd"),
			GetStringFromKey("String.Window.Main.NoticeReturnToPreviousLine"),
			GetStringFromKey("String.Window.Main.NoticePlayPause"),
			GetStringFromKey("String.Window.Main.NoticeSeekBack3s"),
			GetStringFromKey("String.Window.Main.NoticeSeekForward3s"),
			GetStringFromKey("String.Window.Main.NoticeSeekForward10s"),
			GetStringFromKey("String.Window.Main.NoticeSeekForward30s"),
			GetStringFromKey("String.Window.Main.NoticeSeekTo0s"),
		};

		top = h - BUTTON_HEIGHT - MARGIN_VERTICAL - 12 - 36 - 24;
		setfont(DEFAULT_CANVAS_FONTSIZE, 0, SettingsHelper::Settings.GetFont(), 0, 0, FW_BOLD, false, false, false);
		CanvasMain.SetTextColor(FOREGROUND_COLOR);
		CanvasMain.OutTextXY(MARGIN_HORIZONTAL, top, GetStringFromKey("String.Window.Main.KeyTips").c_str());
		setfont(DEFAULT_CANVAS_FONTSIZE - 1, 0, SettingsHelper::Settings.GetFont(), 0, 0, FW_DONTCARE, false, false, false);
		left = 90;
		if (SettingsHelper::Settings.IsNeedTextCalc())
		{
			auto textSize = FontHelper::CalculateTextSize(GetStringFromKey("String.Window.Main.KeyTips").c_str(), SettingsHelper::Settings.GetFont(), DEFAULT_CANVAS_FONTSIZE - 1).cx;
			if (textSize + 40 > left) left = textSize + 40;
		}
		auto fullWidth = w - MARGIN_HORIZONTAL * 2 - left - 10;
		fullWidth /= Notices.size() / 2;
		for (int i = 0; i < Notices.size() / 2; i++)
		{
			CanvasMain.OutTextXY(MARGIN_HORIZONTAL + left + fullWidth * i, top + 1, Notices[i].c_str());
		}
		for (int i = Notices.size() / 2; i < Notices.size(); i++)
		{
			CanvasMain.OutTextXY(MARGIN_HORIZONTAL + left + fullWidth * (i - (int)Notices.size() / 2), top + 1 + 28, Notices[i].c_str());
		}

#pragma endregion

	}

	/// <summary>
	/// 回调时调用的重绘方法
	/// </summary>
	void DrawAtWndProcPaint(bool ignoreInRefreshUI = false)
	{
		if (IsInDrawAtWndProcPaint || IsInRefreshUI && !ignoreInRefreshUI) return;
		IsInDrawAtWndProcPaint = true;

		const auto LINE_COLOR = RGB(0xAF, 0xAF, 0xAF);
		const auto SUBLINE_COLOR = RGB(0xCF, 0xCF, 0xCF);
		int top;
		int w = CanvasMain.GetWidth() / DPI_Scale;
		int h = CanvasMain.GetHeight() / DPI_Scale;

		CanvasMain.SetBkColor(BACKGROUND_COLOR);
		DrawLabelControls();
		DrawPlaybackArea();

		// 顶部区域分割线
		top = MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL * 3 + 10;
		CanvasMain.Line(10, top, w - 10, top, true, LINE_COLOR);

		// 提示区域分割线
		top = h - BUTTON_HEIGHT - MARGIN_VERTICAL - 12 - 50 - 20;
		CanvasMain.Line(10, top, w - 10, top, true, LINE_COLOR);

		// 底部区域分割线
		top = h - BUTTON_HEIGHT - MARGIN_VERTICAL - 12;
		CanvasMain.Line(10, top, w - 10, top, true, LINE_COLOR);

		auto widthAccu = 0;
		auto tempBtnWidth = BUTTON_WIDTH;
		if (SettingsHelper::Settings.IsNeedTextCalc())
		{
			auto textSize = FontHelper::CalculateTextSize(GetStringFromKey("String.Window.Main.Start").c_str(), SettingsHelper::Settings.GetFont(), DEFAULT_BUTTON_FONTSIZE).cx;
			if (textSize + 30 > tempBtnWidth) tempBtnWidth = textSize + 30;
		}
		widthAccu += tempBtnWidth;

		tempBtnWidth = BUTTON_WIDTH;
		if (SettingsHelper::Settings.IsNeedTextCalc())
		{
			auto textSize = FontHelper::CalculateTextSize(GetStringFromKey("String.Window.Main.Restart").c_str(), SettingsHelper::Settings.GetFont(), DEFAULT_BUTTON_FONTSIZE).cx;
			if (textSize + 30 > tempBtnWidth) tempBtnWidth = textSize + 30;
		}
		widthAccu += tempBtnWidth;
		CanvasMain.Line(w - MARGIN_HORIZONTAL - widthAccu - CONTROL_PADDING_HORIZONTAL * 2.5, top + 10, w - MARGIN_HORIZONTAL - widthAccu - CONTROL_PADDING_HORIZONTAL * 2.5, top + 40, true, SUBLINE_COLOR);

		IsInDrawAtWndProcPaint = false;
	}

#pragma endregion

#pragma region Lyrics

	/// <summary>
	/// 获取输出文件完整路径 (含文件名)
	/// </summary>
	/// <returns>输出文件完整路径 (含文件名)</returns>
	std::wstring GetOutputFullpath()
	{
		auto outputPath = TextBoxOutputPath.GetText();
		if (outputPath.empty())
		{
			TCHAR exePath[MAX_PATH];
			GetModuleFileName(NULL, exePath, MAX_PATH);
			outputPath = StringHelper::GetDirectoryFromPath(exePath) + L"\\output\\";
		}
		if (outputPath.back() != L'/' && outputPath.back() != '\\') outputPath += L'\\';
		FileHelper::EnsureDirectoryExists(outputPath);
		auto filename = StringHelper::GetFileNameFromPath(TextBoxChooseAudio.GetText());
		filename = StringHelper::ReplaceFileNameExtension(filename, L"lyl");
		return outputPath + filename;
	}

	/// <summary>
	/// 获取当前行的序号 (以 0 为起点)
	/// </summary>
	/// <returns>当前行的序号</returns>
	int GetCurrentLineIndex()
	{
		for (int i = 0; i < (int)LyricsList.size(); i++)
		{
			if (LyricsList[i].StartTime == -1)
			{
				return i - 1;
			}
		}
		return (int)LyricsList.size() - 1;
	}

	/// <summary>
	/// 获取当前行的歌词对象
	/// </summary>
	/// <param name="index">指定当前行的序号，若不指定则自动查找当前行</param>
	/// <returns>当前行的歌词对象</returns>
	Lyricify::Lyrics* GetCurrentLine(int index)
	{
		if (index == -1)
			index = GetCurrentLineIndex();

		if (index >= 0 && index < (int)LyricsList.size())
			return &LyricsList[index];

		return nullptr;
	}

	/// <summary>
	/// 获取当前行的歌词文本
	/// </summary>
	/// <param name="index">指定当前行的序号，若不指定则自动查找当前行</param>
	/// <returns>当前行的歌词文本</returns>
	std::wstring GetCurrentLineString(int index)
	{
		if (index == -2)
			index = GetCurrentLineIndex();

		if (index >= 0 && index < (int)LyricsList.size())
			return LyricsList[index].Text;

		return L"";
	}

	/// <summary>
	/// 获取后续行的歌词文本列表
	/// </summary>
	/// <param name="index">指定当前行的序号，若不指定则自动查找当前行</param>
	/// <param name="maxSize">歌词文本列表的最大容量</param>
	/// <returns>后续行的歌词文本列表</returns>
	std::vector<std::wstring> GetComingLinesString(int index, size_t maxSize)
	{
		if (index == -2)
			index = GetCurrentLineIndex();

		std::vector<std::wstring> strings;
		for (int i = index + 1; i < (int)LyricsList.size() && (maxSize == -1 || strings.size() < maxSize); i++)
		{
			strings.push_back(LyricsList[i].Text);
		}
		return strings;
	}

#pragma endregion

#pragma region Window

	/// <summary>
	/// 获取窗口区域矩形
	/// </summary>
	/// <returns>窗口区域矩形</returns>
	RECT GetWindowRect()
	{
		auto pos = wnd.GetPos();
		auto size = wnd.GetWindowSize();
		return { pos.x, pos.y, pos.x + size.cx, pos.y + size.cy };
	}

	/// <summary>
	/// 主窗口回调函数
	/// </summary>
	/// <param name="hWnd">窗口句柄</param>
	/// <param name="msg">消息ID</param>
	/// <param name="wParam">消息参数 wParam</param>
	/// <param name="lParam">消息参数 lParam</param>
	/// <returns></returns>
	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_PAINT:
			DrawAtWndProcPaint();
			break;

		case WM_SIZE:
		{
			CanvasMain.Clear(true, BACKGROUND_COLOR);
			ResizeMoveControls();
			break;
		}

		case WM_GETMINMAXINFO:
		{
			MINMAXINFO* pmmi = (MINMAXINFO*)lParam;
			pmmi->ptMinTrackSize.x = MIN_WINDOW_WIDTH * DPI_Scale;
			pmmi->ptMinTrackSize.y = MIN_WINDOW_HEIGHT * DPI_Scale;
			return 0;
		}

		case WM_KEYDOWN:
		case WM_IME_KEYDOWN:
			KeyboardEvents(wParam);
			break;

		default:
			return HIWINDOW_DEFAULT_PROC;
			break;
		}

		return 0;
	}

	void Show(double scale)
	{
		DPI_Scale = scale;

		// 初始化窗口
		wnd.InitWindow(WINDOW_WIDTH * DPI_Scale, WINDOW_HEIGHT * DPI_Scale, EW_NORMAL, L"Lyricify Lines Creator");
		wnd.BindCanvas(&CanvasMain);
		wnd.SetProcFunc(WndProc);
		ImmAssociateContext(wnd.GetHandle(), NULL); // 窗口中禁用 IME
		hiex::AutoExit();

		setaspectratio(DPI_Scale, DPI_Scale);
		CanvasMain.SetTextColor(FOREGROUND_COLOR);

		// 设置 Canvas 字体，参考文档: https://docs.easyx.cn/zh-cn/LOGFONT
		setfont(DEFAULT_CANVAS_FONTSIZE, 0, SettingsHelper::Settings.GetFont(), 0, 0, 0, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);

		// 绘制窗体控件
		AddWindowControls(wnd.GetHandle());

		TaskHelper::Delay(10).wait();
		CanvasMain.Clear(true, BACKGROUND_COLOR);
		DrawAtWndProcPaint();
		wnd.Redraw(); // 立即重绘窗口 才能使得绘制的文本显示出来

		// 关闭窗口，结束程序
		hiex::init_end(wnd.GetHandle());
	}

#pragma endregion
}
