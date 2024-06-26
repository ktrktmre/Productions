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
class Normal_Bullet_Life_Penetration : public Base_Bullet
{
private:
	int				m_StartRange;//弾のスタート射程
	int				m_life;		//存在し続けられる時間
public:
	Normal_Bullet_Life_Penetration() = delete;
	Normal_Bullet_Life_Penetration(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel , int life ,D3DXCOLOR color, bool use,
		Bullet_Side side, int damage, float speed, float gvt, float dec, int range, D3DXVECTOR2 uv_v, D3DXVECTOR2 uv_f, 
		Attribute_Type att_type, Attribute_Element att_element, int* tex, DX11_MODEL* model, float circle);
	~Normal_Bullet_Life_Penetration();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	void Move(void) override;
};