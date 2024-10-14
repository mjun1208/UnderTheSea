#include "DXUT.h"
#include "cTitleScene.h"

#include "cButton.h"
cTitleScene::cTitleScene()
{
}


cTitleScene::~cTitleScene()
{
	Release();
}

void cTitleScene::Init()
{
	mciOpen.lpstrDeviceType = L"WaveAudio";
	mciOpen.lpstrElementName = L"./Sound/Title.wav";

	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);

	mciSendCommand(1, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&mciPlay);

	//ShowCursor(true);
	m_Main = IMAGE->FindImage("Title_Main");
	m_BackGround = IMAGE->FindImage("Title_BackGround");
	m_Logo = IMAGE->FindImage("Title_Logo");
	m_HowToChang = IMAGE->FindImage("HowToChang");

	m_frame = new cFrame;
	m_frame->SetFrame(0, 7, 120);

	m_Start = new cButton(Vec2(500, 500), "Start");
	m_HowTo = new cButton(Vec2(800, 500), "HowTo");
	m_Exit = new cButton(Vec2(1100, 500), "Exit");
	m_Back = new cButton(Vec2(890, 550), "Back");

	b_Chang = false;
}

void cTitleScene::Update()
{
	m_frame->Frame();

	if (b_Chang) {
		if(m_Back->Update())
		b_Chang = false;
	}
	else {
		if (m_Start->Update()) {
			ShowCursor(false);
			SCENE->ChangeScene("Ingame");
		}
		if (m_HowTo->Update()) {
			b_Chang = true;
		}
		if (m_Exit->Update()) {
			ShowCursor(false);
			PostQuitMessage(0);
		}
	}

}

void cTitleScene::Render()
{
	IMAGE->Render(m_BackGround, Vec2(0, 0));
	IMAGE->Render(m_Main->FindImage(m_frame->NowFrame), Vec2(0, 0));
	IMAGE->Render(m_Logo, Vec2(10, 50));

	m_Start->Render();
	m_HowTo->Render();
	m_Exit->Render();

	if (b_Chang) {
		IMAGE->Render(m_HowToChang, Vec2(WINSIZEX / 2, WINSIZEY / 2), 0, true);
		m_Back->Render();
	}

	IMAGE->Render(IMAGE->FindImage("Aim2"), INPUT->GetMousePos(), 0, true);
}

void cTitleScene::Release()
{
	SAFE_DELETE(m_frame);

	SAFE_DELETE(m_Start);
	SAFE_DELETE(m_HowTo);
	SAFE_DELETE(m_Exit);
	SAFE_DELETE(m_Back);

	mciSendCommand(1, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
}
