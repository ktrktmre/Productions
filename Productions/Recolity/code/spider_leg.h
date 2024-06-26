//=============================================================================
//
// 敵処理 [spider_leg.h]
// Author : 
//
//=============================================================================
#ifndef _SPIDER_LEG_H_
#define _SPIDER_LEG_H_

#pragma once

#include <d3dx9.h>
#include "renderer.h"
#include "base_enemy.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define INIT_LEG_ANGLE		(D3DXToRadian(5.0f))
#define LIMIT_LEG_ANGLE		(D3DXToRadian(45.0f))
#define VALUE_LEG_ROTATE	(0.03f)

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class Spider_Leg :public Base_Enemy {
private:
	int m_Reverse;
	float m_Length;
public:
	Spider_Leg() = delete;
	Spider_Leg
	(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use, float len);
	~Spider_Leg();

	HRESULT Init(void)override;
	void Uninit(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Action(void)override;

	//リファレンス
	const float RefLength(void) const { return m_Length; };
};

#endif // !_SPIDER_LEG_H_