#include "cardplaypdeckmanager.h"
#include "material.h"
#include "sprite.h"


void CardPlay_Manager::TabDraw() {
	D3DXVECTOR2 mousepos = GetMousePos();
	if (GetKeyboardPress(DIK_TAB))
	{
		CursprLock(false);
		for (int i = 0; i < CARD_DECKMAX; i++)
		{
			m_Card_Deck[i].m_Card->DrawPreview(D3DXVECTOR2((float)(TabDrawPos_X + TabDrawPos_CREVICE_X * (i % 5)), (float)(TabDrawPos_Y + TabDrawPos_CREVICE_Y * (i / 5))), Tab_SIZE, m_Card_Deck[i].rank);
			if ((float)(TabDrawPos_X + (i % 5) * TabDrawPos_CREVICE_X) - Tab_SIZE * 5.7f * 0.5f < mousepos.x &&
				(float)(TabDrawPos_X + (i % 5) * TabDrawPos_CREVICE_X) + Tab_SIZE * 5.7f * 0.5f > mousepos.x &&
				(float)(TabDrawPos_Y + (float)(i / 5) * TabDrawPos_CREVICE_Y) - Tab_SIZE * 8.9f * 0.5f < mousepos.y &&
				(float)(TabDrawPos_Y + (float)(i / 5) * TabDrawPos_CREVICE_Y) + Tab_SIZE * 8.9f * 0.5f > mousepos.y)
			{
				UI ui = { {800,SCREEN_CENTER_Y}, {1300,900}, {0.0f, 0.0f}, {1.0f, 1.0f}, {0.5f,0.5f,0.5f,0.7} };
				DrawScreen(ui, RefImageMaterial().m_Hp);
				m_Card_Deck[i].m_Card->DrawTextPreview({ 200,200,800,SCREEN_HEIGHT }, m_Card_Deck[i].rank);
			
			}
		
		}


	}
	if (GetKeyboardRelease(DIK_TAB))
	{
		CursprLock(true);
	}
}