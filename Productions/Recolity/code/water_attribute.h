//=============================================================================
//
// 属性処理 [water_attribute.h]
// Author : 
//
//=============================================================================
#ifndef _WATER_ATTRIBUTE_H_
#define _WATER_ATTRIBUTE_H_
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
class Water_Attribute: public Base_Attribute
{
private:
	D3DXVECTOR3 m_OldVel;
	bool m_Once = true;
protected:
	void ToCharacter(Base_Object* pObj)override;
	void ToGround(Base_Object* pObj)override;
	void ToDestructible(Base_Object* pObj)override;
public:
	Water_Attribute() = delete;
	Water_Attribute(Attribute_Element element);
	~Water_Attribute();

};

#endif // !_WATER_ATTRIBUTE_H_