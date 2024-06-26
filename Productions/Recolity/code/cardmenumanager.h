//=========================================
// ゲームスタート画面用マネージャ
//=========================================
#pragma once
#include "main.h"
#include "card_base.h"
#include "carddatamanager.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CARD_DECKMAX (20)//デッキの最大数
class CardMenu_Manager
{
	GameCard m_Card_Deck[CARD_DECKMAX];
	CardDataManager* m_PData;
public:
	CardMenu_Manager(CardDataManager* manager):m_PData(manager){
		for (int i = 0; i < CARD_DECKMAX; i++)
		{
			m_Card_Deck[i].rank = Card_Rank_One;
		}
		m_Card_Deck[0].m_Card = manager->Get_Data(0);
		m_Card_Deck[1].m_Card = manager->Get_Data(1);
		m_Card_Deck[2].m_Card = manager->Get_Data(2);
		m_Card_Deck[3].m_Card = manager->Get_Data(3);
		m_Card_Deck[4].m_Card = manager->Get_Data(4);
		m_Card_Deck[5].m_Card = manager->Get_Data(5);
		m_Card_Deck[6].m_Card = manager->Get_Data(6);
		m_Card_Deck[7].m_Card = manager->Get_Data(7);
		m_Card_Deck[8].m_Card = manager->Get_Data(8);
		m_Card_Deck[9].m_Card = manager->Get_Data(9);
		m_Card_Deck[10].m_Card = manager->Get_Data(10);
		m_Card_Deck[11].m_Card = manager->Get_Data(11);
		m_Card_Deck[12].m_Card = manager->Get_Data(12);
		m_Card_Deck[13].m_Card = manager->Get_Data(13);
		m_Card_Deck[14].m_Card = manager->Get_Data(14);
		m_Card_Deck[15].m_Card = manager->Get_Data(15);
		m_Card_Deck[16].m_Card = manager->Get_Data(16);
		m_Card_Deck[17].m_Card = manager->Get_Data(0);
		m_Card_Deck[18].m_Card = manager->Get_Data(1);
		m_Card_Deck[19].m_Card = manager->Get_Data(2);
	};
	CardMenu_Manager() = delete;
	~CardMenu_Manager() {};
	//デッキのカードのアドレスを渡す
	GameCard* GetDeckCard(int n) { return &m_Card_Deck[n]; }
	void DrawCard();//カード表示
private:

};


