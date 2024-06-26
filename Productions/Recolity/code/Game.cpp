#include "Game.h"
#include "fade.h"
#include "particlemanager.h"
#include "bullet_management.h"
#include "bullet_interface.h"
#include "collision_management.h"
#include "attribute_management.h"
#include "camera.h"
#include "card.h"
#include "carddatamanager.h"
#include "cardplaypdeckmanager.h"
#include "cardplaygetcardh.h"
#include "input.h"
#include "floor.h"
#include "LoadMapTex.h"
#include "sprite.h"
#include "light.h"
#include "DrawDamageManager.h"
#include <map>
#include "button.h"
#include "meshsky.h"
#include "sound.h"
#include "text.h"
std::map<std::string, Button> g_GameButton;
D3DXVECTOR2 g_GamewMousePos;
Particle_Manager g_Particle;
Bullet_Management g_Bullet;
Bullet_Interface g_BulletInter(&g_Bullet);
Enemy_Management g_EnemyManagement(&g_BulletInter);
Attribute_Management g_AttributeMangement;
Collision_Management g_CollisionManagement(g_EnemyManagement.GetEnemyList(), g_Bullet.GetBulletList(), &g_AttributeMangement);
DrawDmageManager g_DrawDamage;
PLAYER				g_player;
Light* g_Light;
StageScelect g_StageScelect = Tutorial;
Gamemode	 g_Gamemode = Nomal;
bool g_gamepose = false;
int g_bgm;
int g_EscSound;
int g_Crick;
int PressTimer = 0;

void InitGame(void) {
	// ライトを有効化
	g_Light = new Light;
	SetLightEnable(true);

	g_GameButton.emplace("メニュー", Button{ { SCREEN_WIDTH * 0.26f,SCREEN_HEIGHT - SCREEN_HEIGHT * 0.7f }, BASE_BUTTTON_SIZE });
	g_GameButton.emplace("コンテニュー", Button{ { SCREEN_WIDTH * 0.26f,SCREEN_HEIGHT - SCREEN_HEIGHT * 0.5f }, BASE_BUTTTON_SIZE });
	InitCamera();
	InitMeshSky(D3DXVECTOR3(0.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 25000.0f, 16, 8);
	InitFloor();
	InitCard();
	InitMapModelObject();
	LoadModelMap();
	g_Bullet.Init();
	g_Particle.Init();
	g_EnemyManagement.Init();
	g_DrawDamage.Init();
	g_player.Init();
	g_bgm = LoadSound("sgatebgm");
	g_EscSound = LoadSound("bottun1");
	g_Crick = LoadSound("bottun2");
	PlaySound(g_bgm, -1, 1.0f);
}
void UninitGame(void) {
	g_GameButton.clear();
	UninitCamera();
	UninitMeshSky();
	UnInitFloor();
	g_EnemyManagement.Uninit();
	g_Bullet.Uninit();
	UninitCard();
	g_DrawDamage.Uninit();
	g_player.Uninit();
	// ライトを無効化
	SetLightEnable(false);
	StopSoundAll();
	delete g_Light;
	
	//カーソルロックの解放
	CursprLock(false);
}
void UpdateGame(void) {
	if (IsMouseLeftPressed())
	{
		PressTimer++;
	}
	if (!IsMouseLeftPressed())
	{
		PressTimer = 0;
	}
	g_GamewMousePos = GetMousePos();

	if (g_gamepose == false && g_player.RefHp() > 0)
	{
		UpdateMeshSky();
		UpdateCard();
		UpdateCamera();
		UpdateFloor();
		if (GetCardflug() == false)
		{
			g_player.Update();
		}
		if (GetCardflug() == true)
		{
			g_player.ClerFlug();
		}

		g_EnemyManagement.Update();
		g_Bullet.Update();
		g_Particle.Update();
		g_CollisionManagement.Update();
		g_DrawDamage.Update();

	}
	if (g_player.RefHp() <= 0)
	{
		g_player.Update();
	}
	if (GetKeyboardTrigger(DIK_ESCAPE))
	{
		if (g_gamepose == false)
		{
			PlaySound(g_EscSound, 0, 1.0f);
		}
		
		g_gamepose = !g_gamepose;
		CursprLock(!g_gamepose);
	}
	if (g_gamepose)
	{
		CursprLock(!g_gamepose);
		if (g_GameButton.at("メニュー").IsPush(g_GamewMousePos, IsMouseLeftTriggered()))
		{
			g_gamepose = false;
			SceneTransition(SCENE_MENU);
		}

		if (g_GameButton.at("コンテニュー").IsPush(g_GamewMousePos, IsMouseLeftTriggered())) {
			g_gamepose = false;
			UninitGame();
			InitGame();
		}
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (GetMousePos().x > (float)i * 160.0f + 450.0f - 32.0f &&
					GetMousePos().x < (float)i * 160.0f + 450.0f + 32.0f &&
					GetMousePos().y >(float)j * 40.0f + 650.0f - 20.0f &&
					GetMousePos().y < (float)j * 40.0f + 650.0f + 20.0f &&
					IsMouseLeftTriggered())
				{
					if (j == 0)
					{
						SetVolumeAll(GetWolrdSound() - 0.01f + i * 0.02f);
					}
					if (j == 1)
					{
						SetVolumeKinds("SE", GetSESound() - 0.01f + i * 0.02f);
					}
					if (j == 2)
					{
						SetVolumeKinds("BGM", GetBGMSound() - 0.01f + i * 0.02f);
					}
					if (j == 3)
					{
						*GetMouseKando() += -0.1f + (float)i * 0.2f;
					}
					
					PlaySound(g_Crick, 0, 1.0f);
				}
				if (PressTimer> 15 && PressTimer % 6 == 0 &&
					GetMousePos().x > (float)i * 160.0f + 450.0f - 32.0f &&
					GetMousePos().x < (float)i * 160.0f + 450.0f + 32.0f &&
					GetMousePos().y >(float)j * 40.0f + 650.0f - 20.0f &&
					GetMousePos().y < (float)j * 40.0f + 650.0f + 20.0f 
					)
				{
					if (j == 0)
					{
						SetVolumeAll(GetWolrdSound() - 0.01f + i * 0.02f);
					}
					if (j == 1)
					{
						SetVolumeKinds("SE", GetSESound() - 0.01f + i * 0.02f);
					}
					if (j == 2)
					{
						SetVolumeKinds("BGM", GetBGMSound() - 0.01f + i * 0.02f);
					}
					if (j == 3)
					{
						*GetMouseKando() += -0.1f + (float)i * 0.2f;
					}

					PlaySound(g_Crick, 0, 1.0f);
				}
			}
		}
	}

}

