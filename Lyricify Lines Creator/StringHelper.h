#pragma once

#include <string>
#include <locale>
#include <codecvt>

class StringHelper
{
public:
	/// <summary>
	/// ½« std::string ×ª»»Îª std::wstring
	/// </summary>
	/// <param name="str">std::string ÀàÐÍµÄ×Ö·û´®</param>
	/// <returns>std::wstring ÀàÐÍµÄ×Ö·û´®</returns>
	static std::wstring StringToWstring(std::string& str);

	/// <summary>
	/// È¥³ý×Ö·û´®Ê×Î²µÄ¿Õ°××Ö·û
	/// </summary>
	static std::string Trim(const std::string&);

	/// <summary>
	/// È¥³ý×Ö·û´®Ê×Î²µÄ¿Õ°××Ö·û
	/// </summary>
	static std::wstring Trim(const std::wstring&);

	/// <summary>
	/// È¥³ý×Ö·û´®¿ªÍ·µÄ¿Õ°××Ö·û
	/// </summary>
	static std::string TrimStart(const std::string&);

	/// <summary>
	/// È¥³ý×Ö·û´®¿ªÍ·µÄ¿Õ°××Ö·û
	/// </summary>
	static std::wstring TrimStart(const std::wstring&);

	/// <summary>
	/// È¥³ý×Ö·û´®½áÎ²µÄ¿Õ°××Ö·û
	/// </summary>
	static std::string TrimEnd(const std::string&);

	/// <summary>
	/// È¥³ý×Ö·û´®½áÎ²µÄ¿Õ°××Ö·û
	/// </summary>
	static std::wstring TrimEnd(const std::wstring&);

	/// <summary>
	/// ÊÇ·ñÎª¿Õ°××Ö·û´®»ò½ö°üº¬¿Õ¸ñµÄ×Ö·û´®
	/// </summary>
	static bool IsEmptyOrWhiteSpace(const std::string&);

	/// <summary>
	/// ÊÇ·ñÎª¿Õ°××Ö·û´®»ò½ö°üº¬¿Õ¸ñµÄ×Ö·û´®
	/// </summary>
	static bool IsEmptyOrWhiteSpace(const std::wstring&);
};
