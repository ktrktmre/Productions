//=============================================================================
//
// �Ǐ��� [wall.h]
// Author : �ؓc�C���l
//
//=============================================================================
#ifndef _WALL_H_
#define _WALL_H_
#pragma once

#include <d3dx9.h>
#include "base_object.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class Wall:public Base_Object
{
private:
	D3DXVECTOR2 m_Uv_v;			//��UV�l
	D3DXVECTOR2 m_Uv_f;			//�Œ�UV�l
	float		m_UvValue;	//UV�l�̉ϗ�
public:
	Wall() = delete;
	Wall(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	~Wall() = default;
	void Update(void);
	void Draw(void);
	void CollDispatch(Base_Object* pObj)override;
};

#endif // !_WALL_H_