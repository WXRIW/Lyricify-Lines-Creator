#pragma once

// ×îµÍÖ§³Ö Windows 7
#define WINVER 0x0601
#define _WIN32_WINNT 0x0601

#include <shellscalingapi.h>
#include "WinUser.h"
#include <Windows.h>

void EnableDpiAwareness();

int GetDpi();

double GetDpiScale();