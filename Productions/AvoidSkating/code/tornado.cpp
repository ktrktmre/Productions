//=============================================================================
//
// トルネードエフェクト処理 [tornado.cpp]
// Author : 切田海畝斗
//
//=============================================================================
#include "tornado.h"
#include "material.h"
#include "sprite.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PART_X (1.0f/8.0f)

//=============================================================================
// 引数付きコンストラクタ
//=============================================================================
Tornado::Tornado(Base_Object* pObj, D3DXVECTOR3 scl, D3DXCOLOR color)
	:Base_Anime(NO_VECTOR3, NO_VECTOR3, scl, NO_VECTOR3, color), m_Target(pObj)
{
	SetPos(pObj->RefPos());

	// マテリアル設定
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = color;
	GetMaterial()->Ambient = color;
	GetMaterial()->Emission = color;
	GetMaterial()->noTexSampling = 0;

	//UVの設定
	m_Uv = (UV{ {0.0f,0.0f},{PART_X,1.0f} });
	SetKeyFrame({ 3,6,9,12,15,18,21,24 });
}

//=============================================================================
// 更新処理
//=============================================================================
void Tornado::Update(void)
{
	Animetion();

	SetPos(m_Target->RefPos());
}

//=============================================================================
// 描画処理
//=============================================================================
void Tornado::Draw(void)
{
	DrawPolygonBill(*this, RefImageMaterial().m_Tornado, m_Uv.m_Uv_v, m_Uv.m_Uv_f);
}