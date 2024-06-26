//=============================================================================
//
// 操作説明画面処理 [explanation.cpp]
// Author : 切田海畝斗
//
//=============================================================================
#include "explanation.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "material.h"
#include "fade.h"
#include "sound.h"
#include "cursor.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BUTTON_SIZE_X	(BASE_BUTTON_SIZE_X*0.7f)
#define BUTTON_SIZE_Y	(BASE_BUTTON_SIZE_Y*0.7f)
#define BUTTON_HSIZE_X	(BUTTON_SIZE_X*0.5f)
#define BUTTON_HSIZE_Y	(BUTTON_SIZE_Y*0.5f)

//*****************************************************************************
// 列挙体宣言
//*****************************************************************************
enum Page {
	rule,
	operation
};

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Cursor* g_EcplanCursor;
Page g_Page;
D3DXVECTOR2 g_TitlePos;
D3DXVECTOR2 g_TurnOverPos;
bool g_Title;
bool g_TurnOver;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitExplanation(void)
{
	g_EcplanCursor = new Cursor;

	g_Page = rule;

	g_TitlePos = { BUTTON_HSIZE_X + 10.0f ,BUTTON_HSIZE_Y + 10.0f };
	g_TurnOverPos = { SCREEN_WIDTH - BUTTON_HSIZE_X - 20.0f ,SCREEN_HEIGHT - BUTTON_HSIZE_Y - 20.0f };

	g_Title = false;
	g_TurnOver = false;

	PlaySound("title_bgm", -1, 0.2f, 0);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitExplanation(void)
{
	StopSoundAll();
	delete g_EcplanCursor;
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateExplanation(void)
{
	g_EcplanCursor->MoveCursor(VALUE_CURSOR);

	g_TurnOver = false;
	if (g_EcplanCursor->RefCorsor().x >= (g_TurnOverPos.x - BUTTON_HSIZE_X) && g_EcplanCursor->RefCorsor().x <= (g_TurnOverPos.x + BUTTON_HSIZE_X) &&
		g_EcplanCursor->RefCorsor().y <= (g_TurnOverPos.y + BUTTON_HSIZE_Y) && g_EcplanCursor->RefCorsor().y >= (g_TurnOverPos.y - BUTTON_HSIZE_Y))
		g_TurnOver = true;

	if (IsMouseLeftTriggered() && g_TurnOver) {

		g_Page = g_Page == rule ? operation : rule;
	}

	g_Title = false;
	if (g_EcplanCursor->RefCorsor().x >= (g_TitlePos.x - BUTTON_HSIZE_X) && g_EcplanCursor->RefCorsor().x <= (g_TitlePos.x + BUTTON_HSIZE_X) &&
		g_EcplanCursor->RefCorsor().y <= (g_TitlePos.y + BUTTON_HSIZE_Y) && g_EcplanCursor->RefCorsor().y >= (g_TitlePos.y - BUTTON_HSIZE_Y))
		g_Title = true;

	if (IsMouseLeftTriggered() && g_Title && GetFadeState() == FADE_NONE)
	{
		SceneTransition(SCENE_TITLE);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawExplanation(void)
{
	D3DXCOLOR color;
	if (g_Page == rule) {
		DrawScreenLT(UI{ { 0.0f,0.0f }, 0, { SCREEN_WIDTH, SCREEN_HEIGHT },  { 0.0f, 0.0f}, {1.0f, 1.0f,}, DEF_COLOR },
			RefImageMaterial().m_Rule);
		color = g_TurnOver ? D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f) : D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		DrawScreen(UI{ g_TurnOverPos , 0, { BUTTON_SIZE_X, BUTTON_SIZE_Y },  { 0.0f, 0.0f}, {1.0f, 1.0f,}, color },
			RefImageMaterial().m_Next);
	}
	else if (g_Page == operation) {
		DrawScreenLT(UI{ { 0.0f,0.0f }, 0, { SCREEN_WIDTH, SCREEN_HEIGHT },  { 0.0f, 0.0f}, {1.0f, 1.0f,}, DEF_COLOR },
			RefImageMaterial().m_Operation);
		color = g_TurnOver ? D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f) : D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		DrawScreen(UI{ g_TurnOverPos , 0, { BUTTON_SIZE_X, BUTTON_SIZE_Y },  { 0.0f, 0.0f}, {1.0f, 1.0f,}, color },
			RefImageMaterial().m_Return);
	}

	color = g_Title ? D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f) : D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	DrawScreen(UI{ g_TitlePos , 0, { BUTTON_SIZE_X, BUTTON_SIZE_Y },  { 0.0f, 0.0f}, {1.0f, 1.0f,}, color },
		RefImageMaterial().m_Title);

	DrawScreenLT(UI{ g_EcplanCursor->RefCorsor(), 0, { 100, 100 },  { 0.0f, 0.0f}, {1.0f, 1.0f,}, DEF_COLOR },
		RefImageMaterial().m_Cursor);
}

