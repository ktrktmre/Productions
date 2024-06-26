//=============================================================================
//
// 絵素材処理 [material.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "material.h"
#include "Texture.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
Model_Material g_Model_Material;
Image_Material g_Image_Material;

//=============================================================================
// 初期化処理
//=============================================================================
void LoadMaterial(void)
{
	//objモデルの読み込み
	LoadModel((char*)"data/MODEL/normalenemy.obj", &g_Model_Material.m_Normal_Enemy);
	LoadModel((char*)"data/MODEL/patrolenemy.obj", &g_Model_Material.m_Patrol_Enemy);
	LoadModel((char*)"data/MODEL/bulletenemy.obj", &g_Model_Material.m_Bullet_Enemy);
	LoadModel((char*)"data/MODEL/boss.obj", &g_Model_Material.m_Boss);
	LoadModel((char*)"data/MODEL/boss2.obj", &g_Model_Material.m_Boss2);
	LoadModel((char*)"data/MODEL/MOB_Scorpion_main.obj", &g_Model_Material.m_Scorpion);
	LoadModel((char*)"data/MODEL/MOB_Scorpion_Leg.obj", &g_Model_Material.m_Scorpion_Leg);
	LoadModel((char*)"data/MODEL/MOB_Scorpion_Tail.obj", &g_Model_Material.m_Scorpion_Tail);
	LoadModel((char*)"data/MODEL/MOB_moth_Body.obj", &g_Model_Material.m_Moth);
	LoadModel((char*)"data/MODEL/MOB_moth_WingL.obj", &g_Model_Material.m_Moth_WingL);
	LoadModel((char*)"data/MODEL/MOB_moth_WingR.obj", &g_Model_Material.m_Moth_WingR);
	LoadModel((char*)"data/MODEL/MOB_Spider_body.obj", &g_Model_Material.m_Spider);
	LoadModel((char*)"data/MODEL/MOB_Spider_leg.obj", &g_Model_Material.m_Spider_Leg);
	LoadModel((char*)"data/MODEL/yazirusi.obj", &g_Model_Material.m_Normal_Bullet);
	LoadModel((char*)"data/MODEL/sphere.obj", &g_Model_Material.m_Sphere);
	LoadModel((char*)"data/MODEL/darddai.obj", &g_Model_Material.m_Carddai);
	LoadModel((char*)"data/MODEL/carddai_card.obj", &g_Model_Material.m_Carddai_Card);
	LoadModel((char*)"data/MODEL/damage_circle.obj", &g_Model_Material.m_Damage_Circle);
	LoadModel((char*)"data/MODEL/cardboard1.obj", &g_Model_Material.m_CardBoard1);
	LoadModel((char*)"data/MODEL/cardboard2.obj", &g_Model_Material.m_CardBoard2);
	LoadModel((char*)"data/MODEL/haguruma.obj", &g_Model_Material.m_Haguruma);
	LoadModel((char*)"data/MODEL/haguruma_hontai.obj", &g_Model_Material.m_Haguruma_Hontai);
	LoadModel((char*)"data/MODEL/bulletenemy_00_00.obj", &g_Model_Material.m_Bullet_Enemy_01);
	LoadModel((char*)"data/MODEL/kama.obj", &g_Model_Material.m_Kama);
	LoadModel((char*)"data/MODEL/BosHand_La.obj", &g_Model_Material.m_Boss2_Hand_L);
	const char* ModelFilePath = "data/LoadMODEL.txt";  // 保存先ファイルパス
	std::string LoadModel_[64] = {};  // 保存先ファイルパス
	std::ifstream ifsm(ModelFilePath);
	if (ifsm.is_open())
	{

		for (int i = 0; i < 64; i++)
		{
			std::string text;
			ifsm >> text;
			if (text != "")
			{
				LoadModel_[i] = "data/MODEL/";
				LoadModel_[i] += text.c_str();
			}
		}
		ifsm.close();
	}
	for (int i = 0; i < 64; i++)
	{
		if (LoadModel_[i] != "")
		{
			LoadModel((char*)LoadModel_[i].c_str(), &g_Model_Material.MapModel[i]);
		}
	}

	//画像の読み込み
	g_Image_Material.m_Reticle = LoadTexture((char*)"data/TEXTURE/Reticle1.png");
	g_Image_Material.m_White_Square = LoadTexture((char*)"data/TEXTURE/white.png");
	g_Image_Material.m_Cannon_Bullet = LoadTexture((char*)"data/TEXTURE/fireball.png");
	g_Image_Material.m_Flame = LoadTexture((char*)"data/TEXTURE/flame.png");//パーティクル
	g_Image_Material.m_Title = LoadTexture((char*)"data/TEXTURE/title.png");
	g_Image_Material.m_Result = LoadTexture((char*)"data/TEXTURE/result.png");
	g_Image_Material.m_BackGround = LoadTexture((char*)"data/TEXTURE/back_ground.png");
	g_Image_Material.m_ClickToStart = LoadTexture((char*)"data/TEXTURE/CLICK_TO_START.png");
	g_Image_Material.m_HpFrame = LoadTexture((char*)"data/TEXTURE/hpberflame.png");
	g_Image_Material.m_Hp = LoadTexture((char*)"data/TEXTURE/hpber.png");
	g_Image_Material.m_Fade = LoadTexture((char*)"data/TEXTURE/fade_white.png");
	g_Image_Material.m_Star = LoadTexture((char*)"data/TEXTURE/star_set.png");//カードの星
	g_Image_Material.m_CardFlame = LoadTexture((char*)"data/TEXTURE/FrameSet.png");
	g_Image_Material.m_Boss_Bullet= LoadTexture((char*)"data/TEXTURE/boss_bullet.png");
	g_Image_Material.m_Menu_scenecard = LoadTexture((char*)"data/TEXTURE/card_menu.png");
	g_Image_Material.m_Crystal = LoadTexture((char*)"data/TEXTURE/cristal.png");
	g_Image_Material.m_EasyIcon = LoadTexture((char*)"data/TEXTURE/easy.png");
	g_Image_Material.m_NomalIcon = LoadTexture((char*)"data/TEXTURE/normal.png");
	g_Image_Material.m_HardIcon = LoadTexture((char*)"data/TEXTURE/hard.png");

	g_Image_Material.m_Suzi = LoadTexture((char*)"data/TEXTURE/suuzi.png");//ダメージ
	g_Image_Material.m_Cursor = LoadTexture((char*)"data/TEXTURE/corsortex.png");
	g_Image_Material.m_Floor_Image_paper = LoadTexture((char*)"data/TEXTURE/tilepaper2.png");//タイル
	g_Image_Material.m_Floor_Image_paper_flame = LoadTexture((char*)"data/TEXTURE/tilepaper2fire.png");//タイル
	g_Image_Material.m_Floor_Image_paper_water = LoadTexture((char*)"data/TEXTURE/tilepaperwater.png");//タイル
	g_Image_Material.m_Card_startex = LoadTexture((char*)"data/TEXTURE/star_set.png");//カードの星
	g_Image_Material.m_Card_flame = LoadTexture((char*)"data/TEXTURE/FrameSet.png");//カードの外枠


	g_Image_Material.m_SingleFire = LoadTexture((char*)"data/TEXTURE/Bullet_Shot_Fire.png");//火単発
	g_Image_Material.m_Card_Bullet_Single_Water = LoadTexture((char*)"data/TEXTURE/Bullet_Shot_Water.png");//水単発
	g_Image_Material.m_Card_Bullet_Single_Wind = LoadTexture((char*)"data/TEXTURE/Bullet_Shot_Wind.png");//風単発

	g_Image_Material.m_RapidFire = LoadTexture((char*)"data/TEXTURE/Bullet_Rapid_Fire.png");//火連射
	g_Image_Material.m_Card_Bullet_Rapid_Water = LoadTexture((char*)"data/TEXTURE/Bullet_Rapid_Water.png");//水連射
	g_Image_Material.m_Card_Bullet_Rapid_Wind = LoadTexture((char*)"data/TEXTURE/Bullet_Rapid_Wind.png");//風連射

	g_Image_Material.m_Card_Bullet_Circle_Fire = LoadTexture((char*)"data/TEXTURE/Bullet_Circle_Fire.png");//火範囲
	g_Image_Material.m_Card_Bullet_Circle_Water = LoadTexture((char*)"data/TEXTURE/Bullet_Circle_Watar.png");//水範囲
	g_Image_Material.m_Card_Bullet_Circle_Wind = LoadTexture((char*)"data/TEXTURE/Bullet_Circle_Wind.png");//風範囲

	g_Image_Material.m_Card_Bullet_Slug_Water = LoadTexture((char*)"data/TEXTURE/Bullet_ShotGun_Watar.png");//水ショットガン	
	g_Image_Material.m_Card_Bullet_Slug_Wind = LoadTexture((char*)"data/TEXTURE/Bullet_ShotGun_Wind.png");//風ショットガン	
	g_Image_Material.m_Card_Bullet_Slug_Fire = LoadTexture((char*)"data/TEXTURE/Bullet_ShotGun_Fire.png");//火ショットガン

	g_Image_Material.m_Card_Bullet_Fun_Fire = LoadTexture((char*)"data/TEXTURE/Bullet_Fan_Fire.png"); //火扇
	g_Image_Material.m_Card_Bullet_Fun_Water = LoadTexture((char*)"data/TEXTURE/Bullet_Fan_Water.png");//水扇
	g_Image_Material.m_Card_Bullet_Fun_Wind = LoadTexture((char*)"data/TEXTURE/Bullet_Fan_Wind.png");//風扇

	g_Image_Material.m_Card_Heal_Moment = LoadTexture((char*)"data/TEXTURE/Heal.png");//回復
	g_Image_Material.m_Card_Heal_Regen = LoadTexture((char*)"data/TEXTURE/Regene.png");//回復
	g_Image_Material.m_Eye = LoadTexture((char*)"data/TEXTURE/eye.png");//エネミーの目
	g_Image_Material.BossCard_7boll = LoadTexture((char*)"data/TEXTURE/7boll.png");
	g_Image_Material.BossCard_Blast = LoadTexture((char*)"data/TEXTURE/card_linebom_low.png");
	g_Image_Material.BossCard_Firelain = LoadTexture((char*)"data/TEXTURE/framelain.png");
	g_Image_Material.BossCard_Hook = LoadTexture((char*)"data/TEXTURE/hook_low.png");
	g_Image_Material.m_Blast = LoadTexture((char*)"data/TEXTURE/blust.png");
	g_Image_Material.m_Blast2 = LoadTexture((char*)"data/TEXTURE/blast.png");
	g_Image_Material.m_PoseUi = LoadTexture((char*)"data/TEXTURE/posewindow.png");
	g_Image_Material.m_Button_ReStart = LoadTexture((char*)"data/TEXTURE/button_continue.png");
	g_Image_Material.m_SoundUi1 = LoadTexture((char*)"data/TEXTURE/soundicon1.png");
	g_Image_Material.m_SoundUi2 = LoadTexture((char*)"data/TEXTURE/soundicon2.png");
	g_Image_Material.m_Wind_Bullet = LoadTexture((char*)"data/TEXTURE/wind_bullet.png");
	g_Image_Material.m_Water_Bullet = LoadTexture((char*)"data/TEXTURE/waterball.png");
	g_Image_Material.m_Bossber = LoadTexture((char*)"data/TEXTURE/bossber.png");
	g_Image_Material.m_Bossber2 = LoadTexture((char*)"data/TEXTURE/bossber2.png");
	g_Image_Material.ScelectAneme = LoadTexture((char*)"data/TEXTURE/scelect8.png");
	const char* MapFilePath = "data/LoadTEXTURE.txt";  // 保存先ファイルパス
	std::string Loadtex[8] = { "","" ,"" ,"" ,"" ,"" ,"" ,"" };  // 保存先ファイルパス
	std::ifstream ifs(MapFilePath);
	if (ifs.is_open())
	{

		for (int i = 0; i < 8; i++)
		{
			std::string text;
			ifs >> text;
			if (text != "")
			{
				Loadtex[i] = "data/TEXTURE/";
				Loadtex[i] += text.c_str();
			}
		}
		ifs.close();
	}
	for (int i = 0; i < 8; i++)
	{
		if (Loadtex[i] != "")
		{
			g_Image_Material.Floor_Image[i] = LoadTexture((char*)Loadtex[i].c_str());
		}
	}

	g_Image_Material.m_Button_Title = LoadTexture((char*)"data/TEXTURE/button_title.png");
	g_Image_Material.m_Button_Stage = LoadTexture((char*)"data/TEXTURE/button_stage.png");
	g_Image_Material.m_Button_Menu = LoadTexture((char*)"data/TEXTURE/button_menu.png");
	g_Image_Material.m_Button_Deck = LoadTexture((char*)"data/TEXTURE/button_deck.png");
	g_Image_Material.m_Button_Start = LoadTexture((char*)"data/TEXTURE/button_start.png");
	g_Image_Material.m_Sky = LoadTexture((char*)"data/TEXTURE/sky.png");
	g_Image_Material.m_Tutorial = LoadTexture((char*)"data/TEXTURE/tutorial.png");
	g_Image_Material.m_Stage_1 = LoadTexture((char*)"data/TEXTURE/stage_1.png");
	g_Image_Material.m_Stage_2 = LoadTexture((char*)"data/TEXTURE/stage_2.png");
	g_Image_Material.m_MiniMapFrame = LoadTexture((char*)"data/TEXTURE/circle_frame.png");
	g_Image_Material.m_MiniMap_1 = LoadTexture((char*)"data/TEXTURE/map.png");
	g_Image_Material.m_MiniMap_2 = LoadTexture((char*)"data/TEXTURE/map3.png");
	g_Image_Material.m_sasori_bullet = LoadTexture((char*)"data/TEXTURE/sasoribullet.png");
	g_Image_Material.m_Kumo_bullet = LoadTexture((char*)"data/TEXTURE/spider_bullet.png");
	g_Image_Material.m_StageClear = LoadTexture((char*)"data/TEXTURE/stage_clear.png");
	g_Image_Material.m_EnemyBulletCannon = LoadTexture((char*)"data/TEXTURE/Enemy_.Bullet_Cannon.png");
	g_Image_Material.m_EnemyBulletTriangle = LoadTexture((char*)"data/TEXTURE/Enemy_.Bullet_Tryangle.png");
}

