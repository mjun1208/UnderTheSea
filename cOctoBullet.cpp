#include "DXUT.h"
#include "cOctoBullet.h"


cOctoBullet::cOctoBullet(Vec2 pos, Vec2 Dir, float rot, float speed)
	:m_pos(pos), m_Dir(Dir), m_rot(rot) , m_speed(speed)
{
	m_image = IMAGE->FindImage("OctoBullet");
	m_frame = new cFrame;
	m_frame->SetFrame(0, 3, 100);

	b_Coll = false;
	b_One = false;
	b_Del = false;
}


cOctoBullet::~cOctoBullet()
{
	Release();
}

void cOctoBullet::Update()
{
	if (b_Coll) {
		m_frame->Frame();
	}
	else {
	m_pos += m_Dir * m_speed;
	}

	if (m_frame->NowFrame == m_frame->EndFrame)
		b_One = true;
	if (b_One && m_frame->NowFrame == 0)
		b_Del = true;


	if (NowStage == 1) {
		m_Winsize.x = STAGE1X;
		m_Winsize.y = STAGE1Y;
	}
	else if (NowStage == 2) {
		m_Winsize.x = STAGE2X;
		m_Winsize.y = STAGE2Y;
	}
}

void cOctoBullet::Render()
{
	IMAGE->Render(m_image->FindImage(m_frame->NowFrame), m_pos, D3DXToDegree(m_rot) + 180, true);
}

void cOctoBullet::Release()
{
	SAFE_DELETE(m_frame);
}

bool cOctoBullet::IsOutMap()
{
	return(m_pos.x < 0 || m_pos.x > m_Winsize.x || m_pos.y < 0 || m_pos.y > m_Winsize.y);
}
