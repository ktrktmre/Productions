//=============================================================================
//
// 敵処理 [normal_enemy.h]
// Author : 
//
//=============================================================================
#ifndef _NORMAL_ENEMY_H_
#define _NORMAL_ENEMY_H_

#pragma once

#include <d3dx9.h>
#include "renderer.h"
#include "base_enemy.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 構クラス宣言
//*****************************************************************************
class Normal_Enemy :public Base_Enemy {
private:
public:
	Normal_Enemy() = delete;
	Normal_Enemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use);
	~Normal_Enemy();

	HRESULT Init(void)override;
	void Uninit(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Action(void)override;
};

#endif // !_NORMAL_ENEMY_H_