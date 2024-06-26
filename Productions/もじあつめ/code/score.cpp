/*==============================================================================

   スコア管理 [score.cpp]
														 Author :切田 海畝斗
														 Date   :2023/06/16
--------------------------------------------------------------------------------

==============================================================================*/
#include "input.h"
#include "sprite.h"
#include "texture.h"
#include "image.h"
#include "game.h"
#include "score.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FILE_NAME_NORMAL "data//DATA//score_nomal.txt"
#define FILE_NAME_HARD "data//DATA//score_hard.txt"
#define FILE_NAME_RANDOM "data//DATA//score_random.txt"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
SCORE g_Score;
int g_ScoreData[SCORE_NUM];

//=============================================================================
// 初期化処理
//=============================================================================
void InitScore(void)
{

	ID3D11Device* pDevice = GetDevice();


	//スコアの初期化
	g_Score.pos = D3DXVECTOR2((SCREEN_WIDTH - NUM_SIZE / 2), NUM_SIZE / 2);
	g_Score.size = D3DXVECTOR2(NUM_SIZE, NUM_SIZE);
	g_Score.tex_f = D3DXVECTOR2(TEX_PART(NUM_PART_X), TEX_PART(NUM_PART_Y));
	g_Score.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Score.score = 0;
	g_Score.newrecord = false;

	for (int scoreCnt = 0; scoreCnt < SCORE_NUM; scoreCnt++)
	{
		g_ScoreData[scoreCnt] = -1;
	}

	GAME_DIFF* pDiff = GetGameDiff();
	switch (*pDiff)
	{
	case NORMAL:
		LoadScore(FILE_NAME_NORMAL);
		break;
	case HARD:
		LoadScore(FILE_NAME_HARD);
		break;
	case FULL:
		LoadScore(FILE_NAME_RANDOM);
		break;
	default:
		break;
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitScore(void)
{
	MySortInt(g_ScoreData, SCORE_NUM, g_Score.score);

	//新記録
	if (g_ScoreData[0] <= g_Score.score)
	{
		g_Score.newrecord = true;
	}

	GAME_DIFF* pDiff = GetGameDiff();
	switch (*pDiff)
	{
	case NORMAL:
		SaveScore(FILE_NAME_NORMAL);
		break;
	case HARD:
		SaveScore(FILE_NAME_HARD);
		break;
	case FULL:
		SaveScore(FILE_NAME_RANDOM);
		break;
	default:
		break;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateScore(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawScore(void)
{
	SetSamplerState(FILTER_MODE_LINEAR, ADDRESS_MODE_WRAP);

	IMAGE* pImage = GetImage();

	//スコアの表示
	int score = g_Score.score;
	for (int scoreCnt = 0; scoreCnt < SCORE_DIGIT; scoreCnt++)
	{
		int bottom = BottomDigit(score);
		score /= 10;

		DrawSpriteColor(pImage->TexDefNumID,
			D3DXVECTOR2(g_Score.pos.x - NUM_SIZE / 2 * scoreCnt, g_Score.pos.y),
			g_Score.size,
			D3DXVECTOR2(bottom % NUM_PART_X * g_Score.tex_f.x, bottom / NUM_PART_X * g_Score.tex_f.y),
			g_Score.tex_f,
			g_Score.color
		);
	}


}

//=============================================================================
// Scoreセッター関数
//=============================================================================
void SetScore(int point)
{
	g_Score.score += point;
	if (g_Score.score <= 0)
	{
		g_Score.score = 0;
	}
}

//=============================================================================
// Scoreゲッター関数
//=============================================================================
SCORE* GetScore(void)
{
	return &g_Score;
}

//=============================================================================
// Scoredataゲッター関数
//=============================================================================
int* GetScoreData(void)
{
	return g_ScoreData;
}

//=============================================================================
// 使っているデータ配列の数
//=============================================================================
int ScoreDataNum(void)
{
	int num = 0;
	for (int scoreCnt = 0; scoreCnt < SCORE_NUM; scoreCnt++)
	{
		if (g_ScoreData[scoreCnt] >= 0)
		{
			num++;
		}
	}

	return num;
}

//=============================================================================
// スコアの読み込み
//=============================================================================
void LoadScore(std::string failename)
{
	std::fstream ifs(failename);
	if (!ifs.fail())
	{
		for (int scoreCnt = 0; scoreCnt < SCORE_NUM; scoreCnt++)
		{
			ifs >> g_ScoreData[scoreCnt];
		}
	}
}

//=============================================================================
// スコアの書き込み
//=============================================================================
void SaveScore(std::string filename)
{
	std::ofstream ofs(filename);
	if (!ofs.fail())
	{
		for (int scoreCnt = 0; scoreCnt < SCORE_NUM; scoreCnt++)
		{
			ofs << g_ScoreData[scoreCnt] << std::endl;
		}
	}
}