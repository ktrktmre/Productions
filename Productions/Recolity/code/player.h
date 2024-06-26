
#pragma once
#include "main.h"
#include "effectmanager.h"
#include "base_character.h"
#include "button.h"
#include <map>
//=================================================
// *******プレイヤーのアップデートの呼び出し順******
// 
// 各パラメーターのリセット	A	: PlayR
// ↓
// 各バフの更新				B	: PlayU
// ↓
// フラグのセット			C	: PlayS
// ↓
// 入力処理					D	: PlayI
//=================================================

//
class PLAYER : public Base_Character
{
private:



	int m_stamina;//スタミナ
	int m_noaction;//スタミナを消費してない時間
	int m_havecard;//カードの持っている場所
	D3DXVECTOR3 m_pos;//現在座標
	D3DXVECTOR3 m_oldpos;//1f前のベクトル
	D3DXVECTOR3 m_vel;//ベクトル
	float m_movespeed;//足の速さ
	bool m_dush;//ダッシュしているか
	bool m_sneak;//スニークしているか
	bool m_wark;//歩いているか
	bool m_jump;//ジャンプしているか
	bool m_nodush;//スタミナがなくなったことによるダッシュ制限
	bool m_minimap;//ミニマップの表示フラグ
	float m_slowness;//プレイヤーのスロウの値
	int		m_WorkSound;//サウンド
	int		m_DushSound;//サウンド
	std::map<std::string, Button> m_Button;
public:
	EFFECTMANAGER effect;
	~PLAYER(void) ;
	PLAYER();
	void SetPosX(float n) { m_pos.x = n; };
	void SetPosY(float n) { m_pos.y = n; };
	void SetPosZ(float n) { m_pos.z = n; };
	void SetVel(D3DXVECTOR3 vel);
	D3DXVECTOR3 GetPos() { return m_pos; };
	bool Get_Sneak() { return m_sneak; };
	void IsDamage(float damage) override;
	void IsDamageDot(float damage) override;
	void ClerFlug();
	virtual HRESULT Init(void)	override;
	virtual void Uninit(void)	 override ;
	virtual void Update(void)	override;
	virtual void Draw(void)		override;
	virtual void Draw2D(void) ;
	virtual void Action(void) override{};
	void PlayU_Vel();//プレイヤーのベクトルが計算される

	void Playerstatusview();//ステータスが見える
	void PlayerHeal(float heal);

	void PlayerDrawUi();

	void PlayR_Stamina();//スタミナの更新
	void PlayR_StateUpdate();//プレイヤーの状態の更新
	void PlayR_PosUpdate();//座標の更新
	void PlayU_EffectUpdate();//エフェクトの更新

	void PlayS_Dush();//ダッシュ
	void PlayS_sneak();//スニーク
	void PlayI_Move();//プレイヤーが移動できるようになる
	void PlayI_FlorEffect();//床からの効果
};



