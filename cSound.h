#pragma once
#pragma comment(lib, "winmm.lib")
#include <mmsystem.h>
#include "Digitalv.h"

class cSound
{
private:
	MCI_OPEN_PARMS mciOpen;
	MCI_PLAY_PARMS mciPlay;
public:
	cSound(bool Mp3 = false);
	~cSound();

	void Update();
	void Release();
};
