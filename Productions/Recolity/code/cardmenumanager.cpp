#pragma once
#include "cardmenumanager.h"
#include "carddatamanager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define InitCardRank Card_Rank_One //カードの初期ランク
#define CardDrawPos_X (300) //カード表示座標の始まりの地点 X
#define CardDrawPos_Y (160) //カード表示座標の始まりの地点 Y
#define CardDrawPos_CREVICE_X (150) //カード同氏の隙間 X
#define CardDrawPos_CREVICE_Y (250) //カード同氏の隙間 X
#define CRAD_SIZE (25)//カード表示のサイズ

void CardMenu_Manager::DrawCard() {
	for (int i = 0; i < CARD_DECKMAX; i++)
	{
		if (m_Card_Deck[i].m_Card != nullptr)
		{
			//=================================
			// カードを表示の参照される値
			//=================================
			int no = m_Card_Deck[i].rank;
			//画面表示
			m_Card_Deck[i].m_Card->DrawPreview(D3DXVECTOR2(CardDrawPos_X + (float)(i % 5) * CardDrawPos_CREVICE_X, (float)(CardDrawPos_Y + (int)((float)i / 5.0f) * CardDrawPos_CREVICE_Y)), CRAD_SIZE, (Card_Rank)no);
		}
	}

}
