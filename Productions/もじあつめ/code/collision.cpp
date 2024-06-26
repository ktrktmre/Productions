/*==============================================================================

   当たり判定管理 [collision.h]
														 Author :切田 海畝斗
														 Date   :2023/06/16
--------------------------------------------------------------------------------

==============================================================================*/
#include "main.h"
#include "myfunction.h"
#include "collision.h"
#include "player.h"
#include "word.h"
#include "titleBG.h"
#include "resultBG.h"
#include "explanationBG.h"
#include "optionBG.h"
#include "sound.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);
bool CollisionBC(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2);
bool CollisionBCSq(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
D3DXCOLOR g_CollColor;
D3DXCOLOR g_UpdateCollColor;
bool g_OnceCollColor = false;

//=============================================================================
// 当たり判定処理
//=============================================================================
void UpdateCollision(void)
{
	SCENE* pScene = GetScene();

	if (*pScene == SCENE_TITLE)
	{
		TITLEBG* pButton = GetTitleButton();
		PLAYER* pPlayer = GetPlayer();
		//ボタンとプレイヤー
		for (int buttonCnt = 0; buttonCnt < TITLE_BUTTON_NUM; buttonCnt++)
		{
			if (CollisionBB(pPlayer->pos, pButton[buttonCnt].pos, D3DXVECTOR2(PALYER_COLL_SIZE, PALYER_COLL_SIZE), pButton[buttonCnt].size))
			{
				pButton[buttonCnt].color = g_CollColor;
				pButton[buttonCnt].coll = true;
				pPlayer->coll = true;
				break;
			}
			else
			{
				pButton[buttonCnt].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pButton[buttonCnt].coll = false;
				pPlayer->coll = false;
			}
		}
	}
	else if (*pScene == SCENE_EXPLANATION)
	{
		EXPLANATIONBG* pButton = GetExplanationBGButton();
		PLAYER* pPlayer = GetPlayer();
		//ボタンとプレイヤー
		if (CollisionBB(pPlayer->pos, pButton->pos, D3DXVECTOR2(PALYER_COLL_SIZE, PALYER_COLL_SIZE), pButton->size))
		{
			pButton->color = g_CollColor;
			pButton->coll = true;
			pPlayer->coll = true;
		}
		else
		{
			pButton->color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pButton->coll = false;
			pPlayer->coll = false;
		}
	}
	else if (*pScene == SCENE_OPTION)
	{
		OPTION* pButton = GetOptionBGButton();
		OPTION* pAdCursor = GetAdCursor();
		PLAYER* pPlayer = GetPlayer();
		//ボタンとプレイヤー
		if (CollisionBB(pPlayer->pos, pButton->pos, D3DXVECTOR2(PALYER_COLL_SIZE, PALYER_COLL_SIZE), pButton->size))
		{
			pButton->color = g_CollColor;
			pButton->coll = true;
			pPlayer->coll = true;
		}
		else
		{
			pButton->color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pButton->coll = false;
			pPlayer->coll = false;
		}
		//調整カーソルとプレイヤー
		for (int adjCnt = 0; adjCnt < ADJUSTMENT_NUM; adjCnt++)
		{
			if (CollisionBB(pPlayer->pos, pAdCursor[adjCnt].pos, D3DXVECTOR2(PALYER_COLL_SIZE, PALYER_COLL_SIZE), pAdCursor[adjCnt].size))
			{
				pAdCursor[adjCnt].coll = true;
				pAdCursor[adjCnt].color = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
				break;
			}
			else
			{
				pAdCursor[adjCnt].coll = false;
				pAdCursor[adjCnt].color = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
			}
		}
	}
	else if (*pScene == SCENE_GAME)
	{
		PLAYER* pPlayer = GetPlayer();
		WORDS* pWord = GetWord();
		//文字とプレイヤー
		for (int cntWord = 0; cntWord < WORD_NUM; cntWord++)
		{
			if (pWord[cntWord].use)
			{
				if (CollisionBC(pWord[cntWord].pos, pPlayer->pos, pWord[cntWord].size.x / 2, PALYER_COLL_SIZE))
				{
					pWord[cntWord].color = g_CollColor;
					pWord[cntWord].coll = true;
					pPlayer->coll = true;
					break;
				}
				else
				{
					pWord[cntWord].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pWord[cntWord].coll = false;
					pPlayer->coll = false;
					pPlayer->shoot = false;
				}
			}
		}
	}
	else if (*pScene == SCENE_RESULT)
	{
		RESULTBG* pButton = GetResultButton();
		PLAYER* pPlayer = GetPlayer();

		//ボタンとプレイヤー
		for (int buttonCnt = 0; buttonCnt < RESULT_BUTTON_NUM; buttonCnt++)
		{
			if (CollisionBB(pPlayer->pos, pButton[buttonCnt].pos, D3DXVECTOR2(PALYER_COLL_SIZE, PALYER_COLL_SIZE), pButton[buttonCnt].size))
			{
				pButton[buttonCnt].color = g_CollColor;
				pButton[buttonCnt].coll = true;
				pPlayer->coll = true;
				break;
			}
			else
			{
				pButton[buttonCnt].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pButton[buttonCnt].coll = false;
				pPlayer->coll = false;
			}
		}
	}
}

//=============================================================================
// BBによる当たり判定処理
// 回転は考慮しない
// 戻り値：当たってたらtrue
//=============================================================================
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	D3DXVECTOR2 min1, max1;
	D3DXVECTOR2 min2, max2;

	min1.x = pos1.x - size1.x / 2;
	min1.y = pos1.y - size1.y / 2;
	max1.x = pos1.x + size1.x / 2;
	max1.y = pos1.y + size1.y / 2;

	min2.x = pos2.x - size2.x / 2;
	min2.y = pos2.y - size2.y / 2;
	max2.x = pos2.x + size2.x / 2;
	max2.y = pos2.y + size2.y / 2;

	//X軸の判定
	if (min1.x < max2.x && max1.x > min2.x)
	{
		//Y軸の判定
		if (min1.y < max2.y && max1.y > min2.y)
		{
			//全ての条件がTRUEならヒット判定
			return true;
		}
	}

	return false;
}

