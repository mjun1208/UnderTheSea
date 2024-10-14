#pragma once
#include "cTexture.h"

class cMultiTexture : public cTexture
{
private:
	vector<cTexture *> m_VecText;
public:
	cMultiTexture();
	virtual ~cMultiTexture();

	virtual cTexture * AddImage(const string& path, int count = 0) override;
	virtual cTexture * FindImage(int count = -1) override;

	virtual int Length() override;
};

