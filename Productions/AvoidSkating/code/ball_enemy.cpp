//=============================================================================
//
// ボールエネミー処理 [bullet.cpp]
// Author : 切田海畝斗
//
//=============================================================================
#include "ball_enemy.h"
#include "object_manager.h"
#include "circle_collision.h"
#include "material.h"
#include "sprite.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COLL_CIRCLE			(45.0f)						// 当たり判定の半径
#define HORIZONTAL_SPEED	(15.0f)						// 水平スピード
#define VERTICAl_SPEED		(7.0f)						// 垂直スピード
#define ACCELERATION		(1.0f)						// 加速度

//=============================================================================
// 引数付きコンストラクタ
//=============================================================================
Ball_Enemy::Ball_Enemy(D3DXVECTOR3 pos, int damage)
	:Base_Enemy(pos, NO_VECTOR3, { COLL_CIRCLE,COLL_CIRCLE,COLL_CIRCLE }, {0.0f,0.0f,-HORIZONTAL_SPEED }, { 1.0f,1.0f,0.0f,1.0f }, true, ball, damage)
{
	// マテリアル設定
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = RefColor();
	GetMaterial()->Ambient = { 0.0f,0.0f,0.0f,1.0f };
	GetMaterial()->Emission = RefColor();
	GetMaterial()->noTexSampling = 0;

	SetColl(new Circle_Collision(RefPos(), COLL_CIRCLE));
}
//=============================================================================
// 更新
//=============================================================================
void Ball_Enemy::Update(void)
{

	Fall();

	//当たり判定の再設定
	for (Base_Collision* pColl : *GetColl())
	{
		if (auto at = dynamic_cast<Circle_Collision*>(pColl)) {
			at->SetPos(RefPos());
		}
	}

	//座標の更新
	SetPos(RefPos() + RefVel());

	MoveRange(-100);
}
//=============================================================================
// 描画
//=============================================================================
void Ball_Enemy::Draw(void)
{
	Draw3DModel(*this, RefModelMaterial().m_Sphere);
}
//=============================================================================
// 衝突判定ディスパッチ
//=============================================================================
void Ball_Enemy::CollDispatch(Base_Object* pObj)
{
	pObj->CollAction(this);
}
//=============================================================================
// 衝突アクション
//=============================================================================
void Ball_Enemy::CollAction(Player* player)
{
}
//=============================================================================
// 落下
//=============================================================================
void Ball_Enemy::Fall(void)
{
	if (RefVel().y > -5.0f) {
		RefVel().y -= 0.2f;
	}
}
//=============================================================================
// バウンド
//=============================================================================
void Ball_Enemy::Bound(void)
{
	RefVel().y = VERTICAl_SPEED;
}
//=============================================================================
// 移動限界
//=============================================================================
void Ball_Enemy::MoveRange(float limit)
{
	//Y軸の移動範囲
	if (RefPos().y < 0 + RefScl().y) {
		SetPos({ RefPos().x,RefScl().y,RefPos().z });
		Bound();
	}

	if (RefPos().z < limit) {
		SetUse(false);
	}
}
