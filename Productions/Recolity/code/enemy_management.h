//=============================================================================
//
// 敵処理 [enemy_management.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY_MANAGEMENT_H_
#define _ENEMY_MANAGEMENT_H_
#pragma once

#include <d3dx9.h>
#include <iostream>
#include <list>
#include "renderer.h"
#include "base_enemy.h"
#include "bullet_interface.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class Enemy_Management {
private:
	std::list<Base_Enemy*> m_EnemyList;
	Bullet_Interface* m_BulletIF;
	MATERIAL	m_Material;
public:
	Enemy_Management() = delete;
	Enemy_Management(Bullet_Interface* bif);
	~Enemy_Management();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Create(Enemy_Type type, D3DXVECTOR3 pos);
	void Delete(void);
	std::list<Base_Enemy*>* GetEnemyList(void);

};

#endif // !_ENEMY_MANAGEMENT_H_