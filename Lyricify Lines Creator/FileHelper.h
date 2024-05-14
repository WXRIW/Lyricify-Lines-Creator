#pragma once

#include <filesystem>
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

	/// <summary>
	/// 确保路径存在，不存在时尝试创建目录
	/// </summary>
	/// <param name="path">要确保存在的路径</param>
	/// <returns>路径是否存在</returns>
	static bool EnsureDirectoryExists(const std::wstring& path);
};
