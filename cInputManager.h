#pragma once
#include "singleton.h"
class cInputManager : public singleton<cInputManager>
{
private:
	bool NowMouseInput[2];
	bool OldMouseInput[2];

	bool NowInput[256];
	bool OldInput[256];
public:
	cInputManager();
	virtual ~cInputManager();

	bool MouseLPress();
	bool MouseLDown();
	bool MouseLUp();

	bool MouseRPress();
	bool MouseRDown();
	bool MouseRUp();

	bool KeyPress(int key);
	bool KeyDown(int key);
	bool KeyUp(int key);

	void Update();
	
	Vec2 GetMousePos() {
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(DXUTGetHWND(), &pt);

		return Vec2((float)pt.x ,(float)pt.y);
	}

	Vec2 GetMouseScrollPos()
	{
		Vec2 mousePos = GetMousePos();
		mousePos -= Vec2(CAMERA->GetScrollPos().x, CAMERA->GetScrollPos().y);
		return mousePos;
	}
};

#define INPUT cInputManager::GetInstance()