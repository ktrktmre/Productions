//=============================================================================
//
// �G�Ǘ����� [enemy_manager.h]
// Author : �ؓc�C���l
//
//=============================================================================
#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_
#pragma once

#include <d3dx9.h>
#include <unordered_map>
#include <vector>
#include "base_enemy.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class Enemy_Manager
{
private:
	Object_Manager* m_ObjManager;
	std::unordered_map<Enemy_Tag, int> m_Frame;
	std::vector<D3DXVECTOR3> m_Table;
public:
	Enemy_Manager() = delete;
	Enemy_Manager(Object_Manager* manager);
	~Enemy_Manager() = default;

	void Update(void);
	void Create(std::pair<const Enemy_Tag, int>& pair);
};

#endif // !_ENEMY_MANAGER_H_