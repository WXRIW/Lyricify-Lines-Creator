/************************************************************************
 * Filename:    StringHelper.cpp
 * Description: 字符串帮助类实现
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#include "StringHelper.h"

std::wstring StringHelper::StringToWstring(const std::string& str)
{
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstr(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstr[0], size_needed);
	return wstr;
}

std::string StringHelper::WstringToString(const std::wstring& wstr)
{
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
	std::string str(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &str[0], size_needed, NULL, NULL);
	return str;
}

std::string StringHelper::Trim(const std::string& str)
{
	size_t first = str.find_first_not_of(" \t\n\r");
	if (first == std::string::npos)
		return "";

	size_t last = str.find_last_not_of(" \t\n\r");
	return str.substr(first, last - first + 1);
}

std::wstring StringHelper::Trim(const std::wstring& str)
{
	size_t first = str.find_first_not_of(L" \t\n\r");
	if (first == std::string::npos)
		return L"";

	size_t last = str.find_last_not_of(L" \t\n\r");
	return str.substr(first, last - first + 1);
}

std::string StringHelper::TrimStart(const std::string& str)
{
	size_t first = str.find_first_not_of(" \t\n\r");
	if (first == std::string::npos) {
		return "";
	}
	return str.substr(first);
}

std::wstring StringHelper::TrimStart(const std::wstring& str)
{
	size_t first = str.find_first_not_of(L" \t\n\r");
	if (first == std::string::npos) {
		return L"";
	}
	return str.substr(first);
}

std::string StringHelper::TrimEnd(const std::string& str)
{
	size_t last = str.find_last_not_of(" \t\n\r");
	if (last == std::string::npos) {
		return "";
	}
	return str.substr(0, last + 1);
}

std::wstring StringHelper::TrimEnd(const std::wstring& str)
{
	size_t last = str.find_last_not_of(L" \t\n\r");
	if (last == std::string::npos) {
		return L"";
	}
	return str.substr(0, last + 1);
}

std::string StringHelper::Replace(const std::string& str, const std::string& search, const std::string& replace)
{
	std::string result = str;
	size_t pos = 0;
	while ((pos = result.find(search, pos)) != std::string::npos)
	{
		result.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return result;
}

std::wstring StringHelper::Replace(const std::wstring& str, const std::wstring& search, const std::wstring& replace)
{
	std::wstring result = str;
	size_t pos = 0;
	while ((pos = result.find(search, pos)) != std::wstring::npos)
	{
		result.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return result;
}

bool StringHelper::IsEmptyOrWhiteSpace(const std::string& str)
{
	if (str.empty()) return true;
	if (Trim(str).empty()) return true;
	return false;
}

bool StringHelper::IsEmptyOrWhiteSpace(const std::wstring& str)
{
	if (str.empty()) return true;
	if (Trim(str).empty()) return true;
	return false;
}

std::string StringHelper::TimeMsToString(long long ms)
{
	std::chrono::milliseconds _ms(ms);

	std::chrono::minutes mm = std::chrono::duration_cast<std::chrono::minutes>(_ms);
	_ms -= mm;
	std::chrono::seconds ss = std::chrono::duration_cast<std::chrono::seconds>(_ms);
	_ms -= ss;

	// 使用 stringstream 构造字符串
	std::stringstream ss_time;
	ss_time << std::setfill('0')
		/*<< std::setw(2)*/ << mm.count() << ":"
		<< std::setw(2) << ss.count() << "."
		<< std::setw(3) << _ms.count();

	return ss_time.str();
}

std::string StringHelper::GetFileNameFromPath(const std::string& path)
{
	size_t pos = path.find_last_of("\\/");
	if (pos != std::string::npos)
	{
		return path.substr(pos + 1);
	}
	return path; // 如果没有找到路径分隔符，返回整个路径
}

std::wstring StringHelper::GetFileNameFromPath(const std::wstring& path)
{
	size_t pos = path.find_last_of(L"\\/");
	if (pos != std::string::npos)
	{
		return path.substr(pos + 1);
	}
	return path; // 如果没有找到路径分隔符，返回整个路径
}

std::string StringHelper::GetDirectoryFromPath(const std::string& path)
{
	size_t pos = path.find_last_of("\\/");
	if (pos != std::string::npos)
	{
		return path.substr(0, pos);
	}
	return path; // 如果没有找到路径分隔符，返回整个路径
}

std::wstring StringHelper::GetDirectoryFromPath(const std::wstring& path)
{
	size_t pos = path.find_last_of(L"\\/");
	if (pos != std::string::npos)
	{
		return path.substr(0, pos);
	}
	return path; // 如果没有找到路径分隔符，返回整个路径
}

std::string StringHelper::ReplaceFileNameExtension(const std::string& filename, const std::string& newExtension)
{
	size_t dotPos = filename.find_last_of('.');
	if (dotPos == std::string::npos)
	{
		// 如果没有找到点，直接添加新的扩展名
		return filename + "." + newExtension;
	}
	else
	{
		// 否则替换掉旧的扩展名
		return filename.substr(0, dotPos + 1) + newExtension;
	}
}

std::wstring StringHelper::ReplaceFileNameExtension(const std::wstring& filename, const std::wstring& newExtension)
{
	size_t dotPos = filename.find_last_of(L'.');
	if (dotPos == std::wstring::npos)
	{
		// 如果没有找到点，直接添加新的扩展名
		return filename + L"." + newExtension;
	}
	else
	{
		// 否则替换掉旧的扩展名
		return filename.substr(0, dotPos + 1) + newExtension;
	}
}
