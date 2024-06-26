//=============================================================================
//
// 属性処理 [fire_attribute.h]
// Author : 
//
//=============================================================================
#ifndef _FIRE_ATTRIBUTE_H_
#define _FIRE_ATTRIBUTE_H_

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
class Fire_Attribute: public Base_Attribute
{
private:
protected:
	void ToCharacter(Base_Object* pObj)override;
	void ToGround(Base_Object* pObj)override;
	void ToDestructible(Base_Object* pObj)override;
public:
	Fire_Attribute() = delete;
	Fire_Attribute(Attribute_Element element);
	~Fire_Attribute();

};


#endif // !_FIRE_ATTRIBUTE_H_