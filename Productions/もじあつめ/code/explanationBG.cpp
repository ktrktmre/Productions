/*==============================================================================

   操作説明BG管理 [explanationBG.cpp]
														 Author :切田 海畝斗
														 Date   :2023/06/16
--------------------------------------------------------------------------------

==============================================================================*/
#include "input.h"
#include "sprite.h"
#include "texture.h"
#include "player.h"
#include "fade.h"
#include "myfunction.h"
#include "explanationBG.h"
#include "image.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define EXPLANATION_BUTTON_SIZE 80

//*****************************************************************************
// グローバル変数
//*****************************************************************************
EXPLANATIONBG g_ExplanationBG;
EXPLANATIONBG g_ExplanationBGButton;
int g_TexExplanationBGID;

//=============================================================================
// 初期化処理
//=============================================================================
void InitExplanationBG(void)
{
	ID3D11Device* pDevice = GetDevice();

	//テクスチャの読み込み
	g_TexExplanationBGID = LoadTexture((char*)"data/TEXTURE/explanation_text.png");

	//背景の初期化
	g_ExplanationBG.pos = D3DXVECTOR2(0.0f, 0.0f);
	g_ExplanationBG.size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	g_ExplanationBG.tex_v = D3DXVECTOR2(0.0f, 0.0f);
	g_ExplanationBG.tex_f = D3DXVECTOR2(1.0f, 1.0f);
	g_ExplanationBG.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_ExplanationBG.rot = 0.0f;
	g_ExplanationBG.coll = false;

	//ボタンの初期化
	g_ExplanationBGButton.pos = D3DXVECTOR2(Contrast(422, 257) * EXPLANATION_BUTTON_SIZE, EXPLANATION_BUTTON_SIZE);
	g_ExplanationBGButton.size = D3DXVECTOR2(Contrast(422, 257) * EXPLANATION_BUTTON_SIZE, EXPLANATION_BUTTON_SIZE);
	g_ExplanationBGButton.tex_v = D3DXVECTOR2(0.0f, 0.0f);
	g_ExplanationBGButton.tex_f = D3DXVECTOR2(1.0f, 1.0f);
	g_ExplanationBGButton.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_ExplanationBGButton.rot = 0.0f;
	g_ExplanationBGButton.coll = false;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitExplanationBG(void)
{
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateExplanationBG(void)
{
	PLAYER* pPlayer = GetPlayer();
	if (g_ExplanationBGButton.coll && pPlayer->shoot)
	{
		//フェードが起きていなかったら
		MODE_FADE* pFade = GetFade();
		if (*pFade == FADE_NOT)
		{
			SetFade(FADE_OUT);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawExplanationBG(void)
{
	SetSamplerState(FILTER_MODE_LINEAR, ADDRESS_MODE_WRAP);

	IMAGE* pImage = GetImage();

	//操作説明BGの描画
	DrawSpriteLeftTop(g_TexExplanationBGID,
		g_ExplanationBG.pos,
		g_ExplanationBG.size,
		g_ExplanationBG.tex_v,
		g_ExplanationBG.tex_f);

	//ボタンの描画
	DrawSpriteColor(pImage->TexReturnID,
		g_ExplanationBGButton.pos,
		g_ExplanationBGButton.size,
		g_ExplanationBGButton.tex_v,
		g_ExplanationBGButton.tex_f,
		g_ExplanationBGButton.color
	);
}

//=============================================================================
// ボタンゲット関数
//=============================================================================
EXPLANATIONBG* GetExplanationBGButton(void)
{
	return &g_ExplanationBGButton;
}