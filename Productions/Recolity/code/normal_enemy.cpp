//=============================================================================
//
// 敵処理 [enemy.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "normal_enemy.h"
#include "base_attribute.h"
#include "material.h"
#include "sprite.h"
#include "floor.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define HIT_POINT	(100)							// ヒットポイント
#define COLL_CIRCLE	(100.0f)						// 当たり判定の半径

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************


//=============================================================================
// 引数付きコンストラクタ
//=============================================================================
Normal_Enemy::Normal_Enemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use)
	:Base_Enemy(pos, rot, scl, vel, color, use, HIT_POINT, normal_enemy)
{

	//当たり判定の設定
	SetColl(new Collision(this, { 0.0f,100.0f,0.0f }, 100));

	// マテリアル設定
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = RefColor();	//拡散色
	GetMaterial()->Ambient = RefColor()*0.3f;	//環境色
	GetMaterial()->Emission = RefColor() * 0.3f;	//自己発光色
	GetMaterial()->noTexSampling = 0;

}
//=============================================================================
// デストラクタ
//=============================================================================
Normal_Enemy::~Normal_Enemy()
{
	Uninit();
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Normal_Enemy::Init(void)
{
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Normal_Enemy::Uninit(void)
{
}

//=============================================================================
// 更新処理
//=============================================================================
void Normal_Enemy::Update(void)
{
	Update_DotDamage();
	//カラーの変更
	if (RefHitFrame() > 0) {
		SetHitFrame(RefHitFrame() - 1);
	}
	else {
		SetColor({ 1.0f,1.0f,1.0f,1.0f });
		GetMaterial()->Diffuse = RefColor();	//拡散色
		GetMaterial()->Ambient = RefColor() * 0.3f;	//環境色
		GetMaterial()->Emission = RefColor() * 0.3f;	//自己発光色
		SetStuck(false);
	}
	if (GetNowAdhere(RefPos()) == Floor_flame)
	{
		IsDamageDot(3.0f /60.0f);
	}
	//受けた属性の処理
	for (int index = 0; index < ATTRIBUTE_NUM; index++)
	{
		if (GetAttribute(index) != nullptr)
			GetAttribute(index)->AttributeByType(this);
	}
	//フロア効果の適応
	GetFloorPos();
	//当たり判定の再設定
	for (Collision* pColl : *GetColl())
	{
		pColl->SetCollPos();
	}
	SetOldPos();
}

//=============================================================================
// 描画処理
//=============================================================================
void Normal_Enemy::Draw(void)
{
	Draw3DModel(*this, RefModelMaterial().m_Normal_Enemy);
	Draw_DotDamage();
	//HPの表示
	Object hp;
	hp.m_Pos = { RefPos().x,RefPos().y - 20.0f + 8.7f * RefScl().y * DISTANCE_DIFF,RefPos().z };
	hp.m_Uv_v = { 0.0f + 0.5f - 0.5f * ((RefHp() / (float)HIT_POINT)),0.0f };
	hp.m_Uv_f = { 0.5f,1.0f };
	hp.m_Scl = { 150.0f ,10.0f,0.0f };
	hp.m_Color = { 1.0f,0.0f,0.0f,1.0f };
	DrawPolygonBillX(hp, RefImageMaterial().m_Hp, 0);
#if _DEBUG
	//当たり判定球の設定
	Object sphere;
	for (Collision* pColl : *GetColl())
	{
		sphere.m_Pos = pColl->RefCollPos();
		sphere.m_Scl = { COLL_CIRCLE ,COLL_CIRCLE ,COLL_CIRCLE };
		sphere.m_Rot = RefRot();
		sphere.m_Color = { 5.0f ,5.0f ,5.0f,1.0f };
		Draw3DModel(sphere, RefModelMaterial().m_Sphere);
	}
	
#endif // _DEBUG

}
//=============================================================================
// アクション
//=============================================================================
void Normal_Enemy::Action(void)
{
}