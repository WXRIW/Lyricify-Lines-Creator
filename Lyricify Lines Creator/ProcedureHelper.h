#pragma once

#include <map>
#include <Windows.h>

class ProcedureHelper
{
private:
	static std::map<HWND, WNDPROC> originalProcs;
	static std::map<HWND, WNDPROC> parentProcs;

	static LRESULT CALLBACK ControlSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	/// <summary>
	/// 将控件的键盘按键回调传给父控件
	/// </summary>
	/// <param name="hControl">控件句柄</param>
	/// <param name="wParent">父控件句柄</param>
	static void TransKeyMsgToParent(HWND hControl, WNDPROC wParent);
};

