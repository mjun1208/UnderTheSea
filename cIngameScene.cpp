#include "DXUT.h"
#include "cIngameScene.h"

cIngameScene::cIngameScene()
{
}


cIngameScene::~cIngameScene()
{
	Release();
}

void cIngameScene::Init()
{
	ShowCursor(false);
}

void cIngameScene::Update()
{
	SCENE->ChangeScene("Stage1");
}

void cIngameScene::Render()
{

}

void cIngameScene::Release()
{
}
