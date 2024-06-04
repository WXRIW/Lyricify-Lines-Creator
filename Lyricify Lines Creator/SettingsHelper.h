/************************************************************************
 * Filename:    SettingsHelper.cpp
 * Description: 设置类及设置帮助类定义
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#pragma once

#include <fstream>
#include <string>
#include <windows.h>
#include <nlohmann/json.hpp>
#include "StringHelper.h"

enum class Languages
{
    EN,
    ZH_HANS,
    ZH_HANT,
};

class MainSettings
{
public:
    /// <summary>
    /// 显示语言
    /// </summary>
    Languages Language = Languages::ZH_HANS;

    /// <summary>
    /// 是否默认输出为 LRC
    /// </summary>
    bool IsOutputLrc = false;

    /// <summary>
    /// 设备延迟毫秒数
    /// </summary>
    int DeviceLatencyMs = 0;

    /// <summary>
    /// 按键延迟毫秒数
    /// </summary>
    int KeyboardLatencyMs = 100;

    /// <summary>
    /// 预览歌词窗体打开时最大化
    /// </summary>
    bool IsPreviewLyricsOpenMaximize = true;

    /// <summary>
    /// 总延迟毫秒数
    /// </summary>
    /// <returns>总延迟毫秒数</returns>
    int TotalLatencyMs() const
    {
        return DeviceLatencyMs + KeyboardLatencyMs;
    }

    bool IsNeedTextCalc() const
    {
        return Language != Languages::ZH_HANS && Language != Languages::ZH_HANT;
    }

    // 接入 nlohmann::json 的序列化和反序列化
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(MainSettings, Language, IsOutputLrc, DeviceLatencyMs, KeyboardLatencyMs, IsPreviewLyricsOpenMaximize)
};

class SettingsHelper
{
private:
    static std::wstring _fileName;
    static std::wstring GetSettingsFilePath();

public:
    /// <summary>
    /// 实例化的设置项
    /// </summary>
    static MainSettings Settings;

    /// <summary>
    /// 初始化设置
    /// </summary>
    static void LoadSettings();

    /// <summary>
    /// 保存设置至文件
    /// </summary>
    static void SaveSettings();
};

inline std::wstring SettingsHelper::_fileName = L"settings.json";
inline MainSettings SettingsHelper::Settings;
