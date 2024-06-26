#pragma once
//=============================================================================
//
// 弾処理 [normal_bullet.h]
// Author : 
//
//=============================================================================
#pragma once

#include <d3dx9.h>
#include "renderer.h"
#include "base_bullet.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class Time_bom_Bullet : public Base_Bullet
{
private:
	D3DXVECTOR3 m_pullpoint;
	int life;
public:
	Time_bom_Bullet() = delete;
	Time_bom_Bullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use,
		Bullet_Side side, int damage, float speed, float gvt, float dec, int range, D3DXVECTOR2 uv_v, D3DXVECTOR2 uv_f,
		Attribute_Type att_type, Attribute_Element att_element, int* tex, DX11_MODEL* model, float circle);
	~Time_bom_Bullet() override;

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	void Move(void) override;
};
