#pragma once
#include "main.h"
#include "base_object.h"
class DrawDmage:public Base_Object
{
private:
	int m_Life = 60;
	int m_Damage;
	float m_Length;
public:
	//===========================
	// ダメージ表記
	// int damage		表示したいダメージ
	// D3DXVECTOR3 pos	表示する座標
	// D3DXCOLOR coler	表示するときの色(何も入れないと白)
	//===========================
	DrawDmage(int damage, D3DXVECTOR3 pos, D3DXCOLOR coler = DIK_COLER_WHITE);
	DrawDmage() = delete;
	~DrawDmage() = default;
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	float GetLength();//プレイヤーとの距離を返す

};




