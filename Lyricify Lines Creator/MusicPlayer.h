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
	static bool CheckInitiation(bool init = true);

public:
	static void InitPlayer();
	static bool Open(const std::wstring filePath, bool override = false);
	static void Play();
	static void Pause();
	static bool IsPlaying();
	static int GetCurrentPositionMs();
	static int GetTotalDurationMs();
	static bool SeekTo(int);
};
