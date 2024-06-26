//=============================================================================
//
// アイテム処理 [crystal_item.cpp]
// Author : 切田海畝斗
//
//=============================================================================
#include "object_manager.h"
#include "crystal_item.h"
#include "shadow.h"
#include "player.h"
#include "material.h"
#include "sprite.h"
#include "circle_collision.h"
#include "disappear.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)			// 回転量
#define COLL_CIRCLE		(50.0f)						// 当たり判定の半径


//=============================================================================
// コンストラクタ
//=============================================================================
Crystal_Item::Crystal_Item(D3DXVECTOR3 pos)
	:Base_Item(pos, { 0.0f, 0.0f, 0.0f }, { 0.1f,0.1f,0.1f }, { 0.0f, 0.0f,-20.0f },
		DEF_COLOR, true, crystal, 10, 200)
{
	// マテリアル設定
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = RefColor();
	GetMaterial()->Ambient = { 0.0f,0.0f,0.0f,0.0f };
	GetMaterial()->Emission = RefColor();
	GetMaterial()->noTexSampling = 0;

	SetColl(new Circle_Collision(RefPos(),COLL_CIRCLE));
}

//=============================================================================
// デストラクタ
//=============================================================================
Crystal_Item::~Crystal_Item()
{
}

//=============================================================================
// 更新
//=============================================================================
void Crystal_Item::Update(void)
{
	//座標の更新
	SetPos(RefPos() + RefVel());
	//回転の更新
	RefRot().y += 0.05f;
	MoveRange(0);
	//サイズの更新
	if(RefScl().x<50)
		SetScl({ RefScl().x + 1.0f,RefScl().y + 1.0f,RefScl().z + 1.0f });

	//当たり判定の再設定
	for (Base_Collision* pColl : *GetColl())
	{
		if (auto at = dynamic_cast<Circle_Collision*>(pColl)) {
			at->SetPos({
			RefPos().x,
			RefPos().y,
			RefPos().z });
		}
	}
}

//=============================================================================
// 描画
//=============================================================================
void Crystal_Item::Draw(void)
{
	Draw3DModel(*this, RefModelMaterial().m_Heart);

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

//=============================================================================
// 衝突アクション
//=============================================================================
void Crystal_Item::CollAction(Player* player)
{
	player->SetHp(player->RefHp() + RefHeal());
	player->AddScore(RefScore());
	GetObjManager()->Accept(new Disappear(RefPos(), NO_VECTOR3, { 500.0f,500.0f,500.0f }, { 199.0f / FULL_COLOR,0.0f,103.0f / FULL_COLOR,1.0f }));
	SetUse(false);
	PlaySound("crystal", 0, 1.0f, 0);
}
