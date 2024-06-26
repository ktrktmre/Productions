//=============================================================================
//
// �A�C�e���Ǘ����� [item_manager.h]
// Author : �ؓc�C���l
//
//=============================================================================
#ifndef _ITEM_MANAGER_H_
#define _ITEM_MANAGER_H_
#pragma once

#include <d3dx9.h>
#include <unordered_map>
#include <vector>
#include "base_item.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class Item_Manager
{
private:
	Object_Manager* m_ObjManager;
	std::unordered_map<Item_Tag, int> m_Frame;
	std::vector<D3DXVECTOR3> m_Table;
public:
	Item_Manager() = delete;
	Item_Manager(Object_Manager* manager);
	~Item_Manager() = default;

	void Update(void);
	void Create(std::pair<const Item_Tag, int>& pair);
};

#endif // !_ITEM_MANAGER_H_