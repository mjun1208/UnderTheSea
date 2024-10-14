#include "DXUT.h"
#include "cOcto.h"

#include "cOctoBullet.h"

cOcto::cOcto(vector<cOctoBullet * >& m_Bullet, cTexture * MiniMap, EnemyState state, Vec2 Pos, Vec2 PlayerPos, cTexture * PlayerTex, bool ReBorn)
	: m_Bullet(m_Bullet), b_ReBorn(ReBorn)
{
	m_MiniMap = MiniMap;
	m_State = state;
	m_State.m_pos = Pos;
	v_Bornpos = Pos;
	m_State.m_Frame->SetFrame(0, m_State.MaxIdleFrame, 100);
	m_State.m_AtkFrame->SetFrame(0, m_State.MaxAtkFrame, 100);

	MoveTime = 0;
	HitDelay = 0;
	m_bShoot = false;
	m_bCanShoot = false;

	m_Shoot = IMAGE->FindImage("OctoShoot");
	m_Shootframe = new cFrame;
	m_Shootframe->SetFrame(0, 1, 150);

	b_BazukaHit = false;
	f_BazukaTime = 0;
}


cOcto::~cOcto()
{
	Release();
}

void cOcto::Update(bool follow, Vec2 Target, cTexture * TargetTex)
{
	if (b_BazukaHit) {
		f_BazukaTime += DX_Time;
	}

	if (f_BazukaTime > 0.3f) {
		f_BazukaTime = 0.f;
		b_BazukaHit = false;
	}

	m_State.m_Frame->Frame();
	m_State.m_AtkFrame->Frame();
	bool m_bMove = false;

	m_State.v_Dir = Target;
	Vec2 DirectionPos = { 0,0 };

	m_State.b_Follow = follow;

	if (m_State.b_Dead) {
		if (DeadAlpha > 0) {
			DeadAlpha -= 10;
		}
	}

	else {
		if (!m_State.b_Follow, !m_State.b_Hit) {
			if (MoveTime > 2.f) {
				RandNumX = rand() % 2;
				RandNumY = rand() % 3;
				MoveTime = 0;
			}
			MoveTime += DX_Time;
			if (RandNumX == 1) {
				m_State.v_Size = Vec3{ -1.f,1.f,1.f };
				DirectionPos.x += m_State.f_Speed / 2;
			}
			else if (RandNumX == 0) {
				m_State.v_Size = Vec3{ 1.f,1.f,1.f };
				DirectionPos.x -= m_State.f_Speed / 2;
			}

			if (RandNumY == 1) {
				DirectionPos.y += m_State.f_Speed / 2;
			}
			else if (RandNumY == 2) {
				DirectionPos.y -= m_State.f_Speed / 2;
			}
			m_State.f_Rot = 0;
			m_bMove = true;
		}

		if (m_State.b_Follow) {
			Vec2 Dir;
			Dir = m_State.v_Dir - m_State.m_pos;
			D3DXVec2Normalize(&Dir, &Dir);
			m_Shootframe->Frame();
			m_bShoot = true;
			if (!m_bCanShoot && m_Shootframe->NowFrame == m_Shootframe->StartFrame)
				m_bCanShoot = true;

			if (m_State.m_pos.x > m_State.v_Dir.x) {
				m_State.v_Size = Vec3{ 1.f, 1.f,1.f };
				if (m_Shootframe->NowFrame == m_Shootframe->EndFrame && m_bCanShoot) {
					m_Bullet.push_back(new cOctoBullet(Vec2(m_State.m_pos.x - 30, m_State.m_pos.y), Dir, atan2f(Dir.y, Dir.x), 10));
					m_bCanShoot = false;
				}
			}
			else {
				m_State.v_Size = Vec3{ -1.f , 1.f, 1.f };
				if (m_Shootframe->NowFrame == m_Shootframe->EndFrame && m_bCanShoot) {
					m_Bullet.push_back(new cOctoBullet(Vec2(m_State.m_pos.x + 30, m_State.m_pos.y), Dir, atan2f(Dir.y, Dir.x), 10));
					m_bCanShoot = false;
				}
			}
		}
		else
			m_bShoot = false;

		if (m_State.b_Hit) {
			HitDelay += DX_Time;
			m_bMove = false;

			if (HitDelay > 0.5f) {
				HitDelay = 0;
				m_bMove = true;
				m_State.b_Hit = false;
			}
		}

		if (m_bMove) {
			Vec2 movePos = (m_State.m_pos + DirectionPos) / 10.f;


			D3DLOCKED_RECT lockRect;
			m_MiniMap->texturePtr->LockRect(0, &lockRect, nullptr, D3DLOCK_DISCARD);
			DWORD * pColor = (DWORD*)lockRect.pBits;


			int x = (int)(movePos.x);
			int y = (int)(movePos.y);

			D3DXCOLOR color = pColor[y * m_MiniMap->info.Width + x];

			if (color != D3DXCOLOR(1.f, 0.f, 1.f, 1.f))
				m_State.m_pos = m_State.m_pos + DirectionPos;


			m_MiniMap->texturePtr->UnlockRect(0);
		}
	}
}

void cOcto::Render()
{
	if (m_State.b_Dead) {
		IMAGE->Render(m_State.m_Dead, m_State.m_pos, m_State.v_Size, m_State.f_Rot, D3DCOLOR_ARGB(DeadAlpha, 255, 255, 255), true);
	}
	else if (m_State.b_Hit) {
		IMAGE->Render(m_State.m_Dead, m_State.m_pos, m_State.v_Size, m_State.f_Rot, D3DCOLOR_ARGB(255, 255, 255, 255), true);
	}
	else if (m_bShoot) {
		IMAGE->Render(m_Shoot->FindImage(m_Shootframe->NowFrame), m_State.m_pos , m_State.v_Size, m_State.f_Rot, D3DCOLOR_ARGB(255, 255, 255, 255), true);
	}
	else if (!m_State.b_Follow) {
		IMAGE->Render(m_State.m_Image->FindImage(m_State.m_Frame->NowFrame), m_State.m_pos, m_State.v_Size, m_State.f_Rot, D3DCOLOR_ARGB(255, 255, 255, 255), true);
	}
	else if (m_State.b_Follow) {
		IMAGE->Render(m_State.m_Follow->FindImage(m_State.m_AtkFrame->NowFrame), m_State.m_pos, m_State.v_Size, m_State.f_Rot, D3DCOLOR_ARGB(255, 255, 255, 255), true);
	}
}

void cOcto::Release()
{
	SAFE_DELETE(m_Shootframe);
}

bool cOcto::IsOutMap(Vec2 Winsize)
{
	D3DLOCKED_RECT lockRect;
	m_MiniMap->texturePtr->LockRect(0, &lockRect, nullptr, D3DLOCK_DISCARD);
	DWORD * pColor = (DWORD*)lockRect.pBits;

	int x = (m_State.m_pos.x) / 10;
	int y = (m_State.m_pos.y) / 10;

	D3DXCOLOR color = pColor[y * m_MiniMap->info.Width + x];

	if (color == D3DXCOLOR(1.f, 0.f, 1.f, 1.f)) {
		m_MiniMap->texturePtr->UnlockRect(0);
		return true;
	}
	else {
		m_MiniMap->texturePtr->UnlockRect(0);
		return (m_State.m_pos.x < 0 || m_State.m_pos.x > Winsize.x || m_State.m_pos.y < 0 || m_State.m_pos.y > Winsize.y);
	}
}