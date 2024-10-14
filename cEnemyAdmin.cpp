#include "DXUT.h"
#include "cEnemyAdmin.h"
#include "cPlayerBullet.h"
#include "cOctoBullet.h"

#include "cEnemy.h"
#include "cPlayer.h"
#include "cOcto.h"
#include "cEffect.h"
#include "cTurtle.h"

cEnemyAdmin::cEnemyAdmin(vector<cOctoBullet*> & OctoBullet , vector<cEffect *>& effect)
	:m_OctoBullet(OctoBullet) , m_effect(effect)
{
}


cEnemyAdmin::~cEnemyAdmin()
{
	Release();
}

void cEnemyAdmin::Init(int stage, cTexture * MiniMap)
{
	if (stage == 1) {
		Winsize.x = STAGE1X;
		Winsize.y = STAGE1Y;
		i_Test = 25;
	}
	else if (stage == 2) {
		Winsize.x = STAGE2X;
		Winsize.y = STAGE2Y;
		i_Test = 20;
	}
	else if (stage == 3) {
		Winsize.x = STAGE3X;
		Winsize.y = STAGE3Y;
		i_Test = 15;
	}

	m_MiniMap = MiniMap;
	Octo = {
		IMAGE->FindImage("Octo"),
		IMAGE->FindImage("OctoDead"),
		IMAGE->FindImage("OctoAtk"),
		new cFrame,
		new cFrame,
		1,
		1,
		false,
		false,
		false,
		false,
		Vec2(0,0),
		Vec2(0,0),
		Vec3(1.f,1.f,1.f),
		0.f,
		10.f,
		4,
		4,
		e_Octo,
		false
	}; 
	FishM = {
		IMAGE->FindImage("FishM"),
		IMAGE->FindImage("FishMDead"),
		IMAGE->FindImage("FishMAtk"),
		new cFrame,
		new cFrame,
		1,
		2,
		false,
		false,
		false,
		false,
		Vec2(0,0),
		Vec2(0,0),
		Vec3(1.f,1.f,1.f),
		0.f,
		7.f,
		1,
		3,
		e_FishM,
		false
	};
	FishF = {
		IMAGE->FindImage("FishF"),
		IMAGE->FindImage("FishFDead"),
		IMAGE->FindImage("FishFAtk"),
		new cFrame,
		new cFrame,
		2,
		2,
		false,
		false,
		false,
		false,
		Vec2(0,0),
		Vec2(0,0),
		Vec3(1.f,1.f,1.f),
		0.f,
		7.f,
		1,
		3,
		e_FishF,
		false
	};
	JFish = {
		IMAGE->FindImage("JFish"),
		IMAGE->FindImage("JFishDead"),
		IMAGE->FindImage("JFishAtk"),
		new cFrame,
		new cFrame,
		2,
		2,
		false,
		false,
		false,
		false,
		Vec2(0,0),
		Vec2(0,0),
		Vec3(1.f,1.f,1.f),
		0.f,
		7.f,
		4,
		5,
		e_JFish,
		false
	};
	OldShark = {
		IMAGE->FindImage("OldShark"),
		IMAGE->FindImage("OldSharkDead"),
		IMAGE->FindImage("OldSharkAtk"),
		new cFrame,
		new cFrame,
		2,
		0,
		false,
		false,
		false,
		false,
		Vec2(0,0),
		Vec2(0,0),
		Vec3(1.f,1.f,1.f),
		0.f,
		7.f,
		5,
		5,
		e_OldShark,
		false
	};
	Shark = {
		IMAGE->FindImage("Shark"),
		IMAGE->FindImage("SharkDead"),
		IMAGE->FindImage("SharkAtk"),
		new cFrame,
		new cFrame,
		2,
		0,
		false,
		false,
		false,
		false,
		Vec2(0,0),
		Vec2(0,0),
		Vec3(1.f,1.f,1.f),
		0.f,
		7.f,
		5,
		5,
		e_Shark,
		false
	};
	// 보스
	Turtle = {
		IMAGE->FindImage("Turtle"),
		IMAGE->FindImage("TurtleDead"),
		IMAGE->FindImage("TurtleAtk"),
		new cFrame,
		new cFrame,
		5,
		3,
		false,
		false,
		false,
		false,
		Vec2(0,0),
		Vec2(0,0),
		Vec3(1.f,1.f,1.f),
		0.f,
		10.f,
		120,
		3,
		e_Turtle,
		true
	};
	BigJFish = {
		IMAGE->FindImage("BigJFish"),
		IMAGE->FindImage("BigJFishDead"),
		IMAGE->FindImage("BigJFishAtk"),
		new cFrame,
		new cFrame,
		3,
		2,
		false,
		false,
		false,
		false,
		Vec2(0,0),
		Vec2(0,0),
		Vec3(1.f,1.f,1.f),
		0.f,
		6.f,
		70,
		2,
		e_BigJFish,
		true
	};
	AFish = {
		IMAGE->FindImage("AFish"),
		IMAGE->FindImage("AFishDead"),
		IMAGE->FindImage("AFishAtk"),
		new cFrame,
		new cFrame,
		4,
		0,
		false,
		false,
		false,
		false,
		Vec2(0,0),
		Vec2(0,0),
		Vec3(1.f,1.f,1.f),
		0.f,
		12.f,
		100,
		8,
		e_AFish,
		true
	};
	AFish2 = {
		IMAGE->FindImage("AFish2"),
		IMAGE->FindImage("AFish2Dead"),
		IMAGE->FindImage("AFish2Atk"),
		new cFrame,
		new cFrame,
		1,
		0,
		false,
		false,
		false,
		false,
		Vec2(0,0),
		Vec2(0,0),
		Vec3(1.f,1.f,1.f),
		0.f,
		11.f,
		50,
		10,
		e_AFish2,
		true
	};

	m_Aim2 = IMAGE->FindImage("Aim2");
	m_Aim1 = IMAGE->FindImage("Aim");
	m_HitEffect = IMAGE->FindImage("Hit_Effect");
	m_BazukaEffect = IMAGE->FindImage("Bazuka_Hit");
    srand(time(NULL));
    MouseColl = false;
	BossSpawn = false;
	BossMove = false;
	b_Clear = false;

	b_AFish2 = false;
}

