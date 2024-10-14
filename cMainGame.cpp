#include "DXUT.h"
#include "cMainGame.h"
#include "cLoadScene.h"
#include "cTitleScene.h"
#include "cIngameScene.h"
#include "cIntroScene.h"
#include "cFailScene.h"
#include "cEndScene.h"

#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"

cMainGame::cMainGame()
{
}


cMainGame::~cMainGame()
{
}

void cMainGame::Init()
{
	ShowCursor(false);
	IMAGE->Init();
	CAMERA->Init();
	SCENE->AddScene("Load", new cLoadScene);
	SCENE->AddScene("Title", new cTitleScene);
	SCENE->AddScene("Ingame", new cIngameScene);
	SCENE->AddScene("Intro", new cIntroScene);
	SCENE->AddScene("Fail", new cFailScene);
	SCENE->AddScene("End", new cEndScene);

	SCENE->AddScene("Stage1", new Stage1);
	SCENE->AddScene("Stage2", new Stage2);
	SCENE->AddScene("Stage3", new Stage3);

	SCENE->ChangeScene("Load");
}

void cMainGame::Update()
{
	SCENE->Update();
	CAMERA->Update();
	INPUT->Update();
}

void cMainGame::Render()
{
	CAMERA->SetTranform();

	IMAGE->Begin(false);

	SCENE->Render();

	IMAGE->End();

}

void cMainGame::Release()
{
	ShowCursor(true);
	cImageManager::ResetInstance();
	cSceneManager::ResetInstance();
	cCameraManager::ResetInstance();
	cInputManager::ResetInstance();
}

void cMainGame::LostDevice()
{
	IMAGE->LostDevice();
}

void cMainGame::ResetDevice()
{
	IMAGE->ResetDevice();
}
