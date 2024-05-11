#pragma once

#include <thread>
#include "CommonDefine.h"

class WindowAbout
{
private:
	static void OpenWindow(bool* isOpened, double DPI_Scale);

public:
	static void Show(double DPI_Scale = 1);
};