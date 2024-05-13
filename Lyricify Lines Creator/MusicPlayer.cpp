#include "MusicPlayer.h"

/// <summary>
/// irrKlang 播放引擎的实例
/// </summary>
irrklang::ISoundEngine* MusicPlayer::engine = nullptr;

/// <summary>
/// 当前正在播放音频的实例
/// </summary>
irrklang::ISound* MusicPlayer::currentAudio = nullptr;

/// <summary>
/// 初始化播放器
/// </summary>
void MusicPlayer::InitPlayer()
{
	if (engine == nullptr)
	{
		engine = irrklang::createIrrKlangDevice();
	}
}

/// <summary>
/// 检查是否完成了播放器初始化
/// </summary>
/// <param name="init">如果未完成，是否进行初始化</param>
/// <returns>是否完成了初始化</returns>
bool MusicPlayer::CheckInitiation(bool init)
{
	if (engine == nullptr)
	{
		engine = irrklang::createIrrKlangDevice();
		return engine != nullptr;
	}
	return true;
}

/// <summary>
/// 打开音频文件
/// </summary>
/// <param name="filePath">音频文件路径</param>
/// <param name="override">覆盖原音频 (如果有)</param>
/// <returns>是否成功打开</returns>
bool MusicPlayer::Open(const std::wstring filePath, bool override)
{
	CheckInitiation();

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