//=============================================================================
// 終了処理
//=============================================================================
void ReleaseMaterial(void)
{
	//終了処理
	//objモデルの解放
	UnloadModel(&g_Model_Material.m_Normal_Enemy);
	UnloadModel(&g_Model_Material.m_Patrol_Enemy);
	UnloadModel(&g_Model_Material.m_Bullet_Enemy);
	UnloadModel(&g_Model_Material.m_Boss);
	UnloadModel(&g_Model_Material.m_Boss2);
	UnloadModel(&g_Model_Material.m_Scorpion);
	UnloadModel(&g_Model_Material.m_Scorpion_Leg);
	UnloadModel(&g_Model_Material.m_Scorpion_Tail);
	UnloadModel(&g_Model_Material.m_Moth);
	UnloadModel(&g_Model_Material.m_Moth_WingL);
	UnloadModel(&g_Model_Material.m_Moth_WingR);
	UnloadModel(&g_Model_Material.m_Spider);
	UnloadModel(&g_Model_Material.m_Spider_Leg);
	UnloadModel(&g_Model_Material.m_Normal_Bullet);
	UnloadModel(&g_Model_Material.m_Sphere);
	UnloadModel(&g_Model_Material.m_Carddai);
	UnloadModel(&g_Model_Material.m_Carddai_Card);
	UnloadModel(&g_Model_Material.m_Damage_Circle);
	UnloadModel(&g_Model_Material.m_CardBoard1);
	UnloadModel(&g_Model_Material.m_CardBoard2);
	UnloadModel(&g_Model_Material.m_Haguruma);
	UnloadModel(&g_Model_Material.m_Haguruma_Hontai);
	UnloadModel(&g_Model_Material.m_Bullet_Enemy_01);
	UnloadModel(&g_Model_Material.m_Kama);
	UnloadModel(&g_Model_Material.m_Boss2_Hand_L);
	for (int i = 0; i < 64; i++)
	{
		UnloadModel(&g_Model_Material.MapModel[i]);
	}
}

//=============================================================================
// モデル構造体のゲッター
//=============================================================================
Model_Material& RefModelMaterial(void)
{
	return g_Model_Material;
}

//=============================================================================
// イメージ構造体のゲッター
//=============================================================================
Image_Material& RefImageMaterial(void)
{
	return g_Image_Material;
}