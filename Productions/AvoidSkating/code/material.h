//=============================================================================
//
// 絵素材処理 [material.h]
// Author : 切田海畝斗
//
//=============================================================================
#ifndef _MATERIAL_H_
#define _MATERIAL_H_
#pragma once

#include <d3dx9.h>
#include "renderer.h"
#include "model.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BASE_BUTTON_SIZE_X	(324.0f)
#define BASE_BUTTON_SIZE_Y	(200.0f)
#define BASE_BUTTON_HSIZE_X	(324.0f*0.5f)
#define BASE_BUTTON_HSIZE_Y	(200.0f*0.5f)

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
struct Model_Material
{
	DX11_MODEL m_Sphere;
	DX11_MODEL m_Torus;
	DX11_MODEL m_Tree;
	DX11_MODEL m_Crystal;
	DX11_MODEL m_Heart;
	DX11_MODEL m_Skateboard;
};

struct Image_Material
{
	int m_White;
	int m_GameTitle;
	int m_Title;
	int m_Rule;
	int m_Operation;
	int m_Shadow;
	int m_Lane;
	int m_SkyNight;
	int m_Mountain;
	int m_ExplosionBule;
	int m_StarGreen;
	int m_Disappear;
	int m_Parry;
	int m_Tornado;
	int m_Lightning;
	int m_BauNumber;
	int m_Play;
	int m_Next;
	int m_Explanation;
	int m_Score;
	int m_Return;
	int m_Cursor;
	int m_Frame;
	int m_Wall;
	int m_HpGauge;
	int m_AvoidGauge;
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void RegisterMaterial(void);
void ReleaseMaterial(void);
Model_Material& RefModelMaterial(void);
Image_Material& RefImageMaterial(void);

#endif // !_MATERIAL_H_