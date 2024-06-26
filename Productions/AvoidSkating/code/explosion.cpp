//=============================================================================
//
// 爆発処理 [explosion.cpp]
// Author : 切田海畝斗
//
//=============================================================================
#include "explosion.h"
#include "material.h"
#include "sprite.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PART_X (1.0f/5.0f)

//=============================================================================
// 引数付きコンストラクタ
//=============================================================================
Explosion::Explosion(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXCOLOR color)
	:Base_Anime(pos, rot, scl, NO_VECTOR3, color)
{
	// マテリアル設定
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = color;
	GetMaterial()->Ambient = color;
	GetMaterial()->Emission = color;
	GetMaterial()->noTexSampling = 0;

	//UVの設定
	m_Uv = (UV{ {0.0f,0.0f},{PART_X,1.0f} });
	SetKeyFrame({ 5, 10, 15, 20, 25 });
}

//=============================================================================
// 更新処理
//=============================================================================
void Explosion::Update(void)
{
	Animetion();
}

//=============================================================================
// 描画処理
//=============================================================================
void Explosion::Draw(void)
{
	DrawPolygonBillCR(*this, RefImageMaterial().m_ExplosionBule, m_Uv.m_Uv_v, m_Uv.m_Uv_f);
}