void DrawGame(void) {
	SetCamera();
	DrawMapModelObject();
	DrawMeshSky();
	DrawFloor();
	DrawCard();
	g_player.Draw();
	g_Bullet.Draw();
	g_EnemyManagement.Draw();
	g_Particle.Draw();
	g_DrawDamage.Draw();
	g_player.Draw2D();
	DrawCard2D();

	if (g_gamepose)
	{
		UI poseui;
		poseui.m_Color = { 1.0f,1.0f ,1.0f ,1.0f };
		poseui.m_Pos = { 500,SCREEN_CENTER_Y -100};
		poseui.m_Uv_v = { 0.0f,0.0f };
		poseui.m_Uv_f = { 1.0f,1.0f };
		poseui.m_Scl = { 300.0f * 1.5f,512.0f * 1.5f };
		poseui.m_Rot = 0.0f;
		DrawScreen(poseui, RefImageMaterial().m_PoseUi);
		SetText({ poseui.m_Pos.x - 190.0f,poseui.m_Pos.y + 200.0f,SCREEN_WIDTH,SCREEN_HEIGHT }, "全体音量");
		SetText({ poseui.m_Pos.x - 190.0f,poseui.m_Pos.y + 240.0f,SCREEN_WIDTH,SCREEN_HEIGHT }, "効果音量");
		SetText({ poseui.m_Pos.x - 190.0f,poseui.m_Pos.y + 280.0f,SCREEN_WIDTH,SCREEN_HEIGHT }, "BGM");
		SetText({ poseui.m_Pos.x - 190.0f,poseui.m_Pos.y + 320.0f,SCREEN_WIDTH,SCREEN_HEIGHT }, "視点感度");

		SetText({ poseui.m_Pos.x + 15.0f,poseui.m_Pos.y + 200.0f,SCREEN_WIDTH,SCREEN_HEIGHT }, std::to_string((int)(GetWolrdSound() * 100.0f)));
		SetText({ poseui.m_Pos.x + 15.0f,poseui.m_Pos.y + 240.0f,SCREEN_WIDTH,SCREEN_HEIGHT }, std::to_string((int)(GetSESound() * 100.0f)));
		SetText({ poseui.m_Pos.x + 15.0f,poseui.m_Pos.y + 280.0f,SCREEN_WIDTH,SCREEN_HEIGHT }, std::to_string((int)(GetBGMSound() * 100.0f)));
		SetText({ poseui.m_Pos.x + 15.0f,poseui.m_Pos.y + 320.0f,SCREEN_WIDTH,SCREEN_HEIGHT }, std::to_string((int)(*GetMouseKando() * 10.0f)));
		poseui.m_Scl = { 64,40 };
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				poseui.m_Rot = D3DX_PI * (float)i + D3DX_PI;
				poseui.m_Pos = { (float)i * 160.0f + 450.0f,(float)j * 40.0f + 650.0f };
				DrawScreen(poseui, RefImageMaterial().m_SoundUi2);
				DrawScreen(poseui, RefImageMaterial().m_SoundUi1);
			}
		}
		UI ui = UI{ {0.0f,0.0f},{SCREEN_WIDTH, SCREEN_HEIGHT},{0.0f,0.0f},{1.0f,1.0f},DIK_COLER_DRAKGRAY,0.0f };
		ui = UI{ g_GameButton.at("メニュー").RefPos(),g_GameButton.at("メニュー").RefSize()
		,{0.0f,0.0f},{1.0f,1.0f},g_GameButton.at("メニュー").RefColor(),0.0f };
		DrawScreen(ui, RefImageMaterial().m_Button_Menu);
		ui = UI{ g_GameButton.at("コンテニュー").RefPos(),g_GameButton.at("コンテニュー").RefSize()
		,{0.0f,0.0f},{1.0f,1.0f},g_GameButton.at("コンテニュー").RefColor(),0.0f };
		DrawScreen(ui, RefImageMaterial().m_Button_ReStart);
		UI cursor = { D3DXVECTOR2(GetMousePos().x + 16,GetMousePos().y + 16) ,D3DXVECTOR2(32,32),D3DXVECTOR2(0.0f,0.0f),D3DXVECTOR2(1.0f ,1.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f) };
		DrawScreen(cursor, RefImageMaterial().m_Cursor);
	}
}

