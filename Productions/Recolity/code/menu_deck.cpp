//=============================================================================
//
// デッキーメニュー画面処理 [menu_deck.cpp]
// Author : 
//
//=============================================================================
#include "menu_deck.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "fade.h"
#include "sound.h"
#include "material.h"
#include "button.h"
#include "card.h"
//*****************************************************************************
// グローバル変数
//*****************************************************************************
std::map<std::string, Button> g_MenuDeckButton;
D3DXVECTOR2 g_MenuDeckMousePos;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitMenuDeck(void)
{
	//ボタンの登録
	g_MenuDeckButton.emplace("メニュー", Button({ SCREEN_WIDTH * 0.15f,SCREEN_HEIGHT * 0.1f }, BASE_BUTTTON_SIZE));
  
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMenuDeck(void)
{
	g_MenuDeckButton.clear();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMenuDeck(void)
{
	//カーソルの座標取得
	g_MenuDeckMousePos = GetMousePos();
	Update_Menu_deck();
	//ボタンごとの処理
	if (g_MenuDeckButton.at("メニュー").IsPush(g_MenuDeckMousePos, IsMouseLeftTriggered()))
		SceneTransition(SCENE_MENU);

#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		SceneTransition(SCENE_MENU);
	}
#endif // _DEBUG
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMenuDeck(void)
{
	//背景
	UI ui = UI{ {0.0f,0.0f},{SCREEN_WIDTH, SCREEN_HEIGHT},{0.0f,0.0f},{1.0f,1.0f},DIK_COLER_WHITE,0.0f };
	DrawScreenLT(ui, RefImageMaterial().m_Menu_scenecard);
	Draw_Menu_deck();
	//タイトルボタン
	ui = UI{ g_MenuDeckButton.at("メニュー").RefPos(),g_MenuDeckButton.at("メニュー").RefSize()
		,{0.0f,0.0f},{1.0f,1.0f},g_MenuDeckButton.at("メニュー").RefColor(),0.0f };
	DrawScreen(ui, RefImageMaterial().m_Button_Menu);

	//カーソル
	ui = UI{ g_MenuDeckMousePos,{50,50},{0.0f,0.0f},{1.0f,1.0f},DIK_COLER_WHITE,0.0f };
	DrawScreen(ui, RefImageMaterial().m_Reticle);
}