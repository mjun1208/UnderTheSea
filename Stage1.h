#pragma once
#include "cScene.h"

class cPlayer;
class cBulletAdmin;
class cEnemyAdmin;
class cEffectAdmin;
class Stage1 : public cScene
{
private:
	MCI_OPEN_PARMS mciOpen;
	MCI_PLAY_PARMS mciPlay;
private:
	cTexture * m_Load;
	cTexture * m_LoadGauge;
	cTexture * m_LoadEdge;

	cFrame * m_Loadframe = nullptr;

	cTexture * m_BackGround;
	cTexture * m_BackColl;
	cTexture * m_MiniMap;
	cTexture * m_MiniPlayer;
	cTexture * m_ShowMiniMap;


	cPlayer * m_Player;

	cFrame * m_frame;

	cTexture * m_PlayerHpGauge;
	cTexture * m_PlayerHpEdge;
	cTexture * m_PlayerDashGauge;
	cTexture * m_PlayerDashEdge;

	cBulletAdmin * m_Bullet;

	cEnemyAdmin * m_Enemy;
	cTexture * m_MiniEnemy;
	cTexture * m_MiniBoss;

	cEffectAdmin * m_Effect;

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
	cTexture * Turtle_Append;
	cTexture * m_V;
	cTexture * m_S;
	int i_Player_x;
	int i_Turtle_x;
	Vec3 V_Size;
	Vec3 S_Size;

	bool BossAppend;
	bool b_VS;
	bool b_V;
	bool b_S;

	bool Boss;

	float f_VSTime;
public:
	Stage1();
	virtual ~Stage1();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

