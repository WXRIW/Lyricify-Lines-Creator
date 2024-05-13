#pragma once

#include <thread>
#include "CommonDefine.h"

class WindowAbout
{
private:
	static void OpenWindow(bool* isOpened, double DPI_Scale, RECT rect = { -1, -1, -1, -1 });

public:
	static void Show(double DPI_Scale = 1, RECT rect = { -1, -1, -1, -1 });
};