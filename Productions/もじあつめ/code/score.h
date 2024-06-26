/*==============================================================================

   スコア管理[score.h]
														 Author :切田 海畝斗
														 Date   :2023/06/16
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"
#include "renderer.h"
#include "myfunction.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SUCCESS_POINT 100
#define SCORE_NUM 5
#define SCORE_DIGIT 6

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
struct SCORE {
	D3DXVECTOR2		pos;	//位置ベクトル
	D3DXVECTOR2		size;	//サイズ
	D3DXVECTOR2		tex_f;	//固定テクスチャ座標
	D3DXCOLOR		color;	//カラー
	int				score;
	bool			newrecord;	//新記録フラグ
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(int point);
SCORE* GetScore(void);
int* GetScoreData(void);
int ScoreDataNum(void);
void LoadScore(std::string failename);
void SaveScore(std::string filename);

#endif // !_SCORE_H_