#include "StringHelper.h"

std::wstring StringHelper::StringToWstring(const std::string& str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.from_bytes(str);
}

/// <summary>
/// È¥³ý×Ö·û´®Ê×Î²µÄ¿Õ°××Ö·û
/// </summary>
std::string StringHelper::Trim(const std::string& str)
{
	size_t first = str.find_first_not_of(" \t\n\r");
	if (first == std::string::npos)
		return "";

	size_t last = str.find_last_not_of(" \t\n\r");
	return str.substr(first, last - first + 1);
}

/// <summary>
/// È¥³ý×Ö·û´®Ê×Î²µÄ¿Õ°××Ö·û
/// </summary>
std::wstring StringHelper::Trim(const std::wstring& str)
{
	size_t first = str.find_first_not_of(L" \t\n\r");
	if (first == std::string::npos)
		return L"";

	size_t last = str.find_last_not_of(L" \t\n\r");
	return str.substr(first, last - first + 1);
}

/// <summary>
/// È¥³ý×Ö·û´®¿ªÍ·µÄ¿Õ°××Ö·û
/// </summary>
std::string StringHelper::TrimStart(const std::string& str)
{
	size_t first = str.find_first_not_of(" \t\n\r");
	if (first == std::string::npos) {
		return "";
	}
	return str.substr(first);
}

/// <summary>
/// È¥³ý×Ö·û´®¿ªÍ·µÄ¿Õ°××Ö·û
/// </summary>
std::wstring StringHelper::TrimStart(const std::wstring& str)
{
	size_t first = str.find_first_not_of(L" \t\n\r");
	if (first == std::string::npos) {
		return L"";
	}
	return str.substr(first);
}

/// <summary>
/// È¥³ý×Ö·û´®½áÎ²µÄ¿Õ°××Ö·û
/// </summary>
std::string StringHelper::TrimEnd(const std::string& str)
{
	size_t last = str.find_last_not_of(" \t\n\r");
	if (last == std::string::npos) {
		return "";
	}
	return str.substr(0, last + 1);
}

/// <summary>
/// È¥³ý×Ö·û´®½áÎ²µÄ¿Õ°××Ö·û
/// </summary>
std::wstring StringHelper::TrimEnd(const std::wstring& str)
{
	size_t last = str.find_last_not_of(L" \t\n\r");
	if (last == std::string::npos) {
		return L"";
	}
	return str.substr(0, last + 1);
}

/// <summary>
/// ÊÇ·ñÎª¿Õ°××Ö·û´®»ò½ö°üº¬¿Õ¸ñµÄ×Ö·û´®
/// </summary>
bool StringHelper::IsEmptyOrWhiteSpace(const std::string& str)
{
	if (str.empty()) return true;
	if (Trim(str).empty()) return true;
	return false;
}

/// <summary>
/// ÊÇ·ñÎª¿Õ°××Ö·û´®»ò½ö°üº¬¿Õ¸ñµÄ×Ö·û´®
/// </summary>
bool StringHelper::IsEmptyOrWhiteSpace(const std::wstring& str)
{
	if (str.empty()) return true;
	if (Trim(str).empty()) return true;
	return false;
}
