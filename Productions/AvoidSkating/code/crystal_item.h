//=============================================================================
//
// アイテム処理 [crystal_item.h]
// Author : 切田海畝斗
//
//=============================================================================
#ifndef _CRYSTAL_ITEM_H_
#define _CRYSTAL_ITEM_H_
#pragma once

#include <d3dx9.h>
#include "base_item.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス宣言
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
