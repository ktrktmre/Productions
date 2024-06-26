//=============================================================================
//
// ìGèàóù [spider.h]
// Author : 
//
//=============================================================================
#ifndef _SPIDER_H_
#define _SPIDER_H_

#pragma once

#include <d3dx9.h>
#include "renderer.h"
#include "base_enemy.h"
#include "spider_leg.h"
#include "bullet_interface.h"

//*****************************************************************************
// É}ÉNÉçíËã`
//*****************************************************************************
#define SPIDER_SCALE		(13.0f)					// ÉNÉÇÇÃÉXÉPÅ[Éã
#define SPIDER_LEG_NUM		(6)						// ãrÇÃêî
#define SPIDER_LEG_WIDHT	(SPIDER_SCALE*0.3f)		// ãrÇÃïù

//*****************************************************************************
// ÉNÉâÉXêÈåæ
//*****************************************************************************

class Spider :public Base_Enemy {
private:
	Bullet_Interface* m_BulletIF;
	Spider_Leg* m_Leg[SPIDER_LEG_NUM];
	int m_Itv_b;	// íeÇÃî≠éÀä‘äu
	int m_LegIndex;
	int	m_Attackdirei = 0;//çUåÇä‘äu
public:
	Spider() = delete;
	Spider
	(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use, Bullet_Interface* pBif);
	~Spider();

	HRESULT Init(void)override;
	void Uninit(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Action(void)override;
	void SearchAction(void)override;
	void IsDamage(float damage)override;
};

#endif // !_SPIDER_H_