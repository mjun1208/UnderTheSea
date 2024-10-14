#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <time.h>
#include <random>

using namespace std;

#define g_device DXUTGetD3D9Device()
#define DX_Time DXUTGetElapsedTime()

#ifdef _DEBUG
#define DEBUG_LOG(log) cout << log << endl;
#else 
#define DEBUG_LOG(log)
#endif // _DEBUG

using Vec2 = D3DXVECTOR2;
using Vec3 = D3DXVECTOR3;

const int WINSIZEX = 1280;
const int WINSIZEY = 720;

extern int NowStage;

const int STAGE1X = 3829;
const int STAGE1Y = 1440;

const int STAGE2X = 1440;
const int STAGE2Y = 5980;

const int STAGE3X = 4242;
const int STAGE3Y = 1226;

#include "cImageManager.h"
#include "cSceneManager.h"
#include "cCameraManager.h"
#include "cInputManager.h"

#include "cTexture.h"

#pragma comment(lib, "winmm.lib")
#include <mmsystem.h>
#include "Digitalv.h"

#include "cButton.h"