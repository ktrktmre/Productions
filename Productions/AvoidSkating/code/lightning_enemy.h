//=============================================================================
//
// �G���� [lightning_enemy.h]
// Author : �ؓc�C���l
//
//=============================================================================
#pragma once

#include <d3dx9.h>
#include "base_enemy.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class Lightning_Enemy :public Base_Enemy {
private:
	D3DXVECTOR2	m_Uv_v;
	D3DXVECTOR2	m_Uv_f;
	int			m_Frame;
public:
	Lightning_Enemy() = delete;
	Lightning_Enemy(D3DXVECTOR3 pos, int damage);
	~Lightning_Enemy();

	void Update(void)override;
	void Draw(void)override;
};