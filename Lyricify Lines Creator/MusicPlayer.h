/************************************************************************
 * Filename:    MusicPlayer.h
 * Description: 音频播放类定义
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#pragma once

#include <conio.h>
#include <string>
#include "irrKlang/include/irrKlang.h"

#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

class MusicPlayer
{
private:
	static irrklang::ISoundEngine* engine;
	static irrklang::ISound* currentAudio;

	/// <summary>
	/// 检查是否完成了播放器初始化
	/// </summary>
	/// <param name="init">如果未完成，是否进行初始化</param>
	/// <returns>是否完成了初始化</returns>
	static bool CheckInitiation(bool init = true);

public:
	static std::wstring CurrentAudioPath;

	/// <summary>
	/// 初始化播放器
	/// </summary>
	static void InitPlayer();

	/// <summary>
	/// 打开音频文件
	/// </summary>
	/// <param name="filePath">音频文件路径</param>
	/// <param name="override">覆盖原音频 (如果有)</param>
	/// <returns>是否成功打开</returns>
	static bool Load(const std::wstring filePath, bool override = true);

	/// <summary>
	/// 开始播放 / 恢复播放
	/// </summary>
	static void Play();

	/// <summary>
	/// 暂停播放
	/// </summary>
	static void Pause();

	/// <summary>
	/// 是否正在播放
	/// </summary>
	/// <returns>是否正在播放，若失败，则返回 false</returns>
	static bool IsPlaying();

	/// <summary>
	/// 获取当前的播放进度，单位为毫秒
	/// </summary>
	/// <returns>当前的播放进度，若失败则返回 -1</returns>
	static int GetCurrentPositionMs();

	/// <summary>
	/// 获取音频的总时长，单位为毫秒
	/// </summary>
	/// <returns>音频总时长，若失败则返回 -1</returns>
	static int GetTotalDurationMs();

	/// <summary>
	/// 跳转音频到指定时刻，单位为毫秒
	/// </summary>
	/// <param name="ms">要跳转到的毫秒数</param>
	/// <returns>是否成功跳转</returns>
	static bool SeekTo(int ms);

	/// <summary>
	/// 向后跳转音频，单位为毫秒
	/// </summary>
	/// <param name="ms">要跳转的毫秒数</param>
	/// <returns>是否成功跳转</returns>
	static bool SeekBack(int ms);

	/// <summary>
	/// 向前跳转音频，单位为毫秒
	/// </summary>
	/// <param name="ms">要跳转的毫秒数</param>
	/// <returns>是否成功跳转</returns>
	static bool SeekForward(int ms);

	/// <summary>
	/// 设置播放速率
	/// </summary>
	/// <param name="speed">播放速率，默认为 1.0f</param>
	/// <returns>是否成功设置</returns>
	static bool SetPlaybackSpeed(float speed = 1.0f);

	/// <summary>
	/// 获取播放速率
	/// </summary>
	/// <returns>播放速率，默认为 1.0f</returns>
	static float GetPlaybackSpeed();
};
