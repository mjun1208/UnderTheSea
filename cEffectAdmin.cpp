#include "DXUT.h"
#include "cEffectAdmin.h"

#include "cEffect.h"

cEffectAdmin::cEffectAdmin()
{
}


cEffectAdmin::~cEffectAdmin()
{
	Release();
}

void cEffectAdmin::Update()
{
	for (auto iter : m_effect)
		iter->Update();

	for (auto iter = m_effect.begin(); iter != m_effect.end();) {
		if ((*iter)->GetDel()) {
			SAFE_DELETE(*iter);
			iter = m_effect.erase(iter);
		}
		else {
			iter++;
		}
	}
}

void cEffectAdmin::Render()
{
	for (auto iter : m_effect)
		iter->Render();
}

void cEffectAdmin::Release()
{
	for (auto iter : m_effect)
		SAFE_DELETE(iter);

	m_effect.clear();
}
