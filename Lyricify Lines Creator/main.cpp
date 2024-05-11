#include <fstream>
#include <vector>
#include <string>

#include "DpiHelper.h" // 须优先引用，其中定义了系统要求常量
#include "CommonDefine.h"
#include "WindowMain.h"

#pragma warning(disable: 4244) // 禁用转换精度损失的 warning

double DPI_Scale = 1;

int main()
{
	if (ENABLE_HIGHDPI)
	{
		// 高 DPI 支持
		DPI_Scale = GetDpiScale(); // 必须先获取，在设置 DPI Aware 后这个值将变为 1
		EnableDpiAwareness();

		hiex::SysControlBase::DPI_Scale = DPI_Scale;
	}

	WindowMain::Show(DPI_Scale);

	closegraph();
	return 0;
}
