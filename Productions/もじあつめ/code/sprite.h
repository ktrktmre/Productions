//=============================================================================
//
// プレイヤー処理 [sprite.h]
// Author :切田 海畝斗 
//
//=============================================================================
#pragma once
#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "main.h"
#include <iostream>

//*****************************************************************************
// マクロ定義
//*****************************************************************************



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitSprite();
void UninitSprite();

void DrawSprite(int texNo, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 tex_v, D3DXVECTOR2 tex_f);
void DrawSpriteLeftTop(int texNo, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 tex_v, D3DXVECTOR2 tex_f);
void DrawSpriteColor(int texNo, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 tex_v, D3DXVECTOR2 tex_f, D3DXCOLOR color);
void DrawSpriteLeftTopColor(int texNo, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 tex_v, D3DXVECTOR2 tex_f, D3DXCOLOR color);
void DrawSpriteColorRotate(int texNo, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 tex_v, D3DXVECTOR2 tex_f, D3DXCOLOR color, float Rot);
void DrawSpriteColorRotateAxis(int texNo, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 dis, D3DXVECTOR2 tex_v, D3DXVECTOR2 tex_f, D3DXCOLOR color, float Rot);
void DrawWord(int texNo, D3DXVECTOR2 pos, const char chr[], float size, D3DXCOLOR color);
void DrawChar(int texNo, D3DXVECTOR2 pos, const char chr[], float size, D3DXCOLOR color);
void DrawCharRot(int texNo, D3DXVECTOR2 pos, char chr[], float size, D3DXCOLOR color, float rot);

#endif // !_SPRITE_H_