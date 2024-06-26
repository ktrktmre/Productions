//=============================================================================
//
// 属性処理 [water_attribute.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "water_attribute.h"
#include "base_character.h"
#include "Game.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//=============================================================================
// 引数付きコンストラクタ
//=============================================================================
Water_Attribute::Water_Attribute(Attribute_Element element)
	:Base_Attribute(element)
{
}
//=============================================================================
// デストラクタ
//=============================================================================
Water_Attribute::~Water_Attribute()
{
}
//=============================================================================
// キャラクターに対しての属性効果処理
//=============================================================================
void Water_Attribute::ToCharacter(Base_Object* pObj)
{
	//ダウンキャスト(安全性を保つためダイナミックキャスト)
	Base_Character* pBc = dynamic_cast<Base_Character*>(pObj);
	if (pBc == nullptr)
		return;

	//元々の速度ベクトルの保存とスロー効果の付与
	if (m_Once)
	{
		m_OldVel = pBc->RefVel();
		pBc->SetVel(pBc->RefVel() * pBc->GetAttribute(water)->RefElement().m_Value);
		m_Once = false;
	}
	if (!(pBc->GetAttribute(water)->RefElement().m_Frame % 10) )
	{
		Emitta(4, { pBc->RefPos().x,pBc->RefPos().y + 100.0f,pBc->RefPos().z });
	}
	//経過フレーム処理
	pBc->GetAttribute(water)->ReduceFrame(1);

	//規定フレーム経ったら削除
	if (pBc->GetAttribute(water)->RefElement().m_Frame <= 0)
	{
		pBc->SetVel(m_OldVel);
		delete pBc->GetAttribute(water);
		pBc->SetAttribute(nullptr, water);
	}
}
//=============================================================================
// 地面に対しての属性効果処理
//=============================================================================
void Water_Attribute::ToGround(Base_Object* pObj)
{
}
//=============================================================================
// 破壊可能オブジェクトに対しての属性効果処理
//=============================================================================
void Water_Attribute::ToDestructible(Base_Object* pObj)
{
}
