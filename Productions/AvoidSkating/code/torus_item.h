//=============================================================================
//
// �A�C�e������ [torus_item.h]
// Author : �ؓc�C���l
//
//=============================================================================
#pragma once

#include <d3dx9.h>
#include "base_item.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class Torus_Item :public Base_Item {
private:
public:
	Torus_Item() = delete;
	Torus_Item(D3DXVECTOR3 pos);
	~Torus_Item();

	void Update(void)override;
	void Draw(void)override;
	void CollAction(Player* player)override;
};