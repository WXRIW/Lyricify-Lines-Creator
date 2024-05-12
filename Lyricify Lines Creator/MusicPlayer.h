#pragma once

#include <conio.h>
#include <string>
#include "irrKlang/include/irrKlang.h"

#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

class MusicPlayer
{
private:
	irrklang::ISoundEngine* engine;
	irrklang::ISound* currentAudio;

public:
	bool Open(const std::wstring filePath, bool override = false);
	void Play();
	void Pause();
	bool IsPlaying();
	int GetCurrentPositionMs();
	int GetTotalDurationMs();
	bool SeekTo(int);

	MusicPlayer()
	{
		engine = irrklang::createIrrKlangDevice();
		currentAudio = nullptr;
	}
};

