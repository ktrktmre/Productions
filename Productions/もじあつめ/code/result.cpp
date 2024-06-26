/*==============================================================================

   リザルト管理 [result.cpp]
														 Author :切田 海畝斗
														 Date   :2023/06/16
--------------------------------------------------------------------------------

==============================================================================*/
#include "sprite.h"
#include "texture.h"
#include "input.h"
#include "myfunction.h"
#include "result.h"
#include "resultBG.h"
#include "player.h"
#include "collision.h"
#include "fade.h"
#include "sound.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
RESULT_MODE g_ResultMode;

//=============================================================================
// 初期化処理
//=============================================================================
void InitResult(void)
{
	InitResultBG();
	InitPlayer();
	InitCollColor();
	SetResultMode(RETURN);

	//オーディオの初期化
	SOUND_RECORD* pSoundRecord = GetSoundRecord();
	PlaySound(pSoundRecord->SEResultID, 0);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResult(void)
{
	UninitResultBG();
	UninitPlayer();

	//オーディオの終了
	StopSoundAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResult(void)
{
	UpdateResultBG();
	UpdatePlayer();
	UpdateCollision();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawResult(void)
{
	DrawResultBG();
	DrawPlayer();
}

//=============================================================================
// セットリザルトモード関数
//=============================================================================
void SetResultMode(RESULT_MODE mode)
{
	g_ResultMode = mode;
}

//=============================================================================
// ゲットリザルトモード関数
//=============================================================================
RESULT_MODE* GetResultMode(void)
{
	return &g_ResultMode;
}