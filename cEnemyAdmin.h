#pragma once
#include "cEnemy.h"

class cEnemy;
class cPlayerBullet;
class cPlayer;
class cOcto;
class cOctoBullet;
class cEffect;

class cTurtle;

class cEnemyAdmin
{
private:
	Vec2 Winsize;

	vector<cEnemy *> m_enemy;
	vector<cOcto *> m_Octo;
	vector<cEffect *>& m_effect;
	vector<cOctoBullet *>& m_OctoBullet;

	cTexture * m_HitEffect;
	cTexture * m_BazukaEffect;

	cTurtle * m_Turtle;

	EnemyState Octo;
	EnemyState FishM;
	EnemyState FishF;
	EnemyState JFish;
	EnemyState BokFish;
	EnemyState OldShark;
	EnemyState Shark;

	EnemyState Turtle;
	EnemyState BigJFish;
	EnemyState AFish;
	EnemyState AFish2;

	int i_Test = 0;
	int i_ReBorn = 0;

	int i_Octo = 0;
	int i_FishM = 0;
	int i_FishF = 0;
	int i_JFish = 0;
	int i_OldShark = 0;
	int i_Shark = 0;
	int i_Turtle = 0;
	int i_BigJFish = 0;
	int i_AFish = 0;

	bool b_AFish2 = false;

	Vec2 Old_AFishPos;

	Vec2 Old_BigFishPos;
	int i_SpawnJFish = 0;

	cTexture * m_MiniMap;

	cTexture * m_Aim2;
	cTexture * m_Aim1;

	bool MouseColl;

	bool BossSpawn;
	bool BossMove;

	bool b_Clear;

public:
	cEnemyAdmin(vector<cOctoBullet*> & OctoBullet, vector<cEffect *>& effect);
	~cEnemyAdmin();

	void Init(int stage,cTexture * MiniMap);
	void Update(Vec2 PlayerPos, cTexture * PlayerTex, vector<cPlayerBullet*>& Bullet, cPlayer * player, bool b_Boss);
	void Render();
	void Release();

	vector<cEnemy*>& GetEnemy() { return m_enemy; }
	vector<cOcto*>& GetOcto() { return m_Octo; }

	size_t GetEnemySize() { return m_enemy.size(); }
	size_t GetOctoSize() { return m_Octo.size(); }

	bool GetClear() { return b_Clear; }
};