void Emitta(int n, D3DXVECTOR3 pos) {
	if (n == 0)
	{
		g_Particle.Brust(pos);
	}
	if (n == 1)
	{
		g_Particle.Brust3(pos);
	}
	if (n == 2)
	{
		g_Particle.SetCircleEffect(pos);
	}
	if (n == 3)
	{
		g_Particle.Brust2(pos);
	}
	if (n == 4)
	{
		g_Particle.Water1(pos);
	}
	if (n == 5)
	{
		g_Particle.Wind1(pos);
	}
	if (n == 6)
	{
		g_Particle.Pull1(pos);
	}
	if (n == 7)
	{
		g_Particle.Pull2(pos);
	}
	if (n == 8)
	{
		g_Particle.SetCircleEffect2(pos);
	}
	if (n == 9)
	{
		g_Particle.BossBlust(pos);
	}
	if (n == 10)
	{
		g_Particle.SetCircleEffect3(pos);
	}
}
void SetDamageText(int Damage, D3DXVECTOR3 pos, D3DXCOLOR coler) {

	g_DrawDamage.SetDamage(Damage, pos, coler);
}
Bullet_Interface* GetBulletInterface() {
	return &g_BulletInter;
}
PLAYER* GetPlayer() { return &g_player; }
Enemy_Management* GetEnemymanager() {
	return &g_EnemyManagement;
}
void SetStageScelect(StageScelect s) {
	g_StageScelect = s;
}

StageScelect GetStageSelect()
{
	return g_StageScelect;
}

void SetGamemode(Gamemode mode)
{
	g_Gamemode = mode;
}

Gamemode GetGamemode()
{
	return g_Gamemode;
}
