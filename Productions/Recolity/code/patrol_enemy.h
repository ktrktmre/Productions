//=============================================================================
//
// 敵処理 [bullet_enemy.h]
// Author : 
//
//=============================================================================
#ifndef _PATROL_ENEMY_H_
#define _PATROL_ENEMY_H_

#pragma once

#include <d3dx9.h>
#include "renderer.h"
#include "base_enemy.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class Patrol_Enemy :public Base_Enemy {
private:
	std::vector<D3DXVECTOR3>	m_Destination;
	int							m_Index;
	int							m_SoundIndex;
	bool						m_Arrival;
	float						m_animetion = 0;
	int							m_Attackdirei = 0;//攻撃間隔
	int					m_heit;//エネミーのヘイト
public:
	Patrol_Enemy() = delete;
	Patrol_Enemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use);
	~Patrol_Enemy();

	HRESULT Init(void)override;
	void Uninit(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Action(void)override;
	void Arrival(void);
	void SearchAction(void)override;
	void IsDamage(float damage) override;
	void DistanceVolume(D3DXVECTOR3 pos) override;
};

#endif // !_PATROL_ENEMY_H_