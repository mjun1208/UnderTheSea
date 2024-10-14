#include "DXUT.h"
#include "cTurtle.h"


cTurtle::cTurtle(cTexture * MiniMap, EnemyState state, Vec2 Pos, Vec2 PlayerPos, cTexture * PlayerTex, bool ReBorn)
	: b_ReBorn(ReBorn)
{
	m_MiniMap = MiniMap;
	m_State = state;
	m_State.m_pos = Pos;
	v_Bornpos = Pos;
	m_State.m_Frame->SetFrame(0, m_State.MaxIdleFrame, 100);
	m_State.m_AtkFrame->SetFrame(0, m_State.MaxAtkFrame, 100);

	MoveTime = 0;
	HitDelay = 0;
}


cTurtle::~cTurtle()
{
	Release();
}

void cTurtle::Update(bool follow, Vec2 Target)
{
	m_State.m_Frame->Frame();
	m_State.m_AtkFrame->Frame();
	bool m_bMove = false;
	m_State.v_Dir = Target;
	Vec2 DirectionPos = { 0,0 };

	if (!m_State.b_Follow) {
	m_State.b_Follow = follow;
	}

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
			m_bMove = true;
			Dir = m_State.m_pos - m_State.v_Dir;
			D3DXVec2Normalize(&Dir, &Dir);

			DirectionPos -= Dir * m_State.f_Speed;

			//m_State.f_Rot = D3DXToDegree(atan2(Dir.y, Dir.y));
			if (m_State.m_pos.x > m_State.v_Dir.x) {
				//m_State.f_Rot + 180;
				m_State.v_Size = Vec3{ 1.f, 1.f,1.f };
			}
			else {
				m_State.v_Size = Vec3{ -1.f , 1.f, 1.f };
			}
		}

		if (m_State.b_Hit) {
			HitDelay += DX_Time;
			//m_bMove = false;

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

void cTurtle::Render()
{
	if (m_State.b_Dead) {
		IMAGE->Render(m_State.m_Dead, m_State.m_pos, m_State.v_Size, m_State.f_Rot, D3DCOLOR_ARGB(DeadAlpha, 255, 255, 255), true);
	}
	else if (m_State.b_Hit) {
		IMAGE->Render(m_State.m_Dead, m_State.m_pos, m_State.v_Size, m_State.f_Rot, D3DCOLOR_ARGB(255, 255, 255, 255), true);
	}
	else if (!m_State.b_Follow) {
		IMAGE->Render(m_State.m_Image->FindImage(m_State.m_Frame->NowFrame), m_State.m_pos, m_State.v_Size, m_State.f_Rot, D3DCOLOR_ARGB(255, 255, 255, 255), true);
	}
	else if (m_State.b_Follow) {
		IMAGE->Render(m_State.m_Follow->FindImage(m_State.m_AtkFrame->NowFrame), m_State.m_pos, m_State.v_Size, m_State.f_Rot, D3DCOLOR_ARGB(255, 255, 255, 255), true);
	}
}

void cTurtle::Release()
{
}

bool cTurtle::IsOutMap(Vec2 Winsize)
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
