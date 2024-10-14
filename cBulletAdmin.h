#pragma once
class cPlayerBullet;
class cOctoBullet;
class cBulletAdmin
{
private:
	vector<cPlayerBullet *> m_PlayerBullet;
	vector<cOctoBullet *> m_OctoBullet;
public:
	cBulletAdmin();
	~cBulletAdmin();

	void Init();
	void Update(Vec2 PlayerPos, cTexture * PlayerTex);
	void Render();
	void Release();


	vector<cPlayerBullet*>& GetPlayerBullet() { return m_PlayerBullet; }
	vector<cOctoBullet*>& GetOctoBullet() { return m_OctoBullet; }
};