void cEnemyAdmin::Update(Vec2 PlayerPos, cTexture * PlayerTex, vector<cPlayerBullet*>& Bullet, cPlayer * player, bool b_Boss)
{
	if (b_Boss && !BossSpawn) {
		i_Test = 1;
		BossSpawn = true;
	}

	MouseColl = false;
	if (i_Test > 0) {
		i_Test--;
		Vec2 v_BornPos;

		v_BornPos.x = rand() % (int)Winsize.x;
		v_BornPos.y = rand() % (int)Winsize.y;

		RECT Coll = {
			PlayerPos.x - (PlayerTex->info.Width / 2),
			PlayerPos.y - (PlayerTex->info.Height / 2),
			PlayerPos.x + (PlayerTex->info.Width / 2),
			PlayerPos.y + (PlayerTex->info.Height / 2)
		};

		if (b_Boss){
			if (Coll.left - 600 < v_BornPos.x &&
				Coll.right + 600 > v_BornPos.x &&
				Coll.top - 600 < v_BornPos.y &&
				Coll.bottom + 600 > v_BornPos.y
				) {
				if (NowStage == 1) {
					m_enemy.push_back(new cEnemy(m_MiniMap, Turtle, Vec2(v_BornPos.x, v_BornPos.y), PlayerPos, PlayerTex, m_effect,true));
				}
				else if (NowStage == 2) {
					m_enemy.push_back(new cEnemy(m_MiniMap, BigJFish, Vec2(v_BornPos.x, v_BornPos.y), PlayerPos, PlayerTex, m_effect, true));
				}
				else if (NowStage == 3) {
					m_enemy.push_back(new cEnemy(m_MiniMap, AFish, Vec2(v_BornPos.x, v_BornPos.y), PlayerPos, PlayerTex, m_effect, true));
				}
			}
			else {
				if (NowStage == 1) {
					m_enemy.push_back(new cEnemy(m_MiniMap, Turtle, Vec2(v_BornPos.x, v_BornPos.y), PlayerPos, PlayerTex, m_effect));
				}
				else if (NowStage == 2) {
					m_enemy.push_back(new cEnemy(m_MiniMap, BigJFish, Vec2(v_BornPos.x, v_BornPos.y), PlayerPos, PlayerTex, m_effect));
				}
				else if (NowStage == 3) {
					m_enemy.push_back(new cEnemy(m_MiniMap, AFish, Vec2(v_BornPos.x, v_BornPos.y), PlayerPos, PlayerTex, m_effect));
				}
			}
		}
		else {
			if (Coll.left - 400 < v_BornPos.x &&
				Coll.right + 400 > v_BornPos.x &&
				Coll.top - 400 < v_BornPos.y &&
				Coll.bottom + 400 > v_BornPos.y
				) {
				if (NowStage == 1) {
					m_enemy.push_back(new cEnemy(m_MiniMap, FishM, Vec2(v_BornPos.x, v_BornPos.y), PlayerPos, PlayerTex, m_effect, true));
					m_enemy.push_back(new cEnemy(m_MiniMap, FishF, Vec2(v_BornPos.x, v_BornPos.y), PlayerPos, PlayerTex, m_effect, true));
				}
				else if (NowStage == 2) {
					m_Octo.push_back(new cOcto(m_OctoBullet, m_MiniMap, Octo, Vec2(v_BornPos.x, v_BornPos.y), PlayerPos, PlayerTex, true));
					m_enemy.push_back(new cEnemy(m_MiniMap, JFish, Vec2(v_BornPos.x, v_BornPos.y), PlayerPos, PlayerTex, m_effect, true));
				}
				else if (NowStage == 3) {
					m_enemy.push_back(new cEnemy(m_MiniMap, OldShark, Vec2(v_BornPos.x, v_BornPos.y), PlayerPos, PlayerTex, m_effect, true));
					//m_enemy.push_back(new cEnemy(m_MiniMap, Shark, Vec2(v_BornPos.x, v_BornPos.y), PlayerPos, PlayerTex, m_effect, true));
				}
			}
			else {
				if (NowStage == 1) {
					m_enemy.push_back(new cEnemy(m_MiniMap, FishM, Vec2(v_BornPos.x, v_BornPos.y), PlayerPos, PlayerTex, m_effect));
					m_enemy.push_back(new cEnemy(m_MiniMap, FishF, Vec2(v_BornPos.x, v_BornPos.y), PlayerPos, PlayerTex, m_effect));

				}
				else if (NowStage == 2) {
					m_Octo.push_back(new cOcto(m_OctoBullet, m_MiniMap, Octo, Vec2(v_BornPos.x, v_BornPos.y), PlayerPos, PlayerTex));
					m_enemy.push_back(new cEnemy(m_MiniMap, JFish, Vec2(v_BornPos.x, v_BornPos.y), PlayerPos, PlayerTex, m_effect));
				}
				else if (NowStage == 3) {
					m_enemy.push_back(new cEnemy(m_MiniMap, OldShark, Vec2(v_BornPos.x, v_BornPos.y), PlayerPos, PlayerTex, m_effect));
					//m_enemy.push_back(new cEnemy(m_MiniMap, Shark, Vec2(v_BornPos.x, v_BornPos.y), PlayerPos, PlayerTex, m_effect));
				}
			}
		}
	}

	if (i_ReBorn > 0) {
		i_ReBorn--;
		Vec2 v_BornPos;
		v_BornPos.x = rand() % (int)Winsize.x;
		v_BornPos.y = rand() % (int)Winsize.y;

		RECT Coll = {
			PlayerPos.x - (PlayerTex->info.Width / 2),
			PlayerPos.y - (PlayerTex->info.Height / 2),
			PlayerPos.x + (PlayerTex->info.Width / 2),
			PlayerPos.y + (PlayerTex->info.Height / 2)
		};

		if (Coll.left - 400 < v_BornPos.x &&
			Coll.right + 400 > v_BornPos.x &&
			Coll.top - 400 < v_BornPos.y &&
			Coll.bottom + 400 > v_BornPos.y
			) {
			if (NowStage == 1) {
				if (b_Boss) {
					m_enemy.push_back(new cEnemy(m_MiniMap, Turtle, Vec2(v_BornPos.x, v_BornPos.y), PlayerPos, PlayerTex, m_effect, true));
					i_Turtle--;
				}
				else {
					if (i_FishM > 0) {
						m_enemy.push_back(new cEnemy(m_MiniMap, FishM, Vec2(v_BornPos.x, v_BornPos.y), PlayerPos, PlayerTex, m_effect, true));
						i_FishM--;
					}
					else if (i_FishF > 0) {
						m_enemy.push_back(new cEnemy(m_MiniMap, FishF, Vec2(v_BornPos.x, v_BornPos.y), PlayerPos, PlayerTex, m_effect, true));
						i_FishF--;
					}
				}
			}
			else if (NowStage == 2) {
				if (b_Boss) {
					m_enemy.push_back(new cEnemy(m_MiniMap, BigJFish, Vec2(v_BornPos.x, v_BornPos.y), PlayerPos, PlayerTex, m_effect, true));
					i_BigJFish--;
				}
				else {
					if (i_JFish > 0) {
						m_enemy.push_back(new cEnemy(m_MiniMap, JFish, Vec2(v_BornPos.x, v_BornPos.y), PlayerPos, PlayerTex, m_effect, true));
						i_JFish--;
					}
					else if (i_Octo > 0) {
						m_Octo.push_back(new cOcto(m_OctoBullet, m_MiniMap, Octo, Vec2(v_BornPos.x, v_BornPos.y), PlayerPos, PlayerTex, true));
						i_Octo--;
					}
				}
			}
			else if (NowStage == 3) {
				if (b_Boss) {
					m_enemy.push_back(new cEnemy(m_MiniMap, AFish, Vec2(v_BornPos.x, v_BornPos.y), PlayerPos, PlayerTex, m_effect, true));
					i_AFish--;
				}
				else {
					if (i_OldShark > 0) {
						m_enemy.push_back(new cEnemy(m_MiniMap, OldShark, Vec2(v_BornPos.x, v_BornPos.y), PlayerPos, PlayerTex, m_effect, true));
						i_OldShark--;
					}
					else if (i_Shark > 0) {
						m_enemy.push_back(new cEnemy(m_MiniMap, Shark, Vec2(v_BornPos.x, v_BornPos.y), PlayerPos, PlayerTex, m_effect, true));
						i_Shark--;
					}
				}
			}
		}
		else {
			if (NowStage == 1) {
				if (b_Boss) {
					m_enemy.push_back(new cEnemy(m_MiniMap, Turtle, Vec2(v_BornPos.x, v_BornPos.y), PlayerPos, PlayerTex, m_effect));
					i_Turtle--;
				}
				else {
					if (i_FishM > 0) {
						m_enemy.push_back(new cEnemy(m_MiniMap, FishM, Vec2(v_BornPos.x, v_BornPos.y), PlayerPos, PlayerTex, m_effect));
						i_FishM--;
					}
					else if (i_FishF > 0) {
						m_enemy.push_back(new cEnemy(m_MiniMap, FishF, Vec2(v_BornPos.x, v_BornPos.y), PlayerPos, PlayerTex, m_effect));
						i_FishF--;
					}

				}
			}
			else if (NowStage == 2) {
				if (b_Boss) {
					m_enemy.push_back(new cEnemy(m_MiniMap, BigJFish, Vec2(v_BornPos.x, v_BornPos.y), PlayerPos, PlayerTex, m_effect));
					i_BigJFish--;
				}
				if (i_JFish > 0) {
					m_enemy.push_back(new cEnemy(m_MiniMap, JFish, Vec2(v_BornPos.x, v_BornPos.y), PlayerPos, PlayerTex, m_effect));
					i_JFish--;
				}
				else if (i_Octo > 0) {
					m_Octo.push_back(new cOcto(m_OctoBullet, m_MiniMap, Octo, Vec2(v_BornPos.x, v_BornPos.y), PlayerPos, PlayerTex));
					i_Octo--;
				}
			}
			else if (NowStage == 3) {
				if (b_Boss) {
					m_enemy.push_back(new cEnemy(m_MiniMap, AFish, Vec2(v_BornPos.x, v_BornPos.y), PlayerPos, PlayerTex, m_effect));
					i_AFish--;
				}
				else {
					if (i_OldShark > 0) {
						m_enemy.push_back(new cEnemy(m_MiniMap, OldShark, Vec2(v_BornPos.x, v_BornPos.y), PlayerPos, PlayerTex, m_effect));
						i_OldShark--;
					}
					else if (i_Shark > 0) {
						m_enemy.push_back(new cEnemy(m_MiniMap, Shark, Vec2(v_BornPos.x, v_BornPos.y), PlayerPos, PlayerTex, m_effect));
						i_Shark--;
					}
				}
			}
		}
	}

	if (i_SpawnJFish > 0) {
		m_enemy.push_back(new cEnemy(m_MiniMap, JFish, Old_BigFishPos , PlayerPos, PlayerTex, m_effect));
		i_SpawnJFish--;
	}

	if (b_AFish2) {
		m_enemy.push_back(new cEnemy(m_MiniMap, AFish2, Old_AFishPos, PlayerPos, PlayerTex, m_effect));
		b_AFish2 = false;
	}

	for (auto iter : m_enemy) {

		if (iter->GetEnemySpawn()) {
			Old_BigFishPos = iter->GetPos();
			i_SpawnJFish += 2;
			iter->InputSpawn(false);
		}


		RECT Coll = {
			PlayerPos.x - (PlayerTex->info.Width / 2),
			PlayerPos.y - (PlayerTex->info.Height / 2),
			PlayerPos.x + (PlayerTex->info.Width / 2),
			PlayerPos.y + (PlayerTex->info.Height / 2)
		};

		if (iter->GetIsBoss()) {
			if (Coll.left - 500 < iter->GetPos().x &&
				Coll.right + 500 > iter->GetPos().x &&
				Coll.top - 500 < iter->GetPos().y &&
				Coll.bottom + 500 > iter->GetPos().y
				)
				iter->Update(true, PlayerPos);
			else
				iter->Update(false, PlayerPos);
		}
		else {
			if (Coll.left - 350 < iter->GetPos().x &&
				Coll.right + 350 > iter->GetPos().x &&
				Coll.top - 350 < iter->GetPos().y &&
				Coll.bottom + 350 > iter->GetPos().y
				)
				iter->Update(true, PlayerPos);
			else
				iter->Update(false, PlayerPos);
		}
		RECT Mouse{
			INPUT->GetMouseScrollPos().x,
			INPUT->GetMouseScrollPos().y,
			INPUT->GetMouseScrollPos().x,
			INPUT->GetMouseScrollPos().y,
		};
		//cout << INPUT->GetMouseScrollPos().x << " " << INPUT->GetMouseScrollPos().y << endl;

		if (Mouse.left - m_Aim1->info.Width / 2 < iter->GetPos().x &&
			Mouse.right + m_Aim1->info.Width / 2 > iter->GetPos().x &&
			Mouse.top - m_Aim1->info.Height / 2 < iter->GetPos().y &&
			Mouse.bottom + m_Aim1->info.Height / 2 > iter->GetPos().y)
		{
			MouseColl = true;
		}
	}

	// 충돌~~~~~~~~~~~~~~~~~~~
	for (auto Eiter = m_enemy.begin(); Eiter != m_enemy.end();) {
		bool b_Del = false;
		bool b_Coll = false;
		bool b_BazukaColl = false;
		for (auto Biter = Bullet.begin(); Biter != Bullet.end();) {
			RECT rc_Bullet = {
				(*Biter)->GetPos().x - (*Biter)->GetTex()->info.Width / 2,
				(*Biter)->GetPos().y - (*Biter)->GetTex()->info.Height / 2,
				(*Biter)->GetPos().x + (*Biter)->GetTex()->info.Width / 2,
				(*Biter)->GetPos().y + (*Biter)->GetTex()->info.Height / 2
			};

			if (rc_Bullet.left < (*Eiter)->GetPos().x + (*Eiter)->GetTex()->info.Width / 2 &&
				rc_Bullet.right >(*Eiter)->GetPos().x - (*Eiter)->GetTex()->info.Width / 2 &&
				rc_Bullet.top < (*Eiter)->GetPos().y + (*Eiter)->GetTex()->info.Height / 2 &&
				rc_Bullet.bottom >(*Eiter)->GetPos().y - (*Eiter)->GetTex()->info.Height / 2
				&& !(*Eiter)->Getb_Dead() && !(*Biter)->GetBazuka()) {
				b_Coll = true;
				m_effect.push_back(new cEffect((*Biter)->GetPos(), m_HitEffect, 0, 7, 60));
			}
			else if (rc_Bullet.left < (*Eiter)->GetPos().x + (*Eiter)->GetTex()->info.Width / 2 &&
				rc_Bullet.right >(*Eiter)->GetPos().x - (*Eiter)->GetTex()->info.Width / 2 &&
				rc_Bullet.top < (*Eiter)->GetPos().y + (*Eiter)->GetTex()->info.Height / 2 &&
				rc_Bullet.bottom >(*Eiter)->GetPos().y - (*Eiter)->GetTex()->info.Height / 2
				&& !(*Eiter)->Getb_Dead() && (*Biter)->GetBazuka()) {
				b_BazukaColl = true;
				m_effect.push_back(new cEffect((*Biter)->GetPos(), m_BazukaEffect, (*Biter)->GetRot(), 9, 50));
			}

			if (b_Coll) {
				SAFE_DELETE((*Biter));
				Biter = Bullet.erase(Biter);
				int Hp = (*Eiter)->GetHp();
				if (Hp <= 0)
					b_Del = true;
				else {
					(*Eiter)->InputHp(--Hp);
					(*Eiter)->InputHit(true);
				}
			}
			else if (b_BazukaColl) {
				SAFE_DELETE((*Biter));
				Biter = Bullet.erase(Biter);
			}
			else {
				++Biter;
			}
		}
		if (b_Del) {
			(*Eiter)->InputDead(true);
			/*SAFE_DELETE((*Eiter));q
			Eiter = m_enemy.erase(Eiter);*/
		}
		else {
			++Eiter;
		}
	}

	for (auto Eiter = m_enemy.begin(); Eiter != m_enemy.end();) {
		bool b_Del = false;
		bool b_Coll = false;
		for (auto Biter = m_effect.begin(); Biter != m_effect.end();) {
			RECT rc_BazukaEffect = {
				(*Biter)->GetPos().x - 150,
				(*Biter)->GetPos().y - 150,
				(*Biter)->GetPos().x + 150,
				(*Biter)->GetPos().y + 150
			};
			if (rc_BazukaEffect.left < (*Eiter)->GetPos().x + (*Eiter)->GetTex()->info.Width / 2 &&
				rc_BazukaEffect.right >(*Eiter)->GetPos().x - (*Eiter)->GetTex()->info.Width / 2 &&
				rc_BazukaEffect.top < (*Eiter)->GetPos().y + (*Eiter)->GetTex()->info.Height / 2 &&
				rc_BazukaEffect.bottom >(*Eiter)->GetPos().y - (*Eiter)->GetTex()->info.Height / 2 && 
				!(*Eiter)->Getb_Dead() && (*Biter)->GetEndFrame() == 9 && (*Biter)->GetNowFrame() == 7 && 
				!(*Eiter)->GetBazukaHit()) {

				(*Eiter)->InputBazukaHit(true);
				int Hp = (*Eiter)->GetHp();
				if (Hp <= 0)
					b_Del = true;
				else {
					(*Eiter)->InputHp(Hp -= 3);
					(*Eiter)->InputHit(true);
				}

			}
			else {
				++Biter;
			}
		}
		if (b_Del) {
			(*Eiter)->InputDead(true);
		}
		else {
			++Eiter;
		}
	}

	for (auto iter = m_enemy.begin(); iter != m_enemy.end();) {
		if ((*iter)->IsOutMap(Winsize)) {
			if ((*iter)->GetEnemyKind() == e_FishM)
				i_FishM++;
			else if ((*iter)->GetEnemyKind() == e_FishF)
				i_FishF++;
			else if ((*iter)->GetEnemyKind() == e_JFish)
				i_JFish++;
			else if ((*iter)->GetEnemyKind() == e_OldShark)
				i_OldShark++;
			else if ((*iter)->GetEnemyKind() == e_Shark)
				i_Shark++;
			else if ((*iter)->GetEnemyKind() == e_Turtle)
				i_Turtle++;
			else if ((*iter)->GetEnemyKind() == e_BigJFish)
				i_BigJFish++;
			else if ((*iter)->GetEnemyKind() == e_AFish)
				i_AFish++;

			SAFE_DELETE(*iter);
			iter = m_enemy.erase(iter);
			i_ReBorn++;
		}
		else
			++iter;
	}

	for (auto iter = m_enemy.begin(); iter != m_enemy.end();) {
		if ((*iter)->GetReBorn()) {
			if ((*iter)->GetEnemyKind() == e_FishM)
				i_FishM++;
			else if ((*iter)->GetEnemyKind() == e_FishF)
				i_FishF++;
			else if ((*iter)->GetEnemyKind() == e_JFish)
				i_JFish++;
			else if ((*iter)->GetEnemyKind() == e_OldShark)
				i_OldShark++;
			else if ((*iter)->GetEnemyKind() == e_Shark)
				i_Shark++;
			else if ((*iter)->GetEnemyKind() == e_Turtle)
				i_Turtle++;
			else if ((*iter)->GetEnemyKind() == e_BigJFish)
				i_BigJFish++;
			else if ((*iter)->GetEnemyKind() == e_AFish)
				i_AFish++;

			SAFE_DELETE(*iter);
			iter = m_enemy.erase(iter);
			i_ReBorn++;
		}
		else
			++iter;
	}

	for (auto iter = m_enemy.begin(); iter != m_enemy.end();) {
		if ((*iter)->GetDead() <= 0) {
			if ((*iter)->GetIsBoss() && ((*iter)->GetEnemyKind() != e_AFish)) {
				b_Clear = true;
			}
			else if ((*iter)->GetEnemyKind() == e_AFish) {
				Old_AFishPos = (*iter)->GetPos();
				b_AFish2 = true;
			}
			SAFE_DELETE(*iter);
			iter = m_enemy.erase(iter);
		}
		else
			++iter;
	}

	for (auto iter = m_enemy.begin(); iter != m_enemy.end();) {
		if (PlayerPos.x - (*iter)->GetTex()->info.Width / 2 < (*iter)->GetPos().x &&
			PlayerPos.x + (*iter)->GetTex()->info.Width / 2 > (*iter)->GetPos().x &&
			PlayerPos.y - (*iter)->GetTex()->info.Height / 2 < (*iter)->GetPos().y &&
			PlayerPos.y + (*iter)->GetTex()->info.Height / 2 > (*iter)->GetPos().y &&
			!player->GetColl() && !(*iter)->Getb_Dead()) {
			int Hp = player->GetHp();
			Hp -= (*iter)->GetAtk();
			player->InputHp(Hp);
			player->InputColl(true);
		}
		else
			++iter;
	}

	//문어
	for (auto iter : m_Octo) {
		RECT Coll = {
			PlayerPos.x - (PlayerTex->info.Width / 2),
			PlayerPos.y - (PlayerTex->info.Height / 2),
			PlayerPos.x + (PlayerTex->info.Width / 2),
			PlayerPos.y + (PlayerTex->info.Height / 2)
		};

		if (Coll.left - 300 < iter->GetPos().x &&
			Coll.right + 300 > iter->GetPos().x &&
			Coll.top - 300 < iter->GetPos().y &&
			Coll.bottom + 300 > iter->GetPos().y
			)
			iter->Update(true, PlayerPos, PlayerTex);
		else
			iter->Update(false, PlayerPos , PlayerTex);

		RECT Mouse{
			INPUT->GetMouseScrollPos().x,
			INPUT->GetMouseScrollPos().y,
			INPUT->GetMouseScrollPos().x,
			INPUT->GetMouseScrollPos().y,
		};
		//cout << INPUT->GetMouseScrollPos().x << " " << INPUT->GetMouseScrollPos().y << endl;

		if (Mouse.left - m_Aim1->info.Width / 2 < iter->GetPos().x &&
			Mouse.right + m_Aim1->info.Width / 2 > iter->GetPos().x &&
			Mouse.top - m_Aim1->info.Height / 2 < iter->GetPos().y &&
			Mouse.bottom + m_Aim1->info.Height / 2 > iter->GetPos().y)
		{
			MouseColl = true;
		}
	}

	//문어 충돌
	for (auto Eiter = m_Octo.begin(); Eiter != m_Octo.end();) {
		bool b_Del = false;
		bool b_Coll = false;
		bool b_BazukaColl = false;
		for (auto Biter = Bullet.begin(); Biter != Bullet.end();) {
			RECT rc_Bullet = {
				(*Biter)->GetPos().x - (*Biter)->GetTex()->info.Width / 2,
				(*Biter)->GetPos().y - (*Biter)->GetTex()->info.Height / 2,
				(*Biter)->GetPos().x + (*Biter)->GetTex()->info.Width / 2,
				(*Biter)->GetPos().y + (*Biter)->GetTex()->info.Height / 2
			};

			if (rc_Bullet.left < (*Eiter)->GetPos().x + (*Eiter)->GetTex()->info.Width / 2 &&
				rc_Bullet.right >(*Eiter)->GetPos().x - (*Eiter)->GetTex()->info.Width / 2 &&
				rc_Bullet.top < (*Eiter)->GetPos().y + (*Eiter)->GetTex()->info.Height / 2 &&
				rc_Bullet.bottom >(*Eiter)->GetPos().y - (*Eiter)->GetTex()->info.Height / 2
				&& !(*Eiter)->Getb_Dead() && !(*Biter)->GetBazuka()) {
				b_Coll = true;
				m_effect.push_back(new cEffect((*Biter)->GetPos(), m_HitEffect, 0, 7, 60));
			}
			else if (rc_Bullet.left < (*Eiter)->GetPos().x + (*Eiter)->GetTex()->info.Width / 2 &&
				rc_Bullet.right >(*Eiter)->GetPos().x - (*Eiter)->GetTex()->info.Width / 2 &&
				rc_Bullet.top < (*Eiter)->GetPos().y + (*Eiter)->GetTex()->info.Height / 2 &&
				rc_Bullet.bottom >(*Eiter)->GetPos().y - (*Eiter)->GetTex()->info.Height / 2
				&& !(*Eiter)->Getb_Dead() && (*Biter)->GetBazuka()) {
				b_BazukaColl = true;
				m_effect.push_back(new cEffect((*Biter)->GetPos(), m_BazukaEffect, (*Biter)->GetRot(), 9, 50));
			}

			if (b_Coll) {
				SAFE_DELETE((*Biter));
				Biter = Bullet.erase(Biter);
				int Hp = (*Eiter)->GetHp();
				if (Hp <= 0)
					b_Del = true;
				else {
					(*Eiter)->InputHp(--Hp);
					(*Eiter)->InputHit(true);
				}
			}
			else if (b_BazukaColl) {
				SAFE_DELETE((*Biter));
				Biter = Bullet.erase(Biter);
			}
			else {
				++Biter;
			}
		}
		if (b_Del) {
			(*Eiter)->InputDead(true);
			/*SAFE_DELETE((*Eiter));q
			Eiter = m_enemy.erase(Eiter);*/
		}
		else {
			++Eiter;
		}
	}

	for (auto iter = m_Octo.begin(); iter != m_Octo.end();) {
		if ((*iter)->IsOutMap(Winsize)) {
			SAFE_DELETE(*iter);
			iter = m_Octo.erase(iter);
			i_Octo++;
			i_ReBorn++;
		}
		else
			++iter;
	}

	for (auto iter = m_Octo.begin(); iter != m_Octo.end();) {
		if ((*iter)->GetReBorn()) {
			SAFE_DELETE(*iter);
			iter = m_Octo.erase(iter);
			i_Octo++;
			i_ReBorn++;
		}
		else
			++iter;
	}

	for (auto iter = m_Octo.begin(); iter != m_Octo.end();) {
		if ((*iter)->GetDead() <= 0) {
			SAFE_DELETE(*iter);
			iter = m_Octo.erase(iter);
		}
		else
			++iter;
	}

	for (auto Eiter = m_Octo.begin(); Eiter != m_Octo.end();) {
		bool b_Del = false;
		bool b_Coll = false;
		for (auto Biter = m_effect.begin(); Biter != m_effect.end();) {
			RECT rc_BazukaEffect = {
				(*Biter)->GetPos().x - 150,
				(*Biter)->GetPos().y - 150,
				(*Biter)->GetPos().x + 150,
				(*Biter)->GetPos().y + 150
			};
			if (rc_BazukaEffect.left < (*Eiter)->GetPos().x + (*Eiter)->GetTex()->info.Width / 2 &&
				rc_BazukaEffect.right >(*Eiter)->GetPos().x - (*Eiter)->GetTex()->info.Width / 2 &&
				rc_BazukaEffect.top < (*Eiter)->GetPos().y + (*Eiter)->GetTex()->info.Height / 2 &&
				rc_BazukaEffect.bottom >(*Eiter)->GetPos().y - (*Eiter)->GetTex()->info.Height / 2 &&
				!(*Eiter)->Getb_Dead() && (*Biter)->GetEndFrame() == 9 && (*Biter)->GetNowFrame() == 7 &&
				!(*Eiter)->GetBazukaHit()) {

				(*Eiter)->InputBazukaHit(true);
				int Hp = (*Eiter)->GetHp();
				if (Hp <= 0)
					b_Del = true;
				else {
					(*Eiter)->InputHp(Hp -= 3);
					(*Eiter)->InputHit(true);
				}

			}
			else {
				++Biter;
			}
		}
		if (b_Del) {
			(*Eiter)->InputDead(true);
		}
		else {
			++Eiter;
		}
	}

	for (auto iter = m_Octo.begin(); iter != m_Octo.end();) {
		if (PlayerPos.x - (*iter)->GetTex()->info.Width / 2 < (*iter)->GetPos().x &&
			PlayerPos.x + (*iter)->GetTex()->info.Width / 2> (*iter)->GetPos().x &&
			PlayerPos.y - (*iter)->GetTex()->info.Height / 2< (*iter)->GetPos().y &&
			PlayerPos.y + (*iter)->GetTex()->info.Height / 2> (*iter)->GetPos().y &&
			!player->GetColl()) {
			int Hp = player->GetHp();
			Hp -= (*iter)->GetAtk();
			player->InputHp(Hp);
			player->InputColl(true);
		}
		else
			++iter;
	}

	//문어 총알 충돌
	for (auto iter = m_OctoBullet.begin(); iter != m_OctoBullet.end();) {
		if (PlayerPos.x - 100 < (*iter)->GetPos().x &&
			PlayerPos.x + 100 > (*iter)->GetPos().x &&
			PlayerPos.y - 100 < (*iter)->GetPos().y &&
			PlayerPos.y + 100 > (*iter)->GetPos().y &&
			!player->GetColl()) {
			int Hp = player->GetHp();
			Hp -= 5;
			player->InputHp(Hp);
			player->InputColl(true);
			(*iter)->InputColl(true);
		}
		else
			++iter;
	}


	if (INPUT->KeyDown('M')) {
		for (auto iter : m_enemy)
			SAFE_DELETE(iter);
		m_enemy.clear();

		for (auto iter : m_Octo)
			SAFE_DELETE(iter);
		m_Octo.clear();
	}
}

