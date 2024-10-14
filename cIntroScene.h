#pragma once
#include "cScene.h"

class cIntroScene : public cScene
{
private: 
	MCI_OPEN_PARMS mciOpen;
	MCI_PLAY_PARMS mciPlay;
private:
	cTexture * m_image1 = nullptr;
	cTexture * m_image2 = nullptr;
	cTexture * m_image3 = nullptr;

	cFrame * m_frame1 = nullptr;
	cFrame * m_frame2 = nullptr;
	cFrame * m_frame3 = nullptr;

	int NowFrame = 0;

	bool b_Ani1;
	bool b_Ani2;
public:
	cIntroScene();
	virtual ~cIntroScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

