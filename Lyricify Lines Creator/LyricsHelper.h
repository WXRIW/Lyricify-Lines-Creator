/************************************************************************
 * Filename:    LyricsHelper.h
 * Description: 歌词帮助类定义
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#pragma once

#include <fstream>
#include <vector>
#include <string>
#include "Lyrics.h"
#include "StringHelper.h"

namespace Lyricify
{
	class LyricsHelper
	{
	public:
		/// <summary>
		/// 从文件读取文本行存入 vector 列表
		/// </summary>
		/// <param name="filePath">文件路径</param>
		/// <returns>存入的 vector 列表，若失败则返回空列表</returns>
		static std::vector<std::wstring> ReadTextToLines(std::wstring filePath);

		/// <summary>
		/// 将文本行列表存入新的 Lyricify.Lyrics 的 vector 列表
		/// </summary>
		/// <param name="lines">文本行 vector 列表</param>
		/// <returns>存入的 vector 列表</returns>
		static std::vector<Lyricify::Lyrics> GetLyricsFromLines(std::vector<std::wstring> lines);

		/// <summary>
		/// 解析歌词到列表
		/// </summary>
		/// <param name="raw">原始 Lyricify Lines 歌词字符串</param>
		/// <returns>歌词列表</returns>
		static std::vector<Lyricify::Lyrics> ParseLyricsFromLyricifyLinesString(std::wstring raw);

		/// <summary>
		/// 生成 Lyricify Lines 歌词字符串
		/// </summary>
		/// <param name="lyrics">歌词列表</param>
		/// <returns>生成的字符串</returns>
		static std::wstring GenerateLyricifyLinesFromLyricsList(const std::vector<Lyricify::Lyrics>& lyrics);

		/// <summary>
		/// 生成 LRC 歌词字符串
		/// </summary>
		/// <param name="lyrics">歌词列表</param>
		/// <returns>生成的字符串</returns>
		static std::wstring GenerateLrcFromLyricsList(const std::vector<Lyricify::Lyrics>& lyrics);
	};
}
