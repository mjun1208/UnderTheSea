#pragma once
#include "cEnemy.h"

class cTurtle
{
private:
	Vec2 v_Bornpos;

	cTexture * m_MiniMap = nullptr;

	float MoveTime;
	float HitDelay;

	EnemyState m_State;

	int RandNumX = 0;
	int RandNumY = 0;
	int DeadAlpha = 255;

	bool b_ReBorn;
public:
	cTurtle(cTexture * MiniMap, EnemyState state, Vec2 Pos, Vec2 PlayerPos, cTexture * PlayerTex, bool ReBorn = false);
	~cTurtle();

	void Update(bool follow, Vec2 Target);
	void Render();
	void Release();

	Vec2 GetPos() { return m_State.m_pos; }
	Vec2 GetMiniPos() { return m_State.m_pos / 20; }
	cTexture * GetTex() { return m_State.m_Image->FindImage(0); }


	bool IsOutMap(Vec2 Winsize);

	bool GetReBorn() { return b_ReBorn; }
	int GetHp() { return m_State.m_Hp; }
	bool GetHit() { return m_State.b_Hit; }
	void InputHit(bool Hit) { m_State.b_Hit = Hit; }
	void InputHp(int Hp) { m_State.m_Hp = Hp; }
	void InputDead(bool Dead) { m_State.b_Dead = Dead; }
	bool Getb_Dead() { return m_State.b_Dead; }
	int GetDead() { return DeadAlpha; }
	int GetAtk() { return m_State.m_Atk; }
};

