//=============================================================================
//
// 敵処理 [scorpion.h]
// Author : 
//
//=============================================================================
#ifndef _SCORPION_H_
#define _SCORPION_H_
#pragma once

#include <d3dx9.h>
#include "renderer.h"
#include "base_enemy.h"
#include "scorpion_tail.h"
#include "scorpion_leg.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCORPION_SCALE		(40.0f)					// サソリのスケール
#define SCORPION_LEG_NUM	(6)							// 脚の数
#define SCORPION_LEG_WIDHT	(SCORPION_SCALE*0.1f)		// 脚の幅

//*****************************************************************************
// クラス宣言
//*****************************************************************************

class Scorpion :public Base_Enemy {
private:
	Scorpion_Tail* m_Tail;
	Scorpion_Leg* m_Leg[SCORPION_LEG_NUM];
	int m_LegIndex;
	int	m_Attackdirei = 0;//攻撃間隔
public:
	Scorpion() = delete;
	Scorpion
	(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use,Bullet_Interface* pBif);
	~Scorpion();

	HRESULT Init(void)override;
	void Uninit(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Action(void)override;
	void SearchAction(void)override;
	void IsDamage(float damage)override;
	void DistanceVolume(D3DXVECTOR3 pos) override;
};

#endif // !_SCORPION_H_