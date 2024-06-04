/************************************************************************
 * Filename:    InternationalizationHelper.cpp
 * Description: 本地化方法实现
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#include "InternationalizationHelper.h"

std::map<std::string, std::map<Languages, std::wstring>> translations =
{
	{
		"String.Window.Main.SelectAudio",
		{
			{ Languages::EN, L"Select Audio:" },
			{ Languages::ZH_HANS, L"选择音频：" },
			{ Languages::ZH_HANT, L"選擇音頻：" }
		}
	},
	{
		"String.Window.Main.SelectLyrics",
		{
			{ Languages::EN, L"Select Lyrics:" },
			{ Languages::ZH_HANS, L"选择歌词：" },
			{ Languages::ZH_HANT, L"選擇歌詞：" }
		}
	},
	{
		"String.Window.Main.OutputPath",
		{
			{ Languages::EN, L"Output Path:" },
			{ Languages::ZH_HANS, L"输出路径：" },
			{ Languages::ZH_HANT, L"輸出路徑：" }
		}
	},
	{
		"String.Window.Main.ImportAudio",
		{
			{ Languages::EN, L"Import Audio" },
			{ Languages::ZH_HANS, L"导入音频" },
			{ Languages::ZH_HANT, L"導入音頻" }
		}
	},
	{
		"String.Window.Main.ImportLyrics",
		{
			{ Languages::EN, L"Import Lyrics" },
			{ Languages::ZH_HANS, L"导入歌词" },
			{ Languages::ZH_HANT, L"導入歌詞" }
		}
	},
	{
		"String.Window.Main.SelectPath",
		{
			{ Languages::EN, L"Select Path" },
			{ Languages::ZH_HANS, L"选择路径" },
			{ Languages::ZH_HANT, L"選擇路徑" }
		}
	},
	{
		"String.Window.Main.Play",
		{
			{ Languages::EN, L"Play" },
			{ Languages::ZH_HANS, L"播放" },
			{ Languages::ZH_HANT, L"播放" }
		}
	},
	{
		"String.Window.Main.Pause",
		{
			{ Languages::EN, L"Pause" },
			{ Languages::ZH_HANS, L"暂停" },
			{ Languages::ZH_HANT, L"暫停" }
		}
	},
	{
		"String.Window.Main.About",
		{
			{ Languages::EN, L"About" },
			{ Languages::ZH_HANS, L"关于" },
			{ Languages::ZH_HANT, L"關於" }
		}
	},
	{
		"String.Window.Main.Settings",
		{
			{ Languages::EN, L"Settings" },
			{ Languages::ZH_HANS, L"设置" },
			{ Languages::ZH_HANT, L"設置" }
		}
	},
	{
		"String.Window.Main.ViewOutput",
		{
			{ Languages::EN, L"View Output" },
			{ Languages::ZH_HANS, L"查看输出" },
			{ Languages::ZH_HANT, L"查看輸出" }
		}
	},
	{
		"String.Window.Main.Preview",
		{
			{ Languages::EN, L"Preview" },
			{ Languages::ZH_HANS, L"预览效果" },
			{ Languages::ZH_HANT, L"預覽效果" }
		}
	},
	{
		"String.Window.Main.Restart",
		{
			{ Languages::EN, L"Restart" },
			{ Languages::ZH_HANS, L"重新制作" },
			{ Languages::ZH_HANT, L"重新製作" }
		}
	},
	{
		"String.Window.Main.Start",
		{
			{ Languages::EN, L"Start" },
			{ Languages::ZH_HANS, L"开始制作" },
			{ Languages::ZH_HANT, L"開始製作" }
		}
	},
	{
		"String.Window.Main.SaveLyrics",
		{
			{ Languages::EN, L"Save Lyrics" },
			{ Languages::ZH_HANS, L"保存歌词" },
			{ Languages::ZH_HANT, L"保存歌詞" }
		}
	},
	{
		"String.Window.Main.AudioLoadFailed",
		{
			{ Languages::EN, L"Audio load failed!" },
			{ Languages::ZH_HANS, L"音频加载失败！" },
			{ Languages::ZH_HANT, L"音頻加載失敗！" }
		}
	},
	{
		"String.Window.Main.SelectAudioDialogTitle",
		{
			{ Languages::EN, L"Select Audio" },
			{ Languages::ZH_HANS, L"选择音频" },
			{ Languages::ZH_HANT, L"選擇音頻" }
		}
	},
	{
		"String.Window.Main.SelectAudioDialogFilter",
		{
			{ Languages::EN, L"Audio (*.mp3;*.wav;*.flac;*.ogg)\0*.mp3;*.wav;*.flac;*.ogg" },
			{ Languages::ZH_HANS, L"音频 (*.mp3;*.wav;*.flac;*.ogg)\0*.mp3;*.wav;*.flac;*.ogg" },
			{ Languages::ZH_HANT, L"音頻 (*.mp3;*.wav;*.flac;*.ogg)\0*.mp3;*.wav;*.flac;*.ogg" }
		}
	},
	{
		"String.Window.Main.SelectLyricsDialogTitle",
		{
			{ Languages::EN, L"Select Lyrics" },
			{ Languages::ZH_HANS, L"选择歌词" },
			{ Languages::ZH_HANT, L"選擇歌詞" }
		}
	},
	{
		"String.Window.Main.SelectLyricsDialogFilter",
		{
			{ Languages::EN, L"Text Files (*.txt)\0*.txt" },
			{ Languages::ZH_HANS, L"文本文档 (*.txt)\0*.txt" },
			{ Languages::ZH_HANT, L"文本文件 (*.txt)\0*.txt" }
		}
	},
	{
		"String.Window.Main.EmptyOrErrorText",
		{
			{ Languages::EN, L"The text is empty or an error occurred while reading!" },
			{ Languages::ZH_HANS, L"文本为空，或出现读取错误！" },
			{ Languages::ZH_HANT, L"文本為空，或出現讀取錯誤！" }
		}
	},
	{
		"String.Window.Main.OutputPathDialogTitle",
		{
			{ Languages::EN, L"Select Export Path" },
			{ Languages::ZH_HANS, L"选择导出路径" },
			{ Languages::ZH_HANT, L"選擇導出路徑" }
		}
	},
	{
		"String.Window.Main.NoOutputToView",
		{
			{ Languages::EN, L"No output to view!" },
			{ Languages::ZH_HANS, L"没有可查看的输出！" },
			{ Languages::ZH_HANT, L"沒有可查看的輸出！" }
		}
	},
	{
		"String.Window.Main.NoPreviewToView",
		{
			{ Languages::EN, L"No preview to view!" },
			{ Languages::ZH_HANS, L"没有可查看的预览！" },
			{ Languages::ZH_HANT, L"沒有可查看的預覽！" }
		}
	},
	{
		"String.Window.Main.NoAudioSelected",
		{
			{ Languages::EN, L"No audio selected!" },
			{ Languages::ZH_HANS, L"未选择音频！" },
			{ Languages::ZH_HANT, L"未選擇音頻！" }
		}
	},
	{
		"String.Window.Main.NoLyricsSelected",
		{
			{ Languages::EN, L"No lyrics file selected!" },
			{ Languages::ZH_HANS, L"未选择歌词文本！" },
			{ Languages::ZH_HANT, L"未選擇歌詞文件！" }
		}
	},
	{
		"String.Window.Main.NoLyricsToSave",
		{
			{ Languages::EN, L"Save failed, no lyrics written to file!" },
			{ Languages::ZH_HANS, L"保存失败，没有歌词被写入文件！" },
			{ Languages::ZH_HANT, L"保存失敗，沒有歌詞被寫入文件！" }
		}
	},
	{
		"String.Window.Main.SaveFailed",
		{
			{ Languages::EN, L"Save failed, unable to write to file!" },
			{ Languages::ZH_HANS, L"保存失败，无法写入文件！" },
			{ Languages::ZH_HANT, L"保存失敗，無法寫入文件！" }
		}
	},
	{
		"String.Window.Main.SaveFailedTitle",
		{
			{ Languages::EN, L"Save Failed" },
			{ Languages::ZH_HANS, L"保存失败" },
			{ Languages::ZH_HANT, L"保存失敗" }
		}
	},
	{
		"String.Window.Main.OutputSaveFailed",
		{
			{ Languages::EN, L"Save failed, unable to write to file!" },
			{ Languages::ZH_HANS, L"保存失败，无法写入文件！" },
			{ Languages::ZH_HANT, L"保存失敗，無法寫入文件！" }
		}
	},
	{
		"String.Window.Main.OutputSaveSuccess",
		{
			{ Languages::EN, L"Save successful!" },
			{ Languages::ZH_HANS, L"保存成功！" },
			{ Languages::ZH_HANT, L"保存成功！" }
		}
	},
	{
		"String.Window.Main.OutputSaveSuccessTitle",
		{
			{ Languages::EN, L"Save Successful" },
			{ Languages::ZH_HANS, L"保存成功" },
			{ Languages::ZH_HANT, L"保存成功" }
		}
	},
	{
		"String.Window.Main.PreviousLine",
		{
			{Languages::EN, L"Previous Line:"},
			{Languages::ZH_HANS, L"上一行："},
			{Languages::ZH_HANT, L"上一行："}
		}
	},
	{
		"String.Window.Main.CurrentLine",
		{
			{Languages::EN, L"Current Line:"},
			{Languages::ZH_HANS, L"当前行："},
			{Languages::ZH_HANT, L"當前行："}
		}
	},
	{
		"String.Window.Main.NextLine",
		{
			{Languages::EN, L"Next Line:"},
			{Languages::ZH_HANS, L"下一行："},
			{Languages::ZH_HANT, L"下一行："}
		}
	},
	{
		"String.Window.Main.NoticeLineStart",
		{
			{Languages::EN, L"Line Start: ↑"},
			{Languages::ZH_HANS, L"行起始: ↑"},
			{Languages::ZH_HANT, L"行起始: ↑"}
		}
	},
	{
		"String.Window.Main.NoticeCurrentLineEnd",
		{
			{Languages::EN, L"Current Line End: →"},
			{Languages::ZH_HANS, L"当前行结束: →"},
			{Languages::ZH_HANT, L"當前行結束: →"}
		}
	},
	{
		"String.Window.Main.NoticePreviousLineEnd",
		{
			{Languages::EN, L"Previous Line End: ←"},
			{Languages::ZH_HANS, L"上一行结束: ←"},
			{Languages::ZH_HANT, L"上一行結束: ←"}
		}
	},
	{
		"String.Window.Main.NoticeReturnToPreviousLine",
		{
			{Languages::EN, L"Return to Previous Line: ↓"},
			{Languages::ZH_HANS, L"回到上一行: ↓"},
			{Languages::ZH_HANT, L"回到上一行: ↓"}
		}
	},
	{
		"String.Window.Main.NoticePlayPause",
		{
			{Languages::EN, L"Play/Pause: Space"},
			{Languages::ZH_HANS, L"播放/暂停: Space"},
			{Languages::ZH_HANT, L"播放/暫停: Space"}
		}
	},
	{
		"String.Window.Main.NoticeSeekBack3s",
		{
			{Languages::EN, L"Seek Back 3s: B"},
			{Languages::ZH_HANS, L"回退 3s: B"},
			{Languages::ZH_HANT, L"回退 3s: B"}
		}
	},
	{
		"String.Window.Main.NoticeSeekForward3s",
		{
			{Languages::EN, L"Seek Forward 3s: N"},
			{Languages::ZH_HANS, L"前进 3s: N"},
			{Languages::ZH_HANT, L"前進 3s: N"}
		}
	},
	{
		"String.Window.Main.NoticeSeekForward10s",
		{
			{Languages::EN, L"Seek Forward 10s: M"},
			{Languages::ZH_HANS, L"前进 10s: M"},
			{Languages::ZH_HANT, L"前進 10s: M"}
		}
	},
	{
		"String.Window.Main.NoticeSeekForward30s",
		{
			{Languages::EN, L"Seek Forward 30s: C"},
			{Languages::ZH_HANS, L"前进 30s: C"},
			{Languages::ZH_HANT, L"前進 30s: C"}
		}
	},
	{
		"String.Window.Main.NoticeSeekTo0s",
		{
			{Languages::EN, L"Seek to 0s: R"},
			{Languages::ZH_HANS, L"回到 0s: R"},
			{Languages::ZH_HANT, L"回到 0s: R"}
		}
	},
	{
		"String.Window.Main.KeyTips",
		{
			{Languages::EN, L"Key Tips:"},
			{Languages::ZH_HANS, L"按键提示："},
			{Languages::ZH_HANT, L"按鍵提示："}
		}
	},
	{
		"String.Window.PreviewLyrics",
		{
			{ Languages::EN, L"Preview Lyrics" },
			{ Languages::ZH_HANS, L"歌词预览" },
			{ Languages::ZH_HANT, L"歌詞預覽" }
		}
	},
	{
		"String.Window.PreviewOutput",
		{
			{ Languages::EN, L"Output Preview" },
			{ Languages::ZH_HANS, L"输出预览" },
			{ Languages::ZH_HANT, L"輸出預覽" }
		}
	},
	{
		"String.Window.PreviewOutput.Save",
		{
			{ Languages::EN, L"Save" },
			{ Languages::ZH_HANS, L"保存" },
			{ Languages::ZH_HANT, L"保存" }
		}
	},
	{
		"String.Window.PreviewOutput.SaveSuccess",
		{
			{ Languages::EN, L"Saved successfully!" },
			{ Languages::ZH_HANS, L"保存成功！" },
			{ Languages::ZH_HANT, L"保存成功！" }
		}
	},
	{
		"String.Window.PreviewOutput.SaveFailed",
		{
			{ Languages::EN, L"Save failed, unable to write to file!" },
			{ Languages::ZH_HANS, L"保存失败，无法写入文件！" },
			{ Languages::ZH_HANT, L"保存失敗，無法寫入文件！" }
		}
	},
	{
		"String.Window.PreviewOutput.SaveFailedTitle",
		{
			{ Languages::EN, L"Save failed" },
			{ Languages::ZH_HANS, L"保存失败" },
			{ Languages::ZH_HANT, L"保存失敗" }
		}
	},
	{
		"String.Window.PreviewOutput.SaveSuccessTitle",
		{
			{ Languages::EN, L"Save successful" },
			{ Languages::ZH_HANS, L"保存成功" },
			{ Languages::ZH_HANT, L"保存成功" }
		}
	},
	{
		"String.Window.About",
		{
			{ Languages::EN, L"About" },
			{ Languages::ZH_HANS, L"关于" },
			{ Languages::ZH_HANT, L"關於" }
		}
	},
	{
		"String.Window.About.FullName",
		{
			{ Languages::EN, L"Lyricify Lines Line-Synced Lyrics Creator" },
			{ Languages::ZH_HANS, L"Lyricify Lines 逐行歌词打轴工具" },
			{ Languages::ZH_HANT, L"Lyricify Lines 逐行歌詞打軸工具" }
		}
	},
	{
		"String.Window.About.Developer",
		{
			{ Languages::EN, L"Developer" },
			{ Languages::ZH_HANS, L"开发者" },
			{ Languages::ZH_HANT, L"開發者" }
		}
	},
	{
		"String.Window.About.ThirdParty",
		{
			{ Languages::EN, L"Third Party Notices" },
			{ Languages::ZH_HANS, L"第三方通知" },
			{ Languages::ZH_HANT, L"第三方通知" }
		}
	},
	{
		"String.Window.About.License.MIT",
		{
			{ Languages::EN, L"MIT License" },
			{ Languages::ZH_HANS, L"MIT 协议" },
			{ Languages::ZH_HANT, L"MIT 協議" }
		}
	},
	{
		"String.Window.About.License.LGPL21",
		{
			{ Languages::EN, L"LGPL-2.1 License" },
			{ Languages::ZH_HANS, L"LGPL-2.1 协议" },
			{ Languages::ZH_HANT, L"LGPL-2.1 協議" }
		}
	},
	{
		"String.Window.Settings",
		{
			{ Languages::EN, L"Settings" },
			{ Languages::ZH_HANS, L"设置" },
			{ Languages::ZH_HANT, L"設置" }
		}
	},
	{
		"String.Window.Settings.Language",
		{
			{ Languages::EN, L"Language" },
			{ Languages::ZH_HANS, L"语言" },
			{ Languages::ZH_HANT, L"語言" }
		}
	},
	{
		"String.Window.Settings.LyricsOutputFormat",
		{
			{ Languages::EN, L"Lyrics Output Format" },
			{ Languages::ZH_HANS, L"歌词输出格式" },
			{ Languages::ZH_HANT, L"歌詞輸出格式" }
		}
	},
	{
		"String.Window.Settings.DeviceLatency",
		{
			{ Languages::EN, L"Device Latency" },
			{ Languages::ZH_HANS, L"设备延迟" },
			{ Languages::ZH_HANT, L"設備延遲" }
		}
	},
	{
		"String.Window.Settings.KeyboardLatency",
		{
			{ Languages::EN, L"Keyboard Latency" },
			{ Languages::ZH_HANS, L"按键延迟" },
			{ Languages::ZH_HANT, L"按鍵延遲" }
		}
	},
	{
		"String.Window.Settings.PreviewLyricsMaximize",
		{
			{ Languages::EN, L"Preview Lyrics Maximize" },
			{ Languages::ZH_HANS, L"歌词预览最大化" },
			{ Languages::ZH_HANT, L"歌詞預覽最大化" }
		}
	},
	{
		"String.Window.Settings.Save",
		{
			{ Languages::EN, L"Save" },
			{ Languages::ZH_HANS, L"确定" },
			{ Languages::ZH_HANT, L"確定" }
		}
	},
	{
		"String.Window.Settings.Cancel",
		{
			{ Languages::EN, L"Cancel" },
			{ Languages::ZH_HANS, L"取消" },
			{ Languages::ZH_HANT, L"取消" }
		}
	},
	{
		"String.Window.Settings.InvalidLatencyValue",
		{
			{ Languages::EN, L"The latency value should be an integer, usually a natural number." },
			{ Languages::ZH_HANS, L"延迟值应为整数，一般为自然数。" },
			{ Languages::ZH_HANT, L"延遲值應為整數，一般為自然數。" }
		}
	},
	{
		"String.Window.Settings.ErrorInput",
		{
			{ Languages::EN, L"Error Input" },
			{ Languages::ZH_HANS, L"错误输入" },
			{ Languages::ZH_HANT, L"錯誤輸入" }
		}
	},
};

std::wstring GetStringFromKey(const std::string& key)
{
	Languages lang = Languages::ZH_HANS;
	try
	{
		lang = static_cast<Languages>(SettingsHelper::Settings.Language);
	}
	catch (...) {}
	return translations[key][lang];
}

std::wstring GetStringFromKey(const std::string& key, Languages lang)
{
	return translations[key][lang];
}
