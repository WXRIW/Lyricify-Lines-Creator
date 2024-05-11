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
		static std::vector<std::string> ReadTextToLines(std::string filePath);
		static std::vector<Lyricify::Lyrics> GetLyricsFromLines(std::vector<std::string> lines);
	};
}
