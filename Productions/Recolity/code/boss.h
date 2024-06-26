//=============================================================================
//
// 敵処理 [boss.h]
// Author : 
//
//=============================================================================
#ifndef _BOSS_H_
#define _BOSS_H_

#pragma once

#include <d3dx9.h>
#include "renderer.h"
#include "base_enemy.h"
#include "bullet_interface.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BOSS_SCALE		(5.0f)					// ボススケール

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class Boss :public Base_Enemy {
private:
	Bullet_Interface* m_BulletIF;	// バレットインターフェース
	int				m_Itv_b;	// 弾の発射間隔
	int				m_Itv_c;	// 大砲の発射間隔
	int				m_CannonSound;
	int				m_BulletSound;;
public:
	Boss() = delete;
	Boss(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use, Bullet_Interface* bif);
	~Boss();

	HRESULT Init(void)override;
	void Uninit(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Action(void)override;
	void SearchAction(void)override;
};

#endif // !_BOSS_H_