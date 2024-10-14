#include "DXUT.h"
#include "cIntroScene.h"


cIntroScene::cIntroScene()
{
}


cIntroScene::~cIntroScene()
{
	Release();
}

void cIntroScene::Init()
{
	mciOpen.lpstrDeviceType = L"WaveAudio";
	mciOpen.lpstrElementName = L"./Sound/Intro.wav";
	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&mciOpen);

	mciSendCommand(mciOpen.wDeviceID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&mciPlay);

	m_image1 = IMAGE->FindImage("Intro1");
	m_image2 = IMAGE->FindImage("Intro2");
	m_image3 = IMAGE->FindImage("Intro3");

	m_frame1 = new cFrame;
	m_frame2 = new cFrame;
	m_frame3 = new cFrame;
	NowFrame = 0;

	m_frame1->SetFrame(0, 7, 100);
	m_frame2->SetFrame(0, 2, 100);
	m_frame3->SetFrame(0, 2, 100);

	b_Ani1 = false;
	b_Ani2 = false;
}

void cIntroScene::Update()
{
	if (INPUT->MouseLUp()) {
		if (b_Ani2)
			SCENE->ChangeScene("Title");
		if (NowFrame < 7)
			NowFrame++;
	    if (!b_Ani2 && b_Ani1)
			b_Ani2 = true;
		else if (NowFrame == 7)
			b_Ani1 = true;
	}
	if (b_Ani1)
		m_frame2->Frame();
	if (b_Ani2)
		m_frame3->Frame();
}

void cIntroScene::Render()
{
	if (b_Ani2)
		IMAGE->Render(m_image3->FindImage(m_frame3->NowFrame), Vec2(0, 0));
	else if (b_Ani1)
		IMAGE->Render(m_image2->FindImage(m_frame2->NowFrame), Vec2(0, 0));
	else
		IMAGE->Render(m_image1->FindImage(NowFrame), Vec2(0, 0));

	IMAGE->Render(IMAGE->FindImage("Aim2"), INPUT->GetMousePos(), 0, true);
}

void cIntroScene::Release()
{
	mciSendCommand(mciOpen.wDeviceID, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
	SAFE_DELETE(m_frame1);
	SAFE_DELETE(m_frame2);
	SAFE_DELETE(m_frame3);
}
