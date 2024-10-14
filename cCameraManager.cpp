#include "DXUT.h"
#include "cCameraManager.h"


cCameraManager::cCameraManager()
{
	Init();
}


cCameraManager::~cCameraManager()
{
}

void cCameraManager::Init()
{
	m_vCameraPos = Vec3(WINSIZEX / 2, WINSIZEY / 2, 0);
	m_vViewSize = Vec3(WINSIZEX, WINSIZEY, 0);
	m_vScale = Vec3(1, 1, 1);

	m_vFollow = Vec3(WINSIZEX / 2, WINSIZEY / 2, 0);
	m_vShake = Vec3(WINSIZEX / 2, WINSIZEY / 2, 0);
	m_fAngle = 0.0f;

	D3DXMatrixOrthoLH(&m_matProj, m_vViewSize.x, -m_vViewSize.y, 0, 1);
	DXUTGetD3D9Device()->SetTransform(D3DTS_PROJECTION, &m_matProj);

	bMove = false;
	bShake = false;
}

void cCameraManager::Update()
{
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

	m_vScrollPos = Vec3(WINSIZEX / 2, WINSIZEY / 2, 0.f) - m_vCameraPos;
	
	if (bShake)
	{
		if (ShakeTime + ShakeDelay > GetTickCount())
		{
			if (ShakeTime + 50 < GetTickCount())
			{
				random_device _Rand;
				uniform_int_distribution<__int64> distRand(-30, 30);

				m_vShake.x = m_vCameraPos.x + distRand(_Rand);
				m_vShake.y = m_vCameraPos.y + distRand(_Rand);
				if (m_vShake.x >= 0 + WINSIZEX / 2 || m_vShake.x <= m_Winsize.x - WINSIZEX / 2)
					m_vCameraPos.x = m_vOldPos.x;
				if (m_vShake.y >= 0 + WINSIZEY / 2 || m_vShake.y <= m_Winsize.y - WINSIZEY / 2)
					m_vCameraPos.y = m_vOldPos.y;
			}
		}

		else
		{
			bShake = false;
			m_vCameraPos = m_vOldPos;
		}
	}

	else if (bMove)
	{
		Vec3 MyPos = m_vCameraPos;
		Vec3 vDir = m_vFollow - MyPos;
		float fDistance = D3DXVec3Length(&vDir);

		if (fDistance < 730.f)
		{
			m_vOldPos = m_vOldPos + (m_vFollow - m_vOldPos) * 0.06f;
			if(m_vOldPos.x >= 0 + WINSIZEX / 2 && m_vOldPos.x <= m_Winsize.x - WINSIZEX / 2)
				m_vCameraPos.x = m_vOldPos.x;
			if (m_vOldPos.y >= 0 + WINSIZEY / 2 && m_vOldPos.y <= m_Winsize.y - WINSIZEY / 2)
				m_vCameraPos.y = m_vOldPos.y;
		} 

		else
		{
			m_vCameraPos = m_vFollow;
			bMove = false;
		}
	}

	this->m_matView = D3DXMATRIX(
		m_vScale.x * cosf(m_fAngle), m_vScale.x * sin(m_fAngle), 0, 0,
		-m_vScale.y * sin(m_fAngle), m_vScale.y * cos(m_fAngle), 0, 0,
		0, 0, m_vScale.z, 0,
		-m_vCameraPos.x * m_vScale.y * cos(m_fAngle) + m_vCameraPos.y * m_vScale.y * sin(m_fAngle),
		-m_vCameraPos.x * m_vScale.x * sin(m_fAngle) - m_vCameraPos.y * m_vScale.y * cos(m_fAngle), 0, 1);
}

void cCameraManager::SetTranform()
{
	DXUTGetD3D9Device()->SetTransform(D3DTS_VIEW, &m_matView);
}

void cCameraManager::ShakeCamera(float Delay)
{
	bShake = true;
	ShakeDelay = Delay;
	m_vShake = m_vCameraPos;
	ShakeTime = GetTickCount();
}