#include "ProcedureHelper.h"

std::map<HWND, WNDPROC> ProcedureHelper::originalProcs;
std::map<HWND, WNDPROC> ProcedureHelper::parentProcs;

LRESULT CALLBACK ProcedureHelper::ControlSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_IME_KEYDOWN:
	case WM_IME_KEYUP:
		return CallWindowProc(parentProcs[hWnd], hWnd, uMsg, wParam, lParam);
	}
	return CallWindowProc(originalProcs[hWnd], hWnd, uMsg, wParam, lParam);
}

void ProcedureHelper::TransKeyMsgToParent(HWND hControl, WNDPROC wParent)
{
	originalProcs[hControl] = (WNDPROC)SetWindowLongPtr(hControl, GWLP_WNDPROC, (LONG_PTR)ControlSubclassProc);
	parentProcs[hControl] = wParent;
}