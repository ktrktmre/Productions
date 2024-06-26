//=============================================================================
//
// 衝突判定処理 [circle_collision.h]
// Author : 切田海畝斗
//
//=============================================================================
#ifndef _CIRCLE_COLLISION_H_
#define _CIRCLE_COLLISION_H_
#pragma once

#include <d3dx9.h>
#include "base_collision.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class Circle_Collision:public Base_Collision
{
private:
	D3DXVECTOR3 m_Pos;
	float m_Circle;
public:
	Circle_Collision(void) = delete;
	Circle_Collision(D3DXVECTOR3 pos, float circle);
	~Circle_Collision(void) = default;
	bool IsCollision(Base_Collision* pColl)override;

	//リファレンス
	const D3DXVECTOR3& RefPos (void) const;

	//セッター
	void SetPos(D3DXVECTOR3 pos);
	void SetCircle(float circle);
};


#endif // !_CIRCLE_COLLISION_H_