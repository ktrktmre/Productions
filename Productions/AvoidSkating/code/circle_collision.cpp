//=============================================================================
//
// �Փ˔��菈�� [circle_collision.cpp]
// Author : �ؓc�C���l
//
//=============================================================================
#include "circle_collision.h"

//=============================================================================
// �����t���R���X�g���N�^
//=============================================================================
Circle_Collision::Circle_Collision(D3DXVECTOR3 pos, float circle)
	:m_Circle(circle), m_Pos(pos)
{
}
//=============================================================================
// �����蔻��
//=============================================================================
bool Circle_Collision::IsCollision(Base_Collision* pColl)
{
	//�L���X�g
	Circle_Collision* pCC = dynamic_cast<Circle_Collision*>(pColl);
	if (!pCC)
		return false;

	//�����蔻�菈��
	float circle = (m_Circle + pCC->m_Circle) * (m_Circle + pCC->m_Circle);
	D3DXVECTOR3 vec = pCC->m_Pos - m_Pos;
	float f = D3DXVec3LengthSq(&vec);
	return f <= circle;
}
//=============================================================================
// ���t�@�����X
//=============================================================================
const D3DXVECTOR3& Circle_Collision::RefPos(void) const
{
	return m_Pos;
}
//=============================================================================
// �Z�b�^�[
//=============================================================================
void Circle_Collision::SetPos(D3DXVECTOR3 pos)
{
	m_Pos = pos;
}
void Circle_Collision::SetCircle(float circle)
{
	m_Circle = circle;
}