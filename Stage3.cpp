#include "DXUT.h"
#include "Stage3.h"

#include "cPlayer.h"
#include "cBulletAdmin.h"
#include "cEnemyAdmin.h"
#include "cEffectAdmin.h"

Stage3::Stage3()
{
	ShowCursor(false);
}


Stage3::~Stage3()
{
	Release();
}

void Stage3::Init()
{
	mciOpen.lpstrDeviceType = L"MpegVideo";
	mciOpen.lpstrElementName = L"./Sound/Stage3.mp3";
	mciSendCommand(1, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&mciOpen);

	mciSendCommand(1, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&mciPlay);

	ShowCursor(false);
	m_Load = IMAGE->FindImage("Load");
	m_LoadEdge = IMAGE->FindImage("LoadGaugeEdge");
	m_LoadGauge = IMAGE->FindImage("LoadGauge");

	m_Loadframe = new cFrame();
	m_Loadframe->SetFrame(0, 1, 150);

	NowStage = 3;
	m_BackGround = IMAGE->FindImage("Stage3BackGroud");
	//m_BackColl = IMAGE->FindImage("Stage3BackColl");
	m_MiniMap = IMAGE->FindImage("Stage3MiniMap");
	m_MiniPlayer = IMAGE->FindImage("MiniPlayer");
	m_ShowMiniMap = IMAGE->FindImage("Stage3ShowMiniMap");
	m_PlayerHpGauge = IMAGE->FindImage("HpGauge");
	m_PlayerHpEdge = IMAGE->FindImage("HpEdge");
	m_PlayerDashGauge = IMAGE->FindImage("DashGauge");
	m_PlayerDashEdge = IMAGE->FindImage("DashEdge");
	m_MiniEnemy = IMAGE->FindImage("MiniEnemy");
	m_MiniBoss = IMAGE->FindImage("MiniBoss");

	m_Bullet = new cBulletAdmin;
	m_Effect = new cEffectAdmin;
	m_Player = new cPlayer(m_Bullet->GetPlayerBullet(), m_Effect->GetEffect());
	m_Enemy = new cEnemyAdmin(m_Bullet->GetOctoBullet(), m_Effect->GetEffect());

	b_Coll = false;

	m_Player->Init(3, m_MiniMap);
	m_Enemy->Init(3, m_MiniMap);
	MiniAlpha = 255;

	b_Load = true;

	b_Started = false;
	b_Start = false;
	i_Start_y = -100;

	b_Fail = false;
	i_Fail_y = -100;

	b_Clear = false;
	i_Clear_y = -100;

	Player_Append = IMAGE->FindImage("Player_Append");
	AFish_Append = IMAGE->FindImage("AFish_Append");
	i_Player_x = -1380;
	i_AFish_x = 1380;
	V_Size = Vec3(3.f, 3.f, 3.f);
	S_Size = Vec3(3.f, 3.f, 3.f);

	m_V = IMAGE->FindImage("V");
	m_S = IMAGE->FindImage("S");

	b_VS = false;
	BossAppend = false;
	b_V = false;
	b_S = false;
	Boss = false;
	f_VSTime = 0;
}

void Stage3::Update()
{
	if (b_Load) {
		CAMERA->SetPosition(Vec3(WINSIZEX / 2, WINSIZEY / 2, 0));
		m_Loadframe->Frame();
	}
	if (b_Start) {
		i_Start_y += 10;
		if (i_Start_y >= 820) {
			b_Start = false;
			b_Started = true;
		}
	}
	else if (b_Fail) {
		i_Fail_y += 10;
		if (i_Fail_y >= 820) {
			CAMERA->SetPosition(Vec3(WINSIZEX / 2, WINSIZEY / 2, 0));
			//ShowCursor(true);
			SCENE->ChangeScene("Fail");
		}
	}
	else if (b_Clear) {
		i_Clear_y += 10;
		if (i_Clear_y >= 820) {
			CAMERA->SetPosition(Vec3(WINSIZEX / 2, WINSIZEY / 2, 0));
			//ShowCursor(true);
			SCENE->ChangeScene("End");
		}
	}
	else if (BossAppend) {
		if (i_Player_x < 0) {
			i_AFish_x -= 10;
			i_Player_x += 10;
		}

		if (i_Player_x == 0 && i_AFish_x == 0) {
			b_VS = true;
			if (V_Size.x > 1) {
				b_V = true;
				V_Size.x -= 0.03f;
				V_Size.y -= 0.03f;
				V_Size.z -= 0.03f;
			}
			else if (S_Size.x > 1) {
				b_S = true;
				S_Size.x -= 0.03f;
				S_Size.y -= 0.03f;
				S_Size.z -= 0.03f;
			}
			else {
				f_VSTime += DX_Time;

				if (f_VSTime > 1.5f) {
					b_Started = false;
					BossAppend = false;
					b_VS = false;
					b_V = false;
					b_S = false;
					Boss = true;
				}
			}
		}
	}
	else {
		m_Bullet->Update(m_Player->GetPos(), m_Player->GetTex());
		m_Player->Update();
		m_Enemy->Update(m_Player->GetPos(), m_Player->GetTex(), m_Bullet->GetPlayerBullet(), m_Player , Boss);
		m_Effect->Update();

		if (INPUT->KeyDown('1')) {
			SCENE->ChangeScene("Stage1");
		}

		if (INPUT->GetMouseScrollPos().x > 0 &&
			INPUT->GetMousePos().x < 0 + m_ShowMiniMap->info.Width &&
			INPUT->GetMousePos().y > 0 &&
			INPUT->GetMousePos().y < 0 + m_ShowMiniMap->info.Height)
		{
			MiniAlpha = 120;
		}
		else {
			MiniAlpha = 255;
		}

		if (m_Enemy->GetEnemySize() == 15 && !b_Start && i_Start_y < 820) {
			b_Start = true;
			b_Load = false;
		}

		if (m_Player->GetHp() <= 0 && !b_Fail && i_Fail_y < 820) {
			b_Fail = true;
		}

		if (m_Enemy->GetEnemySize() == 0 && !BossAppend && b_Started) {
			BossAppend = true;
		}

		if (m_Enemy->GetEnemySize() == 0 && m_Enemy->GetClear())
			b_Clear = true;
	}
}

