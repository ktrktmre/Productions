/*==============================================================================

   タイトルBG管理 [titleBG.cpp]
														 Author :切田 海畝斗
														 Date   :2023/06/16
--------------------------------------------------------------------------------

==============================================================================*/
#include "titleBG.h"
#include "input.h"
#include "sprite.h"
#include "texture.h"
#include "game.h"
#include "player.h"
#include "fade.h"
#include "myfunction.h"
#include "image.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BUTTON_SIZE 80
#define TITLE_SIZE 200.0f

//*****************************************************************************
// グローバル変数
//*****************************************************************************
TITLEBG g_TitleBG;
TITLEBG g_Title;
TITLEBG g_TitleButton[TITLE_BUTTON_NUM];
int g_TexTitleButtonID[TITLE_BUTTON_NUM];
int g_TexTitleID;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void SetTitleButton(GAME_DIFF index, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR color, GAME_DIFF diff);

//=============================================================================
// 初期化処理
//=============================================================================
void InitTitleBG(void)
{
	ID3D11Device* pDevice = GetDevice();

	//テクスチャの読み込み
	g_TexTitleButtonID[NORMAL] = LoadTexture((char*)"data/TEXTURE/normal.png");
	g_TexTitleButtonID[HARD] = LoadTexture((char*)"data/TEXTURE/hard.png");
	g_TexTitleButtonID[FULL] = LoadTexture((char*)"data/TEXTURE/random.png");
	g_TexTitleButtonID[OPTION] = LoadTexture((char*)"data/TEXTURE/option.png");
	g_TexTitleButtonID[EXPLANATION] = LoadTexture((char*)"data/TEXTURE/explanation.png");
	g_TexTitleID = LoadTexture((char*)"data/TEXTURE/gamename.png");

	//背景の初期化
	g_TitleBG.pos = D3DXVECTOR2(0.0f, 0.0f);
	g_TitleBG.size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	g_TitleBG.tex_v = D3DXVECTOR2(0.0f, 0.0f);
	g_TitleBG.tex_f = D3DXVECTOR2(1.0f, 1.0f);
	g_TitleBG.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_TitleBG.rot = 0.0f;
	g_TitleBG.coll = false;

	//タイトルの初期化
	g_Title.pos = D3DXVECTOR2(SCREEN_WIDTH/2, 300.0f);
	g_Title.size = D3DXVECTOR2(TITLE_SIZE * Contrast(911, 163), TITLE_SIZE);
	g_Title.tex_v = D3DXVECTOR2(0.0f, 0.0f);
	g_Title.tex_f = D3DXVECTOR2(1.0f, 1.0f);
	g_Title.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Title.rot = 0.0f;
	g_Title.coll = false;

	//ボタンの初期化
	for (int buttonCnt = 0; buttonCnt < TITLE_BUTTON_NUM; buttonCnt++)
	{
		g_TitleButton[buttonCnt].pos = D3DXVECTOR2(0.0f, 0.0f);
		g_TitleButton[buttonCnt].size = D3DXVECTOR2(0.0f, 0.0f);
		g_TitleButton[buttonCnt].tex_v = D3DXVECTOR2(0.0f, 0.0f);
		g_TitleButton[buttonCnt].tex_f = D3DXVECTOR2(0.0f, 0.0f);
		g_TitleButton[buttonCnt].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_TitleButton[buttonCnt].rot = 0.0f;
		g_TitleButton[buttonCnt].coll = false;
	}

	//ボタンのセット
	SetTitleButton(NORMAL, D3DXVECTOR2(SCREEN_H_WIDTH - 500.0f, SCREEN_H_HEIGHT + 150.0f), D3DXVECTOR2(Contrast(849, 257) * BUTTON_SIZE, BUTTON_SIZE), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), NORMAL);
	SetTitleButton(HARD, D3DXVECTOR2(SCREEN_H_WIDTH, SCREEN_H_HEIGHT + 150.0f), D3DXVECTOR2(Contrast(569, 257) * BUTTON_SIZE, BUTTON_SIZE), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), HARD);
	SetTitleButton(FULL, D3DXVECTOR2(SCREEN_H_WIDTH + 500.0f, SCREEN_H_HEIGHT + 150.0f), D3DXVECTOR2(Contrast(882, 257) * BUTTON_SIZE, BUTTON_SIZE), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), FULL);
	SetTitleButton(OPTION, D3DXVECTOR2(SCREEN_H_WIDTH - 300.0f, SCREEN_H_HEIGHT + 300.0f), D3DXVECTOR2(Contrast(999, 257) * BUTTON_SIZE, BUTTON_SIZE), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), OPTION);
	SetTitleButton(EXPLANATION, D3DXVECTOR2(SCREEN_H_WIDTH + 300.0f, SCREEN_H_HEIGHT + 300.0f), D3DXVECTOR2(Contrast(807, 257) * BUTTON_SIZE, BUTTON_SIZE), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EXPLANATION);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitleBG(void)
{
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitleBG(void)
{
	PLAYER* pPlayer = GetPlayer();
	for (int buttonCnt = 0; buttonCnt < TITLE_BUTTON_NUM; buttonCnt++)
	{
		if (g_TitleButton[buttonCnt].coll&&pPlayer->shoot)
		{
			switch (buttonCnt)
			{
			case NORMAL:
				SetGameDiff(NORMAL);
				break;
			case HARD:
				SetGameDiff(HARD);
				break;
			case FULL:
				SetGameDiff(FULL);
				break;
			case OPTION:
				SetGameDiff(OPTION);
				break;
			case EXPLANATION:
				SetGameDiff(EXPLANATION);
				break;
			default:
				break;
			}

			//フェードが起きていなかったら
			MODE_FADE* pFade = GetFade();
			if (*pFade == FADE_NOT)
			{
				SetFade(FADE_OUT);
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitleBG(void)
{
	SetSamplerState(FILTER_MODE_LINEAR, ADDRESS_MODE_WRAP);
	IMAGE* pImage = GetImage();
	//タイトルBGの描画
	DrawSpriteLeftTop(pImage->TexBlackBoardID,
		g_TitleBG.pos,
		g_TitleBG.size,
		g_TitleBG.tex_v,
		g_TitleBG.tex_f);

	//タイトルの描画
	DrawSpriteColor(g_TexTitleID,
		g_Title.pos,
		g_Title.size,
		g_Title.tex_v,
		g_Title.tex_f,
		g_Title.color);

	//ボタンの描画
	for (int buttonCnt = 0; buttonCnt < TITLE_BUTTON_NUM; buttonCnt++)
	{
		DrawSpriteColor(g_TexTitleButtonID[buttonCnt],
			g_TitleButton[buttonCnt].pos,
			g_TitleButton[buttonCnt].size,
			g_TitleButton[buttonCnt].tex_v,
			g_TitleButton[buttonCnt].tex_f,
			g_TitleButton[buttonCnt].color
		);
	}
}

//=============================================================================
// ボタンセット関数
//=============================================================================
void SetTitleButton(GAME_DIFF index, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR color, GAME_DIFF diff)
{
	g_TitleButton[index].pos = pos;
	g_TitleButton[index].size = size;
	g_TitleButton[index].tex_v = D3DXVECTOR2(0.0f, 0.0f);
	g_TitleButton[index].tex_f = D3DXVECTOR2(1.0f, 1.0f);
	g_TitleButton[index].color = color;
}

//=============================================================================
// ボタンゲット関数
//=============================================================================
TITLEBG* GetTitleButton(void)
{
	return g_TitleButton;
}