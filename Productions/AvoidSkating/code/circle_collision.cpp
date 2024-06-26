//=============================================================================
//
// 衝突判定処理 [circle_collision.cpp]
// Author : 切田海畝斗
//
//=============================================================================
#include "circle_collision.h"

//=============================================================================
// 引数付きコンストラクタ
//=============================================================================
Circle_Collision::Circle_Collision(D3DXVECTOR3 pos, float circle)
	:m_Circle(circle), m_Pos(pos)
{
}
//=============================================================================
// 当たり判定
//=============================================================================
bool Circle_Collision::IsCollision(Base_Collision* pColl)
{
	//キャスト
	Circle_Collision* pCC = dynamic_cast<Circle_Collision*>(pColl);
	if (!pCC)
		return false;

	//当たり判定処理
	float circle = (m_Circle + pCC->m_Circle) * (m_Circle + pCC->m_Circle);
	D3DXVECTOR3 vec = pCC->m_Pos - m_Pos;
	float f = D3DXVec3LengthSq(&vec);
	return f <= circle;
}
//=============================================================================
// リファレンス
//=============================================================================
const D3DXVECTOR3& Circle_Collision::RefPos(void) const
{
	return m_Pos;
}
//=============================================================================
// セッター
//=============================================================================
void Circle_Collision::SetPos(D3DXVECTOR3 pos)
{
	m_Pos = pos;
}
void Circle_Collision::SetCircle(float circle)
{
	m_Circle = circle;
}