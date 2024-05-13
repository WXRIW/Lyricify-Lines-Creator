#pragma once

// 最低支持 Windows 7
#define WINVER 0x0601
#define _WIN32_WINNT 0x0601

#include <shellscalingapi.h>
#include "WinUser.h"
#include <Windows.h>

/// <summary>
/// 启用 DPI 感知 (程序自动处理 DPI)
/// </summary>
void EnableDpiAwareness();

/// <summary>
/// 获取 DPI 值
/// </summary>
/// <returns>DPI 值 (默认为 96)</returns>
int GetDpi();

/// <summary>
/// 获取 DPI 缩放比
/// </summary>
/// <returns>DPI 缩放比 (默认为 1.0)</returns>
double GetDpiScale();