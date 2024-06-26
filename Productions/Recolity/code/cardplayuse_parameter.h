#pragma once
#include "cardplayuse_mana.h"
#include "cardplayuse_drawtimer.h" 
#include "sprite.h"
#include "material.h"
#include "main.h"
class CardPlay_Use_Parameter
{
private:
	CardPlay_Use_DrawTime	m_timer;
	CardPlay_Use_Mana		m_mana;
public:
	CardPlay_Use_Parameter() {};
	~CardPlay_Use_Parameter() {};
	void Init() {
		m_timer.SetDrawTime(0);
		m_mana.IncreaseMana(CARD_MANA_MAX);
	}
	void Update() {
		m_mana.Update();
		m_timer.Update();
	
	}



	CardPlay_Use_Mana* GetMana()
	{
		return &m_mana;
	}

	CardPlay_Use_DrawTime* GetTimer()
	{
		return &m_timer;
	}



};