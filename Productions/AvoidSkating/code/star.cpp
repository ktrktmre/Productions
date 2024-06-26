//=============================================================================
//
// 流れ星処理 [explosion.cpp]
// Author : 切田海畝斗
//
//=============================================================================
#include "explosion.h"
#include "material.h"
#include "sprite.h"
#include "star.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PART_X (1.0f/5.0f)
#define PART_Y (1.0f/4.0f)

//=============================================================================
// 引数付きコンストラクタ
//=============================================================================
Star::Star(Base_Object* pObj, D3DXVECTOR3 scl, D3DXCOLOR color)
	:Base_Anime(NO_VECTOR3, NO_VECTOR3, scl, NO_VECTOR3, color), m_Target(pObj)
{
	SetPos({
		m_Target->RefPos().x + m_Length * sinf(RefRot().y),
		m_Target->RefPos().y,
		m_Target->RefPos().z + m_Length * cosf(RefRot().y),
		}
	);

	// マテリアル設定
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = color;
	GetMaterial()->Ambient = color;
	GetMaterial()->Emission = color;
	GetMaterial()->noTexSampling = 0;

	//UVの設定
	m_Uv = (UV{ {0.0f,0.0f},{PART_X,PART_Y} });

	m_Length = 100.0f;
	SetKeyFrame({ 300 });
}

//=============================================================================
// 更新処理
//=============================================================================
void Star::Update(void)
{
	Animetion();

	SetRot({ 0.0f,RefRot().y + 0.1f,0.0f });

	SetPos({
		m_Target->RefPos().x + m_Length * sinf(RefRot().y),
		m_Target->RefPos().y,
		m_Target->RefPos().z + m_Length * cosf(RefRot().y),
		}
	);
}

//=============================================================================
// 描画処理
//=============================================================================
void Star::Draw(void)
{
	DrawPolygonBill(*this, RefImageMaterial().m_StarGreen, m_Uv.m_Uv_v, m_Uv.m_Uv_f);
}

//=============================================================================
// アニメーション
//=============================================================================
void Star::Animetion(void)
{
	if (!(m_Frame % 10)) {
		m_Uv.m_Uv_v += m_Uv.m_Uv_f;
	}
	++m_Frame;

	if (m_Frame == m_KeyFrame.front())
		SetUse(false);
}