void Stage3::Render()
{
	if (b_Load) {
		RECT GaugeRect = {
			0,
			0,
			((float)m_LoadGauge->info.Width / 50) * m_Enemy->GetEnemySize(),
			m_LoadGauge->info.Height
		};

		IMAGE->Render(m_Load->FindImage(m_Loadframe->NowFrame), Vec2(0, 0));
		IMAGE->CropRender(m_LoadGauge, Vec2(WINSIZEX / 2, 550), Vec3(1.f, 1.f, 1.f), GaugeRect);
		IMAGE->Render(m_LoadEdge, Vec2(WINSIZEX / 2, 550), 0, true);
	}
	else {
		IMAGE->Render(m_BackGround, Vec2(0, 0));

		m_Player->Render();
		m_Enemy->Render();
		m_Bullet->Render();
		m_Effect->Render();

		IMAGE->ReBegin(true);

		IMAGE->Render(m_ShowMiniMap, Vec2(0, 0), Vec3(1.f, 1.f, 1.f), 0, D3DCOLOR_ARGB(MiniAlpha, 255, 255, 255), false);
		IMAGE->Render(m_MiniPlayer, m_Player->GetMiniPos(), Vec3(1.f, 1.f, 1.f), 0, D3DCOLOR_ARGB(MiniAlpha, 255, 255, 255), true);

		for (auto iter : m_Enemy->GetEnemy()) {
			if (iter->GetIsBoss())
				IMAGE->Render(m_MiniBoss, iter->GetMiniPos(), Vec3(1.f, 1.f, 1.f), 0, D3DCOLOR_ARGB(MiniAlpha, 255, 255, 255), true);
			else
				IMAGE->Render(m_MiniEnemy, iter->GetMiniPos(), Vec3(1.f, 1.f, 1.f), 0, D3DCOLOR_ARGB(MiniAlpha, 255, 255, 255), true);
		}
		IMAGE->Render(m_PlayerHpEdge, Vec2(150, 620), 0, true);
		RECT HpGauge = {
			0,
			0,
			((float)m_PlayerHpGauge->info.Width / 100) * m_Player->GetHp(),
			m_PlayerHpGauge->info.Height
		};
		IMAGE->CropRender(m_PlayerHpGauge, Vec2(150, 620), Vec3(1.f, 1.f, 1.f), HpGauge);
		IMAGE->PrintText("100 / " + to_string(m_Player->GetHp()), Vec2(150, 620), 30, D3DCOLOR_XRGB(255, 255, 255), true);

		IMAGE->Render(m_PlayerDashEdge, Vec2(102, 655), 0, true);
		RECT DashGauge = {
			0,
			0,
			((float)m_PlayerDashGauge->info.Width / 3) * m_Player->GetDash(),
			m_PlayerDashGauge->info.Height
		};
		IMAGE->CropRender(m_PlayerDashGauge, Vec2(102, 655), Vec3(1.f, 1.f, 1.f), DashGauge);

		IMAGE->PrintText("남은 몬스터 : 15 / " + to_string(m_Enemy->GetEnemySize()), Vec2(1000, 620), 50, D3DCOLOR_XRGB(255, 50, 50), true);

		if (b_Start)
			IMAGE->Render(IMAGE->FindImage("Stage_Start"), Vec2(WINSIZEX / 2, i_Start_y), 0, true);
		if (b_Fail)
			IMAGE->Render(IMAGE->FindImage("Stage_Fail"), Vec2(WINSIZEX / 2, i_Fail_y), 0, true);
		if (b_Clear)
			IMAGE->Render(IMAGE->FindImage("Stage_Clear"), Vec2(WINSIZEX / 2, i_Clear_y), 0, true);

		if (BossAppend) {
			IMAGE->Render(Player_Append, Vec2(i_Player_x, 0));
			IMAGE->Render(AFish_Append, Vec2(i_AFish_x, 0));
		}
		if (b_V)
			IMAGE->Render(m_V, Vec2(WINSIZEX / 2 - 100, WINSIZEY / 2), V_Size, 0, D3DCOLOR_XRGB(255, 255, 255), true);
		if (b_S)
			IMAGE->Render(m_S, Vec2(WINSIZEX / 2, WINSIZEY / 2), S_Size, 0, D3DCOLOR_XRGB(255, 255, 255), true);
	}
}

void Stage3::Release()
{
	SAFE_DELETE(m_Bullet);
	SAFE_DELETE(m_Player);
	SAFE_DELETE(m_Enemy);
	//SAFE_DELETE(m_frame);
	SAFE_DELETE(m_Effect);
	SAFE_DELETE(m_Loadframe);
	mciSendCommand(1, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
}
