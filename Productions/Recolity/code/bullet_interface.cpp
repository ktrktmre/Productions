//=============================================================================
//
// 弾入出力処理 [bullet_interface.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "camera.h"
#include "model.h"
#include "texture.h"
#include "bullet_interface.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// 引数付きコンストラクタ
//=============================================================================
Bullet_Interface::Bullet_Interface(Bullet_Management* management)
	:m_Management(management)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
Bullet_Interface::~Bullet_Interface()
{
}
//=============================================================================
// 通常弾セット
//=============================================================================
void Bullet_Interface::SetNBullet(Bullet_Type type, Bullet_Side side, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXCOLOR color, int damage, float speed, float gvt, float dec, int range, Attribute_Type att_type, Attribute_Element att_element, int* tex)
{
	m_Management->Create(type, side, pos,NO_VECTOR3, rot, scl,
		D3DXVECTOR3(speed * sinf(rot.y) * cosf(rot.x), speed * sinf(rot.x), speed * cosf(rot.y) * cosf(rot.x)),
		color, damage, speed, gvt, dec, range, { 0.0f,0.0f }, { 1.0f,1.0f }, att_type, att_element, tex, nullptr, 100);
}

void Bullet_Interface::SetNBullet(Bullet_Type type, Bullet_Side side, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXCOLOR color, int damage, float speed, float gvt, float dec, int range, D3DXVECTOR2 uv_v, D3DXVECTOR2 uv_f, Attribute_Type att_type, Attribute_Element att_element, int* tex)
{
	m_Management->Create(type, side, pos, NO_VECTOR3, rot, scl,
		D3DXVECTOR3(speed * sinf(rot.y) * cosf(rot.x), speed * sinf(rot.x), speed * cosf(rot.y) * cosf(rot.x)),
		color, damage, speed, gvt, dec, range, uv_v, uv_f, att_type, att_element, tex, nullptr, 100);
}

void Bullet_Interface::SetNBullet(Bullet_Type type, Bullet_Side side, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXCOLOR color, int damage, float speed, float gvt, float dec, int range, Attribute_Type att_type, Attribute_Element att_element, int* tex, float circle)
{
	m_Management->Create(type, side, pos, NO_VECTOR3, rot, scl,
		D3DXVECTOR3(speed * sinf(rot.y) * cosf(rot.x), speed * sinf(rot.x), speed * cosf(rot.y) * cosf(rot.x)),
		color, damage, speed, gvt, dec, range, { 0.0f,0.0f }, { 1.0f,1.0f }, att_type, att_element, tex, nullptr, circle);
}

void Bullet_Interface::SetNBullet(Bullet_Type type, Bullet_Side side, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXCOLOR color, int damage, float speed, float gvt, float dec, int range, D3DXVECTOR2 uv_v, D3DXVECTOR2 uv_f, Attribute_Type att_type, Attribute_Element att_element, int* tex, float circle)
{
	m_Management->Create(type, side, pos, NO_VECTOR3, rot, scl,
		D3DXVECTOR3(speed * sinf(rot.y) * cosf(rot.x), speed * sinf(rot.x), speed * cosf(rot.y) * cosf(rot.x)),
		color, damage, speed, gvt, dec, range, uv_v, uv_f, att_type, att_element, tex, nullptr, circle);
}

void Bullet_Interface::SetNBullet(Bullet_Type type, Bullet_Side side, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXCOLOR color, int damage, float speed, float gvt, float dec, int range, Attribute_Type att_type, Attribute_Element att_element, DX11_MODEL* model)
{
	m_Management->Create(type, side, pos, NO_VECTOR3, rot, scl,
		D3DXVECTOR3(speed * sinf(rot.y) * cosf(rot.x), speed * sinf(rot.x), speed * cosf(rot.y) * cosf(rot.x)),
		color, damage, speed, gvt, dec, range, { 0.0f,0.0f }, { 1.0f,1.0f }, att_type, att_element, nullptr, model, 100);
}

