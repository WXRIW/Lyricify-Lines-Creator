#pragma once

#include <string>

namespace Lyricify
{
	class Lyrics
	{
	public:
		/// <summary>
		/// 歌词行原文
		/// </summary>
		std::wstring Text;

		/// <summary>
		/// 歌词行起始时间
		/// </summary>
		int StartTime;

		/// <summary>
		/// 歌词行结束时间<br/>
		/// 特别的，若结束时间为 -1，则认为没有设置结束时间，应当采用下一行的起始时间
		/// </summary>
		int EndTime;

		Lyrics()
		{
			Text = L"";
			StartTime = -1;
			EndTime = -1;
		}

		Lyrics(std::wstring text)
		{
			Text = text;
			StartTime = -1;
			EndTime = -1;
		}

		Lyrics(std::wstring text, int start)
		{
			Text = text;
			StartTime = start;
			EndTime = -1;
		}

		Lyrics(std::wstring text, int start, int end)
		{
			Text = text;
			StartTime = start;
			EndTime = end;
		}
	};
}
