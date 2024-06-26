//=============================================================================
//
// リザルト画面処理 [result.cpp]
// Author : 切田海畝斗
//
//=============================================================================
#include <fstream>
#include "result.h"
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
#define SCORE_DIGIT			(5)			// 桁数
#define CHARA_SIZE			(100.0f)
#define PART_X				(5)
#define PART_Y				(2)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
Cursor* g_ResultCursor;
D3DXVECTOR2 g_NextPos;
D3DXVECTOR2 g_ReturnPos;
D3DXVECTOR2 g_ScorePos;
D3DXVECTOR2 g_ScoreScl;
bool g_Next;
bool g_Return;
int g_Score;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitResult(void)
{
	g_ResultCursor = new Cursor;

	std::fstream ifs("data/SAVE/scoredata.txt");
	if (!ifs.fail()) {
		ifs >> g_Score;
		g_ScoreScl = { 100.0f,100.0f };
		g_ScorePos = { SCREEN_CENTER_X + g_ScoreScl.x * 1.5f,SCREEN_CENTER_Y - g_ScoreScl.y };
	}

	g_Next = false;
	g_Return = false;

	g_NextPos = { SCREEN_CENTER_X + 500,SCREEN_CENTER_Y + 300 };
	g_ReturnPos = { SCREEN_CENTER_X - 500,SCREEN_CENTER_Y + 300 };

	PlaySound("result", 0, 0.2f, 0);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResult(void)
{
	StopSoundAll();
	delete g_ResultCursor;
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResult(void)
{
	g_ResultCursor->MoveCursor(VALUE_CURSOR);

	g_Next = false;
	g_Return = false;
	if (g_ResultCursor->RefCorsor().x >= (g_NextPos.x - BASE_BUTTON_HSIZE_X) && g_ResultCursor->RefCorsor().x <= (g_NextPos.x + BASE_BUTTON_HSIZE_X) &&
		g_ResultCursor->RefCorsor().y <= (g_NextPos.y + BASE_BUTTON_HSIZE_Y) && g_ResultCursor->RefCorsor().y >= (g_NextPos.y - BASE_BUTTON_HSIZE_Y))
		g_Next = true;
	if (g_ResultCursor->RefCorsor().x >= (g_ReturnPos.x - BASE_BUTTON_HSIZE_X) && g_ResultCursor->RefCorsor().x <= (g_ReturnPos.x + BASE_BUTTON_HSIZE_X) &&
		g_ResultCursor->RefCorsor().y <= (g_ReturnPos.y + BASE_BUTTON_HSIZE_Y) && g_ResultCursor->RefCorsor().y >= (g_ReturnPos.y - BASE_BUTTON_HSIZE_Y))
		g_Return = true;

	if (GetKeyboardTrigger(DIK_RETURN) && GetFadeState() == FADE_NONE)
	{
		SceneTransition(SCENE_TITLE);
	}
	if (IsMouseLeftTriggered() && g_Next && GetFadeState() == FADE_NONE) {
		SceneTransition(SCENE_TITLE);
	}
	if (IsMouseLeftTriggered() && g_Return && GetFadeState() == FADE_NONE) {
		SceneTransition(SCENE_GAME);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawResult(void)
{
	DrawScreenLT(UI{ { 0.0f,0.0f }, 0, { SCREEN_WIDTH, SCREEN_HEIGHT },  { 0.0f, 0.0f}, {1.0f, 1.0f,}, DEF_COLOR },
		RefImageMaterial().m_White);

	DrawScreen(UI{ { SCREEN_CENTER_X,SCREEN_CENTER_Y - 300 }, 0, { 386, 94 },  { 0.0f, 0.0f}, {1.0f, 1.0f,}, {0,0,0,1.0f} },
		RefImageMaterial().m_Score);

	// 桁数分処理する
	int number = g_Score;
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		// 今回表示する桁の数字
		int x = (number % 10);

		// スコアの位置やテクスチャー座標を反映
		float px = g_ScorePos.x - g_ScoreScl.x * i;	// 表示位置X

		// テクスチャ座標
		float v_x = (x % PART_X) * (1.0f / (float)PART_X);
		float v_y = (x / PART_X) * (1.0f / (float)PART_Y);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		DrawScreenLT(UI{ {px ,g_ScorePos.y},0.0f,g_ScoreScl,{v_x,v_y},
			{1.0f / (float)PART_X,1.0f / (float)PART_Y},{0,0,0,1} }, RefImageMaterial().m_BauNumber);

		// 次の桁へ
		number /= 10;
	}

	D3DXCOLOR color;
	color = g_Next ? D3DXCOLOR(1, 1, 0, 1) : D3DXCOLOR(0, 0, 0, 1);
	DrawScreen(UI{ g_NextPos, 0, { BASE_BUTTON_SIZE_X, BASE_BUTTON_SIZE_Y },  { 0.0f, 0.0f}, {1.0f, 1.0f,}, color },
		RefImageMaterial().m_Title);
	color = g_Return ? D3DXCOLOR(1, 1, 0, 1) : D3DXCOLOR(0, 0, 0, 1);
	DrawScreen(UI{ g_ReturnPos, 0, { BASE_BUTTON_SIZE_X, BASE_BUTTON_SIZE_Y },  { 0.0f, 0.0f}, {1.0f, 1.0f,}, color },
		RefImageMaterial().m_Return);

	DrawScreenLT(UI{ g_ResultCursor->RefCorsor(), 0, { 100, 100 },  { 0.0f, 0.0f}, {1.0f, 1.0f,}, DEF_COLOR },
		RefImageMaterial().m_Cursor);
}