//=============================================================================
// BCによる当たり判定処理
// サイズは半径
// 戻り値：当たってたらtrue
//=============================================================================
bool CollisionBC(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2)
{
	//pos1とpos2をつなぐベクトルを作る
	D3DXVECTOR2 vDistance = pos1 - pos2;

	//vDistanceのベクトル長を得る
	float length;
	length = D3DXVec2Length(&vDistance);

	//1と2の半径を足す
	float size = size1 + size2;

	//足した半径とベクトル長とで大きさを判定する
	//差分のベクトル長の方が小さければヒットしている
	if (length < size)
	{
		return true;
	}

	return false;
}

//=============================================================================
// BCによる当たり判定処理
// サイズは半径
// 戻り値：当たってたらtrue
//=============================================================================
bool CollisionBCSq(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2)
{
	//pos1とpos2をつなぐベクトルを作る
	D3DXVECTOR2 vDistance = pos1 - pos2;

	//vDistanceのベクトル長の2乗の値を得る
	float length;
	length = D3DXVec2LengthSq(&vDistance);

	//1と2の半径を足して2乗する
	float size = (size1 + size2) * (size1 + size2);

	//足した半径とベクトル長とで大きさを判定する
	//差分のベクトル長の方が小さければヒットしている
	if (length < size)
	{
		return true;
	}

	return false;
}

//=============================================================================
// 衝突カラー初期化
//=============================================================================
void InitCollColor(void)
{
	//初期化
	g_CollColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	if (!g_OnceCollColor)	//初回だけでデフォルトの色で呼び出し
	{
		SetCollColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	}
	else
	{
		SetCollColor(g_UpdateCollColor);
	}
}

//=============================================================================
// 衝突カラーコピー
//=============================================================================
D3DXCOLOR CopyCollColor(void)
{
	return (D3DXCOLOR(g_CollColor.r * FULL_COLOR, g_CollColor.g * FULL_COLOR, g_CollColor.b * FULL_COLOR, g_CollColor.a));
}

//=============================================================================
// 衝突カラーセッター
//=============================================================================
void SetCollColor(D3DXCOLOR color)
{
	g_CollColor.r = color.r;
	g_CollColor.g = color.g;
	g_CollColor.b = color.b;
	g_CollColor.a = 1.0f;

	g_UpdateCollColor = g_CollColor;

	g_OnceCollColor = true;
}