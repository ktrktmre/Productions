//=============================================================================
//
// 属性処理 [base_attribute.cpp]
// Author : 
//
//=============================================================================
#include "base_attribute.h"
#include "base_object.h"

//=============================================================================
// 引数付きコンストラクタ
//=============================================================================
Base_Attribute::Base_Attribute(Attribute_Element element)
	:m_Element(element)
{
}
//==========================================================
// タイプ別属性振り分け
//==========================================================
void Base_Attribute::AttributeByType(Base_Object* pObj)
{
	if (pObj->RefObjType() == character)ToCharacter(pObj);
	if (pObj->RefObjType() == ground)ToGround(pObj);
	if (pObj->RefObjType() == destructible)ToDestructible(pObj);
}
//==========================================================
// 属性の構成要素参照
//==========================================================
const Attribute_Element& Base_Attribute::RefElement(void) const
{
	return m_Element;
}
//==========================================================
// 経過フレーム
//==========================================================
void Base_Attribute::ReduceFrame(int frame)
{
	m_Element.m_Frame -= frame;
}
