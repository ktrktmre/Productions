/*==============================================================================

   操作説明管理 [explanation.cpp]
														 Author :切田 海畝斗
														 Date   :2023/06/16
--------------------------------------------------------------------------------

==============================================================================*/
#include "input.h"
#include "sprite.h"
#include "texture.h"
#include "explanation.h"
#include "explanationBG.h"
#include "player.h"
#include "collision.h"
#include "sound.h"


//=============================================================================
// 初期化処理
//=============================================================================
void InitExplanation(void)
{
	InitExplanationBG();
	InitPlayer();

	//オーディオの初期化
	SOUND_RECORD* pSoundRecord = GetSoundRecord();
	PlaySound(pSoundRecord->BGMGameID, SOUND_LOOP);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitExplanation(void)
{
	UninitExplanationBG();
	UninitPlayer();

	//オーディオの終了
	StopSoundAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateExplanation(void)
{
	UpdateExplanationBG();
	UpdatePlayer();
	UpdateCollision();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawExplanation(void)
{
	DrawExplanationBG();
	DrawPlayer();
}