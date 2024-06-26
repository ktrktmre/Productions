//=============================================================================
//
// テキスト処理 [text.h]
// Author : 
//
//=============================================================================
#ifndef _TEXT_H_
#define _TEXT_H_
#pragma once
#include "font.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitText(void);
void UninitText(void);
void SetText(D2D1_RECT_F rect, std::string text);

#endif // !_TEXT_H_