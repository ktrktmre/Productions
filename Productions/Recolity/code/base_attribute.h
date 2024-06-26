//=============================================================================
//
// 属性処理 [base_attribute.h]
// Author : 
//
//=============================================================================
#ifndef _BASE_ATTRIBUTE_H_
#define _BASE_ATTRIBUTE_H_
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class Base_Object;


//*****************************************************************************
// 列挙体宣言
//*****************************************************************************
enum Attribute_Type {	//属性のタイプ
	fire,
	water,
	wind,
	none,
};

//*****************************************************************************
// 構成体宣言
//*****************************************************************************
struct Attribute_Element {	//属性の構成要素
	int		m_Frame = 0;
	int		m_Interval = 0;
	float	m_Value = 0.0f;
};
#define FIER_ATTRIBUTE_TICK 20
#define FIER_ATTRIBUTE_SECOND_DAMAGE 5.0f
//火属性の規定値
#define FIER_ATTRIBUTE {600,FIER_ATTRIBUTE_TICK,FIER_ATTRIBUTE_SECOND_DAMAGE * ((float)FIER_ATTRIBUTE_TICK / 60.0f)}

#define WATER_ATTRIBUTE_SECOND_SLOW 0.8f
#define WATER_ATTRIBUTE {210,0,WATER_ATTRIBUTE_SECOND_SLOW}

//風属性の規定値
#define WIND_ATTRIBUTE {10,0,10.0f}
//*****************************************************************************
// クラス宣言
//*****************************************************************************
class Base_Attribute
{
private:
	Attribute_Element m_Element;
protected:
	virtual void ToCharacter(Base_Object* pObj) = 0;
	virtual void ToGround(Base_Object* pObj) = 0;
	virtual void ToDestructible(Base_Object* pObj) = 0;
public:
	Base_Attribute() = delete;
	Base_Attribute(Attribute_Element element);
	virtual ~Base_Attribute() = default;

	void AttributeByType(Base_Object* pObj);
	const Attribute_Element& RefElement(void) const;
	void ReduceFrame(int frame);
};


#endif // !_BASE_ATTRIBUTE_H_