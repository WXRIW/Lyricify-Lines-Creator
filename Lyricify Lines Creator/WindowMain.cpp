#include "WindowMain.h"

namespace WindowMain
{
#pragma region Variable Definations

	double DPI_Scale = 1;

	// 顶部区域左侧 Label 的宽度，后期本地化时在这里更改尺寸
	int TOP_LEFT_LABEL_MAX_WIDTH = 65;

	bool IsInRefreshUI = false;
	bool IsInDrawAtWndProcPaint = false;
	bool IsMaking = false;
	std::vector<Lyricify::Lyrics> LyricsList;

#pragma endregion

#pragma region Control Definations

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

	// 底部区域

	hiex::SysButton ButtonAbout;
	hiex::SysButton ButtonViewOutput;
	hiex::SysButton ButtonPreview;
	hiex::SysButton ButtonRestart;
	hiex::SysButton ButtonStart;

#pragma endregion

#pragma region Button Clicks & Keyboard Events

	void ButtonChooseAudio_Click()
	{
		auto path = FileHelper::SelectFile(L"选择音频", L"音频 (*.mp3;*.wav;*.flac;*.ogg)\0*.mp3;*.wav;*.flac;*.ogg");
		if (!path.empty())
		{
			TextBoxChooseAudio.SetText(path);

			if (!MusicPlayer::Load(path))
			{
				MessageBox(wnd.GetHandle(), L"音频加载失败！", L"加载失败", MB_OK | MB_ICONWARNING);
			}
		}
	}

