//=============================================================================
//
// 敵処理 [scorpion_leg.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "scorpion_leg.h"
#include "material.h"
#include "sprite.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//=============================================================================
// 引数付きコンストラクタ
//=============================================================================
Scorpion_Leg::Scorpion_Leg(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use, float len)
	:Base_Enemy(pos, rot, scl, vel, color, use, NULL, scorpion_enemy),m_Reverse(1),m_Length(len)
{

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
HRESULT Scorpion_Leg::Init(void)
{
	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void Scorpion_Leg::Uninit(void)
{
}
//=============================================================================
// 更新処理
//=============================================================================
void Scorpion_Leg::Update(void)
{
	//アクション
	Action();

	//カラー変更
	if (RefHitFrame() > 0) {
		SetHitFrame(RefHitFrame() - 1);
	}
	else {
		GetMaterial()->Diffuse = RefColor();	//拡散色
		GetMaterial()->Ambient = RefColor();	//環境色
		GetMaterial()->Emission = RefColor();	//自己発光色
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void Scorpion_Leg::Draw(void)
{

	// 脚モデルの描画
	Draw3DModel(*this, RefModelMaterial().m_Scorpion_Leg);

}
//=============================================================================
// アクション
//=============================================================================
void Scorpion_Leg::Action(void)
{
	SetRot({ RefRot().x + VALUE_LEG_ROTATE * m_Reverse,RefRot().y,RefRot().z });
	if (RefRot().x >= LIMIT_LEG_ANGLE || RefRot().x <= -LIMIT_LEG_ANGLE)
	{
		m_Reverse *= -1;
	}
}
