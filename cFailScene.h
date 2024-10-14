#pragma once
#include "cScene.h"

class cButton;
class cFailScene : public cScene
{
private:
	cTexture * m_BackGround;
	cButton * m_Re = nullptr;
	//bool b_Spawn = false;
public:
	cFailScene();
	virtual ~cFailScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

