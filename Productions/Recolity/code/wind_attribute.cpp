//=============================================================================
//
// 属性処理 [wind_attribute.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "wind_attribute.h"
#include "base_character.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//=============================================================================
// 引数付きコンストラクタ
//=============================================================================
Wind_Attribute::Wind_Attribute(Attribute_Element element, float rot)
	:Base_Attribute(element), m_Rot(rot)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
Wind_Attribute::~Wind_Attribute()
{
}
//=============================================================================
// キャラクターに対しての属性効果処理
//=============================================================================
void Wind_Attribute::ToCharacter(Base_Object* pObj)
{
	//ダウンキャスト(安全性を保つためダイナミックキャスト)
	Base_Character* pBc = dynamic_cast<Base_Character*>(pObj);
	if (pBc == nullptr)
		return;

	//スタック処理
	if (!pBc->RefStuck())
	{
		pBc->SetStuck(true);
	}

	//座標の更新
	pBc->SetPos({
		pBc->RefPos().x + pBc->GetAttribute(wind)->RefElement().m_Value * sinf(m_Rot),
		pBc->RefPos().y,
		pBc->RefPos().z + pBc->GetAttribute(wind)->RefElement().m_Value * cosf(m_Rot),
		}
	);

	//経過フレーム処理
	pBc->GetAttribute(wind)->ReduceFrame(1);

	//規定フレーム経ったら削除
	if (pBc->GetAttribute(wind)->RefElement().m_Frame <= 1)
	{
		pBc->SetStuck(false);
		delete pBc->GetAttribute(wind);
		pBc->SetAttribute(nullptr, wind);
	}
}
//=============================================================================
// 地面に対しての属性効果処理
//=============================================================================
void Wind_Attribute::ToGround(Base_Object* pObj)
{
}
//=============================================================================
// 破壊可能オブジェクトに対しての属性効果処理
//=============================================================================
void Wind_Attribute::ToDestructible(Base_Object* pObj)
{
}
