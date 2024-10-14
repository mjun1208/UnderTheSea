#include "DXUT.h"
#include "cLoadScene.h"

cLoadScene::cLoadScene()
{
	m_image = IMAGE->AddImage("Load", "./Image/Load/BackGround(%d).png", 1);
	m_Gauge = IMAGE->AddImage("LoadGauge", "./Image/Load/Gauge.png");
	m_GaugeEdge = IMAGE->AddImage("LoadGaugeEdge", "./Image/Load/GaugeEdge.png");
}


cLoadScene::~cLoadScene()
{
	Release();
}

void cLoadScene::Init()
{
	m_iCurLoad = 0;
	m_frame = new cFrame;
	m_frame->SetFrame(0, 1, 150);
	
	// 인트로
	Load("Intro1", "./Image/Intro/(%d).png", 7);
	Load("Intro2", "./Image/Intro/Ang(%d).png", 2);
	Load("Intro3", "./Image/Intro/Bng(%d).png", 2);
	// 엔딩
	Load("End_BackGround", "./Image/End/BackGround.png");

	// 게임 오버
	Load("GameOver_BackGround", "./Image/GameOver/BackGround.png");
	Load("Re_Nomal", "./Image/GameOver/Re_Nomal.png");
	Load("Re_OnCursor", "./Image/GameOver/Re_OnCursor.png");
	Load("Re_Click", "./Image/GameOver/Re_Click.png");

	// 타이틀
	Load("Title_BackGround", "./Image/Title/BackGround.png");
	Load("Title_Main", "./Image/Title/Main/(%d).png", 7);
	Load("Title_Logo", "./Image/Title/Logo.png");

	Load("HowToChang", "./Image/Title/HowToChang.png");

	Load("Back_Nomal", "./Image/Title/Back/Back_Nomal.png");
	Load("Back_OnCursor", "./Image/Title/Back/Back_OnCursor.png");
	Load("Back_Click", "./Image/Title/Back/Back_Click.png");
	// 버튼
	Load("Start_Nomal", "./Image/Title/Start/Start_Nomal.png");
	Load("Start_OnCursor", "./Image/Title/Start/Start_OnCursor.png");
	Load("Start_Click", "./Image/Title/Start/Start_Click.png");

	Load("HowTo_Nomal", "./Image/Title/HowTo/HowTo_Nomal.png");
	Load("HowTo_OnCursor", "./Image/Title/HowTo/HowTo_OnCursor.png");
	Load("HowTo_Click", "./Image/Title/HowTo/HowTo_Click.png");

	Load("Exit_Nomal", "./Image/Title/Exit/Exit_Nomal.png");
	Load("Exit_OnCursor", "./Image/Title/Exit/Exit_OnCursor.png");
	Load("Exit_Click", "./Image/Title/Exit/Exit_Click.png");
	// 플레이어
	Load("Player_Head2", "./Image/Player/Test2.png");
	Load("Player_Head", "./Image/Player/Test.png");
	Load("Player_Arm", "./Image/Player/Arm.png");
	Load("Player_Leg", "./Image/Player/Leg(%d).png", 3);

	//스테이지
	Load("Stage_Start", "./Image/Ingame/Start.png");
	Load("Stage_Clear", "./Image/Ingame/Clear.png");
	Load("Stage_Fail", "./Image/Ingame/Fail.png");

	// 1스테이지
	Load("Stage1BackGroud", "./Image/Ingame/Stage1/BackGround.png");
	Load("Stage1BackColl", "./Image/Ingame/Stage1/(%d).png", 1);
	Load("Stage1MiniMap", "./Image/Ingame/Stage1/MiniMap.png");
	Load("Stage1ShowMiniMap", "./Image/Ingame/Stage1/MiniMapShow.png");
	// 2스테이지
	Load("Stage2BackGroud", "./Image/Ingame/Stage2/BackGround.png");
	Load("Stage2BackColl", "./Image/Ingame/Stage2/(%d).png", 1);
	Load("Stage2MiniMap", "./Image/Ingame/Stage2/MiniMap.png");
	Load("Stage2ShowMiniMap", "./Image/Ingame/Stage2/MiniMapShow.png");
	// 3스테이지
	Load("Stage3BackGroud", "./Image/Ingame/Stage3/BackGround.png");
	Load("Stage3MiniMap", "./Image/Ingame/Stage3/MiniMap.png");
	Load("Stage3ShowMiniMap", "./Image/Ingame/Stage3/MiniMapShow.png");

	// 총 관련
	Load("Player_Bullet", "./Image/Player/Bullet.png");
	Load("Bazuka_Bullet", "./Image/Player/BazukaBullet.png");
	Load("Aim", "./Image/Player/aim1.png");
	Load("Aim2", "./Image/Player/aim2.png");

	Load("Shoot_Effect", "./Image/Effect/Shoot/(%d).png", 2);
	Load("Shoot_Effect2", "./Image/Effect/Shoot2/(%d).png", 5);

	Load("Bazuka_Hit", "./Image/Effect/BazukaHit/(%d).png", 9);
	// 미니맵 표시
	Load("MiniPlayer", "./Image/Player/Mini.png");
	Load("MiniEnemy", "./Image/Enemy/Mini.png");

	// 플레이어 UI
	Load("HpGauge", "./Image/Player/HpGauge.png");
	Load("HpEdge", "./Image/Player/HpEdge.png");
	Load("DashGauge", "./Image/Player/DashGauge.png");
	Load("DashEdge", "./Image/Player/DashEdge.png");
	Load("Colled", "./Image/Player/Colled(%d).png",1);
	
	// 몬스터들
	Load("Hit_Effect", "./Image/Effect/Hit/(%d).png", 7);

	Load("Octo", "./Image/Enemy/Octo/(%d).png", 1);
	Load("OctoDead", "./Image/Enemy/Octo/Dead.png");
	Load("OctoAtk", "./Image/Enemy/Octo/Atk(%d).png", 1);
	Load("OctoShoot", "./Image/Enemy/Octo/Shoot(%d).png", 1);
	Load("OctoBullet", "./Image/Enemy/Octo/Bullet/(%d).png", 3);

	Load("FishM", "./Image/Enemy/FishM/(%d).png", 1);
	Load("FishMDead", "./Image/Enemy/FishM/Dead.png");
	Load("FishMAtk", "./Image/Enemy/FishM/Atk(%d).png", 2);

	Load("FishF", "./Image/Enemy/FishF/(%d).png", 2);
	Load("FishFDead", "./Image/Enemy/FishF/Dead.png");
	Load("FishFAtk", "./Image/Enemy/FishF/Atk(%d).png", 2);

	Load("JFish", "./Image/Enemy/JFish/(%d).png", 2);
	Load("JFishDead", "./Image/Enemy/JFish/Dead.png");
	Load("JFishAtk", "./Image/Enemy/JFish/Atk(%d).png",2);

	Load("BokFish", "./Image/Enemy/BokFish/(%d).png", 1);
	Load("BokFishDead", "./Image/Enemy/BokFish/Dead.png");
	Load("BokFishAtk", "./Image/Enemy/BokFish/Atk(%d).png",4);

	Load("OldShark", "./Image/Enemy/OldShark/(%d).png", 2);
	Load("OldSharkDead", "./Image/Enemy/OldShark/Dead.png");
	Load("OldSharkAtk", "./Image/Enemy/OldShark/Atk.png");

	Load("Shark", "./Image/Enemy/Shark/(%d).png",2);
	Load("SharkDead", "./Image/Enemy/Shark/Dead.png");
	Load("SharkAtk", "./Image/Enemy/Shark/Atk.png");

	//보스
	Load("Boss_HpGauge", "./Image/Boss/HpGauge.png");
	Load("Boss_Edge", "./Image/Boss/HpEdge.png");

	Load("MiniBoss", "./Image/Boss/Mini.png");

	Load("Turtle", "./Image/Boss/Turtle/(%d).png", 5);
	Load("TurtleDead", "./Image/Boss/Turtle/Dead.png");
	Load("TurtleAtk", "./Image/Boss/Turtle/Atk(%d).png", 3);

	Load("BigJFish", "./Image/Boss/BigJFish/(%d).png", 3);
	Load("BigJFishDead", "./Image/Boss/BigJFish/Dead.png");
	Load("BigJFishAtk", "./Image/Boss/BigJFish/Atk(%d).png",2);

	Load("AFish", "./Image/Boss/AFish/(%d).png", 4);
	Load("AFishDead", "./Image/Boss/AFish/Dead.png");
	Load("AFishAtk", "./Image/Boss/AFish/Atk.png");

	Load("AFish2", "./Image/Boss/AFish2/(%d).png", 1);
	Load("AFish2Dead", "./Image/Boss/AFish2/Dead.png");
	Load("AFish2Atk", "./Image/Boss/AFish2/Atk.png");

	//보스 출현
	Load("V", "./Image/BossAppend/V.png");
	Load("S", "./Image/BossAppend/S.png");
	Load("Player_Append", "./Image/BossAppend/Player.png");
	Load("Turtle_Append", "./Image/BossAppend/Turtle.png");
	Load("BigJFish_Append", "./Image/BossAppend/BigJFish.png");
	Load("AFish_Append", "./Image/BossAppend/AFish.png");
	m_iMaxLoad = m_sLoading.size();
}