void Bullet_Interface::SetNBullet(Bullet_Type type, Bullet_Side side, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXCOLOR color, int damage, float speed, float gvt, float dec, int range, Attribute_Type att_type, Attribute_Element att_element, DX11_MODEL* model, float circle)
{
	m_Management->Create(type, side, pos, NO_VECTOR3, rot, scl,
		D3DXVECTOR3(speed * sinf(rot.y) * cosf(rot.x), speed * sinf(rot.x), speed * cosf(rot.y) * cosf(rot.x)),
		color, damage, speed, gvt, dec, range, { 0.0f,0.0f }, { 1.0f,1.0f }, att_type, att_element, nullptr, model, circle);
}

void Bullet_Interface::SetCBullet(Bullet_Type type, Bullet_Side side, D3DXVECTOR3 pos, D3DXVECTOR3 des, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXCOLOR color, int damage, float speed, float gvt, float dec, int range, Attribute_Type att_type, Attribute_Element att_element, int* tex)
{
	m_Management->Create(this,type, side, pos, des, rot, scl,NO_VECTOR3,
		color, damage, speed, gvt, dec, range, { 0.0f,0.0f }, { 1.0f,1.0f }, att_type, att_element, tex, nullptr, 100);
}

void Bullet_Interface::SetCBullet(Bullet_Type type, Bullet_Side side, D3DXVECTOR3 pos, D3DXVECTOR3 des, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXCOLOR color, int damage, float speed, float gvt, float dec, int range, D3DXVECTOR2 uv_v, D3DXVECTOR2 uv_f, Attribute_Type att_type, Attribute_Element att_element, int* tex)
{
	m_Management->Create(this, type, side, pos, des, rot, scl, NO_VECTOR3,
		color, damage, speed, gvt, dec, range, uv_v, uv_f, att_type, att_element, tex, nullptr, 100);
}

void Bullet_Interface::SetCBullet(Bullet_Type type, Bullet_Side side, D3DXVECTOR3 pos, D3DXVECTOR3 des, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXCOLOR color, int damage, float speed, float gvt, float dec, int range, Attribute_Type att_type, Attribute_Element att_element, int* tex, float circle)
{
	m_Management->Create(this, type, side, pos, des, rot, scl, NO_VECTOR3,
		color, damage, speed, gvt, dec, range, { 0.0f,0.0f }, { 1.0f,1.0f }, att_type, att_element, tex, nullptr, circle);
}

void Bullet_Interface::SetCBullet(Bullet_Type type, Bullet_Side side, D3DXVECTOR3 pos, D3DXVECTOR3 des, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXCOLOR color, int damage, float speed, float gvt, float dec, int range, D3DXVECTOR2 uv_v, D3DXVECTOR2 uv_f, Attribute_Type att_type, Attribute_Element att_element, int* tex, float circle)
{
	m_Management->Create(this, type, side, pos, des, rot, scl, NO_VECTOR3,
		color, damage, speed, gvt, dec, range, uv_v, uv_f, att_type, att_element, tex, nullptr, circle);
}

void Bullet_Interface::SetCBullet(Bullet_Type type, Bullet_Side side, D3DXVECTOR3 pos, D3DXVECTOR3 des, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXCOLOR color, int damage, float speed, float gvt, float dec, int range, Attribute_Type att_type, Attribute_Element att_element, DX11_MODEL* model)
{
	m_Management->Create(this, type, side, pos, des, rot, scl, NO_VECTOR3,
		color, damage, speed, gvt, dec, range, { 0.0f,0.0f }, { 1.0f,1.0f }, att_type, att_element, nullptr, model, 100);
}

void Bullet_Interface::SetCBullet(Bullet_Type type, Bullet_Side side, D3DXVECTOR3 pos, D3DXVECTOR3 des, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXCOLOR color, int damage, float speed, float gvt, float dec, int range, Attribute_Type att_type, Attribute_Element att_element, DX11_MODEL* model, float circle)
{
	m_Management->Create(this, type, side, pos, des, rot, scl, NO_VECTOR3,
		color, damage, speed, gvt, dec, range, { 0.0f,0.0f }, { 1.0f,1.0f }, att_type, att_element, nullptr, model, circle);
}
