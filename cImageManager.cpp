#include "DXUT.h"
#include "cImageManager.h"

#include "cTexture.h"
#include "cSingleTexture.h"
#include "cMultiTexture.h"

cImageManager::cImageManager()
	:m_sprite(nullptr)
{
}


cImageManager::~cImageManager()
{
	Release();
}

void cImageManager::Init()
{
	D3DXCreateSprite(g_device, &m_sprite);
}

void cImageManager::Release()
{
	SAFE_RELEASE(m_sprite);

	for (auto iter : m_image)
		SAFE_DELETE(iter.second);

	m_image.clear();

}

void cImageManager::Begin(bool Ui)
{
	if(Ui)
		m_sprite->Begin(D3DXSPRITE_ALPHABLEND);
	else
	    m_sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);
}

void cImageManager::End()
{
	m_sprite->End();
}

void cImageManager::LostDevice()
{
	m_sprite->OnLostDevice();
}

void cImageManager::ResetDevice()
{
	m_sprite->OnResetDevice();
}

cTexture * cImageManager::AddImage(const string & key, const string & path, int count)
{
	auto find = m_image.find(key);

	if (find == m_image.end()) {
		cTexture* ret;
		if (count == 0) {
			ret = new cSingleTexture();
		}
		else {
			ret = new cMultiTexture();
		}
		ret->AddImage(path, count);

		m_image.insert(make_pair(key, ret));

		return ret;
	}
	return nullptr;
}

cTexture * cImageManager::FindImage(const string& key,int count)
{
	auto find = m_image.find(key);

	if (find != m_image.end()) {
		return find->second->FindImage(count);
	}
	else {
		return nullptr;
	}
}

void cImageManager::PrintText(const string & str, Vec2 pos, float size, D3DCOLOR color, bool Center)
{
	D3DXMATRIX mat;
	if (!Center) {
		D3DXCreateFontA(g_device, size, 0, 10, 1, FALSE, HANGEUL_CHARSET, 0, 0, 0, "Fixedsys", &pFont);

		D3DXMatrixTranslation(&mat, pos.x, pos.y, 0);
	}
	else {
		D3DXCreateFontA(g_device, size, 0, 0, 1, FALSE, HANGEUL_CHARSET, 0, 0, 0, "Fixedsys", &pFont);

		D3DXMatrixTranslation(&mat, pos.x - size * (str.size() * 0.25), pos.y - size / 2.f, 0);
	}

	m_sprite->SetTransform(&mat);
	pFont->DrawTextA(m_sprite, str.c_str(), str.size(), nullptr, DT_NOCLIP, color);

	SAFE_RELEASE(pFont);
}

void cImageManager::Render(cTexture * pTexture, Vec2 pos, const Vec3 & size, float rot, D3DCOLOR color, bool Center)
{
	if (pTexture) {
		D3DXMATRIX mat;
		D3DXMATRIX matS, matT, matR;

		D3DXMatrixScaling(&matS, size.x, size.y, size.z);
		D3DXMatrixRotationZ(&matR, D3DXToRadian(rot));
		D3DXMatrixTranslation(&matT, pos.x, pos.y, 0.f);

		mat = matS * matR * matT;

		m_sprite->SetTransform(&mat);
		if (Center) {
			m_sprite->Draw(pTexture->texturePtr, NULL,
				&D3DXVECTOR3(pTexture->info.Width / 2.f, pTexture->info.Height / 2.f, 0.f), NULL, color);
		}
		else {
			m_sprite->Draw(pTexture->texturePtr, NULL, NULL, NULL, color);
		}
	}
}

void cImageManager::Render(cTexture * pTexture, Vec2 pos, float rot , bool Center)
{
	if (pTexture) {
		D3DXMATRIX mat;
		D3DXMATRIX matS, matT, matR;

		D3DXMatrixScaling(&matS, 1.f, 1.f, 1.f);
		D3DXMatrixRotationZ(&matR, D3DXToRadian(rot));
		D3DXMatrixTranslation(&matT, pos.x, pos.y, 0.f);

		mat = matS * matR * matT;

		m_sprite->SetTransform(&mat);
		if (!Center) {
			m_sprite->Draw(pTexture->texturePtr, NULL, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		else
			m_sprite->Draw(pTexture->texturePtr, NULL,
				&D3DXVECTOR3(pTexture->info.Width / 2.f, pTexture->info.Height / 2.f, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void cImageManager::CenterRender(cTexture * pTexture, Vec2 pos, const Vec3 & size, Vec3 Center, float rot, D3DCOLOR color)
{
	if (pTexture) {
		D3DXMATRIX mat;
		D3DXMATRIX matS, matT, matR;

		D3DXMatrixScaling(&matS, size.x, size.y, size.z);
		D3DXMatrixRotationZ(&matR, D3DXToRadian(rot));
		D3DXMatrixTranslation(&matT, pos.x, pos.y, 0.f);

		mat = matS * matR * matT;

		m_sprite->SetTransform(&mat);
		
		m_sprite->Draw(pTexture->texturePtr, NULL,
			&Center, NULL, color);
	}
}

void cImageManager::CropRender(cTexture * pTexture, Vec2 pos, const Vec3 & size, const RECT & rcRange)
{
	D3DXMATRIX mat;
	D3DXMATRIX matS, matT, matR;

	D3DXMatrixScaling(&matS, size.x, size.y, size.z);
	D3DXMatrixRotationZ(&matR, D3DXToRadian(0));
	D3DXMatrixTranslation(&matT, pos.x, pos.y, 0.f);

	mat = matS * matR * matT;

	m_sprite->SetTransform(&mat);
	m_sprite->Draw(pTexture->texturePtr, &rcRange, &D3DXVECTOR3(
		pTexture->info.Width / 2, pTexture->info.Height / 2, 0), nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void cFrame::SetFrame(int start, int end, unsigned long delay)
{
	StartFrame = NowFrame = start;
	EndFrame = end;
	FrameDelay = delay;
	FrameSkip = FrameDelay + timeGetTime();
}

bool cFrame::Frame()
{
	if (FrameSkip <= timeGetTime()) {
		if (NowFrame >= EndFrame) {
			NowFrame = StartFrame;
		}
		else NowFrame++;
		FrameSkip = FrameDelay + timeGetTime();

		return true;
	}
	return false;
}
