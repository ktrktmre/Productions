//=============================================================================
//
//‘®«ŠÇ—ˆ— [attribute_management.cpp]
// Author : 
//
//=============================================================================
#include "base_object.h"
#include "attribute_management.h"
#include "fire_attribute.h"
#include "water_attribute.h"
#include "wind_attribute.h"

//*****************************************************************************
// ƒ}ƒNƒ’è‹`
//*****************************************************************************

//=============================================================================
// ¶¬
//=============================================================================
Base_Attribute* Attribute_Management::Create(Attribute_Element att_element, Attribute_Type att_type, Base_Object* pObj)
{
	if (att_type == fire)
	{
		return new Fire_Attribute(att_element);
	}
	else if (att_type == water)
	{
		return new Water_Attribute(att_element);
	}
	else if(att_type == wind)
	{
		return new Wind_Attribute(att_element, pObj->RefRot().y);
	}

	return nullptr;
}
