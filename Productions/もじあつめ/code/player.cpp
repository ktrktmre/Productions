/*==============================================================================

   プレイヤー管理 [player.cpp]
														 Author :切田 海畝斗
														 Date   :2023/06/16
--------------------------------------------------------------------------------

==============================================================================*/
#include "input.h"
#include "sprite.h"
#include "texture.h"
#include "myfunction.h"
#include "image.h"
#include "player.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CURSOR_SIZE 60.0f
#define SCORE_DIGIT 6

//*****************************************************************************
// グローバル変数
//*****************************************************************************
PLAYER g_Player;
POINT g_Cursor;
D3DXCOLOR g_UpdatePlayerColor;
bool g_OncePlayerColor = false;

//=============================================================================
// 初期化処理
//=============================================================================
void InitPlayer(void)
{

	ID3D11Device* pDevice = GetDevice();


	//マウスの現在座標の取得
	GetCursorPos(&g_Cursor);

	//プレイヤーの初期化
	g_Player.pos = D3DXVECTOR2(0.0f, 0.0f);
	g_Player.size = D3DXVECTOR2(0.0f, 0.0f);
	g_Player.tex_v = D3DXVECTOR2(0.0f, 0.0f);
	g_Player.tex_f = D3DXVECTOR2(0.0f, 0.0f);
	g_Player.color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	g_Player.coll = false;
	g_Player.shoot = false;
	g_Player.grab = false;
	g_Player.stuck = false;

	//プレイヤーのセット
	SetPlayer(D3DXVECTOR2(g_Cursor.x, g_Cursor.y), D3DXVECTOR2(CURSOR_SIZE, CURSOR_SIZE));
	if (!g_OncePlayerColor)	//初回だけでデフォルトの色で呼び出し
	{
		SetPlayerColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f));
	}
	else
	{
		SetPlayerColor(g_UpdatePlayerColor);
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	if (!g_Player.stuck)
	{
		//マウスの現在座標の取得
		GetCursorPos(&g_Cursor);
		g_Player.pos = D3DXVECTOR2(g_Cursor.x, g_Cursor.y);
	}

	//クリック操作
	if (g_Player.coll)
	{
		if (IsMouseLeftTriggered()|| GetKeyboardTrigger(DIK_SPACE))
		{
			g_Player.shoot = true;
			SOUND_RECORD* pSoundRecord = GetSoundRecord();

			//カーソルスタック
			SCENE* pScene = GetScene();
			if (*pScene != SCENE_GAME)
			{
				g_Player.stuck = true;
			}

			//サウンド
			if (*pScene != SCENE_GAME)
			{
				PlaySound(pSoundRecord->SEButtonID, 0);
			}
		}
	}
	if (IsMouseLeftPressed() || GetKeyboardPress(DIK_SPACE))
	{
		g_Player.grab = true;
	}
	else
	{
		g_Player.grab = false;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	SetSamplerState(FILTER_MODE_LINEAR, ADDRESS_MODE_WRAP);

	IMAGE* pImage = GetImage();

	//プレイヤーの描画
	DrawSpriteColor(pImage->TexCursorID,
		g_Player.pos,
		g_Player.size,
		g_Player.tex_v,
		g_Player.tex_f,
		g_Player.color);
}

//=============================================================================
// プレイヤーゲッター
//=============================================================================
PLAYER* GetPlayer(void)
{
	return &g_Player;
}

//=============================================================================
// プレイヤーセッター
//=============================================================================
void SetPlayer(D3DXVECTOR2 pos, D3DXVECTOR2 size)
{
	g_Player.pos = pos;
	g_Player.size = size;
	g_Player.tex_v = D3DXVECTOR2(0.0f, 0.0f);
	g_Player.tex_f = D3DXVECTOR2(1.0f, 1.0f);
}

//=============================================================================
// プレイヤーカラーコピー
//=============================================================================
D3DXCOLOR CopyPlayerColor(void)
{
	return (D3DXCOLOR(g_Player.color.r * FULL_COLOR, g_Player.color.g * FULL_COLOR, g_Player.color.b * FULL_COLOR, g_Player.color.a));
}

//=============================================================================
// プレイヤーカラーセッター
//=============================================================================
void SetPlayerColor(D3DXCOLOR color)
{
	//プレイヤーカラーの変更
	g_Player.color.r = color.r;
	g_Player.color.g = color.g;
	g_Player.color.b = color.b;
	g_Player.color.a = 1.0f;

	//プレイヤーカラーの保存
	g_UpdatePlayerColor = g_Player.color;

	g_OncePlayerColor = true;
}