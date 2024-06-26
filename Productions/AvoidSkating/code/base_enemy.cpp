//=============================================================================
//
// 敵処理 [base_enemy.cpp]
// Author : 切田海畝斗
//
//=============================================================================
#include "base_enemy.h"
#include "object_manager.h"

//=============================================================================
// 引数付きコンストラクタ
//=============================================================================
Base_Enemy::Base_Enemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use, Enemy_Tag tag, int damage)
	:Base_Object(enemy, pos, rot, scl, vel, color, use), m_Tag(tag), m_Damage(damage)
{
}
//=============================================================================
// 衝突判定ディスパッチ
//=============================================================================
void Base_Enemy::CollDispatch(Base_Object* pObj)
{
	pObj->CollAction(this);
}
//=============================================================================
// 移動範囲
//=============================================================================
void Base_Enemy::MoveRange(float limit)
{
	if (RefPos().z <= limit)
		SetUse(false);
}
//=============================================================================
// リファレンス
//=============================================================================
const Enemy_Tag& Base_Enemy::RefType(void) const
{
	return m_Tag;
}
const int& Base_Enemy::RefDamage(void) const
{
	return m_Damage;
}
//=============================================================================
// セッター
//=============================================================================
void Base_Enemy::SetType(Enemy_Tag tag)
{
	m_Tag = tag;
}