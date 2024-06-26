//=============================================================================
//
// 当たり判定管理処理 [collision_management.h]
// Author : 
//
//=============================================================================
#ifndef _COLLISION_MANAGEMENT_H_
#define _COLLISION_MANAGEMENT_H_
#pragma once

#include <d3dx9.h>
#include <iostream>
#include <list>
#include "renderer.h"
#include "base_enemy.h"
#include "base_bullet.h"
#include "attribute_management.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class Collision_Management {
private:
	std::list<Base_Enemy*>* m_EnemyList;
	std::list<Base_Bullet*>* m_BulletList;
	Attribute_Management* m_AttributeManagement;
public:
	Collision_Management() = delete;
	Collision_Management(std::list<Base_Enemy*>* enemey_list, std::list<Base_Bullet*>* bullet_list, Attribute_Management* att_manager);
	~Collision_Management() = default;

	void Update(void);

};

#endif // !_COLLISION_MANAGEMENT_H_