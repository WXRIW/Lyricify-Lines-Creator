/************************************************************************
 * Filename:    LyricsHelper.cpp
 * Description: 歌词帮助类实现
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#include "LyricsHelper.h"

namespace Lyricify
{
	std::vector<std::wstring> LyricsHelper::ReadTextToLines(std::wstring filePath)
	{
        std::ifstream inputFile(filePath);

        if (!inputFile) // 文件流创建失败
        {
            return std::vector<std::wstring>(); // 返回空列表
        }

        std::vector<std::wstring> lines;

        std::string line;
        while (std::getline(inputFile, line))
        {
            auto ws = StringHelper::StringToWstring(line);
            if (StringHelper::IsEmptyOrWhiteSpace(ws)) continue; // 丢弃空行
            lines.push_back(StringHelper::Trim(ws));
        }

        inputFile.close();

        return lines;
	}

	std::vector<Lyricify::Lyrics> LyricsHelper::GetLyricsFromLines(std::vector<std::wstring> lines)
	{
        std::vector<Lyricify::Lyrics> list;

        for (uint32_t i = 0; i < lines.size(); i++)
        {
            Lyricify::Lyrics line(lines[i]);
            list.push_back(line);
        }

		return list;
	}

	std::vector<Lyricify::Lyrics> LyricsHelper::ParseLyricsFromLyricifyLinesString(std::wstring raw)
	{
		std::vector<Lyricify::Lyrics> list;

		// 分割输入为每一行
		std::wistringstream iss(raw);
		std::wstring line;
		while (std::getline(iss, line))
		{
			// 检查是否是歌词行
			if (line.find(L"[") != std::wstring::npos && line.find(L"]") != std::wstring::npos)
			{
				// 获取起始时间和结束时间
				size_t startPos = line.find(L"[");
				size_t endPos = line.find(L"]");
				std::wstring timeStr = line.substr(startPos + 1, endPos - startPos - 1);
				if (timeStr[0] < '0' || timeStr[1] > '9') continue;// 可能是头部信息行，跳过

				// 获取首尾时间
				size_t commaPos = timeStr.find(L",");
				int startTime = -1, endTime = -1;
				try
				{
					startTime = std::stoi(timeStr.substr(0, commaPos));
					endTime = std::stoi(timeStr.substr(commaPos + 1));
				}
				catch (...)
				{
					continue; // 出错了，跳过该行
				}

				// 获取歌词文本
				std::wstring text = line.substr(endPos + 1);

				// 创建 Lyrics 对象并添加到列表中
				list.push_back(Lyricify::Lyrics(StringHelper::Trim(text), startTime, endTime));
			}
		}

		return list;
	}

	std::wstring LyricsHelper::GenerateLyricifyLinesFromLyricsList(const std::vector<Lyricify::Lyrics>& lyrics)
	{
		if (lyrics.size() < 1) return L"";

		std::wstring result = L"[type:LyricifyLines]\n";
		for (size_t i = 0; i < lyrics.size(); i++)
		{
			if (lyrics[i].StartTime == -1)
				break; // 遇到没有起始时间的歌词，直接结束字符串生成

			int startTime = lyrics[i].StartTime;
			int endTime = (lyrics[i].EndTime != -1) ? lyrics[i].EndTime : ((i + 1 < lyrics.size() && lyrics[i + 1].StartTime != -1) ? lyrics[i + 1].StartTime : 0);

			result += L"[" + std::to_wstring(startTime) + L"," + std::to_wstring(endTime) + L"]" + lyrics[i].Text + L"\n";
		}

		return result == L"[type:LyricifyLines]\n" ? L"" : StringHelper::TrimEnd(result);
	}

	/// <summary>
	/// 格式化时间为字符串，用于 LRC 歌词
	/// </summary>
	/// <param name="timeMs">时间毫秒数</param>
	/// <returns>时间字符串</returns>
	static std::wstring FormatTime(int timeMs)
	{
		int minutes = timeMs / 60000;
		int seconds = (timeMs % 60000) / 1000;
		int hundredths = (timeMs % 1000) / 10;

		std::wostringstream oss;
		oss << L"[" << std::setfill(L'0') << std::setw(2) << minutes << L":"
			<< std::setfill(L'0') << std::setw(2) << seconds << L"."
			<< std::setfill(L'0') << std::setw(2) << hundredths << L"]";
		return oss.str();
	}

	std::wstring LyricsHelper::GenerateLrcFromLyricsList(const std::vector<Lyricify::Lyrics>& lyrics)
	{
		if (lyrics.empty()) return L"";

		std::wstring result;
		for (const auto& lyric : lyrics)
		{
			if (lyric.StartTime == -1)
				break; // 遇到没有起始时间的歌词，直接结束字符串生成

			result += FormatTime(lyric.StartTime) + lyric.Text + L"\n";
		}

		return result.empty() ? L"" : StringHelper::TrimEnd(result);
	}
}
