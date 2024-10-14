#pragma once
class cOctoBullet
{
private:
	Vec2 m_pos;
	Vec2 m_Dir;
	float m_speed;
	float m_rot;

	cTexture * m_image = nullptr;
	cTexture * m_Collimage = nullptr;

	Vec2 m_Winsize;

	bool b_Coll;
	cFrame * m_frame = nullptr;

	bool b_One;
	bool b_Del;
public:
	cOctoBullet(Vec2 pos, Vec2 Dir, float rot, float speed);
	~cOctoBullet();

	void Update();
	void Render();
	void Release();

	bool IsOutMap();

	Vec2 GetPos() { return m_pos; }
	cTexture * GetTex() { return m_image->FindImage(m_frame->StartFrame); }
	bool GetDel() { return b_Del;}

	void InputColl(bool Coll) { b_Coll = Coll; }

};

