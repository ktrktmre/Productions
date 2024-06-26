//=============================================================================
//
// 衝突判定処理 [collision.cpp]
// Author : 
//
//=============================================================================
#include "collision.h"
#include "base_object.h"
//=============================================================================
// 引数付きコンストラクタ
//=============================================================================
Collision::Collision(Base_Object* Target, D3DXVECTOR3 Dis, float circle)
	:m_Circle(circle), m_Dis(Dis),m_Target(Target)
{
}
//=============================================================================
// リファレンス
//=============================================================================
const D3DXVECTOR3& Collision::RefCollPos(void)
{
	return m_Pos;
}
const float& Collision::RefCollCircle(void)
{
	return m_Circle;
}
//=============================================================================
// セッター
//=============================================================================
void Collision::SetCollPos(void)
{
	m_Pos = m_Target->RefPos() + m_Dis;
}
void Collision::SetCollPos(D3DXVECTOR3 pos)
{
	m_Pos = pos;
}
void Collision::SetCircle(float circle)
{
	m_Circle = circle;
}
//=============================================================================
// 当たり判定
//=============================================================================
bool Collision::IsCollision(Collision* obj)
{
	//2点間の距離の2乗
	D3DXVECTOR3 vec = (m_Pos - obj->m_Pos);
	float dis = D3DXVec3LengthSq(&vec);

	//2つのオブジェクトの半径の和
	float len = m_Circle * 0.5f + obj->m_Circle * 0.5f;

	//半径の和が距離の2乗以下だったら
	if (dis <= powf(len, 2))
		return true;
	return false;
}
