#pragma once
//=============================================================================
//
// 敵処理 [boss.h]
// Author : 
//
//=============================================================================
#ifndef _BOSS2_MAIN_H_
#define _BOSS2_MAIN_H_

#pragma once

#include <d3dx9.h>
#include "renderer.h"
#include "base_enemy.h"
#include "bullet_interface.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BOSS_SCALE		(5.0f)					// ボススケール
enum Boss2State
{
	idol,
	move,
	card_attack,
};
enum CardSclect
{
	None,
	Hook,
	Blast,
	Ball,
	FireRain,
};
//*****************************************************************************
// クラス宣言
//*****************************************************************************
class Boss2_Main :public Base_Enemy {
private:
	Bullet_Interface* m_BulletIF;	// バレットインターフェース
	int				m_Itv_b;	// 弾の発射間隔
	int				m_Itv_c;	// 大砲の発射間隔
	bool				m_agro;//戦闘中か判定
	Boss2State     m_state;//状態
	int				nomalattack;//近づいた時の攻撃クールタイム
	float			idoltime;//idol状態の揺れ
	int				cardattackcd;
	D3DXVECTOR2		m_MoveStatepos; //moveの行先
	int			m_MoveStatetime; //moveの行先
	int			m_Card_attackcelecttime;//カードの選んでるモーション時間
	int			m_card_attacktime;//攻撃してる時間を計測してる
	CardSclect m_card;
	int cd;//テスト用

	int attacksound1;
	int attacksound2;
public:
	Boss2_Main() = delete;
	Boss2_Main(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use, Bullet_Interface* bif);
	~Boss2_Main();

	HRESULT Init(void)override;
	void Uninit(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Action(void)override;
	void SearchAction(void)override;
	void StateSwap_Move(D3DXVECTOR3 pos);
	void StateSwap_Idol();
	void CardAttack();
};

#endif // !_BOSS2_MAIN_H_