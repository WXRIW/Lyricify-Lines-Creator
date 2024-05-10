#include "HiEasyX.h"
#include <map>

int main()
{
	hiex::Window wnd(640, 480);
	hiex::AutoExit();

	HWND hwnd = wnd.GetHandle();

	hiex::init_end(hwnd);

	closegraph();
	return 0;
}
