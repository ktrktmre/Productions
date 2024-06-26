//=============================================================================
//
// 敵処理 [moth_wing.h]
// Author : 
//
//=============================================================================
#ifndef _MOTH_WING_H_
#define _MOTH_WING_H_

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
// 列挙体宣言
//*****************************************************************************
enum Wing_LR {	//翼の左右
	w_left,
	w_right,
};

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class Moth_Wing :public Base_Enemy {
private:
	Wing_LR m_LR;
	int m_Reverse;
	float m_Length;
public:
	Moth_Wing() = delete;
	Moth_Wing
	(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use, Wing_LR lr, float len);
	~Moth_Wing() = default;

	HRESULT Init(void)override;
	void Uninit(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Action(void)override;

	//リファレンス
	const float RefLength(void) const { return m_Length; };
};

#endif // !_MOTH_WING_H_