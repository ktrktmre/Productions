/*==============================================================================

   もじ管理[word.h]
														 Author :切田 海畝斗
														 Date   :2023/06/16
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once
#ifndef _WORD_H_
#define _WORD_H_

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define WORD_NUM 20
#define NORMAL_MODE_NUM 4;
#define HARD_MODE_NUM 5;
#define GAME_MODE_NUM 7;

//*****************************************************************************
// 列挙体宣言
//*****************************************************************************
enum GAME_MODE {
	ALIGNMENT=0,
	ALIGNMENT_MOVE,
	ALIGNMENT_ROTATE,
	ALIGNMENT_ROT_MOVE,
	DIRECTION,
	FOUNTAIN,
	RAIN,
};

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
struct WORDS {
	D3DXVECTOR2		pos;		//位置ベクトル
	D3DXVECTOR2		size;		//サイズ
	D3DXVECTOR2		vel;		//速度ベクトル
	D3DXVECTOR2		tex_v;		//可変テクスチャ座標
	D3DXVECTOR2		tex_f;		//固定テクスチャ座標
	D3DXCOLOR		color;		//カラー
	int				frame;
	char			chr;
	float			rot;		//回転角度
	float			rot_speed;	//回転速度
	bool			coll;
	bool			use;
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitWord(void);
void UninitWord(void);
void UpdateWord(void);
void DrawWord(void);
WORDS* GetWord(void);
void SetWord(D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR color, char chr);

#endif // !_WORD_H_