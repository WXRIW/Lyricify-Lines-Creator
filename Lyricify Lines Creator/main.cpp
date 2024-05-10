#include "HiEasyX.h"

int main()
{
	// 初始化窗口
	hiex::Window wnd(640, 480);
	hiex::AutoExit();

	HWND hwnd = wnd.GetHandle();

	// 关闭窗口，结束程序
	hiex::init_end(hwnd);

	closegraph();
	return 0;
}
