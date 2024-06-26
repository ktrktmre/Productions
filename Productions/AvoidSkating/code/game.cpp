//=============================================================================
//
// ゲーム処理 [gamen.h]
// Author : 切田海畝斗
//
//=============================================================================

#include "game.h"
#include "main.h"
#include "input.h"
#include "sprite.h"
#include "fade.h"
#include "player.h"
#include "meshfield.h"
#include "meshsky.h"
#include "sound.h"
#include "camera.h"
#include "shadow.h"
#include "object_manager.h"
#include "light.h"
#include "enemy_manager.h"
#include "item_manager.h"


/*------------------------------------------------------------------------------
   グローバル変数の定義
------------------------------------------------------------------------------*/
static int g_BGMNo = 0;
bool g_Pause = false;
UINT32 CurrentSample = 0;
Player* g_Player;
Object_Manager* g_ObjectManager;
Field* g_Field;
Sky* g_Sky;
Light* g_Light;
Enemy_Manager* g_EnemyManager;
Item_Manager* g_ItemManager;


/*------------------------------------------------------------------------------
   初期化関数
------------------------------------------------------------------------------*/
void InitGame(void)
{
	// 地面の初期化
	g_Field = new Field(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 0.0f, 500.0f), 3, 100);

	// 空の初期化
	g_Sky = new Sky(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 4000.0f, 16, 8, false);

	// プレイヤーの初期化
	g_Player = new Player;

	// オブジェクトマネージャーの初期化
	g_ObjectManager = new Object_Manager(g_Player);

	// エネミーマネージャーの初期化
	g_EnemyManager = new Enemy_Manager(g_ObjectManager);

	// アイテムマネージャーの初期化
	g_ItemManager = new Item_Manager(g_ObjectManager);

	// ライトの初期化
	g_Light = new Light;

	SetLightEnable(true);

	SetAlphaTestEnable(false);

	PlaySound("game_bgm", -1, 0.2f, 0);
}

/*------------------------------------------------------------------------------
   終了処理をする関数
------------------------------------------------------------------------------*/
void UninitGame()
{
	StopSoundAll();
	//初期化とは逆順に終了処理を行う
	delete g_Light;
	delete g_ItemManager;
	delete g_EnemyManager;
	delete g_ObjectManager;
	delete g_Sky;
	delete g_Field;

}

/*------------------------------------------------------------------------------
   更新処理をする関数
------------------------------------------------------------------------------*/
void UpdateGame(void)
{
	GetCamera()->Update();
	g_Field->Update();
	g_Sky->Update();
	g_ItemManager->Update();
	g_EnemyManager->Update();
	g_ObjectManager->Update();

#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_RETURN) && GetFadeState() == FADE_NONE)
	{
		SceneTransition(SCENE_RESULT);
	}
#endif // _DEBUG
}

/*------------------------------------------------------------------------------
   描画処理をする関数
------------------------------------------------------------------------------*/
void DrawGame(void)
{
	// プレイヤー視点
	D3DXVECTOR3 pos = g_Player->RefPos();
	pos.y = 0.0f;			// カメラ酔いを防ぐためにクリアしている
	GetCamera()->SetCameraAT(pos);
	GetCamera()->SetCamera();

	// 深度テスト有効
	SetDepthEnable(true);

	// 地面の描画処理
	g_Sky->Draw();
	g_Field->Draw();

	g_ObjectManager->Draw();
}

