//=============================================================================
//
// タイトル画面処理 [title.cpp]
// Author : 切田海畝斗
//
//=============================================================================
#include "title.h"
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
#define GAMETITLE_SIZE_X	(616.0f)
#define GAMETITLE_SIZE_Y	(400.0f)


//*****************************************************************************
// グローバル変数
//*****************************************************************************
Cursor* g_TitleCursor;
D3DXVECTOR2 g_PlayPos;
D3DXVECTOR2 g_ExplanPos;
bool g_Play;
bool g_Explanation;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTitle(void)
{
	g_TitleCursor = new Cursor;

	g_Play = false;
	g_Explanation = false;

	g_PlayPos = { SCREEN_CENTER_X + 500.0f,SCREEN_CENTER_Y + 300.0f };
	g_ExplanPos = { SCREEN_CENTER_X - 500.0f,SCREEN_CENTER_Y + 300.0f };

	PlaySound("title_bgm", -1, 0.2f, 0);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitle(void)
{
	StopSoundAll();
	delete g_TitleCursor;
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitle(void)
{
	g_TitleCursor->MoveCursor(VALUE_CURSOR);

	g_Play = false;
	g_Explanation = false;
	if (g_TitleCursor->RefCorsor().x >= (g_PlayPos.x - BASE_BUTTON_HSIZE_X) && g_TitleCursor->RefCorsor().x <= (g_PlayPos.x + BASE_BUTTON_HSIZE_X) &&
		g_TitleCursor->RefCorsor().y <= (g_PlayPos.y + BASE_BUTTON_HSIZE_Y) && g_TitleCursor->RefCorsor().y >= (g_PlayPos.y - BASE_BUTTON_HSIZE_Y))
		g_Play = true;
	if (g_TitleCursor->RefCorsor().x >= (g_ExplanPos.x - BASE_BUTTON_HSIZE_X) && g_TitleCursor->RefCorsor().x <= (g_ExplanPos.x + BASE_BUTTON_HSIZE_X) &&
		g_TitleCursor->RefCorsor().y <= (g_ExplanPos.y + BASE_BUTTON_HSIZE_Y) && g_TitleCursor->RefCorsor().y >= (g_ExplanPos.y - BASE_BUTTON_HSIZE_Y))
		g_Explanation = true;

#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_RETURN) && GetFadeState() == FADE_NONE)
	{
		SceneTransition(SCENE_GAME);
	}
#endif // _DEBUG

	if (IsMouseLeftTriggered() && g_Play && GetFadeState() == FADE_NONE) {
		SceneTransition(SCENE_GAME);
	}
	if (IsMouseLeftTriggered() && g_Explanation && GetFadeState() == FADE_NONE) {
		SceneTransition(SCENE_EXPLANATION);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitle(void)
{
	DrawScreenLT(UI{ { 0.0f,0.0f }, 0, { SCREEN_WIDTH, SCREEN_HEIGHT },  { 0.0f, 0.0f}, {1.0f, 1.0f,}, DEF_COLOR }, 
		RefImageMaterial().m_White);

	DrawScreen(UI{ { SCREEN_CENTER_X,SCREEN_CENTER_Y - GAMETITLE_SIZE_Y*0.5f }, 0, { GAMETITLE_SIZE_X, GAMETITLE_SIZE_Y },  { 0.0f, 0.0f}, {1.0f, 1.0f,}, {0,0,0,1.0f} },
		RefImageMaterial().m_GameTitle);

	D3DXCOLOR color;
	color = g_Play ? D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f) : D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	DrawScreen(UI{ g_PlayPos, 0, { BASE_BUTTON_SIZE_X, BASE_BUTTON_SIZE_Y },  { 0.0f, 0.0f}, {1.0f, 1.0f,}, color },
		RefImageMaterial().m_Play);
	color = g_Explanation ? D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f) : D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	DrawScreen(UI{ g_ExplanPos, 0, { BASE_BUTTON_SIZE_X, BASE_BUTTON_SIZE_Y },  { 0.0f, 0.0f}, {1.0f, 1.0f,}, color },
		RefImageMaterial().m_Explanation);

	DrawScreenLT(UI{ g_TitleCursor->RefCorsor(), 0, { 100, 100 },  { 0.0f, 0.0f}, {1.0f, 1.0f,}, DEF_COLOR },
		RefImageMaterial().m_Cursor);
}

