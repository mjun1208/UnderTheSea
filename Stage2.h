#pragma once
#include "cScene.h"

class cPlayer;
class cBulletAdmin;
class cEnemyAdmin;
class cEffectAdmin;
class Stage2 : public cScene
{
private:
	MCI_OPEN_PARMS mciOpen;
	MCI_PLAY_PARMS mciPlay;
private:
	cTexture * m_Load;
	cTexture * m_LoadGauge;
	cTexture * m_LoadEdge;

	cFrame * m_Loadframe = nullptr;

	cTexture * m_BackGround = nullptr;
	cTexture * m_BackColl = nullptr;
	cTexture * m_MiniMap = nullptr;
	cTexture * m_MiniPlayer = nullptr;
	cTexture * m_ShowMiniMap = nullptr;

	cPlayer * m_Player = nullptr;

	cFrame * m_frame = nullptr;

	cTexture * m_PlayerHpGauge = nullptr;
	cTexture * m_PlayerHpEdge = nullptr;
	cTexture * m_PlayerDashGauge = nullptr;
	cTexture * m_PlayerDashEdge = nullptr;

	cBulletAdmin * m_Bullet = nullptr;

	cEnemyAdmin * m_Enemy = nullptr;
	cTexture * m_MiniEnemy = nullptr;
	cTexture * m_MiniBoss;

	cEffectAdmin * m_Effect = nullptr;

	bool b_Coll;
	bool b_One;

	int MiniAlpha;

	bool b_Load;
	bool b_Start;
	bool b_Clear;
	bool b_Fail;

	int i_Start_y;
	int i_Fail_y;
	int i_Clear_y;

	bool b_Started;

	cTexture * Player_Append;
	cTexture * BigJFish_Append;
	cTexture * m_V;
	cTexture * m_S;
	int i_Player_x;
	int i_BigJFish_x;
	Vec3 V_Size;
	Vec3 S_Size;

	bool BossAppend;
	bool b_VS;
	bool b_V;
	bool b_S;

	bool Boss;

	float f_VSTime;
public:
	Stage2();
	virtual ~Stage2();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

