#include "StringHelper.h"

std::wstring StringHelper::StringToWstring(const std::string& str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.from_bytes(str);
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
