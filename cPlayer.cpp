#include "DXUT.h"
#include "cPlayer.h"

#include "cPlayerBullet.h"
#include "cEffect.h"

cPlayer::cPlayer(vector<cPlayerBullet*>& PlayerBullet , vector<cEffect *>& effect)
	:m_pos(WINSIZEX / 2, WINSIZEY/ 2) , m_Bullet(PlayerBullet), m_effect(effect)
{
}


cPlayer::~cPlayer()
{
	Release();
}

void cPlayer::Init(int stage, cTexture * MiniMap)
{
	mciOpen.lpstrDeviceType = L"WaveAudio";
	mciOpen.lpstrElementName = L"./Sound/Fire.wav";

	mciOpen2.lpstrDeviceType = L"WaveAudio";
	mciOpen2.lpstrElementName = L"./Sound/Bazuka.wav";

	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);
	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen2);

	//mciSendCommand(mciOpen.wDeviceID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&mciPlay);

	m_Head = IMAGE->FindImage("Player_Head"); //IMAGE->AddImage("Player_Head", "./Image/Player/Head.png");
	m_Head2 = IMAGE->FindImage("Player_Head2");
	//m_Arm = IMAGE->FindImage("Player_Arm");
	m_Leg = IMAGE->FindImage("Player_Leg");
	m_ShootEffect = IMAGE->FindImage("Shoot_Effect");
	m_ShootEffect2 = IMAGE->FindImage("Shoot_Effect2");
	m_PlayerColled = IMAGE->FindImage("Colled");
	//m_Aim2 = IMAGE->FindImage("Aim2");
	//m_Aim1 = IMAGE->FindImage("Aim");

	//m_HpGauge = IMAGE->FindImage("HpGauge");
	//m_HpEdge = IMAGE->FindImage("HpEdge");

	PlayerRot = 0.f;

	m_bDiv = true;

	m_frame = new cFrame;
	m_frame->SetFrame(0, 3, 60);

	m_Collframe = new cFrame;
	m_Collframe->SetFrame(0, 1, 120);

	m_bBack = false;
	m_bDash = false;

	m_Shoot = 5;
	ShootTime = 0.f;
	m_bShoot = true;

	m_Dash = 3;
	DashTime = 0.f;
	DashChargeTime = 0.f;
	m_bDashCharge = false;

	m_bRight = false;
	m_bLeft = false;
	m_bUp = false;
	m_bDown = false;

	b_Coll = false;
	CollTime = 0.f;
	i_CollAlpha = 255;
	i_CollCount = 0;

	if (stage == 1) {
		Winsize.x = STAGE1X;
		Winsize.y = STAGE1Y;
	}
	else if (stage == 2) {
		Winsize.x = STAGE2X;
		Winsize.y = STAGE2Y;
	}
	else if (stage == 3) {
		Winsize.x = STAGE3X;
		Winsize.y = STAGE3Y;
	}


	m_MiniMap = MiniMap;

	m_Hp = 100;

	CAMERA->SetPosition(Vec3(m_pos.x, m_pos.y , 0));
	f_ChangeWeaponTime = 10.f;
	f_BazukaTime = 0.f;
	b_Bazuka = false;
	mciTime = 0;
	mci2Time = 0;
}

