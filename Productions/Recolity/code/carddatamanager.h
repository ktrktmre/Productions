
#pragma once
#include "card_base.h"
#include "card_bullet_single_fier.h"
#include "card_bullet_five_fire.h"
#include "card_bullet_circle_fire.h"
#include "card_bullet_fan_fire.h"
#include "card_bullet_Slug_fire.h"
#include "card_heal_moment.h"
#include "card_heal_regen.h"
#include "card_bullet_single_water.h"
#include "card_bullet_single_wind.h"
#include "card_bullet_five_water.h"
#include "card_bullet_five_wind.h"
#include "card_bullet_circle_water.h"
#include "card_bullet_circle_wind.h"
#include "card_bullet_fan_water.h"
#include "card_bullet_fan_wind.h"
#include "card_bullet_Slug_water.h"
#include "card_bullet_Slug_wind.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CARD_DATA_MAX (64) //登録最大数
class CardDataManager
{
private:
	 Card_Base* m_card_data[CARD_DATA_MAX];
public:
	CardDataManager() {
		for (int i = 0; i < CARD_DATA_MAX; i++)
		{
			m_card_data[i] = nullptr;
		}
		//===============================
		// ここでカードナンバーとカード属性を決める;
		//===============================
		m_card_data[0] = new Bullet_Single_Fier(Card_Type_Fier);
		m_card_data[1] = new Bullet_Single_Water(Card_Type_Water); 
		m_card_data[2] = new Bullet_Single_Wind(Card_Type_Wind); 
		m_card_data[3] = new Bullet_Circle_Fier(Card_Type_Fier); 
		m_card_data[4] = new Bullet_Circle_Water(Card_Type_Water); 
		m_card_data[5] = new Bullet_Circle_Wind(Card_Type_Wind); 
		m_card_data[6] = new Bullet_Five_Fier(Card_Type_Fier); 
		m_card_data[7] = new Bullet_Five_Water(Card_Type_Water);
		m_card_data[8] = new Bullet_Five_Wind(Card_Type_Wind); 
		m_card_data[9] = new Bullet_Fun_Fier(Card_Type_Fier); 
		m_card_data[10] = new Bullet_Fun_Water(Card_Type_Water); 
		m_card_data[11] = new Bullet_Fun_Wind(Card_Type_Wind);
		m_card_data[12] = new Bullet_Slug_Fier(Card_Type_Fier); 
		m_card_data[13] = new Bullet_Slug_Water(Card_Type_Water);
		m_card_data[14] = new Bullet_Slug_Wind(Card_Type_Wind);
		m_card_data[15] = new Heal_Moment(Card_Type_Fier);
		m_card_data[16] = new Heal_Regen(Card_Type_Fier); 
	};
	~CardDataManager() {
		for (int i = 0; i < CARD_DATA_MAX; i++)
		{
			delete m_card_data[i];
		}
	}
	//カードデータをナンバーで取得する
	Card_Base* Get_Data(int number) { if (number > -1 && number < CARD_DATA_MAX && m_card_data[number] != nullptr) { return  m_card_data[number]; } return nullptr; }
	void InitCard();

};



