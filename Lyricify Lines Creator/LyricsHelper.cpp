#include "LyricsHelper.h"

namespace Lyricify
{
	/// <summary>
	/// 从文件读取文本行存入 vector 列表
	/// </summary>
	/// <param name="filePath">文件路径</param>
	/// <returns>存入的 vector 列表，若失败则返回空列表</returns>
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

	/// <summary>
	/// 将文本行列表存入新的 Lyricify.Lyrics 的 vector 列表
	/// </summary>
	/// <param name="lines">文本行 vector 列表</param>
	/// <returns>存入的 vector 列表</returns>
	std::vector<Lyricify::Lyrics> LyricsHelper::GetLyricsFromLines(std::vector<std::wstring> lines)
	{
        std::vector<Lyricify::Lyrics> list;

        for (int i = 0; i < lines.size(); i++)
        {
            Lyricify::Lyrics line(lines[i]);
            list.push_back(line);
        }

        return list;
	}
}
