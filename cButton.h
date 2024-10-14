#pragma once
class cButton
{
private:

	Vec2 m_pos;
	cTexture * m_Nomal = nullptr;
	cTexture * m_OnCursor = nullptr;
	cTexture * m_Click = nullptr;
	bool b_OnCursor;
	bool b_Click;
	RECT m_rc;

	void SettingRect() {
		SetRect(&m_rc, m_pos.x - m_Nomal->info.Width / 2,
			m_pos.y - m_Nomal->info.Height / 2,
			m_pos.x + m_Nomal->info.Width / 2,
			m_pos.y + m_Nomal->info.Height / 2);
	};

public:
	cButton(Vec2 Pos, const string& key);
	~cButton();

	bool Update();
	void Render();
	void Release();

};

