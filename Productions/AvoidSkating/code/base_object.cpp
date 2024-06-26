//=============================================================================
//
// オブジェクト処理 [base_object.cpp]
// Author : 切田海畝斗
//
//=============================================================================

#include "base_object.h"
#include "object_manager.h"

//=============================================================================
// 引数付きコンストラクタ
//=============================================================================
Base_Object::Base_Object(Object_Tag tag, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use)
	:m_ObjTag(tag), m_Pos(pos), m_Rot(rot), m_Scl(scl), m_Vel(vel), m_Color(color), m_Use(use)
{
}
//=============================================================================
//デストラクタ
//=============================================================================
Base_Object::~Base_Object()
{
	for (auto pColl:m_Collision)
	{
		delete pColl;
	}
}
//=============================================================================
// ゲッター
//=============================================================================
Object_Manager* Base_Object::GetObjManager(void)
{
	return m_ObjManager;
}
D3DXMATRIX* Base_Object::GetMtx(void)
{
	return &m_MtxWorld;
}
MATERIAL* Base_Object::GetMaterial(void)
{
	return &m_Material;
}
const std::vector<Base_Collision*>* Base_Object::GetColl(void)
{
	return &m_Collision;
}
Base_Collision* Base_Object::GetColl(int index)
{
	if (index >= m_Collision.size())
		return nullptr;
	return m_Collision[index];
}
//=============================================================================
// リファレンス
//=============================================================================
Object_Tag& Base_Object::RefTag(void)
{
	return m_ObjTag;
}
D3DXVECTOR3& Base_Object::RefPos(void)
{
	return m_Pos;
}
D3DXVECTOR3& Base_Object::RefRot(void)
{
	return m_Rot;
}
D3DXVECTOR3& Base_Object::RefScl(void)
{
	return m_Scl;
}
D3DXVECTOR3& Base_Object::RefVel(void)
{
	return m_Vel;
}
D3DXCOLOR& Base_Object::RefColor(void)
{
	return m_Color;
}
const bool& Base_Object::RefUse(void) const
{
	return m_Use;
}
//=============================================================================
// セッター
//=============================================================================
void Base_Object::SetObjManager(Object_Manager* manager)
{
	m_ObjManager = manager;
}
void Base_Object::SetPos(D3DXVECTOR3 pos)
{
	m_Pos = pos;
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
void Base_Object::SetColl(Base_Collision* coll)
{
	m_Collision.push_back(coll);
}

//=============================================================================
// 衝突アクション
//=============================================================================
void Base_Object::CollAction(Player* player)
{
}
void Base_Object::CollAction(Base_Enemy* enemy)
{
}
void Base_Object::CollAction(Base_Item* item)
{
}