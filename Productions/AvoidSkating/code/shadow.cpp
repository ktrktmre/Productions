//=============================================================================
//
// 影処理 [shadow.cpp]
// Author : 切田海畝斗
//
//=============================================================================
#include "shadow.h"
#include "material.h"
#include "sprite.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//=============================================================================
// 引数付きコンストラクタ
//=============================================================================
Shadow::Shadow(Base_Object* pTarget)
	:Base_Object(inviolability, { 0.0f,0.1f,0.0f }, NO_VECTOR3, { 80.0f,0.0f,80.0f }, NO_VECTOR3, {0.5f,0.5f,0.5f,0.7f}, true), m_Target(pTarget)
{
	// マテリアル設定
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = DEF_COLOR;
	GetMaterial()->Ambient = { 0.0f,0.0f,0.0f,0.0f };
	GetMaterial()->Emission = { 0.0f,0.0f,0.0f,0.0f };
	GetMaterial()->noTexSampling = 0;

	m_TargetTag = pTarget->RefTag();
}

//=============================================================================
// 更新処理
//=============================================================================
void Shadow::Update(void)
{
	SetPos({
		m_Target->RefPos().x,
		0.0f,
		m_Target->RefPos().z
		});

	if (!m_Target->RefUse() || m_Target->RefTag() != m_TargetTag)
 		SetUse(false);
}

//=============================================================================
// 描画処理
//=============================================================================
void Shadow::Draw(void)
{
	// 減算合成
	SetBlendState(BLEND_MODE_SUBTRACT);
	// Z比較なし
	SetDepthEnable(false);

	DrawPolygonZCR(*this, RefImageMaterial().m_Shadow, { 0.0f,0.0f }, { 1.0f,1.0f });

	// Z比較あり
	SetDepthEnable(true);
	// 通常ブレンド
	SetBlendState(BLEND_MODE_ALPHABLEND);
}
//=============================================================================
// 衝突判定ディスパッチ
//=============================================================================
void Shadow::CollDispatch(Base_Object* pObj)
{
}
