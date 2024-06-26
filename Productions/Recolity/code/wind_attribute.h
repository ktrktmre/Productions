//=============================================================================
//
// 属性処理 [wind_attribute.h]
// Author : 
//
//=============================================================================
#ifndef _WIND_ATTRIBUTE_H_
#define _WIND_ATTRIBUTE_H_
#pragma once

#include <d3dx9.h>
#include "renderer.h"
#include "base_attribute.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class Wind_Attribute: public Base_Attribute
{
private:
	float		m_Rot;
	bool		m_Once = true;
protected:
	void ToCharacter(Base_Object* pObj)override;
	void ToGround(Base_Object* pObj)override;
	void ToDestructible(Base_Object* pObj)override;
public:
	Wind_Attribute() = delete;
	Wind_Attribute(Attribute_Element element, float rot);
	~Wind_Attribute();

};

#endif // !_WIND_ATTRIBUTE_H_