#pragma once
#include "singleton.h"
class cTexture;

class cFrame {
public:
	int NowFrame = 0;
	int StartFrame = 0;
	int EndFrame = 0;

	unsigned long FrameSkip = 0;
	unsigned long FrameDelay = 0;
	void SetFrame(int start, int end, unsigned long delay);

	bool Frame();
};

class cImageManager : public singleton<cImageManager>
{
private:
	LPD3DXSPRITE m_sprite;

	map<string, cTexture*> m_image;
	LPD3DXFONT pFont = nullptr;
public:

	cImageManager();
	virtual ~cImageManager();

	void Init();
	void Release();

	void Begin(bool Ui);
	void End();

	void ReBegin(bool Ui) { End(); Begin(Ui); }

	void LostDevice();
	void ResetDevice();
	
	cTexture * AddImage(const string& key, const string& path, int count = 0);
	cTexture * FindImage(const string& key, int count = -1);

	void PrintText(const string& str, Vec2 pos ,float size , D3DCOLOR color, bool Center = false);

	void Render(cTexture * pTexture, Vec2 pos,const Vec3 &size, float rot, D3DCOLOR color = D3DCOLOR_XRGB(255,255,255), bool Center = false);
	void Render(cTexture * pTexture, Vec2 pos, float rot = 0, bool Center = false);
	void CenterRender(cTexture * pTexture, Vec2 pos, const Vec3 & size, Vec3 Center, float rot = 0, D3DCOLOR color =  D3DCOLOR_ARGB(255,255,255,255));
	void CropRender(cTexture * pTexture , Vec2 pos, const Vec3 &size, const RECT& rcRange);

};

#define IMAGE cImageManager::GetInstance()
