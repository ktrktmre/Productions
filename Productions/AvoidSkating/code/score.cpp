
//=============================================================================
//
// スコア処理 [score.cpp]
// Author : 切田海畝斗
//
//=============================================================================
#include <fstream>
#include "score.h"
#include "texture.h"
#include "sprite.h"
#include "material.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCORE_MAX			(99999)		// スコアの最大値
#define SCORE_DIGIT			(5)			// 桁数
#define CHARA_SIZE			(100.0f)
#define PART_X				(5)
#define PART_Y				(2)

//=============================================================================
// コンストラクタ
//=============================================================================
Score::Score()
	:m_Pos({ SCREEN_WIDTH - CHARA_SIZE,0.0f }), m_Scl({ CHARA_SIZE,CHARA_SIZE }), m_Color({0.0f,1.0f,0.0f,1.0f}), m_Score(0)
{
}
//=============================================================================
// デストラクタ
//=============================================================================
Score::~Score()
{
	std::ofstream ofs("data/SAVE/scoredata.txt");
	if (ofs.fail())
		return;

	ofs << m_Score;
}

//=============================================================================
// 加算
//=============================================================================
void Score::AddScore(int value)
{
	m_Score += value;

	if (m_Score > SCORE_MAX)
	{
		m_Score = SCORE_MAX;
	}
}

//=============================================================================
// 描画
//=============================================================================
void Score::Draw(void)
{
	// 桁数分処理する
	int number = m_Score;
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		// 今回表示する桁の数字
		int x = (number % 10);

		// スコアの位置やテクスチャー座標を反映
		float px = m_Pos.x - m_Scl.x * i;	// 表示位置X

		// テクスチャ座標
		float v_x = (x % PART_X) * (1.0f / (float)PART_X);
		float v_y = (x / PART_X) * (1.0f / (float)PART_Y);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		DrawScreenLT(UI{ {px ,m_Pos.y},0.0f,m_Scl,{v_x,v_y},
			{1.0f / (float)PART_X,1.0f / (float)PART_Y},m_Color },RefImageMaterial().m_BauNumber);

		// 次の桁へ
		number /= 10;
	}
}