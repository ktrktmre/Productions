//=============================================================================
//
// 敵処理 [base_enemy.h]
// Author : 切田海畝斗
//
//=============================================================================
#ifndef _BASE_ENEMY_H_
#define _BASE_ENEMY_H_
#pragma once

#include <d3dx9.h>
#include "base_object.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define VALUE_ADD_DAMAGE	(5)
#define VALUE_ADD_TIME		(5)

//*****************************************************************************
// 列挙体宣言
//*****************************************************************************
enum Enemy_Tag {	//エネミータイプ
	tree,
	lightning,
	ball
};

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class Base_Enemy:public Base_Object
{
private:
	Enemy_Tag			m_Tag;				// エネミーのタイプ
	int					m_Damage;			// ダメージ
public:
	Base_Enemy() = default;
	Base_Enemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use, Enemy_Tag tag, int damage);
	virtual ~Base_Enemy() = default;
	void CollDispatch(Base_Object* pObj)override;
	virtual void MoveRange(float limit);

	//リファレンス
	const Enemy_Tag& RefType(void) const;
	const int& RefDamage(void) const;

	//セッター
	void SetType(Enemy_Tag tag);
};

#endif // !_BASE_ENEMY_H_