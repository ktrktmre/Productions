//=============================================================================
//
// �A�C�e������ [crystal_item.h]
// Author : �ؓc�C���l
//
//=============================================================================
#ifndef _CRYSTAL_ITEM_H_
#define _CRYSTAL_ITEM_H_
#pragma once

#include <d3dx9.h>
#include "base_item.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class Crystal_Item :public Base_Item {
private:
public:
	Crystal_Item() = delete;
	Crystal_Item(D3DXVECTOR3 pos);
	~Crystal_Item();

	void Update(void)override;
	void Draw(void)override;
	void CollAction(Player* player)override;
};
#endif // !_CRYSTAL_ITEM_H_
