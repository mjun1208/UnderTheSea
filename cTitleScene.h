#pragma once
#include "cScene.h"

class cButton;
class cTitleScene : public cScene
{
private:
	MCI_OPEN_PARMS mciOpen;
	MCI_PLAY_PARMS mciPlay;
private:
	cTexture * m_Main = nullptr;
	cTexture * m_BackGround = nullptr;
	cTexture * m_Logo = nullptr;
	cTexture * m_HowToChang = nullptr;

	cFrame * m_frame = nullptr;

	cButton * m_Start = nullptr;
	cButton * m_HowTo = nullptr;
	cButton * m_Exit = nullptr;
	cButton * m_Back = nullptr;

	bool b_Chang = false;
public:
	cTitleScene();
	virtual ~cTitleScene();
	
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

