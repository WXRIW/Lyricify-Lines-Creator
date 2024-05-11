#pragma once

#include "HiEasyX.h"

constexpr auto ENABLE_HIGHDPI = true; // 启用高 DPI 支持

//constexpr auto DEFAULT_FONT = L"PingFang SC Pro";
constexpr auto DEFAULT_FONT = L"Microsoft YaHei UI";
constexpr auto DEFAULT_BUTTON_FONTSIZE = 18;

constexpr auto BACKGROUND_COLOR = CLASSICGRAY;

constexpr auto WINDOW_WIDTH = 800;
constexpr auto WINDOW_HEIGHT = 500;

constexpr auto MARGIN_HORIZONTAL = 15;
constexpr auto MARGIN_VERTICAL = 15;

constexpr auto CONTROL_HEIGHT = 23;

constexpr auto BUTTON_WIDTH = 80;
constexpr auto BUTTON_HEIGHT = 26;
// 让 Button 的位置与其他控件保持居中所需要的位移值
constexpr auto BUTTON_HEIGHT_OFFSET = (CONTROL_HEIGHT - BUTTON_HEIGHT) / 2.0;

// 控件默认间距 (不含控件本身高度)
constexpr auto CONTROL_PADDING_HORIZONTAL = 10;
// 控件默认行距 (竖直方向间距) (含控件本身高度)
constexpr auto CONTROL_PADDING_VERTICAL = 28;

constexpr auto LYRICS_PADDING_VERTICAL = 32;