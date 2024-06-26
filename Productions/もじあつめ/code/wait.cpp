/*==============================================================================

   待機管理 [wait.cpp]
														 Author :切田 海畝斗
														 Date   :2023/06/16
--------------------------------------------------------------------------------

==============================================================================*/
#include "sprite.h"
#include "texture.h"
#include "myfunction.h"
#include "wait.h"
#include "image.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define WAIT_TIME 3
#define WAIT_DIGIT 1
#define WAIT_NUM_SIZE (NUM_SIZE*5)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
int g_WaitFrame;
int g_WaitTimer;

//=============================================================================
// 初期化処理
//=============================================================================
void InitWait(void)
{
	//待機タイマー初期化
	g_WaitTimer = WAIT_TIME;
	g_WaitFrame = 0;

	//オーディオの初期化
	SOUND_RECORD* pSoundRecord = GetSoundRecord();
	PlaySound(pSoundRecord->SEWaitID, 0);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitWait(void)
{
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateWait(void)
{
	g_WaitFrame++;
	if (g_WaitFrame >= FPS)
	{
		g_WaitFrame = 0;
		g_WaitTimer--;
	}
	if (g_WaitTimer < 0)
	{
		//シーンの切り替え
		SetScene(SCENE_GAME);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawWait(void)
{
	IMAGE* pImage = GetImage();

	//背景描画
	DrawSpriteLeftTopColor(pImage->TexBlackBoardID,
		D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT),
		D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f, 1.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//待機時間描画
	if (g_WaitTimer > 0)
	{
		int time = g_WaitTimer;
		for (int waitCnt = 0; waitCnt < WAIT_DIGIT; waitCnt++)
		{
			int bottom = BottomDigit(time);

			time /= 10;

			DrawSpriteColor(pImage->TexDefNumID,
				D3DXVECTOR2(SCREEN_H_WIDTH, SCREEN_H_HEIGHT),
				D3DXVECTOR2(WAIT_NUM_SIZE, WAIT_NUM_SIZE),
				D3DXVECTOR2(bottom % NUM_PART_X * TEX_PART(NUM_PART_X), bottom / NUM_PART_X * TEX_PART(NUM_PART_Y)),
				D3DXVECTOR2(TEX_PART(NUM_PART_X), TEX_PART(NUM_PART_Y)),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			);
		}
	}
	else
	{
		DrawWord(pImage->TexDefChrID,
			D3DXVECTOR2(SCREEN_H_WIDTH - WAIT_NUM_SIZE * 2.5f, SCREEN_H_HEIGHT - WAIT_NUM_SIZE * 0.5f),
			"start",
			WAIT_NUM_SIZE,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
		);
	}
}