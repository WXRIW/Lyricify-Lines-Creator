#pragma once

#include <string>
#include <locale>
#include <codecvt>

class StringHelper
{
public:
	static std::wstring StringToWstring(const std::string& str);
	static std::string Trim(const std::string&);
	static std::wstring Trim(const std::wstring&);
	static std::string TrimStart(const std::string&);
	static std::wstring TrimStart(const std::wstring&);
	static std::string TrimEnd(const std::string&);
	static std::wstring TrimEnd(const std::wstring&);
	static bool IsEmptyOrWhiteSpace(const std::string&);
	static bool IsEmptyOrWhiteSpace(const std::wstring&);
};
