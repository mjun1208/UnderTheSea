#pragma once
class cPlayerBullet
{
private:
	Vec2 m_pos;
	Vec2 m_Dir;
	float m_speed;
	float m_rot;
	bool b_Bazuka;

	cTexture * m_image;
	cTexture * m_Bazuka;

	Vec2 m_Winsize;
public:
	cPlayerBullet(Vec2 pos, Vec2 Dir, float rot, float speed, bool Bazuka = false);
	~cPlayerBullet();

	void Update();
	void Render();
	void Release();

	bool IsOutMap();
	bool IsOutPlayer(Vec2 PlayerPos, cTexture * PlayerTex);

	Vec2 GetPos() { return m_pos; }
	cTexture * GetTex() { return m_image; }
	bool GetBazuka() { return b_Bazuka; }
	float GetRot() { return m_rot; }
};

