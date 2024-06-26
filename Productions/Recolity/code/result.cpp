//=============================================================================
//
// リザルト画面処理 [result.cpp]
// Author : 
//
//=============================================================================
#include <map>
#include "result.h"
#include "texture.h"
#include "sprite.h"
#include "fade.h"
#include "material.h"
#include "input.h"
#include "sound.h"
#include "title.h"
#include "button.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
std::map<std::string, Button> g_ResultButton;
D3DXVECTOR2 g_ResultMousePos;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitResult(void)
{
	g_ResultButton.emplace("タイトル", Button({ SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT - 300 }, { 500,150 }));

	PlaySound("menu", -1, 1.0f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResult(void)
{
	g_ResultButton.clear();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResult(void)
{
	//カーソルの座標取得
	g_ResultMousePos = GetMousePos();

	if (g_ResultButton.at("タイトル").IsPush(g_ResultMousePos, IsMouseLeftTriggered()))
		SceneTransition(SCENE_TITLE);

#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_RETURN) && GetFadeState() == FADE_NONE)
	{
		SceneTransition(SCENE_TITLE);
	}
#endif // _DEBUG
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawResult(void)
{
	UI ui = UI{ {0.0f,0.0f},{SCREEN_WIDTH, SCREEN_HEIGHT},{0.0f,0.0f},{1.0f,1.0f},{1.0f,1.0f,1.0f,1.0f},0.0f };
	DrawScreenLT(ui, RefImageMaterial().m_BackGround);

	//タイトルボタン
	ui = UI{ g_ResultButton.at("タイトル").RefPos(),g_ResultButton.at("タイトル").RefSize()
		,{0.0f,0.0f},{1.0f,1.0f},g_ResultButton.at("タイトル").RefColor(),0.0f };
	DrawScreen(ui, RefImageMaterial().m_Button_Title);

	//タイトルボタン
	ui = UI{ {SCREEN_WIDTH * 0.5f, 400.0f},{519.0f,308.0f}
		,{0.0f,0.0f},{1.0f,1.0f},{1.0f,1.0f,1.0f,1.0f},0.0f };
	DrawScreen(ui, RefImageMaterial().m_StageClear);

	//カーソル
	ui = UI{ g_ResultMousePos,{50,50},{0.0f,0.0f},{1.0f,1.0f},DIK_COLER_WHITE,0.0f };
	DrawScreen(ui, RefImageMaterial().m_Reticle);
}
