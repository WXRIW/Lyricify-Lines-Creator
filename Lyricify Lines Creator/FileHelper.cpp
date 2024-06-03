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

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lpstrTitle = title;
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = fileFilter;
	ofn.nFilterIndex = 1;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrFileTitle = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

	if (GetOpenFileName(&ofn) == TRUE)
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
