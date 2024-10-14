#include "DXUT.h"
#include "cBulletAdmin.h"

#include "cPlayerBullet.h"
#include "cOctoBullet.h"

cBulletAdmin::cBulletAdmin()
{
}


cBulletAdmin::~cBulletAdmin()
{
	Release();
}

void cBulletAdmin::Init()
{
}

void cBulletAdmin::Update(Vec2 PlayerPos, cTexture * PlayerTex)
{
	for (auto iter : m_PlayerBullet)
		iter->Update();

	for (auto iter = m_PlayerBullet.begin(); iter != m_PlayerBullet.end(); ) {
		if ((*iter)->IsOutMap()) {
			SAFE_DELETE(*iter);
			iter = m_PlayerBullet.erase(iter);
		}
		else
			++iter;
	}

	for (auto iter = m_PlayerBullet.begin(); iter != m_PlayerBullet.end();) {
		if ((*iter)->IsOutPlayer(PlayerPos, PlayerTex)) {
			SAFE_DELETE(*iter);
			iter = m_PlayerBullet.erase(iter);
		}
		else
			++iter;
	}

	//¹®¾î ÃÑ¾Ë 
	for (auto iter : m_OctoBullet)
		iter->Update();

	for (auto iter = m_OctoBullet.begin(); iter != m_OctoBullet.end(); ) {
		if ((*iter)->IsOutMap()) {
			SAFE_DELETE(*iter);
			iter = m_OctoBullet.erase(iter);
		}
		else
			++iter;
	}

	for (auto iter = m_OctoBullet.begin(); iter != m_OctoBullet.end();) {
		if ((*iter)->GetDel()) {
			SAFE_DELETE(*iter);
			iter = m_OctoBullet.erase(iter);
		}
		else
			++iter;
	}
}

void cBulletAdmin::Render()
{
	for (auto iter : m_PlayerBullet)
		iter->Render();

	for (auto iter : m_OctoBullet)
		iter->Render();
}

void cBulletAdmin::Release()
{
	for (auto iter : m_PlayerBullet)
		SAFE_DELETE(iter);
	m_PlayerBullet.clear();

	for (auto iter : m_OctoBullet)
		SAFE_DELETE(iter);
	m_OctoBullet.clear();
}
