/*==============================================================================

   リザルトBG管理 [resultBG.cpp]
														 Author :切田 海畝斗
														 Date   :2023/06/16
--------------------------------------------------------------------------------

==============================================================================*/
#include "input.h"
#include "sprite.h"
#include "texture.h"
#include "result.h"
#include "resultBG.h"
#include "score.h"
#include "player.h"
#include "image.h"
#include "fade.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCORE_NUM_SIZE 150
#define RANKING_NUM_SIZE 75
#define RESULT_BUTTON_SIZE 80

//*****************************************************************************
// グローバル変数
//*****************************************************************************
RESULTBG g_ResultBG;
RESULTBG g_ResultButton[RESULT_BUTTON_NUM];
int g_TexScoreID;
int g_TexNewRecordID;
int g_TexHighScoreID;
int g_TexRankingID;
int g_TexDigitID;
int g_TexReplayButtonID;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void SetButton(int index, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR color, float rot);

//=============================================================================
// 初期化処理
//=============================================================================
void InitResultBG(void)
{
	ID3D11Device* pDevice = GetDevice();

	//テクスチャ読み込み
	g_TexScoreID = LoadTexture((char*)"data/TEXTURE/score.png");
	g_TexNewRecordID = LoadTexture((char*)"data/TEXTURE/newrecord.png");
	g_TexHighScoreID = LoadTexture((char*)"data/TEXTURE/hanagata_tyd.png");
	g_TexRankingID = LoadTexture((char*)"data/TEXTURE/ranking.png");
	g_TexDigitID = LoadTexture((char*)"data/TEXTURE/digit.png");
	g_TexReplayButtonID = LoadTexture((char*)"data/TEXTURE/replay.png");

	//背景初期化
	g_ResultBG.pos = D3DXVECTOR2(0.0f, 0.0f);
	g_ResultBG.size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	g_ResultBG.tex_v = D3DXVECTOR2(0.0f, 0.0f);
	g_ResultBG.tex_f = D3DXVECTOR2(1.0f, 1.0f);
	g_ResultBG.color = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
	g_ResultBG.rot = 0.0f;
	g_ResultBG.coll = false;

	//ボタン初期化
	for (int buttonCnt = 0; buttonCnt < RESULT_BUTTON_NUM; buttonCnt++)
	{
		g_ResultButton[buttonCnt].pos= D3DXVECTOR2(0.0f, 0.0f);
		g_ResultButton[buttonCnt].size= D3DXVECTOR2(0.0f, 0.0f);
		g_ResultButton[buttonCnt].tex_v = D3DXVECTOR2(0.0f, 0.0f);
		g_ResultButton[buttonCnt].tex_f = D3DXVECTOR2(0.0f, 0.0f);
		g_ResultButton[buttonCnt].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_ResultButton[buttonCnt].rot = 0.0f;
		g_ResultButton[buttonCnt].coll = false;
	}

	SetButton(RETURN, D3DXVECTOR2(RESULT_BUTTON_SIZE * 1.5f, RESULT_BUTTON_SIZE * 1.5f), D3DXVECTOR2(RESULT_BUTTON_SIZE * Contrast(422, 257), RESULT_BUTTON_SIZE), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);
	SetButton(REPLAY, D3DXVECTOR2(RESULT_BUTTON_SIZE * Contrast(807, 257) + RESULT_BUTTON_SIZE * 1.5f, RESULT_BUTTON_SIZE * 1.5f), D3DXVECTOR2(RESULT_BUTTON_SIZE * Contrast(807, 257), RESULT_BUTTON_SIZE), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResultBG(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResultBG(void)
{
	PLAYER* pPlayer = GetPlayer();
	for (int buttonCnt = 0; buttonCnt < RESULT_BUTTON_NUM; buttonCnt++)
	{
		if (g_ResultButton[buttonCnt].coll && pPlayer->shoot)
		{
			switch (buttonCnt)
			{
			case RETURN:
				SetResultMode(RETURN);
				break;
			case REPLAY:
				SetResultMode(REPLAY);
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
void DrawResultBG(void)
{
	SetSamplerState(FILTER_MODE_LINEAR, ADDRESS_MODE_WRAP);

	IMAGE* pImage = GetImage();
	int* pScoreData = GetScoreData();
	SCORE* pScore = GetScore();
	int num = ScoreDataNum();

	//リザルトBGの描画
	DrawSpriteLeftTop(pImage->TexBlackBoardID,
		g_ResultBG.pos,
		g_ResultBG.size,
		g_ResultBG.tex_v,
		g_ResultBG.tex_f);

	//ランキング表示
	DrawSpriteColor(g_TexRankingID,
		D3DXVECTOR2(SCREEN_WIDTH - SCREEN_Q_WIDTH, RANKING_NUM_SIZE * 1.5f),
		D3DXVECTOR2(RANKING_NUM_SIZE * Contrast(924, 170), RANKING_NUM_SIZE),
		D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f, 1.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
	);
	for (int scoreCnt = 0; scoreCnt < num; scoreCnt++)
	{
		int scoredata = pScoreData[scoreCnt];
		for (int digit = 0; digit < SCORE_DIGIT; digit++)
		{
			int bottom = scoredata % 10;
			scoredata /= 10;

			DrawSpriteLeftTopColor(pImage->TexDefNumID,
				D3DXVECTOR2((SCREEN_WIDTH - SCREEN_Q_WIDTH / 2) - (RANKING_NUM_SIZE * digit), RANKING_NUM_SIZE * 3 + (RANKING_NUM_SIZE * 2 * scoreCnt)),
				D3DXVECTOR2(RANKING_NUM_SIZE, RANKING_NUM_SIZE),
				D3DXVECTOR2(bottom % NUM_PART_X * TEX_PART(NUM_PART_X), bottom / NUM_PART_X * TEX_PART(NUM_PART_Y)),
				D3DXVECTOR2(TEX_PART(NUM_PART_X), TEX_PART(NUM_PART_Y)),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			);
		}

		DrawSpriteLeftTopColor(pImage->TexDefNumID,
			D3DXVECTOR2(SCREEN_H_WIDTH + RANKING_NUM_SIZE * 2, RANKING_NUM_SIZE * 3 + (RANKING_NUM_SIZE * 2 * scoreCnt)),
			D3DXVECTOR2(RANKING_NUM_SIZE, RANKING_NUM_SIZE),
			D3DXVECTOR2((scoreCnt + 1) % NUM_PART_X * TEX_PART(NUM_PART_X), (scoreCnt + 1) / NUM_PART_X * TEX_PART(NUM_PART_Y)),
			D3DXVECTOR2(TEX_PART(NUM_PART_X), TEX_PART(NUM_PART_Y)),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
		);
		DrawSpriteLeftTopColor(g_TexDigitID,
			D3DXVECTOR2(SCREEN_H_WIDTH + RANKING_NUM_SIZE * 3, RANKING_NUM_SIZE * 3 + (RANKING_NUM_SIZE * 2 * scoreCnt)),
			D3DXVECTOR2(RANKING_NUM_SIZE, RANKING_NUM_SIZE),
			D3DXVECTOR2(0.0f, 0.0f),
			D3DXVECTOR2(1.0f, 1.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
		);
	}

	//スコア表示
	int score = pScore->score;
	for (int digit = 0; digit < SCORE_DIGIT; digit++)
	{
		int bottom = score;
		score /= 10;

		DrawSpriteLeftTopColor(pImage->TexDefNumID,
			D3DXVECTOR2((SCREEN_H_WIDTH - SCORE_NUM_SIZE) - (SCORE_NUM_SIZE * digit), SCREEN_HEIGHT / 2),
			D3DXVECTOR2(SCORE_NUM_SIZE, SCORE_NUM_SIZE),
			D3DXVECTOR2(bottom % NUM_PART_X * TEX_PART(NUM_PART_X), bottom / NUM_PART_X * TEX_PART(NUM_PART_Y)),
			D3DXVECTOR2(TEX_PART(NUM_PART_X), TEX_PART(NUM_PART_Y)),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
		);
	}
	if (pScore->newrecord)
	{
		DrawSpriteColor(g_TexNewRecordID,
			D3DXVECTOR2(SCREEN_H_WIDTH - SCORE_NUM_SIZE * 3, SCREEN_HEIGHT / 2 - SCORE_NUM_SIZE),
			D3DXVECTOR2(SCORE_NUM_SIZE * Contrast(712, 173), SCORE_NUM_SIZE),
			D3DXVECTOR2(0.0f, 0.0f),
			D3DXVECTOR2(1.0f, 1.0f),
			D3DXCOLOR(234.0f / FULL_COLOR, 85.0f / FULL_COLOR, 80.0f / FULL_COLOR, 1.0f)
		);
		//ハンコ
		DrawSpriteColor(g_TexHighScoreID,
			D3DXVECTOR2(SCREEN_H_WIDTH, SCREEN_H_HEIGHT- SCORE_NUM_SIZE*2),
			D3DXVECTOR2(SCORE_NUM_SIZE*2, SCORE_NUM_SIZE*2),
			D3DXVECTOR2(0.0f, 0.0f),
			D3DXVECTOR2(1.0f, 1.0f),
			D3DXCOLOR(234.0f / FULL_COLOR, 85.0f / FULL_COLOR, 80.0f / FULL_COLOR, 1.0f)
		);

	}
	else
	{
		DrawSpriteColor(g_TexScoreID,
			D3DXVECTOR2(SCREEN_H_WIDTH - SCORE_NUM_SIZE * 3, SCREEN_HEIGHT / 2 - SCORE_NUM_SIZE),
			D3DXVECTOR2(SCORE_NUM_SIZE * Contrast(954, 177), SCORE_NUM_SIZE),
			D3DXVECTOR2(0.0f, 0.0f),
			D3DXVECTOR2(1.0f, 1.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
		);
	}

	//ボタン描画
	DrawSpriteColor(pImage->TexReturnID,
		g_ResultButton[RETURN].pos,
		g_ResultButton[RETURN].size,
		g_ResultButton[RETURN].tex_v,
		g_ResultButton[RETURN].tex_f,
		g_ResultButton[RETURN].color
	);
	DrawSpriteColor(g_TexReplayButtonID,
		g_ResultButton[REPLAY].pos,
		g_ResultButton[REPLAY].size,
		g_ResultButton[REPLAY].tex_v,
		g_ResultButton[REPLAY].tex_f,
		g_ResultButton[REPLAY].color
	);
}

//=============================================================================
// ボタンセット関数
//=============================================================================
void SetButton(int index, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR color,float rot)
{
	g_ResultButton[index].pos = pos;
	g_ResultButton[index].size = size;
	g_ResultButton[index].tex_v = D3DXVECTOR2(0.0f, 0.0f);
	g_ResultButton[index].tex_f = D3DXVECTOR2(1.0f, 1.0f);
	g_ResultButton[index].color = color;
	g_ResultButton[index].rot = rot;
	g_ResultButton[index].coll = false;
}

//=============================================================================
// ボタンゲット関数
//=============================================================================
RESULTBG* GetResultButton(void)
{
	return g_ResultButton;
}