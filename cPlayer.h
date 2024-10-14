#pragma once
enum PlayerDiv{
	Left, Right
};
class cPlayerBullet;
class cEffect;
class cPlayer
{
private:
	MCI_OPEN_PARMS mciOpen;
	MCI_PLAY_PARMS mciPlay;

	MCI_OPEN_PARMS mciOpen2;
	MCI_PLAY_PARMS mciPlay2;

	float mciTime;
	float mci2Time;
private:
	int m_Hp;

	vector<cPlayerBullet*>& m_Bullet;
	vector<cEffect*>& m_effect;

	cTexture * m_Head = nullptr;
	cTexture * m_Head2 = nullptr;
	cTexture * m_Arm = nullptr;
	cTexture * m_Leg = nullptr;

	cTexture * m_ShootEffect = nullptr;
	cTexture * m_ShootEffect2 = nullptr;

	cTexture * m_Shadow = nullptr;

	cTexture * m_MiniMap = nullptr;

	cTexture * m_HpGauge = nullptr;
	cTexture * m_HpEdge = nullptr;

	cTexture * m_PlayerColled = nullptr;

	cFrame * m_frame = nullptr;
	cFrame * m_Collframe = nullptr;

	Vec2 m_pos;
	Vec2 MousePos;
	Vec2 m_vDir;
	Vec2 OldMousePos;
	Vec2 DirectionPos;

	bool m_bRight;
	bool m_bLeft;
	bool m_bUp;
	bool m_bDown;

	float PlayerRot;

	bool m_bDiv;
	bool m_bBack;
	bool m_bDash;
	bool m_bShoot;
	bool m_bDashCharge;

	int m_Shoot;
	int m_Dash;

	float DashTime;
	float ShootTime;
	float DashChargeTime;

	Vec2 Winsize;
	Vec2 ShowPos;
	int NowStage;

	bool b_Coll;
	int i_CollAlpha;
	float CollTime;
	int i_CollCount;

	float f_ChangeWeaponTime;
	float f_BazukaTime = 0;
	bool b_Bazuka = false;
public:
	cPlayer(vector<cPlayerBullet*>& PlayerBullet, vector<cEffect *>& effect);
	~cPlayer();

	void Init(int stage, cTexture * MiniMap);
	void Update();
	void Render();
	void Release();

	Vec2 GetMiniPos() { return ShowPos; }
	Vec2 GetPos() { return m_pos; }
	cTexture * GetTex() { return m_Leg->FindImage(1); }
	int GetHp() { return m_Hp; }
	int GetDash() { return m_Dash; }
	bool GetColl() { return b_Coll; }
	
	void InputColl(bool Coll) { b_Coll = Coll; }
	void InputHp(int Hp) { m_Hp = Hp; }
};

