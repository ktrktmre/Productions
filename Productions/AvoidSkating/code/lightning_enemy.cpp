//=============================================================================
//
// 敵処理 [lightning_enemy.cpp]
// Author : 切田海畝斗
//
//=============================================================================
#include "object_manager.h"
#include "lightning_enemy.h"
#include "shadow.h"
#include "material.h"
#include "sprite.h"
#include "circle_collision.h"
#include "lightning.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)			// 回転量
#define COLL_CIRCLE		(40.0f)						// 当たり判定の半径


//=============================================================================
// コンストラクタ
//=============================================================================
Lightning_Enemy::Lightning_Enemy(D3DXVECTOR3 pos, int damage)
	:Base_Enemy(pos, { 0.0f, 0.0f, 0.0f }, { 1200.0f,150.0f,0.0f }, { 0.0f, 0.0f,-30.0f },
		{ 1.0f,1.0f,1.0f,1.0f }, true, lightning, damage)
{
	// マテリアル設定
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = RefColor();
	GetMaterial()->Ambient = { 0.0f,0.0f,0.0f,0.0f };
	GetMaterial()->Emission = { 0.0f,0.0f,0.0f,0.0f };
	GetMaterial()->noTexSampling = 0;

	SetColl(new Circle_Collision(RefPos(),COLL_CIRCLE));
	SetColl(new Circle_Collision(RefPos(),COLL_CIRCLE));
	SetColl(new Circle_Collision(RefPos(),COLL_CIRCLE));

	m_Uv_v = { 0.0f,0.0f };
	m_Uv_f = { 0.25f,1.0f };
}

//=============================================================================
// デストラクタ
//=============================================================================
Lightning_Enemy::~Lightning_Enemy()
{
}

//=============================================================================
// 更新
//=============================================================================
void Lightning_Enemy::Update(void)
{

	//座標の更新
	SetPos(RefPos() + RefVel());
	MoveRange(-100);

	//アニメーションの更新
	if (!(m_Frame % 10)) {
		m_Uv_v.x += m_Uv_f.x;
	}
	++m_Frame;

	//当たり判定の再設定
	for (int index = 0; index < GetColl()->size(); index++)
	{
		Base_Collision* pColl = GetColl(index);
		if (auto at = dynamic_cast<Circle_Collision*>(pColl)) {
			float init_pos = 500.0f;
			at->SetPos({
			RefPos().x - init_pos + init_pos * index,
			RefPos().y,
			RefPos().z });
		}
	}
}

//=============================================================================
// 描画
//=============================================================================
void Lightning_Enemy::Draw(void)
{
	DrawPolygonCR(*this, RefImageMaterial().m_Lightning, m_Uv_v, m_Uv_f);

#if _DEBUG
	//当たり判定球の設定
	for (Base_Collision* pColl : *GetColl())
	{
		if (auto at = dynamic_cast<Circle_Collision*>(pColl)) {
			Object sphere;
			sphere.m_Pos = at->RefPos();
			sphere.m_Scl = { COLL_CIRCLE ,COLL_CIRCLE ,COLL_CIRCLE };
			sphere.m_Rot = RefRot();
			sphere.m_Color = { 1.0f ,1.0f ,1.0f,0.2f };
			sphere.m_Material.Diffuse = sphere.m_Color;
			Draw3DModel(sphere, RefModelMaterial().m_Sphere);
		}
	}
#endif // _DEBUG
}