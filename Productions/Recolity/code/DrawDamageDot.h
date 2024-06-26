#pragma once
#include "main.h"
#include "base_object.h"
class DrawDmageDot
{
private:
	int m_Life = 0;
	float m_Damage;//ゴールのダメージ
	float m_Nowdamage;//現在のダメージ
	float m_Length;//カメラとの距離
	D3DXVECTOR3 m_pos;
	D3DXCOLOR	m_coler;
public:
	//===========================
	// ダメージ表記
	// D3DXCOLOR coler	表示するときの色
	//===========================
	DrawDmageDot();
	~DrawDmageDot() = default;
	void IsDamageDot(float damage);
	void Update(D3DXVECTOR3 pos) ;
	void Draw(void) ;
	float GetLength();//プレイヤーとの距離を返す

};