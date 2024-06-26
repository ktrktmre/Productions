//=============================================================================
//
// テクチャー処理 [texture.h]
// Author :切田 海畝斗 
//
//=============================================================================
#pragma once
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "renderer.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
int LoadTexture(char* fileName);
void UninitTexture(void);
ID3D11ShaderResourceView** GetTexture(int index);

#endif // !_TEXTURE_H_