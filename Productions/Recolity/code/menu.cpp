//=============================================================================
//
// メニュー画面処理 [menu.cpp]
// Author : 
//
//=============================================================================
#include "menu.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "fade.h"
#include "sound.h"
#include "material.h"
#include "button.h"
#include "title.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
std::map<std::string, Button> g_MenuButton;
D3DXVECTOR2 g_MenuMousePos;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitMenu(void)
{
	//ボタンの登録
	g_MenuButton.emplace("ステージ", Button({ SCREEN_WIDTH * 0.3f,SCREEN_HEIGHT * 0.25f }, { 500,150 }));
	g_MenuButton.emplace("タイトル", Button({ SCREEN_WIDTH * 0.3f,SCREEN_HEIGHT * 0.5f }, { 500,150 }));
	g_MenuButton.emplace("デッキ", Button({ SCREEN_WIDTH * 0.3f,SCREEN_HEIGHT * 0.75f }, { 500,150 }));

	ResumeSound("menu");

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMenu(void)
{
	g_MenuButton.clear();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMenu(void)
{
	//カーソルの座標取得
	g_MenuMousePos = GetMousePos();

	//ボタンごとの処理
	if (g_MenuButton.at("ステージ").IsPush(g_MenuMousePos, IsMouseLeftTriggered()))
		SceneTransition(SCENE_STAGE);
	if (g_MenuButton.at("タイトル").IsPush(g_MenuMousePos, IsMouseLeftTriggered()))
		SceneTransition(SCENE_TITLE);
	if (g_MenuButton.at("デッキ").IsPush(g_MenuMousePos, IsMouseLeftTriggered()))
		SceneTransition(SCENE_DECK);

#ifdef _DEBUG
	//デバック用シーン遷移
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		SceneTransition(SCENE_GAME);
	}
#endif // _DEBUG
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMenu(void)
{
	//背景
	UI ui = UI{ {0.0f,0.0f},{SCREEN_WIDTH, SCREEN_HEIGHT},{0.0f,0.0f},{1.0f,1.0f},DIK_COLER_WHITE,0.0f };
	DrawScreenLT(ui, RefImageMaterial().m_BackGround);

	//ゲームボタン
	ui = UI{ g_MenuButton.at("ステージ").RefPos(),g_MenuButton.at("ステージ").RefSize()
		,{0.0f,0.0f},{1.0f,1.0f},g_MenuButton.at("ステージ").RefColor(),0.0f };
	DrawScreen(ui, RefImageMaterial().m_Button_Stage);

	//タイトルボタン
	ui = UI{ g_MenuButton.at("タイトル").RefPos(),g_MenuButton.at("タイトル").RefSize()
		,{0.0f,0.0f},{1.0f,1.0f},g_MenuButton.at("タイトル").RefColor(),0.0f };
	DrawScreen(ui, RefImageMaterial().m_Button_Title);

	//デッキボタン
	ui = UI{ g_MenuButton.at("デッキ").RefPos(),g_MenuButton.at("デッキ").RefSize()
		,{0.0f,0.0f},{1.0f,1.0f},g_MenuButton.at("デッキ").RefColor(),0.0f };
	DrawScreen(ui, RefImageMaterial().m_Button_Deck);

	//カーソル
	ui = UI{ g_MenuMousePos,{50,50},{0.0f,0.0f},{1.0f,1.0f},DIK_COLER_WHITE,0.0f };
	DrawScreen(ui, RefImageMaterial().m_Reticle);
}