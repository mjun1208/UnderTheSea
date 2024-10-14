 #pragma once
#include "singleton.h"

class cCameraManager : public singleton<cCameraManager>
{
private:
	D3DXMATRIX m_matProj, m_matView;

	Vec3 m_vCameraPos, m_vViewSize, m_vScale, m_vScrollPos , m_vFollow , m_vOldPos, m_vShake;

	float m_fAngle = 0.0;

	bool bMove;
	bool bShake;

	float ShakeDelay;
	float ShakeTime;

	Vec2 m_Winsize;
public:
	inline void FollowX(float Pos_x) { m_vFollow.x = Pos_x; bMove = true; m_vOldPos.x = m_vCameraPos.x; }
	inline void FollowY(float Pos_y) { m_vFollow.y = Pos_y; bMove = true; m_vOldPos.y = m_vCameraPos.y; }
	inline void Follow(Vec3 Pos) { m_vFollow = Pos; bMove = true; m_vOldPos = m_vCameraPos; }
	void ShakeCamera(float Delay);
public:
	cCameraManager();
	virtual ~cCameraManager();

	void SetPosition(const Vec3& vSet) { m_vCameraPos = vSet; bMove = false; }
	void MovePosition(const Vec3& vPlus) { m_vCameraPos += vPlus; }

	Vec3 GetPosition() { return m_vCameraPos; }
	Vec3 GetScrollPos() { return m_vScrollPos; }

	void Init();
	void Update();
	void SetTranform();
};


#define CAMERA cCameraManager::GetInstance()