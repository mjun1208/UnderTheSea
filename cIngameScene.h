#pragma once
#include "cScene.h"

class cIngameScene : public cScene
{
private:
	cButton * m_Button;
public:
	cIngameScene();
	virtual ~cIngameScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

