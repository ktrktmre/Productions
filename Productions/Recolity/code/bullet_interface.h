//=============================================================================
//
// 弾入出力処理 [bullet_interface.h]
// Author : 
//
//=============================================================================
#ifndef _BULLET_INTERFACE_H_
#define _BULLET_INTERFACE_H_
#pragma once

#include <d3dx9.h>
#include "renderer.h"
#include "bullet_management.h"
#include "base_bullet.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class Bullet_Interface {
private:
	Bullet_Management* m_Management;
public:
	Bullet_Interface() = delete;
	Bullet_Interface(Bullet_Management* management);
	~Bullet_Interface();

	void SetNBullet(Bullet_Type type, Bullet_Side side, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXCOLOR color,
		int damage, float speed, float gvt, float dec, int range, Attribute_Type att_type, Attribute_Element att_element, int* tex);
	void SetNBullet(Bullet_Type type, Bullet_Side side, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXCOLOR color,
		int damage, float speed, float gvt, float dec, int range,D3DXVECTOR2 uv_v,D3DXVECTOR2 uv_f,Attribute_Type att_type, Attribute_Element att_element, int* tex);
	void SetNBullet(Bullet_Type type, Bullet_Side side, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXCOLOR color,
		int damage, float speed, float gvt, float dec, int range, Attribute_Type att_type, Attribute_Element att_element, int* tex, float circle);
	void SetNBullet(Bullet_Type type, Bullet_Side side, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXCOLOR color,
		int damage, float speed, float gvt, float dec, int range, D3DXVECTOR2 uv_v, D3DXVECTOR2 uv_f, Attribute_Type att_type, Attribute_Element att_element, int* tex, float circle);
	void SetNBullet(Bullet_Type type, Bullet_Side side, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXCOLOR color,
		int damage, float speed, float gvt, float dec, int range, Attribute_Type att_type, Attribute_Element att_element, DX11_MODEL* model);
	void SetNBullet(Bullet_Type type, Bullet_Side side, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXCOLOR color,
		int damage, float speed, float gvt, float dec, int range, Attribute_Type att_type, Attribute_Element att_element, DX11_MODEL* model, float circle);

	void SetCBullet(Bullet_Type type, Bullet_Side side, D3DXVECTOR3 pos, D3DXVECTOR3 des, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXCOLOR color,
		int damage, float speed, float gvt, float dec, int range, Attribute_Type att_type, Attribute_Element att_element, int* tex);
	void SetCBullet(Bullet_Type type, Bullet_Side side, D3DXVECTOR3 pos, D3DXVECTOR3 des, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXCOLOR color,
		int damage, float speed, float gvt, float dec, int range, D3DXVECTOR2 uv_v, D3DXVECTOR2 uv_f, Attribute_Type att_type, Attribute_Element att_element, int* tex);
	void SetCBullet(Bullet_Type type, Bullet_Side side, D3DXVECTOR3 pos, D3DXVECTOR3 des, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXCOLOR color,
		int damage, float speed, float gvt, float dec, int range, Attribute_Type att_type, Attribute_Element att_element, int* tex, float circle);
	void SetCBullet(Bullet_Type type, Bullet_Side side, D3DXVECTOR3 pos, D3DXVECTOR3 des, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXCOLOR color,
		int damage, float speed, float gvt, float dec, int range, D3DXVECTOR2 uv_v, D3DXVECTOR2 uv_f, Attribute_Type att_type, Attribute_Element att_element, int* tex, float circle);
	void SetCBullet(Bullet_Type type, Bullet_Side side, D3DXVECTOR3 pos, D3DXVECTOR3 des, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXCOLOR color,
		int damage, float speed, float gvt, float dec, int range, Attribute_Type att_type, Attribute_Element att_element, DX11_MODEL* model);
	void SetCBullet(Bullet_Type type, Bullet_Side side, D3DXVECTOR3 pos, D3DXVECTOR3 des, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXCOLOR color,
		int damage, float speed, float gvt, float dec, int range, Attribute_Type att_type, Attribute_Element att_element, DX11_MODEL* model, float circle);
};

#endif // !_BULLET_INTERFACE_H_