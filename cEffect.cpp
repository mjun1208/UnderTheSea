#include "DXUT.h"
#include "cEffect.h"


cEffect::cEffect(Vec2 pos, cTexture * image, float angle , int MaxFrame, unsigned long time, bool Shoot)
	:m_pos(pos) ,  m_angle(angle) , b_Shoot(Shoot)
{
	m_image = image;
	m_frame = new cFrame;
	m_frame->SetFrame(0, MaxFrame, time);
	b_One = false; 
	b_Del = false;
}


cEffect::~cEffect()
{
	Release();
}

void cEffect::Update()
{
	m_frame->Frame();

	if (m_frame->NowFrame == m_frame->EndFrame) {
		b_One = true;
	}
	if (b_One && m_frame->NowFrame == 0) {
		b_Del = true;
	}
}

void cEffect::Render()
{
	if (!b_Shoot && m_frame->EndFrame == 9)
		IMAGE->Render(m_image->FindImage(m_frame->NowFrame), m_pos, Vec3(1.5f, 1.5f, 1.5f), D3DXToDegree(m_angle), D3DCOLOR_XRGB(255,255,255), true);
	else if (!b_Shoot) 
		IMAGE->Render(m_image->FindImage(m_frame->NowFrame), m_pos, Vec3(1.f, 1.f, 1.f), D3DXToDegree(m_angle), D3DCOLOR_XRGB(255, 255, 255), true);
	else
		IMAGE->CenterRender(m_image->FindImage(m_frame->NowFrame), m_pos, Vec3(1.f, 1.f, 1.f),
			Vec3(m_image->FindImage(m_frame->NowFrame)->info.Width / 2 , m_image->FindImage(m_frame->NowFrame)->info.Height,0), m_angle);
}

void cEffect::Release()
{
	SAFE_DELETE(m_frame);
}
