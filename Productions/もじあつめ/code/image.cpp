/*==============================================================================

   イメージ管理 [image.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "image.h"
#include "input.h"
#include "sprite.h"
#include "texture.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
IMAGE g_Image;

//=============================================================================
// 初期化処理
//=============================================================================
void InitImage(void)
{
	ID3D11Device* pDevice = GetDevice();

	//テクスチャ読み込み
	g_Image.TexDefNumID = LoadTexture((char*)"data/TEXTURE/cursor_game.png");
	g_Image.TexDefNumID = LoadTexture((char*)"data/TEXTURE/number_chalk.png");
	g_Image.TexDefChrID= LoadTexture((char*)"data/TEXTURE/alphabet_chalk.png");
	g_Image.TexBlackBoardID = LoadTexture((char*)"data/TEXTURE/blackboard.png");
	g_Image.TexReturnID = LoadTexture((char*)"data/TEXTURE/return.png");
	g_Image.TexBoxID = LoadTexture((char*)"data/TEXTURE/box.png");
	g_Image.TexGradationBoxID = LoadTexture((char*)"data/TEXTURE/gradation.png");
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitImage(void)
{

}

//=============================================================================
// イメージゲッター
//=============================================================================
IMAGE* GetImage(void)
{
	return &g_Image;
}