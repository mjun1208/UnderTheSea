#pragma once
enum EnemyKind {
	e_FishM, e_FishF, e_Octo, e_JFish, e_Shark, e_OldShark, e_Turtle, e_BigJFish, e_AFish, e_AFish2
};
struct EnemyState {
	cTexture * m_Image;
	cTexture * m_Dead;
	cTexture * m_Follow;
	cFrame * m_Frame;
	cFrame * m_AtkFrame;
	int MaxIdleFrame;
	int MaxAtkFrame;
	bool b_Dead;
	bool b_Follow;
	bool b_Hit;
	bool b_Del;
	Vec2 m_pos;
	Vec2 v_Dir;
	Vec3 v_Size;
	float f_Rot;
	float f_Speed;
	int m_Hp;
	int m_Atk;
	EnemyKind m_Kind;
	bool b_IsBoss;
};
class cEffect;
class cEnemy
{
private:
	cTexture * m_HpGauge;
	cTexture * m_HpEdge;

	int Max_Hp;

	vector<cEffect *>& m_effect;

	Vec2 v_Bornpos;

	cTexture * m_MiniMap = nullptr;
	cTexture * m_HitEffect;

	float MoveTime;
	float HitDelay;

	EnemyState m_State;

	int RandNumX = 0;
	int RandNumY = 0;
	int DeadAlpha = 255;

	bool b_ReBorn;

	float f_EnemySpawn; 
	bool b_EnemySpawn;

	bool b_BazukaHit;
	float f_BazukaTime;
public:
	cEnemy(cTexture * MiniMap, EnemyState state, Vec2 Pos ,Vec2 PlayerPos, cTexture * PlayerTex, vector<cEffect *>& effect, bool ReBorn = false);
	~cEnemy();

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
	EnemyKind GetEnemyKind() { return m_State.m_Kind; }
	bool GetIsBoss() { return m_State.b_IsBoss; }

	void InputSpawn(bool spawn) { b_EnemySpawn = spawn; }
	bool GetEnemySpawn() { return b_EnemySpawn; }
	
	bool GetBazukaHit() { return b_BazukaHit; }
	void InputBazukaHit(bool Hit) { b_BazukaHit = Hit; }
};

