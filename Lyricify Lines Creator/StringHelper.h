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
	/// �� std::string ת��Ϊ std::wstring
	/// </summary>
	/// <param name="str">std::string ���͵��ַ���</param>
	/// <returns>std::wstring ���͵��ַ���</returns>
	static std::wstring StringToWstring(const std::string& str);

	/// <summary>
	/// ȥ���ַ�����β�Ŀհ��ַ�
	/// </summary>
	static std::string Trim(const std::string&);

	/// <summary>
	/// ȥ���ַ�����β�Ŀհ��ַ�
	/// </summary>
	static std::wstring Trim(const std::wstring&);

	/// <summary>
	/// ȥ���ַ�����ͷ�Ŀհ��ַ�
	/// </summary>
	static std::string TrimStart(const std::string&);

	/// <summary>
	/// ȥ���ַ�����ͷ�Ŀհ��ַ�
	/// </summary>
	static std::wstring TrimStart(const std::wstring&);

	/// <summary>
	/// ȥ���ַ�����β�Ŀհ��ַ�
	/// </summary>
	static std::string TrimEnd(const std::string&);

	/// <summary>
	/// ȥ���ַ�����β�Ŀհ��ַ�
	/// </summary>
	static std::wstring TrimEnd(const std::wstring&);

	/// <summary>
	/// �Ƿ�Ϊ�հ��ַ�����������ո���ַ���
	/// </summary>
	static bool IsEmptyOrWhiteSpace(const std::string&);

	/// <summary>
	/// �Ƿ�Ϊ�հ��ַ�����������ո���ַ���
	/// </summary>
	static bool IsEmptyOrWhiteSpace(const std::wstring&);

	/// <summary>
	/// ��ȡʱ���ַ���
	/// </summary>
	/// <param name="ms">ʱ�䣬��λ����</param>
	/// <returns>std:string �ַ���</returns>
	static std::string TimeMsToString(long long ms);
};
