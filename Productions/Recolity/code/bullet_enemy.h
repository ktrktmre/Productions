//=============================================================================
//
// 敵処理 [bullet_enemy.h]
// Author : 
//
//=============================================================================
#ifndef _BULLET_ENEMY_H_
#define _BULLET_ENEMY_H_

#pragma once

#include <d3dx9.h>
#include "renderer.h"
#include "base_enemy.h"
#include "bullet_interface.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// クラス宣言
//*****************************************************************************
//m_Itv_bが0だったら射程だった場合bullet_motionが始まりm_Itv_bに発射間隔が足される
//bullet_motionが規定値溜まったら弾が発射される
class Bullet_Enemy :public Base_Enemy {
private:
	Bullet_Interface*	m_BulletIF;	// バレットインターフェース
	int					m_Itv_b;	// 弾の発射間隔
	int					m_bullet_motion;//弾の発射モーションタイマー
	bool				m_trigger;//発射トリガー
	float				m_animationtimer;//アニメーションのタイマー
	int					m_BulletSound;
	int					m_ChargeSound;
public:
	Bullet_Enemy() = delete;
	Bullet_Enemy
	(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use, Bullet_Interface* bif);
	~Bullet_Enemy();

	HRESULT Init(void)override;
	void Uninit(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Action(void)override;
	void SearchAction(void)override;
	void DistanceVolume(D3DXVECTOR3 pos) override;
};

#endif // !_BULLET_ENEMY_H_