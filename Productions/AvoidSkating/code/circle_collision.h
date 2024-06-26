//=============================================================================
//
// �Փ˔��菈�� [circle_collision.h]
// Author : �ؓc�C���l
//
//=============================================================================
#ifndef _CIRCLE_COLLISION_H_
#define _CIRCLE_COLLISION_H_
#pragma once

#include <d3dx9.h>
#include "base_collision.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �N���X�錾
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

	//���t�@�����X
	const D3DXVECTOR3& RefPos (void) const;

	//�Z�b�^�[
	void SetPos(D3DXVECTOR3 pos);
	void SetCircle(float circle);
};


#endif // !_CIRCLE_COLLISION_H_