	void ButtonChooseRawLyrics_Click()
	{
		auto path = FileHelper::SelectFile(L"选择歌词", L"文本文档 (*.txt)\0*.txt");
		if (!path.empty())
		{
			TextBoxChooseRawLyrics.SetText(path);

			auto stringLines = Lyricify::LyricsHelper::ReadTextToLines(TextBoxChooseRawLyrics.GetText());
			if (stringLines.size() == 0)
			{
				MessageBox(wnd.GetHandle(), L"文本为空，或出现读取错误！", L"预处理错误", MB_OK | MB_ICONWARNING);
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
		auto path = FileHelper::SelectFolder(L"选择导出路径");
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
			ButtonPlayPause.SetText(L"播放");
		}
		else
		{
			if (MusicPlayer::CurrentAudioPath.empty() && !TextBoxChooseAudio.GetText().empty()
				|| MusicPlayer::CurrentAudioPath != TextBoxChooseAudio.GetText())
			{
				// 没有加载音频，或音频变更时，需要重新加载
				if (!MusicPlayer::Load(TextBoxChooseAudio.GetText()))
				{
					MessageBox(wnd.GetHandle(), L"音频加载失败！", L"加载失败", MB_OK | MB_ICONWARNING);
				}
			}

			MusicPlayer::Play();
			ButtonPlayPause.SetText(L"暂停");

			std::thread([]()
				{
					static bool IsRefreshThreadRunning = false;
					if (IsRefreshThreadRunning) return;
					IsRefreshThreadRunning = true;

					std::wstring audio = MusicPlayer::CurrentAudioPath;
					while (audio == MusicPlayer::CurrentAudioPath && MusicPlayer::IsPlaying())
					{
						if (!WindowAbout::IsOpened() && !WindowPreviewOutput::IsOpened()) // 关于被打开时，不再刷新进度，防止渲染错乱
						{
							RefreshUI();
						}
						TaskHelper::Delay(25).wait();
					}
					if (!MusicPlayer::IsPlaying())
					{
						ButtonPlayPause.SetText(L"播放");
					}

					IsRefreshThreadRunning = false;
				}).detach();
		}
	}

	void ButtonAbout_Click()
	{
		WindowAbout::Show(DPI_Scale, GetWindowRect(), wnd.GetHandle());
	}

	void ButtonViewOutput_Click()
	{
		auto filePath = GetOutputFullpath();
		auto fileContent = Lyricify::LyricsHelper::GenerateLyricifyLinesFromLyricsList(LyricsList);
		if (fileContent.empty())
		{
			MessageBox(wnd.GetHandle(), L"没有可查看的输出！", L"错误", MB_OK | MB_ICONINFORMATION);
			return;
		}
		WindowPreviewOutput::Show(filePath, fileContent, DPI_Scale, GetWindowRect(), wnd.GetHandle());
	}

	void ButtonPreview_Click()
	{

	}

	void ButtonRestart_Click()
	{
		// 清空歌词的时间信息，并返回头部
		auto stringLines = Lyricify::LyricsHelper::ReadTextToLines(TextBoxChooseRawLyrics.GetText());
		if (stringLines.size() == 0)
		{
			MessageBox(wnd.GetHandle(), L"文本为空，或出现读取错误！", L"预处理错误", MB_OK | MB_ICONWARNING);
			return;
		}
		LyricsList = Lyricify::LyricsHelper::GetLyricsFromLines(stringLines);
		MusicPlayer::SeekTo(0);

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
				MessageBox(wnd.GetHandle(), L"未选择音频！", L"预处理错误", MB_OK | MB_ICONWARNING);
				return;
			}
			if (MusicPlayer::CurrentAudioPath != TextBoxChooseAudio.GetText() && !MusicPlayer::Load(TextBoxChooseAudio.GetText()))
			{
				MessageBox(wnd.GetHandle(), L"音频加载失败！", L"预处理错误", MB_OK | MB_ICONWARNING);
				return;
			}
			if (TextBoxChooseRawLyrics.GetTextLength() == 0)
			{
				MessageBox(wnd.GetHandle(), L"未选择歌词文本！", L"预处理错误", MB_OK | MB_ICONWARNING);
				return;
			}
			auto stringLines = Lyricify::LyricsHelper::ReadTextToLines(TextBoxChooseRawLyrics.GetText());
			if (stringLines.size() == 0)
			{
				MessageBox(wnd.GetHandle(), L"文本为空，或出现读取错误！", L"预处理错误", MB_OK | MB_ICONWARNING);
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
			ButtonStart.SetText(L"保存歌词");
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
			auto lyricifyLinesString = Lyricify::LyricsHelper::GenerateLyricifyLinesFromLyricsList(LyricsList);
			if (lyricifyLinesString.empty())
			{
				MessageBox(wnd.GetHandle(), L"保存失败，没有歌词被写入文件！", L"保存失败", MB_OK | MB_ICONWARNING);
				return;
			}
			else
			{
				std::wofstream outFile(GetOutputFullpath());
				if (!outFile)
				{
					MessageBox(wnd.GetHandle(), L"保存失败，无法写入文件！", L"保存失败", MB_OK | MB_ICONWARNING);
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
			ButtonStart.SetText(L"开始制作");
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

		case VK_UP: // 为当前行 (下一行) 标记起始时间
		{
			if (!IsMaking) break;
			auto index = GetCurrentLineIndex();
			if (index < (int)LyricsList.size() - 1)
			{
				auto line = GetCurrentLine(index + 1);
				if (line != nullptr)
				{
					line->StartTime = MusicPlayer::GetCurrentPositionMs();
				}
			}
			else if (index == (int)LyricsList.size() - 1)
			{
				auto line = GetCurrentLine(index);
				if (line != nullptr && line->EndTime == -1)
				{
					line->EndTime = MusicPlayer::GetCurrentPositionMs();
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
				line->EndTime = MusicPlayer::GetCurrentPositionMs();
			}
			if (!MusicPlayer::IsPlaying()) RefreshUI();
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

#pragma region 顶部区域

		DrawLabelControls();

		left = MARGIN_HORIZONTAL + TOP_LEFT_LABEL_MAX_WIDTH + CONTROL_PADDING_HORIZONTAL;
		auto width = w - (MARGIN_HORIZONTAL * 2 + TOP_LEFT_LABEL_MAX_WIDTH + BUTTON_WIDTH + CONTROL_PADDING_HORIZONTAL * 2);
		TextBoxChooseAudio.Create(hwnd, left, MARGIN_VERTICAL, width, CONTROL_HEIGHT);
		TextBoxChooseRawLyrics.Create(hwnd, left, MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL, width, CONTROL_HEIGHT);
		TextBoxOutputPath.Create(hwnd, left, MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL * 2, width, CONTROL_HEIGHT);

		left = w - MARGIN_HORIZONTAL - BUTTON_WIDTH;
		ButtonChooseAudio.Create(hwnd, left, BUTTON_HEIGHT_OFFSET + MARGIN_VERTICAL, BUTTON_WIDTH, BUTTON_HEIGHT, L"导入音频");
		ButtonChooseRawLyrics.Create(hwnd, left, BUTTON_HEIGHT_OFFSET + MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL, BUTTON_WIDTH, BUTTON_HEIGHT, L"导入歌词");
		ButtonOutputPath.Create(hwnd, left, BUTTON_HEIGHT_OFFSET + MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL * 2, BUTTON_WIDTH, BUTTON_HEIGHT, L"选择路径");

#pragma endregion

#pragma region 播放区域

		top = MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL * 3 + 25;
		ButtonPlayPause.Create(hwnd, left, BUTTON_HEIGHT_OFFSET + top, BUTTON_WIDTH, BUTTON_HEIGHT, L"播放");

#pragma endregion

#pragma region 底部区域

		top = h - MARGIN_VERTICAL - BUTTON_HEIGHT;
		ButtonAbout.Create(hwnd, MARGIN_HORIZONTAL, top, BUTTON_WIDTH, BUTTON_HEIGHT, L"关于");
		ButtonViewOutput.Create(hwnd, w - MARGIN_HORIZONTAL - BUTTON_WIDTH * 4 - CONTROL_PADDING_HORIZONTAL * 5, top, BUTTON_WIDTH, BUTTON_HEIGHT, L"查看输出");
		ButtonPreview.Create(hwnd, w - MARGIN_HORIZONTAL - BUTTON_WIDTH * 3 - CONTROL_PADDING_HORIZONTAL * 4, top, BUTTON_WIDTH, BUTTON_HEIGHT, L"预览效果");
		ButtonRestart.Create(hwnd, w - MARGIN_HORIZONTAL - BUTTON_WIDTH * 2 - CONTROL_PADDING_HORIZONTAL, top, BUTTON_WIDTH, BUTTON_HEIGHT, L"重新制作");
		ButtonStart.Create(hwnd, w - MARGIN_HORIZONTAL - BUTTON_WIDTH, top, BUTTON_WIDTH, BUTTON_HEIGHT, L"开始制作");

#pragma endregion

		// 设置字体
		TextBoxChooseAudio.SetFont(DEFAULT_TEXTBOX_FONTSIZE, 0, DEFAULT_FONT);
		TextBoxChooseRawLyrics.SetFont(DEFAULT_TEXTBOX_FONTSIZE, 0, DEFAULT_FONT);
		TextBoxOutputPath.SetFont(DEFAULT_TEXTBOX_FONTSIZE, 0, DEFAULT_FONT);
		ButtonChooseAudio.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, DEFAULT_FONT);
		ButtonChooseRawLyrics.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, DEFAULT_FONT);
		ButtonOutputPath.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, DEFAULT_FONT);
		ButtonPlayPause.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, DEFAULT_FONT);
		ButtonAbout.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, DEFAULT_FONT);
		ButtonViewOutput.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, DEFAULT_FONT);
		ButtonPreview.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, DEFAULT_FONT);
		ButtonRestart.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, DEFAULT_FONT);
		ButtonStart.SetFont(DEFAULT_BUTTON_FONTSIZE, 0, DEFAULT_FONT);

		// 注册点击消息
		ButtonChooseAudio.RegisterMessage(ButtonChooseAudio_Click);
		ButtonChooseRawLyrics.RegisterMessage(ButtonChooseRawLyrics_Click);
		ButtonOutputPath.RegisterMessage(ButtonOutputPath_Click);
		ButtonPlayPause.RegisterMessage(ButtonPlayPause_Click);
		ButtonAbout.RegisterMessage(ButtonAbout_Click);
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

