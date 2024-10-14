#include "DXUT.h"
#include "cMultiTexture.h"

#include "cSingleTexture.h"
cMultiTexture::cMultiTexture()
{
}


cMultiTexture::~cMultiTexture()
{
	for (auto iter : m_VecText) {
		SAFE_DELETE(iter);
	}
	//m_VecText.clear();
}

cTexture * cMultiTexture::AddImage(const string & path, int count)
{
	char sz[128] = "";
	for (int i = 0; i <= count; i++) {
		sprintf(sz, path.c_str(), i);

		cTexture* pTex = new cSingleTexture;
		pTex->AddImage(sz);

		m_VecText.push_back(pTex);
	}

	return this;
}

cTexture * cMultiTexture::FindImage(int count)
{
	if (count == -1) {
		return this;
	}
	else
		return m_VecText[count];
}

int cMultiTexture::Length()
{
	return m_VecText.size();
}
