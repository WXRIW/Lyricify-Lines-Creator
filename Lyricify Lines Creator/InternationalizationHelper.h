/************************************************************************
 * Filename:    InternationalizationHelper.h
 * Description: 本地化方法定义
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#pragma once

#include "SettingsHelper.h"

/// <summary>
/// 通过 Key 获取本地化字符串
/// </summary>
std::wstring GetStringFromKey(const std::string& key);

/// <summary>
/// 通过 Key 获取本地化字符串
/// </summary>
/// <param name="lang">指定语言</param>
std::wstring GetStringFromKey(const std::string& key, Languages lang);