#pragma region 顶部区域

		// 因 HiEasyX 的一些问题，Resize 后边框将变粗
		auto width = w - (MARGIN_HORIZONTAL * 2 + TOP_LEFT_LABEL_MAX_WIDTH + BUTTON_WIDTH + CONTROL_PADDING_HORIZONTAL * 2);
		TextBoxChooseAudio.Resize(width, CONTROL_HEIGHT);
		TextBoxChooseRawLyrics.Resize(width, CONTROL_HEIGHT);
		TextBoxOutputPath.Resize(width, CONTROL_HEIGHT);

		left = w - MARGIN_HORIZONTAL - BUTTON_WIDTH;
		ButtonChooseAudio.Move(left, BUTTON_HEIGHT_OFFSET + MARGIN_VERTICAL);
		ButtonChooseRawLyrics.Move(left, BUTTON_HEIGHT_OFFSET + MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL);
		ButtonOutputPath.Move(left, BUTTON_HEIGHT_OFFSET + MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL * 2);

#pragma endregion

#pragma region 播放区域

		top = MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL * 3 + 25;
		ButtonPlayPause.Move(left, BUTTON_HEIGHT_OFFSET + top);

#pragma endregion

#pragma region 底部区域

		top = h - MARGIN_VERTICAL - BUTTON_HEIGHT;
		ButtonAbout.Move(MARGIN_HORIZONTAL, top);
		ButtonViewOutput.Move(w - MARGIN_HORIZONTAL - BUTTON_WIDTH * 4 - CONTROL_PADDING_HORIZONTAL * 5, top);
		ButtonPreview.Move(w - MARGIN_HORIZONTAL - BUTTON_WIDTH * 3 - CONTROL_PADDING_HORIZONTAL * 4, top);
		ButtonRestart.Move(w - MARGIN_HORIZONTAL - BUTTON_WIDTH * 2 - CONTROL_PADDING_HORIZONTAL, top);
		ButtonStart.Move(w - MARGIN_HORIZONTAL - BUTTON_WIDTH, top);

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
		CanvasMain.OutTextXY(MARGIN_HORIZONTAL, 1 + MARGIN_VERTICAL, L"选择音频：");
		CanvasMain.OutTextXY(MARGIN_HORIZONTAL, 1 + MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL, L"选择歌词：");
		CanvasMain.OutTextXY(MARGIN_HORIZONTAL, 1 + MARGIN_VERTICAL + CONTROL_PADDING_VERTICAL * 2, L"输出路径：");
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

		setfont(DEFAULT_CANVAS_FONTSIZE, 0, DEFAULT_FONT, 0, 0, FW_BOLD, false, false, false);
		CanvasMain.OutTextXY(MARGIN_HORIZONTAL, top + LYRICS_PADDING_VERTICAL, L"当前行：");
		CanvasMain.OutTextXY(MARGIN_HORIZONTAL, top + LYRICS_PADDING_VERTICAL * 2, L"下一行：");

		// 还原字体设置
		setfont(DEFAULT_CANVAS_FONTSIZE, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, false, false);

		// 绘制歌词文本
		// 可通过剩余高度 判断绘制多行歌词
		left = MARGIN_HORIZONTAL + 66;
		auto currentIndex = GetCurrentLineIndex();
		auto currentLine = GetCurrentLine(currentIndex);
		auto isCurrentLineHasEndTime = false;
		if (currentLine != nullptr && currentLine->EndTime != -1)
		{
			CanvasMain.SetTextColor(RGB(0x7F, 0x7F, 0x7F));
		}
		CanvasMain.OutTextXY(left, top + LYRICS_PADDING_VERTICAL, GetCurrentLineString(currentIndex).c_str());
		auto lyricsHeight = h - BUTTON_HEIGHT - MARGIN_VERTICAL - 12 - 76 - top;
		auto linesAvailable = lyricsHeight / LYRICS_PADDING_VERTICAL - 1;
		linesAvailable = linesAvailable < 1 ? 1 : linesAvailable;
		auto comingLines = GetComingLinesString(currentIndex, linesAvailable);
		CanvasMain.SetTextColor(RGB(0x7F, 0x7F, 0x7F));
		for (size_t i = 0; i < comingLines.size(); i++)
		{
			CanvasMain.OutTextXY(left, top + LYRICS_PADDING_VERTICAL * (i + 2), comingLines[i].c_str());
		}

