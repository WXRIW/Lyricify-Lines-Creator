#pragma once

#include <chrono>
#include <codecvt>
#include <iomanip>
#include <locale>
#include <sstream>
#include <string>

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
};
