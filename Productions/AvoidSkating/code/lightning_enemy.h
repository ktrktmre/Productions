//=============================================================================
//
// “Gˆ— [lightning_enemy.h]
// Author : Ø“cŠC¤“l
//
//=============================================================================
#pragma once

#include <d3dx9.h>
#include "base_enemy.h"

//*****************************************************************************
// ‘O•ûéŒ¾
//*****************************************************************************

//*****************************************************************************
// ƒNƒ‰ƒXéŒ¾
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