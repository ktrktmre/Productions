//=============================================================================
//
// オブジェクト処理 [base_object.cpp]
// Author : 
//
//=============================================================================
#include "base_object.h"
#include "base_attribute.h"

//=============================================================================
// 引数付きコンストラクタ
//=============================================================================
Base_Object::Base_Object(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, Object_Type obj_type, bool use)
	:m_Pos(pos),m_Rot(rot),m_Scl(scl),m_Vel(vel),m_Color(color),m_ObjType(obj_type),m_Use(use)
{
	for (int index = 0; index < ATTRIBUTE_NUM; index++)
	{
		m_Attribute[index] = nullptr;
	}
}
//=============================================================================
// デストラクタ
//=============================================================================
Base_Object::~Base_Object()
{
	//コリジョンの解放
	for (Collision* pColl : m_Collision) {
		delete pColl;
	};

	//属性の解放
	for (Base_Attribute* pAtt:m_Attribute){
		delete pAtt;
	}

}
//=============================================================================
// 破棄する
//=============================================================================
void Base_Object::IsDiscard(void)
{
	m_Use = false;
}
//=============================================================================
// ゲッター
//=============================================================================
D3DXMATRIX* Base_Object::GetMtx(void)
{
	return &m_MtxWorld;
}
MATERIAL* Base_Object::GetMaterial(void)
{
	return &m_Material;
}
std::vector<Collision*>* Base_Object::GetColl(void)
{
	return &m_Collision;
}
Collision* Base_Object::GetColl(int index)
{
	if (index >= m_Collision.size())
		return nullptr;
	return m_Collision[index];
}
Base_Attribute* Base_Object::GetAttribute(int index)
{
	return m_Attribute[index];
}
//=============================================================================
// リファレンス
//=============================================================================
const D3DXVECTOR3& Base_Object::RefPos(void) const
{
	return m_Pos;
}
const D3DXVECTOR3& Base_Object::RefOldPos(void) const
{
	return m_OldPos;
}
const D3DXVECTOR3& Base_Object::RefRot(void) const
{
	return m_Rot;
}
const D3DXVECTOR3& Base_Object::RefScl(void) const
{
	return m_Scl;
}
const D3DXVECTOR3& Base_Object::RefVel(void) const
{
	return m_Vel;
}
const D3DXCOLOR& Base_Object::RefColor(void) const
{
	return m_Color;
}
const Object_Type& Base_Object::RefObjType(void) const
{
	return m_ObjType;
}
const Attribute_Type& Base_Object::RefAttType(void) const
{
	return m_AttType;
}
const bool& Base_Object::RefUse(void) const
{
	return m_Use;
}
//=============================================================================
// セッター
//=============================================================================
void Base_Object::SetPos(D3DXVECTOR3 pos)
{
	m_Pos = pos;
}
void Base_Object::SetOldPos(void)
{
	m_OldPos = m_Pos;
}
void Base_Object::SetRot(D3DXVECTOR3 rot)
{
	m_Rot = rot;
}
void Base_Object::SetScl(D3DXVECTOR3 scl)
{
	m_Scl = scl;
}
void Base_Object::SetVel(D3DXVECTOR3 vel)
{
	m_Vel = vel;
}
void Base_Object::SetColor(D3DXCOLOR color)
{
	m_Color = color;
}
void Base_Object::SetUse(bool use)
{
	m_Use = use;
}
void Base_Object::SetColl(Collision* coll)
{
	m_Collision.push_back(coll);
}
void Base_Object::SetColl(int index)
{
	if (index >= m_Collision.size())
		return;
	m_Collision[index]->SetCollPos();
}
void Base_Object::SetAttribute(Base_Attribute* attribute, Attribute_Type att_type)
{
	if(att_type!=none)
		m_Attribute[att_type] = attribute;
}
void Base_Object::SetAttType(Attribute_Type att_type)
{
	m_AttType = att_type;
}
