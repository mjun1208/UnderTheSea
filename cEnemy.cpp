#include "DXUT.h"
#include "cEnemy.h"

#include "cEffect.h"

cEnemy::cEnemy(cTexture * MiniMap, EnemyState state, Vec2 Pos, Vec2 PlayerPos, cTexture * PlayerTex, vector<cEffect *>& effect, bool ReBorn)
	: m_effect(effect), b_ReBorn(ReBorn)
{
	m_MiniMap = MiniMap;
	m_State = state;
	m_State.m_pos = Pos;
	v_Bornpos = Pos;
	m_State.m_Frame->SetFrame(0, m_State.MaxIdleFrame, 100);
	m_State.m_AtkFrame->SetFrame(0, m_State.MaxAtkFrame, 100);

	MoveTime = 0;
	HitDelay = 0;
	m_HitEffect = IMAGE->FindImage("Hit_Effect");

	f_EnemySpawn = 0;
	b_EnemySpawn = false;

	m_HpGauge = IMAGE->FindImage("Boss_HpGauge");
	m_HpEdge = IMAGE->FindImage("Boss_Edge");

	Max_Hp = m_State.m_Hp;
	b_BazukaHit = false;
	f_BazukaTime = 0;
}


cEnemy::~cEnemy()
{
	Release();
}

void cEnemy::Update(bool follow, Vec2 Target)
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

	if (!m_State.b_Follow && m_State.b_IsBoss) {
		m_State.b_Follow = follow;
	}
	else
		m_State.b_Follow = follow;

	if (m_State.b_Dead) {
		if (DeadAlpha > 0) {
			if (m_State.b_IsBoss) {
				int Rand_X = rand() % 2;
				int Rand_Y = rand() % 2;
				Vec2 Rand_Pos;
				Rand_Pos.x = rand() % m_State.m_Dead->info.Width / 2;
				Rand_Pos.y = rand() % m_State.m_Dead->info.Height / 2;
				Vec2 Old_Pos = m_State.m_pos;
				if (Rand_X == 0)
					Old_Pos.x -= Rand_Pos.x;
				else
					Old_Pos.x += Rand_Pos.x;

				if (Rand_Y == 0)
					Old_Pos.y -= Rand_Pos.y;
				else
					Old_Pos.y += Rand_Pos.y;

				m_effect.push_back(new cEffect(Old_Pos, m_HitEffect, 0, 7, 60));
				DeadAlpha--;
			}
			else
				DeadAlpha-=10;
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

			if (m_State.m_Kind == e_BigJFish && f_EnemySpawn > 2.f) {
				b_EnemySpawn = true;
				f_EnemySpawn = 0;
			}
			else if (m_State.m_Kind == e_BigJFish){
				f_EnemySpawn += DX_Time;
			}
		}

		if (m_State.b_IsBoss) {
			if (m_State.b_Hit) {
				HitDelay += DX_Time;

				if (HitDelay > 0.5f) {
					HitDelay = 0;
					m_bMove = true;
					m_State.b_Hit = false;
				}
			}
		}
		else {
			if (m_State.b_Hit) {
				HitDelay += DX_Time;
				m_bMove = false;

				if (HitDelay > 0.5f) {
					HitDelay = 0;
					m_bMove = true;
					m_State.b_Hit = false;
				}
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

	if (m_State.m_Hp <= 0) {
		m_State.b_Dead = true;
	}
}

void cEnemy::Render()
{
	if (m_State.b_Dead) {
		IMAGE->Render(m_State.m_Dead, m_State.m_pos, m_State.v_Size, m_State.f_Rot, D3DCOLOR_ARGB(DeadAlpha, 255, 255, 255), true);
	}
	else if (m_State.b_Hit) {
		IMAGE->Render(m_State.m_Dead, m_State.m_pos, m_State.v_Size, m_State.f_Rot, D3DCOLOR_ARGB(255, 255, 255, 255), true);
	}
	else if (!m_State.b_Follow) {
		IMAGE->Render(m_State.m_Image->FindImage(m_State.m_Frame->NowFrame), m_State.m_pos, m_State.v_Size ,m_State.f_Rot , D3DCOLOR_ARGB(255,255,255,255), true);
	}
	else if (m_State.b_Follow) {
		IMAGE->Render(m_State.m_Follow->FindImage(m_State.m_AtkFrame->NowFrame), m_State.m_pos, m_State.v_Size, m_State.f_Rot, D3DCOLOR_ARGB(255, 255, 255, 255), true);
	}

	if (m_State.b_IsBoss) {
		IMAGE->Render(m_HpEdge, Vec2(m_State.m_pos.x, m_State.m_pos.y + m_State.m_Image->FindImage(0)->info.Height / 2 + 30), 0, true);
		RECT rc_Gauge = {
			0,
			0,
			((float)m_HpGauge->info.Width / (float)Max_Hp) * (float)m_State.m_Hp ,
			m_HpGauge->info.Height
		};
		IMAGE->CropRender(m_HpGauge, Vec2(m_State.m_pos.x, m_State.m_pos.y + m_State.m_Image->FindImage(0)->info.Height / 2 + 30), Vec3(1.f,1.f,1.f), rc_Gauge);
	}

}


void cEnemy::Release()
{
}

bool cEnemy::IsOutMap(Vec2 Winsize)
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
