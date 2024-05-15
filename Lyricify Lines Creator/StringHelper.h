#pragma once

#include <chrono>
#include <codecvt>
#include <iomanip>
#include <locale>
#include <sstream>
#include <string>
#include <windows.h>

class StringHelper
{
public:
	/// <summary>
	/// 将 std::string 转换为 std::wstring
	/// </summary>
	/// <param name="str">std::string 类型的字符串</param>
	/// <returns>std::wstring 类型的字符串</returns>
	static std::wstring StringToWstring(const std::string& str);

	/// <summary>
	/// 将 std::wstring 转换为 std::string
	/// </summary>
	/// <param name="str">std::wstring 类型的字符串</param>
	/// <returns>std::string 类型的字符串</returns>
	static std::string WstringToString(const std::wstring& str);

	/// <summary>
	/// 去除字符串首尾的空白字符
	/// </summary>
	static std::string Trim(const std::string&);

	/// <summary>
	/// 去除字符串首尾的空白字符
	/// </summary>
	static std::wstring Trim(const std::wstring&);

	/// <summary>
	/// 去除字符串开头的空白字符
	/// </summary>
	static std::string TrimStart(const std::string&);

	/// <summary>
	/// 去除字符串开头的空白字符
	/// </summary>
	static std::wstring TrimStart(const std::wstring&);

	/// <summary>
	/// 去除字符串结尾的空白字符
	/// </summary>
	static std::string TrimEnd(const std::string&);

	/// <summary>
	/// 去除字符串结尾的空白字符
	/// </summary>
	static std::wstring TrimEnd(const std::wstring&);

	/// <summary>
	/// 替换字符串中的子字符串
	/// </summary>
	/// <param name="str">原始字符串</param>
	/// <param name="search">要替换的子字符串</param>
	/// <param name="replace">要替换成的字符串</param>
	/// <returns>替换后的字符串</returns>
	static std::string Replace(const std::string& str, const std::string& search, const std::string& replace);

	/// <summary>
	/// 替换字符串中的子字符串
	/// </summary>
	/// <param name="str">原始字符串</param>
	/// <param name="search">要替换的子字符串</param>
	/// <param name="replace">要替换成的字符串</param>
	/// <returns>替换后的字符串</returns>
	static std::wstring Replace(const std::wstring& str, const std::wstring& search, const std::wstring& replace);

	/// <summary>
	/// 是否为空白字符串或仅包含空格的字符串
	/// </summary>
	static bool IsEmptyOrWhiteSpace(const std::string&);

	/// <summary>
	/// 是否为空白字符串或仅包含空格的字符串
	/// </summary>
	static bool IsEmptyOrWhiteSpace(const std::wstring&);

	/// <summary>
	/// 获取时间字符串
	/// </summary>
	/// <param name="ms">时间，单位毫秒</param>
	/// <returns>std:string 字符串</returns>
	static std::string TimeMsToString(long long ms);

	/// <summary>
	/// 从路径中获取文件名
	/// </summary>
	/// <param name="path">路径字符串</param>
	/// <returns>文件名。如果没有找到路径分隔符，则返回整个路径</returns>
	static std::string GetFileNameFromPath(const std::string& path);

	/// <summary>
	/// 从路径中获取文件名
	/// </summary>
	/// <param name="path">路径字符串</param>
	/// <returns>文件名。如果没有找到路径分隔符，则返回整个路径</returns>
	static std::wstring GetFileNameFromPath(const std::wstring& path);
	
	/// <summary>
	/// 从路径中获取目录路径 (不含末尾分隔符)
	/// </summary>
	/// <param name="path">路径字符串</param>
	/// <returns>目录路径。如果没有找到路径分隔符，则返回整个路径</returns>
	static std::string GetDirectoryFromPath(const std::string& path);

	/// <summary>
	/// 从路径中获取目录路径 (不含末尾分隔符)
	/// </summary>
	/// <param name="path">路径字符串</param>
	/// <returns>目录路径。如果没有找到路径分隔符，则返回整个路径</returns>
	static std::wstring GetDirectoryFromPath(const std::wstring& path);

	/// <summary>
	/// 替换文件名的扩展名
	/// </summary>
	/// <param name="filename">文件名字符串</param>
	/// <param name="newExtension">要替换成的扩展名</param>
	/// <returns>替换后的文件名，若原文件名没有扩展名，则会添加扩展名</returns>
	static std::string ReplaceFileNameExtension(const std::string& filename, const std::string& newExtension);

	/// <summary>
	/// 替换文件名的扩展名
	/// </summary>
	/// <param name="filename">文件名字符串</param>
	/// <param name="newExtension">要替换成的扩展名</param>
	/// <returns>替换后的文件名，若原文件名没有扩展名，则会添加扩展名</returns>
	static std::wstring ReplaceFileNameExtension(const std::wstring& filename, const std::wstring& newExtension);
};
