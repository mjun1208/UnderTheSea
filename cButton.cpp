#include "DXUT.h"
#include "cButton.h"


cButton::cButton(Vec2 Pos, const string& key)
	: m_pos(Pos)
{
	m_Nomal = IMAGE->FindImage(key + "_Nomal");
	m_OnCursor = IMAGE->FindImage(key + "_OnCursor");
	m_Click = IMAGE->FindImage(key + "_Click");
	SettingRect();
}


cButton::~cButton()
{
	Release();
}

bool cButton::Update()
{
	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(DXUTGetHWND(), &ptMouse);
	if (PtInRect(&m_rc, ptMouse)) {
		b_OnCursor = true;

		if (INPUT->MouseLPress())
			b_Click = true;
		else if (INPUT->MouseLUp())
			return true;
		else
			b_Click = false;
	}
	else {
		b_OnCursor = false;
		b_Click = false;
	}
	return false;
}

void cButton::Render()
{
	if (b_Click) {
		IMAGE->Render(m_Click, m_pos, 0, true);
	}
	else if (b_OnCursor) {
		IMAGE->Render(m_OnCursor, m_pos, 0, true);
	}
	else
		IMAGE->Render(m_Nomal, m_pos, 0, true);
}

void cButton::Release()
{
}
