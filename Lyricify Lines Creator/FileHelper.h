#pragma once

#include <string>
#include <ShlObj.h>

class FileHelper
{
public:
	static std::wstring SelectFile(LPCWSTR title, LPCWSTR fileFilter);
	static std::wstring SelectFolder(LPCWSTR title);
};
