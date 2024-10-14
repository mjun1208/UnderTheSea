#pragma once
class cEffect
{
private:
	Vec2 m_pos;
	cTexture * m_image;
	cFrame * m_frame;

	float m_angle;

	bool b_Shoot;
	bool b_One;
	bool b_Del;
public:
	cEffect(Vec2 m_pos,cTexture * m_image, float angle, int MaxFrame, unsigned long time, bool Shoot = false);
	~cEffect();

	void Update();
	void Render();
	void Release();

	bool GetDel() { return b_Del; }
	Vec2 GetPos() { return m_pos; }
	int GetNowFrame() { return m_frame->NowFrame; }
	int GetEndFrame() { return m_frame->EndFrame; }
};

