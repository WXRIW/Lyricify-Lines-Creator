/************************************************************************
 * Filename:    MusicPlayer.cpp
 * Description: 音频播放类实现
 * Author:      XY Wang, TL Chen, JZ Zhang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

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
/// 当前正在播放音频的文件路径
/// </summary>
std::wstring MusicPlayer::CurrentAudioPath = L"";

void MusicPlayer::InitPlayer()
{
	if (engine == nullptr)
	{
		engine = irrklang::createIrrKlangDevice();
	}
}

bool MusicPlayer::CheckInitiation(bool init)
{
	if (engine == nullptr)
	{
		engine = irrklang::createIrrKlangDevice();
		return engine != nullptr;
	}
	return true;
}

class SoundEndReceiver : public irrklang::ISoundStopEventReceiver
{
public:
	virtual void OnSoundStopped(irrklang::ISound* sound, irrklang::E_STOP_EVENT_CAUSE reason, void* userData)
	{
		if (reason == irrklang::ESEC_SOUND_FINISHED_PLAYING)
		{
			MusicPlayer::Load(MusicPlayer::CurrentAudioPath, true);
		}
	}
};

bool MusicPlayer::Load(const std::wstring filePath, bool override)
{
	CheckInitiation();

	try
	{
		const int nBufferSize = 2048; // large enough, but best would be wcslen(yourFilename)*3.
		char strBuffer[nBufferSize];
		irrklang::makeUTF8fromUTF16string(filePath.c_str(), strBuffer, nBufferSize);

		auto audio = engine->play2D(strBuffer, false, true);
		SoundEndReceiver* myReceiver = new SoundEndReceiver();
		audio->setSoundStopEventReceiver(myReceiver, nullptr);

		if (override || audio != nullptr)
		{
			if (currentAudio != nullptr)
			{
				currentAudio->stop();
				currentAudio->drop();
			}

			currentAudio = audio;
			CurrentAudioPath = (audio != nullptr) ? filePath : L"";

			return (audio != nullptr);
		}
		return false;
	}
	catch (...)
	{
		return false;
	}
}

void MusicPlayer::Play()
{
	if (currentAudio != nullptr)
		currentAudio->setIsPaused(false);
}

void MusicPlayer::Pause()
{
	if (currentAudio != nullptr)
		currentAudio->setIsPaused(true);
}

bool MusicPlayer::IsPlaying()
{
	if (currentAudio != nullptr)
		return !(currentAudio->getIsPaused() || currentAudio->isFinished());
	return false; // 空音频，则认为不在播放
}

int MusicPlayer::GetCurrentPositionMs()
{
	if (currentAudio != nullptr)
		return currentAudio->getPlayPosition();
	return -1;
}

int MusicPlayer::GetTotalDurationMs()
{
	if (currentAudio != nullptr)
		return currentAudio->getPlayLength();
	return -1;
}

bool MusicPlayer::SeekTo(int ms)
{
	if (currentAudio != nullptr)
	{
		if (ms < 0)
			ms = 0;
		auto length = currentAudio->getPlayLength();
		if (length != -1 && ms > (int)length)
			ms = currentAudio->getPlayLength();

		return currentAudio->setPlayPosition(ms);
	}
	return false;
}

bool MusicPlayer::SeekBack(int ms)
{
	if (currentAudio != nullptr)
	{
		int pos = currentAudio->getPlayPosition();
		pos -= ms;
		if (pos < 0) pos = 0;
		return currentAudio->setPlayPosition(pos);
	}
	return false;
}

bool MusicPlayer::SeekForward(int ms)
{
	if (currentAudio != nullptr)
	{
		int pos = currentAudio->getPlayPosition();
		pos += ms;
		if (pos > (int)currentAudio->getPlayLength()) pos = currentAudio->getPlayLength();
		return currentAudio->setPlayPosition(pos);
	}
	return false;
}

bool MusicPlayer::SetPlaybackSpeed(float speed)
{
	if (currentAudio != nullptr)
		return currentAudio->setPlaybackSpeed(speed);
	return false;
}

float MusicPlayer::GetPlaybackSpeed()
{
	if (currentAudio != nullptr)
		return currentAudio->getPlaybackSpeed();
	return 1.0f;
}
