#pragma once

#include <string>
#include <ShlObj.h>

class FileHelper
{
public:
	/// <summary>
	/// 选择文件
	/// </summary>
	/// <param name="title">对话框标题</param>
	/// <param name="fileFilter">文件类型筛选器</param>
	/// <returns>文件名，未选择为空字符串</returns>
	static std::wstring SelectFile(LPCWSTR title, LPCWSTR fileFilter);

	/// <summary>
	/// 选择文件夹
	/// </summary>
	/// <param name="title">对话框标题</param>
	/// <returns>路径，未选择为空字符串</returns>
	static std::wstring SelectFolder(LPCWSTR title);
};
