//=============================================================================
//
// 敵処理 [moth_wing.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "moth_wing.h"
#include "material.h"
#include "sprite.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//=============================================================================
// 引数付きコンストラクタ
//=============================================================================
Moth_Wing::Moth_Wing(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use, Wing_LR lr, float len)
	:Base_Enemy(pos, rot, scl, vel, color, use, NULL, moth_enemy),m_LR(lr),m_Length(len)
{
	if (lr == w_left)
		m_Reverse = 1;
	else
		m_Reverse = -1;

	// マテリアル設定
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = RefColor();	//拡散色
	GetMaterial()->Ambient = RefColor();	//環境色
	GetMaterial()->Emission = RefColor();	//自己発光色
	GetMaterial()->noTexSampling = 0;
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Moth_Wing::Init(void)
{
	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void Moth_Wing::Uninit(void)
{
}
//=============================================================================
// 更新処理
//=============================================================================
void Moth_Wing::Update(void)
{
	//アクション
	Action();
}
//=============================================================================
// 描画処理
//=============================================================================
void Moth_Wing::Draw(void)
{
	//翼モデルの描画
	if (m_LR == w_left)
		Draw3DModel(*this, RefModelMaterial().m_Moth_WingL);
	if (m_LR == w_right)
		Draw3DModel(*this, RefModelMaterial().m_Moth_WingR);
}
//=============================================================================
// アクション
//=============================================================================
void Moth_Wing::Action(void)
{
	SetRot({ RefRot().x  ,RefRot().y + VALUE_LEG_ROTATE * m_Reverse,RefRot().z });
	if (RefRot().y >= LIMIT_LEG_ANGLE || RefRot().y <= -LIMIT_LEG_ANGLE)
	{
		m_Reverse *= -1;
	}
}