void cEnemyAdmin::Render()
{
	for (auto iter : m_enemy) 
		iter->Render();

	for (auto iter : m_Octo)
		iter->Render();

	if (MouseColl)
		IMAGE->Render(m_Aim1, INPUT->GetMouseScrollPos(), 0, true);
	else
		IMAGE->Render(m_Aim2, INPUT->GetMouseScrollPos(), 0, true);
}

void cEnemyAdmin::Release()
{
	for (auto iter : m_enemy) 
		SAFE_DELETE(iter);

	m_enemy.clear();

	for (auto iter : m_Octo)
		SAFE_DELETE(iter);

	m_Octo.clear();

	SAFE_DELETE(Octo.m_Frame);
	SAFE_DELETE(Octo.m_AtkFrame);

	SAFE_DELETE(FishM.m_Frame);
	SAFE_DELETE(FishM.m_AtkFrame);

	SAFE_DELETE(FishF.m_Frame);
	SAFE_DELETE(FishF.m_AtkFrame);

	SAFE_DELETE(JFish.m_Frame);
	SAFE_DELETE(JFish.m_AtkFrame);

	SAFE_DELETE(OldShark.m_Frame);
	SAFE_DELETE(OldShark.m_AtkFrame);

	SAFE_DELETE(Shark.m_Frame);
	SAFE_DELETE(Shark.m_AtkFrame);

	SAFE_DELETE(Turtle.m_Frame);
	SAFE_DELETE(Turtle.m_AtkFrame);

	SAFE_DELETE(BigJFish.m_Frame);
	SAFE_DELETE(BigJFish.m_AtkFrame);

	SAFE_DELETE(AFish.m_Frame);
	SAFE_DELETE(AFish.m_AtkFrame);

	SAFE_DELETE(AFish2.m_Frame);
	SAFE_DELETE(AFish2.m_AtkFrame);
}