#pragma endregion

#pragma region 提示区域

		top = h - BUTTON_HEIGHT - MARGIN_VERTICAL - 12 - 36;
		setfont(DEFAULT_CANVAS_FONTSIZE, 0, DEFAULT_FONT, 0, 0, FW_BOLD, false, false, false);
		CanvasMain.SetTextColor(FOREGROUND_COLOR);
		CanvasMain.OutTextXY(MARGIN_HORIZONTAL, top, L"按键提示：");
		setfont(DEFAULT_CANVAS_FONTSIZE - 1, 0, DEFAULT_FONT, 0, 0, FW_DONTCARE, false, false, false);
		CanvasMain.OutTextXY(MARGIN_HORIZONTAL + 90, top + 1, L"行起始: ↑      行结束: →      回到上一行: ↓      回退 3s: B      前进 3s: N      前进 10s: M      播放/暂停: Space");

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
		top = h - BUTTON_HEIGHT - MARGIN_VERTICAL - 12 - 50;
		CanvasMain.Line(10, top, w - 10, top, true, LINE_COLOR);

		// 底部区域分割线
		top = h - BUTTON_HEIGHT - MARGIN_VERTICAL - 12;
		CanvasMain.Line(10, top, w - 10, top, true, LINE_COLOR);
		CanvasMain.Line(w - MARGIN_HORIZONTAL - BUTTON_WIDTH * 2 - CONTROL_PADDING_HORIZONTAL * 2.5, top + 10, w - MARGIN_HORIZONTAL - BUTTON_WIDTH * 2 - CONTROL_PADDING_HORIZONTAL * 2.5, top + 40, true, SUBLINE_COLOR);

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
		setfont(DEFAULT_CANVAS_FONTSIZE, 0, DEFAULT_FONT, 0, 0, 0, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH);

		// 绘制窗体控件
		AddWindowControls(wnd.GetHandle());
		wnd.Redraw(); // 立即重绘窗口 才能使得绘制的文本显示出来

		// 关闭窗口，结束程序
		hiex::init_end(wnd.GetHandle());
	}

#pragma endregion
}
