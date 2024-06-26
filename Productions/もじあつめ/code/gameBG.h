/*==============================================================================

   ゲームBG管理 [gameBG.h]
														 Author :切田 海畝斗
														 Date   :2023/06/16
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once
#ifndef _GAMEBG_H_
#define _GAMEBG_H_

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
struct GAMEBG {
	D3DXVECTOR2		pos;	//位置ベクトル
	D3DXVECTOR2		size;	//サイズ
	D3DXVECTOR2		tex_v;	//可変テクスチャ座標
	D3DXVECTOR2		tex_f;	//固定テクスチャ座標
	D3DXCOLOR		color;	//カラー
	float rot;
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitGameBG(void);
void UninitGameBG(void);
void UpdateGameBG(void);
void DrawGameBG(void);

#endif // !_GAMEBG_H_