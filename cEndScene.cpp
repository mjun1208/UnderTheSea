#include "DXUT.h"
#include "cEndScene.h"


cEndScene::cEndScene()
{
	//ShowCursor(true);
}


cEndScene::~cEndScene()
{
}

void cEndScene::Init()
{
	//ShowCursor(true);
	m_BackGround = IMAGE->FindImage("End_BackGround");
}

void cEndScene::Update()
{
	//ShowCursor(true);
	if (INPUT->MouseLUp()) {
		SCENE->ChangeScene("Title");
	}
}

void cEndScene::Render()
{
	IMAGE->Render(m_BackGround, Vec2(0, 0));

	IMAGE->Render(IMAGE->FindImage("Aim2"), INPUT->GetMousePos(), 0, true);
}

void cEndScene::Release()
{
}
