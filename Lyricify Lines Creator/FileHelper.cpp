#include "FileHelper.h"

/// <summary>
/// 选择文件
/// </summary>
/// <param name="title">对话框标题</param>
/// <param name="fileFilter">文件类型筛选器</param>
/// <returns>文件名，未选择为空字符串</returns>
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

/// <summary>
/// 选择文件夹
/// </summary>
/// <param name="title">对话框标题</param>
/// <returns>路径，未选择为空字符串</returns>
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
