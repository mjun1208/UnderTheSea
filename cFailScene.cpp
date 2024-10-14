#include "DXUT.h"
#include "cFailScene.h"

#include "cButton.h"

cFailScene::cFailScene()
{
	//ShowCursor(true);
}


cFailScene::~cFailScene()
{
	Release();
}

void cFailScene::Init()
{ 
	//ShowCursor(true);
	m_Re = new cButton(Vec2(420, 400), "Re");
	//b_Spawn = true;
	m_BackGround = IMAGE->FindImage("GameOver_BackGround");
}

void cFailScene::Update()
{
	if (m_Re->Update()) {
		ShowCursor(false);
		if (NowStage == 1)
			SCENE->ChangeScene("Stage1");
		else if (NowStage == 2)
			SCENE->ChangeScene("Stage2");
		else if (NowStage == 3)
			SCENE->ChangeScene("Stage3");
	}
}

void cFailScene::Render()
{
	IMAGE->Render(m_BackGround, Vec2(0, 0));
	m_Re->Render();
	IMAGE->Render(IMAGE->FindImage("Aim2"), INPUT->GetMousePos(), 0 , true);
}

void cFailScene::Release()
{
	//if(b_Spawn)
	SAFE_DELETE(m_Re);
}