void cPlayer::Update()
{
	bool m_bMove = false;
	DirectionPos = Vec2(0.f, 0.f);

	MousePos = INPUT->GetMouseScrollPos();
	m_vDir = MousePos - m_pos;
	D3DXVec2Normalize(&m_vDir, &m_vDir);

	DEBUG_LOG(m_vDir.x << " " << m_vDir.y);
	if (m_Dash > 0 && INPUT->KeyDown(VK_SPACE)) {
		m_bDash = true;
		DashTime = DX_Time;
		OldMousePos = MousePos;
		OldMousePos = m_pos - MousePos;
		D3DXVec2Normalize(&OldMousePos, &OldMousePos);
		if (m_Dash > 0) {
			--m_Dash;
		}
	}

	if (m_Dash >= 0 && m_bDash && DashTime < 0.13f) {
		if (m_pos.x + 30 < Winsize.x - m_Head->info.Width / 2 &&
			m_pos.x - 30 > 0 + m_Head->info.Width / 2) {
			if (m_bRight) {
				DirectionPos.x += 20;
				//m_pos.x += 20;
			}
			else if (m_bLeft) {
				DirectionPos.x -= 20;
				//m_pos.x -= 20;
			}
		}
		if (m_pos.y + 30 < Winsize.y - m_Head->info.Height &&
			m_pos.y - 30 > 0 + m_Head->info.Height) {
			if (m_bUp) {
				DirectionPos.y -= 20;
				//m_pos.y -= 20;
			}
			else if (m_bDown) {
				DirectionPos.y += 20;
				//m_pos.y += 20;
			}
		}
		DashTime += DX_Time;
	}
	else if (m_bDash && DashTime >= 1.f) {
		m_bDash = false;
		DashTime = 0;
	}

	if (/*m_pos.x < Winsize.x - m_Head->info.Width / 2 &&*/ INPUT->KeyPress('D')) {
		if (!m_bDiv) {
			m_bBack = true;
		}
		else {
			m_bBack = false;
		}
		DirectionPos.x += 10;
		//m_pos.x += 10;
		m_frame->Frame();
		//CAMERA->SetPosition(Vec3(m_pos.x,m_pos.y, 0));
		m_bRight = true;
		m_bMove = true;
	}
	else
		m_bRight = false;

	if (/* m_pos.x > 0 + m_Head->info.Width / 2 &&*/ INPUT->KeyPress('A')) {
		if (m_bDiv) {
			m_bBack = true;
		}
		else {
			m_bBack = false;
		}
		// m_pos.x -= 10;
		DirectionPos.x -= 10;
		m_frame->Frame();
		//CAMERA->SetPosition(Vec3(m_pos.x, m_pos.y, 0));
		m_bLeft = true;
		m_bMove = true;
	}
	else
		m_bLeft = false;

	if (/* m_pos.y < Winsize.y - m_Head->info.Height && */ INPUT->KeyPress('S')) {
		DirectionPos.y += 10;
		//m_pos.y += 10;
		m_frame->Frame();
		//CAMERA->SetPosition(Vec3(m_pos.x, m_pos.y, 0));
		m_bDown = true;
		m_bMove = true;
	}
	else
		m_bDown = false;

	if (/* m_pos.y > 0 + m_Head->info.Height && */ INPUT->KeyPress('W')) {
		DirectionPos.y -= 10;
		//m_pos.y -= 10;
		m_frame->Frame();
		//CAMERA->SetPosition(Vec3(m_pos.x, m_pos.y, 0));
		m_bUp = true;
		m_bMove = true;
	}
	else
		m_bUp = false;

	if (INPUT->GetMouseScrollPos().x > m_pos.x) {
		m_bDiv = true;
	}
	else
		m_bDiv = false;

	if (m_bMove) {
		Vec2 movePos = (m_pos + DirectionPos) / 10.f;


		D3DLOCKED_RECT lockRect;
		//ZeroMemory(&lockRect, sizeof(lockRect));


		m_MiniMap->texturePtr->LockRect(0, &lockRect, nullptr, D3DLOCK_DISCARD);
		DWORD * pColor = (DWORD*)lockRect.pBits;


		int x = (int)(movePos.x);
		int y = (int)(movePos.y);

		D3DXCOLOR color = pColor[y * m_MiniMap->info.Width + x];

		if (color != D3DXCOLOR(1.f, 0.f, 1.f, 1.f))
			m_pos = m_pos + DirectionPos;

		m_MiniMap->texturePtr->UnlockRect(0);
	}
	ShowPos = m_pos / 20;

	if (INPUT->MouseLPress()) {
		float fAngle = (atan2f(m_vDir.y, m_vDir.x));// + 180 - 45;

		Vec2 FirePos;

		FirePos.x = m_pos.x + cosf(fAngle) * 140;
		FirePos.y = m_pos.y + sinf(fAngle) * 140;
		
		if (!b_Bazuka) {
			if (m_Shoot >= 5) {
				//m_effect.push_back(new cEffect(FirePos, m_ShootEffect2, fAngle, 5, 20));
				m_effect.push_back(new cEffect(FirePos, m_ShootEffect, 0, 2, 50, true));
				mciSendCommand(mciOpen.wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
				mciTime = 0;
			}
			if (m_Shoot > 0) {
				m_Bullet.push_back(new cPlayerBullet(FirePos, m_vDir, fAngle, 50.f));
				m_Shoot--; 
			}
		}
		else if (f_BazukaTime > 0.8f){
			m_Bullet.push_back(new cPlayerBullet(FirePos, m_vDir, fAngle, 50.f , true));
			mciSendCommand(mciOpen2.wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay2);
			mci2Time = 0;
			f_BazukaTime = 0.f;
		}


	}
	mciTime += DX_Time;
	mci2Time += DX_Time;
	if (mciTime > 0.3f) {
		mciSendCommand(mciOpen.wDeviceID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
	}
	if (mci2Time > 0.8f) {
		mciSendCommand(mciOpen2.wDeviceID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
	}

	f_BazukaTime += DX_Time;

	if (INPUT->MouseRUp() && f_ChangeWeaponTime > 1.5f) {
		f_ChangeWeaponTime = 0;
		if (b_Bazuka)
			b_Bazuka = false;
		else
			b_Bazuka = true;
	}
	else {
		f_ChangeWeaponTime += DX_Time;
	}

	if (m_Shoot <= 0) {
		m_bShoot = false;
		if (ShootTime >= 0.5f) {
			m_Shoot = 5;
			ShootTime = 0;
		}
		else {
			ShootTime += DX_Time;
		}
	}

	if (!m_bShoot && ShootTime <= 0) {
		ShootTime = DX_Time;
		m_bShoot = true;
	}

	CAMERA->Follow(Vec3(m_pos.x, m_pos.y, 0.f));

	//DEBUG_LOG(m_pos.x << " , " << m_pos.y);

	if (INPUT->KeyPress('V')) {
		m_Hp = 100;
	}
	if (INPUT->KeyPress('B')) {
		if (m_Hp > 1) {
			m_Hp--;
		}
	}

	if (m_Dash < 3) {
		m_bDashCharge = true;
	}
	if (m_bDashCharge) {
		DashChargeTime += DX_Time;
		if (DashChargeTime > 2.f) {
			DashChargeTime = 0.f;
			m_Dash++;
			m_bDashCharge = false;
		}
	}

	if (INPUT->KeyDown('C')) {
		if (b_Coll)
			b_Coll = false;
		else
			b_Coll = true;
	}

	if (b_Coll) {
		m_Collframe->Frame();
		i_CollAlpha += 15;
		if (i_CollAlpha >= 1020) {
			b_Coll = false;
			i_CollAlpha = 255;
		}
	}

	//if (m_Hp <= 0) {
	//	CAMERA->SetPosition(Vec3(WINSIZEX / 2, WINSIZEY / 2, 0));
	//	ShowCursor(true);
	//	SCENE->ChangeScene("Title");
	//}
} 

void cPlayer::Render()
{
	if (m_bDiv == Right) {
		if(m_bBack)
			IMAGE->Render(m_Leg->FindImage(m_frame->NowFrame), Vec2(m_pos.x + 55, m_pos.y + 55), Vec3(1.f, 1.f, 1.f), 270, D3DCOLOR_ARGB(i_CollAlpha,255, 255, 255), true);
		else
			IMAGE->Render(m_Leg->FindImage(m_frame->NowFrame), Vec2(m_pos.x - 50, m_pos.y + 50), Vec3(1.f, 1.f, 1.f), 0, D3DCOLOR_ARGB(i_CollAlpha,255, 255, 255), true);

		if (!b_Bazuka)
			IMAGE->CenterRender(m_Head, Vec2(m_pos.x, m_pos.y), Vec3(1.f, 1.f, 1.f), Vec3(m_Head->info.Width / 2 - m_Head->info.Width / 4, m_Head->info.Height / 2 + 10, 0.f), D3DXToDegree(atan2f(m_vDir.y, m_vDir.x)), D3DCOLOR_ARGB(i_CollAlpha,255,255,255));
		else 
			IMAGE->CenterRender(m_Head2, Vec2(m_pos.x, m_pos.y), Vec3(1.f, 1.f, 1.f), Vec3(m_Head2->info.Width / 2 - m_Head2->info.Width / 4, m_Head2->info.Height / 2 + 10, 0.f), D3DXToDegree(atan2f(m_vDir.y, m_vDir.x)), D3DCOLOR_ARGB(i_CollAlpha, 255, 255, 255));
	}

	else if (m_bDiv == Left) {
		if (m_bBack)
			IMAGE->Render(m_Leg->FindImage(m_frame->NowFrame), Vec2(m_pos.x - 55, m_pos.y + 55), Vec3(-1.f, 1.f, 1.f), -270, D3DCOLOR_ARGB(i_CollAlpha, 255, 255, 255), true);
		else
			IMAGE->Render(m_Leg->FindImage(m_frame->NowFrame), Vec2(m_pos.x + 50, m_pos.y + 50), Vec3(-1.f, 1.f, 1.f), 0, D3DCOLOR_ARGB(i_CollAlpha, 255, 255, 255), true);
		if (!b_Bazuka)
			IMAGE->CenterRender(m_Head, Vec2(m_pos.x, m_pos.y), Vec3(-1.f, 1.f, 1.f), Vec3(m_Head->info.Width / 2 - m_Head->info.Width / 4, m_Head->info.Height / 2 + 10, 0.f), D3DXToDegree(atan2f(m_vDir.y, m_vDir.x)) + 180, D3DCOLOR_ARGB(i_CollAlpha, 255, 255, 255));
		else
			IMAGE->CenterRender(m_Head2, Vec2(m_pos.x, m_pos.y), Vec3(-1.f, 1.f, 1.f), Vec3(m_Head2->info.Width / 2 - m_Head2->info.Width / 4, m_Head2->info.Height / 2 + 10, 0.f), D3DXToDegree(atan2f(m_vDir.y, m_vDir.x)) + 180, D3DCOLOR_ARGB(i_CollAlpha, 255, 255, 255));
	}

	IMAGE->ReBegin(true);
	if (b_Coll)
		IMAGE->Render(m_PlayerColled->FindImage(m_Collframe->NowFrame), Vec2(0, 0));
	IMAGE->ReBegin(false); 
}

void cPlayer::Release()
{
	mciSendCommand(mciOpen.wDeviceID, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
	mciSendCommand(mciOpen2.wDeviceID, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
	SAFE_DELETE(m_frame);
	SAFE_DELETE(m_Collframe);
}
