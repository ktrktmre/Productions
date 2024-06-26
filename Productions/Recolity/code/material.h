//=============================================================================
//
// 絵素材処理 [material.h]
// Author : 
//
//=============================================================================
#ifndef _MATERIAL_H_
#define _MATERIAL_H_
#pragma once

#include <d3dx9.h>
#include "renderer.h"
#include "model.h"

//*****************************************************************************
// マクロ定義   
//*****************************************************************************

//*****************************************************************************
// 構造体宣言   
//*****************************************************************************
struct Model_Material
{
	DX11_MODEL m_Normal_Enemy;
	DX11_MODEL m_Patrol_Enemy;
	DX11_MODEL m_Bullet_Enemy;
	DX11_MODEL m_Boss;
	DX11_MODEL m_Boss2;
	DX11_MODEL m_Boss2_Hand_R;
	DX11_MODEL m_Boss2_Hand_L;
	DX11_MODEL m_Scorpion;
	DX11_MODEL m_Scorpion_Leg;
	DX11_MODEL m_Scorpion_Tail;
	DX11_MODEL m_Moth;
	DX11_MODEL m_Moth_WingL;
	DX11_MODEL m_Moth_WingR;
	DX11_MODEL m_Spider;
	DX11_MODEL m_Spider_Leg;
	DX11_MODEL m_Normal_Bullet;
	DX11_MODEL m_Sphere;
	DX11_MODEL m_Carddai;
	DX11_MODEL m_Carddai_Card;
	DX11_MODEL m_Damage_Circle;
	DX11_MODEL m_Kama;
	DX11_MODEL m_Bullet_Enemy_01;
	DX11_MODEL m_Haguruma;
	DX11_MODEL m_Haguruma_Hontai;
	DX11_MODEL m_CardBoard1;
	DX11_MODEL m_CardBoard2;
	DX11_MODEL MapModel[64];//モデルの読み込み  
};

struct Image_Material
{
	int m_EasyIcon;
	int m_NomalIcon;
	int m_HardIcon;
	int m_Bossber;
	int m_Bossber2;
	int m_Reticle;
	int m_White_Square;
	int m_Cannon_Bullet;
	int m_Wind_Bullet;
	int m_Water_Bullet;
	int m_Flame;
	int m_Title;
	int m_Result;
	int m_BackGround;
	int m_ClickToStart;
	int m_HpFrame;
	int m_Hp;
	int m_Fade;
	int m_Star;
	int m_CardFlame;
	int m_SingleFire;
	int m_RapidFire;
	int m_Crystal;
	int m_Eye;
	int m_Boss_Bullet;
	int m_Suzi;
	int m_Cursor;
	int m_Floor_Image_paper;
	int m_Floor_Image_paper_flame;
	int m_Floor_Image_paper_water;
	int m_Card_Bullet_Circle_Fire;
	int m_Card_Bullet_Fun_Fire;
	int m_Card_Bullet_Slug_Fire;
	int m_Card_Bullet_Single_Water;//単発:水 
	int m_Card_Bullet_Rapid_Water;//連射:水 
	int m_Card_Bullet_Circle_Water;//全方位:水 
	int m_Card_Bullet_Fun_Water;//扇:水 
	int m_Card_Bullet_Slug_Water;//ショットガン:水 
	int m_Card_Bullet_Single_Wind;//単発:風 
	int m_Card_Bullet_Rapid_Wind;//連射:水 
	int m_Card_Bullet_Circle_Wind;//全方位:水 
	int m_Card_Bullet_Fun_Wind;//扇:水 
	int m_Card_Bullet_Slug_Wind;//ショットガン:水 
	int m_Card_Heal_Moment;
	int m_Card_Heal_Regen;
	int m_Card_startex;
	int m_Card_flame;
	int Floor_Image[8] = { -1, -1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 };
	int BossCard_Firelain;
	int BossCard_Hook;
	int BossCard_7boll;
	int BossCard_Blast;
	int m_Menu_scenecard;
	int m_Button_Title;
	int m_Button_Stage;
	int m_Button_Menu;
	int m_Button_Deck;
	int m_Button_Start;
	int m_Button_ReStart;
	int m_Blast;
	int m_Blast2;
	int m_PoseUi;
	int m_SoundUi1;
	int m_SoundUi2;
	int m_Sky;
	int m_Tutorial;
	int m_Stage_1;
	int m_Stage_2;
	int m_MiniMapFrame;
	int m_MiniMap_1;
	int m_MiniMap_2;
	int ScelectAneme;
	int m_sasori_bullet;
	int m_Kumo_bullet;
	int m_StageClear;
	int m_EnemyBulletCannon;
	int m_EnemyBulletTriangle;
};

//*****************************************************************************
// プロトタイプ宣言 
//*****************************************************************************
void LoadMaterial(void);
void ReleaseMaterial(void);
Model_Material& RefModelMaterial(void);
Image_Material& RefImageMaterial(void);

#endif // !_MATERIAL_H_



