/*==============================================================================

   自己関数管理 [myfunction.cpp]
														 Author :切田 海畝斗
														 Date   :2023/09/14
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once
#ifndef _MYFUNCTION_H_
#define _MYFUNCTION_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <iostream>
#include <iostream>
#include <fstream>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEX_PART(part) (1.0f/(float)part)	//画像の分割
#define FULL_COLOR 255.0f


//*****************************************************************************
// 構造体定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
D3DXVECTOR2 LeftTopToCenter(D3DXVECTOR2 pos, D3DXVECTOR2 size, float rot);
D3DXVECTOR2 CenterToLeftTop(D3DXVECTOR2 pos, D3DXVECTOR2 size, float rot);
D3DXVECTOR2 LeftTopToRightTop(D3DXVECTOR2 pos, D3DXVECTOR2 size, float rot);
float RoundOff(float num);
D3DXVECTOR2 LeftTopCamera(D3DXVECTOR2 wpos, D3DXVECTOR2 lpos);
int PlusMinus(void);
float RandPercent(int max, int min);
int BottomDigit(int num);
void MySortInt(int array[], int num, int data);
bool EvenOdd(int num);
float Contrast(float num1, float num2);
#endif // !_MYFUNCTION_H_