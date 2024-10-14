#include "cSound.h"



cSound::cSound(bool Mp3)
{
	if (Mp3) {
		mciOpen.lpstrDeviceType = L"mpegvideo";
		mciOpen.lpstrElementName = L"./Sound/52.mp3";
		mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);
	}
	else {

	}
}


cSound::~cSound()
{
}

void cSound::Update()
{
}

void cSound::Release()
{
}
