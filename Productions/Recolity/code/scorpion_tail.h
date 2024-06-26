//=============================================================================
//
// 敵処理 [scorpion_tail.h]
// Author : 
//
//=============================================================================
#ifndef _SCORPION_TAIL_H_
#define _SCORPION_TAIL_H_
#pragma once

#include <d3dx9.h>
#include "renderer.h"
#include "base_enemy.h"
#include "bullet_interface.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define LIMIT_TAIL_ANGLE	(D3DXToRadian(10))
#define VALUE_TAIL_ROTATE	(0.005f)
//*****************************************************************************
// クラス宣言
//*****************************************************************************

class Scorpion_Tail :public Base_Enemy {
private:
	Bullet_Interface* m_BulletIF;
	int m_Itv_b;	// 弾の発射間隔
	int m_Reverse;
	float m_Length;
public:
	Scorpion_Tail() = delete;
	Scorpion_Tail
	(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use, float len, Bullet_Interface* pBif);
	~Scorpion_Tail();

	HRESULT Init(void)override;
	void Uninit(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Action(void)override;
	void SearchAction(void)override;

	//リファレンス
	const float RefLength(void) const { return m_Length; };
};

#endif // !_SCORPION_TAIL_H_