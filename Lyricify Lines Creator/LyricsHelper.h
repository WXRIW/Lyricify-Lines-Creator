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
		static std::vector<std::wstring> ReadTextToLines(std::wstring filePath);
		static std::vector<Lyricify::Lyrics> GetLyricsFromLines(std::vector<std::wstring> lines);
		static std::vector<Lyricify::Lyrics> ParseLyricsFromLyricifyLinesString(std::wstring raw);
		static std::wstring GenerateLyricifyLinesFromLyricsList(std::vector<Lyricify::Lyrics> lyrics);
	};
}
