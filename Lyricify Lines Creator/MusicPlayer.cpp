#include "MusicPlayer.h"

/// <summary>
/// 打开音频文件
/// </summary>
/// <param name="filePath">音频文件路径</param>
/// <param name="override">覆盖原音频 (如果有)</param>
/// <returns>是否成功打开</returns>
bool MusicPlayer::Open(const std::wstring filePath, bool override)
{
	const int nBufferSize = 2048; // large enough, but best would be wcslen(yourFilename)*3.
	char strBuffer[nBufferSize];
	irrklang::makeUTF8fromUTF16string(filePath.c_str(), strBuffer, nBufferSize);

	auto audio = engine->play2D(strBuffer, false, true);
	MusicPlayer::currentAudio = audio;
	return audio != NULL;
}

/// <summary>
/// 开始播放 / 恢复播放
/// </summary>
void MusicPlayer::Play()
{
	if (currentAudio != NULL)
		MusicPlayer::currentAudio->setIsPaused(false);
}

/// <summary>
/// 暂停播放
/// </summary>
void MusicPlayer::Pause()
{
	if (currentAudio != NULL)
		MusicPlayer::currentAudio->setIsPaused(true);
}

/// <summary>
/// 是否正在播放
/// </summary>
/// <returns>是否正在播放，若失败，则返回 false</returns>
bool MusicPlayer::IsPlaying()
{
	if (currentAudio != NULL)
		return !MusicPlayer::currentAudio->getIsPaused();
	return false; // 空音频，则认为不在播放
}

/// <summary>
/// 获取当前的播放进度，单位为毫秒
/// </summary>
/// <returns>当前的播放进度，若失败则返回 -1</returns>
int MusicPlayer::GetCurrentPositionMs()
{
	if (currentAudio != NULL)
		return MusicPlayer::currentAudio->getPlayPosition();
	return -1;
}

/// <summary>
/// 获取音频的总时长，单位为毫秒
/// </summary>
/// <returns>音频总时长，若失败则返回 -1</returns>
int MusicPlayer::GetTotalDurationMs()
{
	if (currentAudio != NULL)
		return MusicPlayer::currentAudio->getPlayLength();
	return -1;
}

/// <summary>
/// 跳转音频到指定时刻，单位为毫秒
/// </summary>
/// <param name="ms">要跳转到的毫秒数</param>
/// <returns></returns>
bool MusicPlayer::SeekTo(int ms)
{
	if (currentAudio != NULL)
		return MusicPlayer::currentAudio->setPlayPosition(ms);
	return false;
}