#include "DXUT.h"
#include "cPlayerBullet.h"


cPlayerBullet::cPlayerBullet(Vec2 pos, Vec2 Dir, float rot ,float speed , bool Bazuka)
	:m_pos(pos) , m_Dir(Dir) , m_rot(rot), m_speed(speed) , b_Bazuka(Bazuka)
{
	m_Bazuka = IMAGE->FindImage("Bazuka_Bullet");
	m_image = IMAGE->FindImage("Player_Bullet");
}


cPlayerBullet::~cPlayerBullet()
{
}

void cPlayerBullet::Update()
{
	m_pos += m_Dir * m_speed;

	if (NowStage == 1) {
		m_Winsize.x = STAGE1X;
		m_Winsize.y = STAGE1Y;
	}
	else if (NowStage == 2) {
		m_Winsize.x = STAGE2X;
		m_Winsize.y = STAGE2Y;
	}
	else if (NowStage == 3) {
		m_Winsize.x = STAGE3X;
		m_Winsize.y = STAGE3Y;
	}
}

void cPlayerBullet::Render()
{
	if (!b_Bazuka)
		IMAGE->Render(m_image, m_pos, D3DXToDegree(m_rot), true);
	else 
		IMAGE->Render(m_Bazuka, m_pos, D3DXToDegree(m_rot), true);
}

void cPlayerBullet::Release()
{
}

bool cPlayerBullet::IsOutMap()
{
	return(m_pos.x < 0 || m_pos.x > m_Winsize.x || m_pos.y < 0 || m_pos.y > m_Winsize.y);
}

bool cPlayerBullet:: IsOutPlayer(Vec2 PlayerPos, cTexture * PlayerTex)
{
	return (m_pos.x < PlayerPos.x - 1000 || m_pos.x > PlayerPos.x + 1000 || m_pos.y < PlayerPos.y - 1000 || m_pos.y > PlayerPos.y + 1000);
}
