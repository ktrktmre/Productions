//=============================================================================
//
// 弾管理処理 [bullet_management.h]
// Author : 
//
//=============================================================================
#ifndef _BULLET_MANAGEMENT_H_
#define _BULLET_MANAGEMENT_H_
#pragma once

#include <d3dx9.h>
#include <iostream>
#include <list>
#include "renderer.h"
#include "base_bullet.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class Bullet_Interface;

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class Bullet_Management {
private:
	std::list<Base_Bullet*> m_BulletList;
	MATERIAL	m_Material;
public:
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Create(Bullet_Type type, Bullet_Side side, D3DXVECTOR3 pos, D3DXVECTOR3 des, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vec, D3DXCOLOR color,
		int damage, float speed, float gvt, float dec, int range, D3DXVECTOR2 uv_v, D3DXVECTOR2 uv_f, Attribute_Type att_type, Attribute_Element att_element, int* tex, DX11_MODEL* model, float circle);
	void Create(Bullet_Interface* bif,Bullet_Type type, Bullet_Side side, D3DXVECTOR3 pos, D3DXVECTOR3 des, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vec, D3DXCOLOR color,
		int damage, float speed, float gvt, float dec, int range, D3DXVECTOR2 uv_v, D3DXVECTOR2 uv_f, Attribute_Type att_type, Attribute_Element att_element, int* tex, DX11_MODEL* model, float circle);
	void Delete(void);
	std::list<Base_Bullet*>* GetBulletList(void);

};

#endif // !_BULLET_MANAGEMENT_H_