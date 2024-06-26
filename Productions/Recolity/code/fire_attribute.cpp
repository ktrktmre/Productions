//=============================================================================
//
// 属性処理 [fire_attribute.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "fire_attribute.h"
#include "base_character.h"
#include "Game.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//=============================================================================
// 引数付きコンストラクタ
//=============================================================================
Fire_Attribute::Fire_Attribute(Attribute_Element element)
	:Base_Attribute(element)
{
}
//=============================================================================
// デストラクタ
//=============================================================================
Fire_Attribute::~Fire_Attribute()
{
}
//=============================================================================
// キャラクターに対しての属性効果処理
//=============================================================================
void Fire_Attribute::ToCharacter(Base_Object* pObj)
{
	//ダウンキャスト(安全性を保つためダイナミックキャスト)
	Base_Character* pBc = dynamic_cast<Base_Character*>(pObj);
	if (pBc == nullptr)
		return;

	//インターバル処理
	if (!(pBc->GetAttribute(fire)->RefElement().m_Frame % pBc->GetAttribute(fire)->RefElement().m_Interval))
	{
		pBc->IsDamageDot(pBc->GetAttribute(fire)->RefElement().m_Value);
		Emitta(3, { pBc ->RefPos().x,pBc->RefPos().y + 100.0f,pBc->RefPos().z});
	}

	//経過フレーム処理
	pBc->GetAttribute(fire)->ReduceFrame(1);

	//規定フレーム経ったら削除
	if (pBc->GetAttribute(fire)->RefElement().m_Frame <= 0)
	{
		delete pBc->GetAttribute(fire);
		pBc->SetAttribute(nullptr, fire);
	}
}
//=============================================================================
// 地面に対しての属性効果処理
//=============================================================================
void Fire_Attribute::ToGround(Base_Object* pObj)
{
}
//=============================================================================
// 破壊可能オブジェクトに対しての属性効果処理
//=============================================================================
void Fire_Attribute::ToDestructible(Base_Object* pObj)
{
}
