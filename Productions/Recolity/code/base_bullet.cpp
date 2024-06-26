//=============================================================================
//
// 弾処理 [base_bullet.cpp]
// Author : 
//
//=============================================================================
#include "base_bullet.h"

//=============================================================================
// 引数付きコンストラクタ
//=============================================================================
Base_Bullet::Base_Bullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use, Bullet_Type type, Bullet_Side side, int damage, float speed, float gvt, float dec, int range, D3DXVECTOR2 uv_v, D3DXVECTOR2 uv_f, Attribute_Type att_type, Attribute_Element att_element, int* tex, DX11_MODEL* model)
	:Base_Object(pos, rot, scl, vel, color, inviolability, use),
	m_Type(type), m_Side(side), m_Damage(damage), m_Speed(speed), m_Gvt(gvt), m_Dec(dec), m_Range(range),
	m_Uv_v(uv_v), m_Uv_f(uv_f), m_AttElement(att_element), m_TexId(tex), m_ModelId(model)
{
		SetAttType(att_type);
}
//=============================================================================
// ゲッター
//=============================================================================
DX11_MODEL* Base_Bullet::GetModelId(void)
{
	return m_ModelId;
}
//=============================================================================
// リファレンス
//=============================================================================

const Bullet_Type& Base_Bullet::RefType(void) const
{
	return m_Type;
}
const Bullet_Side& Base_Bullet::RefSide(void) const
{
	return m_Side;
}
const int& Base_Bullet::RefDamage(void) const
{
	return m_Damage;
}
const float& Base_Bullet::RefSpeed(void) const
{
	return m_Speed;
}
const float& Base_Bullet::RefGvt(void) const
{
	return m_Gvt;
}
const float& Base_Bullet::RefDec(void) const
{
	return m_Dec;
}
const int& Base_Bullet::RefRange(void) const
{
	return m_Range;
}
const D3DXVECTOR2& Base_Bullet::RefUv_v(void) const
{
	return m_Uv_v;
}
const D3DXVECTOR2& Base_Bullet::RefUv_f(void) const
{
	return m_Uv_f;
}
const Attribute_Element& Base_Bullet::RefElemet(void) const
{
	return m_AttElement;
}

const int& Base_Bullet::RefTexId(void) const
{
	return *m_TexId;
}
//=============================================================================
// セッター
//=============================================================================
void Base_Bullet::SetType(Bullet_Type type)
{
	m_Type = type;
}
void Base_Bullet::SetSide(Bullet_Side side)
{
	m_Side = side;
}
void Base_Bullet::SetDamage(int damage)
{
	m_Damage = damage;
}
void Base_Bullet::SetSpeed(float speed)
{
	m_Speed = speed;
}
void Base_Bullet::SetGvt(float gvt)
{
	m_Gvt = gvt;
}
void Base_Bullet::SetDec(float dec)
{
	m_Dec = dec;
}
void Base_Bullet::SetRange(int range)
{
	m_Range = range;
}
void Base_Bullet::SetUv_v(D3DXVECTOR2 uv_v)
{
	m_Uv_v = uv_v;
}
void Base_Bullet::SetUv_f(D3DXVECTOR2 uv_f)
{
	m_Uv_f = uv_f;
}

void Base_Bullet::IsDiscard()
{
	if (m_Penetration)
	{
		this->SetUse(false);
	}
}
