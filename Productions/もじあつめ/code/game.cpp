/*==============================================================================

   ゲーム管理 [game.cpp]
														 Author :切田 海畝斗
														 Date   :2023/06/16
--------------------------------------------------------------------------------

==============================================================================*/
#include "game.h"
#include "gameBG.h"
#include "player.h"
#include "collision.h"
#include "fade.h"
#include "input.h"
#include "sound.h"
#include "word.h"
#include "timer.h"
#include "score.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// グローバル変数
//=============================================================================
int g_GameBGMNo;
bool g_GamePause;
GAME_DIFF g_Diff;

//=============================================================================
// 初期化処理
//=============================================================================
void InitGame(void)
{

	InitPlayer();
	InitWord();
	InitScore();
	InitTimer();
	InitGameBG();
	InitCollColor();

	//オーディオの初期化
	SOUND_RECORD* pSoundRecord = GetSoundRecord();
	PlaySound(pSoundRecord->BGMGameID, SOUND_LOOP);

	//一時停止フラグの初期化
	g_GamePause = false;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGame(void)
{
	UninitPlayer();
	UninitWord();
	UninitScore();
	UninitTimer();
	UninitGameBG();
	//オーディオの終了
	StopSoundAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGame(void)
{
	if (!g_GamePause)
	{
		UpdatePlayer();
		UpdateWord();
		UpdateScore();
		UpdateGameBG();
		UpdateCollision();
	}
	UpdateTimer();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGame(void)
{
	DrawGameBG();
	DrawWord();
	DrawPlayer();
	DrawScore();
	DrawTimer();
}

//=============================================================================
// 難易度セッター
//=============================================================================
void SetGameDiff(GAME_DIFF diff)
{
	g_Diff = diff;
}

//=============================================================================
// 難易度ゲッター
//=============================================================================
GAME_DIFF* GetGameDiff(void)
{
	return &g_Diff;
}

//=============================================================================
// ポーズセッター
//=============================================================================
void SetPause(bool pause)
{
	g_GamePause = pause;
}