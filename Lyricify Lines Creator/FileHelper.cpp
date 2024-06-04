/************************************************************************
 * Filename:    FileHelper.cpp
 * Description: 文件帮助类实现
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#include "FileHelper.h"

std::wstring FileHelper::SelectFile(LPCWSTR title, LPCWSTR fileFilter)
{
	OPENFILENAME ofn;
	TCHAR szFile[260] = { 0 };

	LPWSTR filter = new wchar_t[wcslen(fileFilter) + 2];
	wcscpy_s(filter, wcslen(fileFilter) + 1, fileFilter);

	// 确保最后两位都是 \0，让字符串能够正确结束
	filter[wcslen(filter) + 1] = L'\0';
	filter[wcslen(filter)] = L'\0';

	// 将 filter 中的 | 替换为 \0
	for (int i = (int)wcslen(filter) - 1; i >= 0; --i)
	{
		if (filter[i] == L'|')
			filter[i] = L'\0';
	}

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lpstrTitle = title;
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = 1;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrFileTitle = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

	auto result = GetOpenFileName(&ofn) == TRUE;

	// 释放 filter 的内存
	delete[] filter;

	if (result)
	{
		return ofn.lpstrFile;
	}

	return L"";
}

std::wstring FileHelper::SelectFolder(LPCWSTR title)
{
	BROWSEINFO bi = { 0 };
	bi.lpszTitle = title;
	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

	if (pidl != nullptr) {
		wchar_t path[MAX_PATH] = { 0 };
		SHGetPathFromIDList(pidl, path);

		CoTaskMemFree(pidl);

		return path;
	}
	return L"";
}

bool FileHelper::EnsureDirectoryExists(const std::wstring& path)
{
	if (!std::filesystem::exists(path))
	{
		if (!std::filesystem::create_directory(path))
		{
			return false;
		}
	}
	return true;
}

std::string FileHelper::ReadAllText(const std::wstring& filePath)
{
	std::ifstream file(filePath);
	if (!file.is_open())
	{
		throw std::runtime_error("Could not open file");
	}

	std::stringstream buffer;
	buffer << file.rdbuf();

	file.close();
	return buffer.str();
}
