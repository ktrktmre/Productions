/*==============================================================================

   イメージ管理[image.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/

//*****************************************************************************
// インクルードガード
//*****************************************************************************
#pragma once
#ifndef _IMAGE_H_
#define _IMAGE_H_


//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUM_PART_X 5
#define NUM_PART_Y 2
#define NUM_SIZE 80

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
struct IMAGE {
	unsigned int TexCursorID;
	unsigned int TexDefNumID;
	unsigned int TexDefChrID;
	unsigned int TexBlackBoardID;
	unsigned int TexReturnID;
	unsigned int TexBoxID;
	unsigned int TexGradationBoxID;
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitImage(void);
void UninitImage(void);
IMAGE* GetImage(void);

#endif // !_IMAGE_H_