void cLoadScene::Update()
{
	m_frame->Frame();

	if (m_iCurLoad != m_iMaxLoad) {
		IMAGE->AddImage(
			m_sLoading[m_iCurLoad].key, 
			m_sLoading[m_iCurLoad].path, 
			m_sLoading[m_iCurLoad].count);

		m_iCurLoad++;
	}

	else
	{
		SCENE->ChangeScene("Intro");
	}
}

void cLoadScene::Render()
{
	IMAGE->Render(m_image->FindImage(m_frame->NowFrame), Vec2(0, 0));

	RECT GaugeRect = {
		0,
		0,
		((float)m_Gauge->info.Width / m_iMaxLoad) * m_iCurLoad,
		m_Gauge->info.Height
	};

	IMAGE->CropRender(m_Gauge, Vec2(WINSIZEX / 2, 550), Vec3(1.f, 1.f, 1.f), GaugeRect);
	IMAGE->Render(m_GaugeEdge, Vec2(WINSIZEX / 2, 550), 0 , true);

	IMAGE->PrintText(to_string(
		(int)(((float)m_iCurLoad / (float)m_iMaxLoad) * 100)) + "%"
		, Vec2(WINSIZEX / 2, 550), 30, D3DCOLOR_ARGB(255, 0, 0, 0), true);
}

void cLoadScene::Release()
{
	SAFE_DELETE(m_frame);
	for (auto iter : m_sLoading) {
		//SAFE_DELETE(iter);
	}
	m_sLoading.clear();
}
