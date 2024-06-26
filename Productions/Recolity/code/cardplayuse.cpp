#include "cardplayuse.h"

void CardPlay_Use::Draw(int clect)
{
	
		int pos = (int)m_Hand.size();
		int count = 0;
		float cardsizex = CARD_SIZE * 5.7f;
		float cardsizey = CARD_SIZE * 8.9f;
		for (GameCard* a : m_Hand)
		{
			float fitHub = 0;
			if (count == clect)
			{
				fitHub = 80;
			}
			a->m_Card->DrawPreview(D3DXVECTOR2(SCREEN_WIDTH - cardsizex * 0.5f - pos * cardsizex + count * cardsizex, SCREEN_HEIGHT - cardsizey * 0.6f - fitHub - 50), CARD_SIZE, a->rank);
			count++;
		}
	
}

void CardPlay_Use::DebugDraw(int clect)
{
	int pos = (int)m_Hand.size();
	int count = 0;
	int count2 = 0;
	int count3 = 0;
	float cardsizex = CARD_SIZE * 5.7f * 0.5f;
	float cardsizey = CARD_SIZE * 8.9f * 0.5f;
	for (GameCard* a : m_Yamafuda)
	{
		a->m_Card->DrawPreview(D3DXVECTOR2(300 + count2 * cardsizex, 200 - cardsizey * 0.6f), CARD_SIZE * 0.5f, a->rank);
		count2++;
	}
	for (GameCard* a : m_Hand)
	{
		float fitHub = 0;
		if (count == clect)
		{
			fitHub = 80;
		}
		a->m_Card->DrawPreview(D3DXVECTOR2(300 + count * cardsizex, 500 - cardsizey * 0.6f - fitHub), CARD_SIZE * 0.5f, a->rank);
		count++;
	}
	for (GameCard* a : m_Boti)
	{
		a->m_Card->DrawPreview(D3DXVECTOR2(300 + count3 * cardsizex, 700 - cardsizey * 0.6f), CARD_SIZE * 0.5f, a->rank);
		count3++;
	}
}
