#include "cardmanuget.h"
#include "input.h"
#include "material.h"
#include "sprite.h"
#include "text.h"
#define DEK_STARTPOS_X (750)
#define DEK_STARTPOS_Y (250)
#define DEK_CARD_SIZE (20.0f)

#define DATA_STARTPOS_X (1430)
#define DATA_STARTPOS_Y (185)
#define DATA_CARD_SIZE (16.0f)
CardMenu_Get::CardMenu_Get(CardMenu_Manager* pmnager, CardDataManager* pdata)
	:m_PCardMenu_Manager(pmnager),m_PCardDataManager(pdata) {}

CardMenu_Get::~CardMenu_Get(){}
void CardMenu_Get::Update() {
	D3DXVECTOR2 mopos = GetMousePos();
	if (m_SameCard == false)
	{
		for (int i = 0; i < CARD_DATA_MAX; i++)
		{

			if (m_PCardDataManager->Get_Data(i) != nullptr &&
				mopos.x > DATA_STARTPOS_X + (float)((DATA_CARD_SIZE * 6.0f) * (i % 5)) - DATA_CARD_SIZE * 3.0f &&
				mopos.x < DATA_STARTPOS_X + (float)((DATA_CARD_SIZE * 6.0f) * (i % 5)) + DATA_CARD_SIZE * 3.0f &&
				mopos.y > DATA_STARTPOS_Y + (float)(DATA_CARD_SIZE * 11.0f) * (int)((float)i / 5.0f) - DATA_CARD_SIZE * 5.5f &&
				mopos.y < DATA_STARTPOS_Y + (float)(DATA_CARD_SIZE * 11.0f) * (int)((float)i / 5.0f) + DATA_CARD_SIZE * 5.5f &&
				IsMouseLeftTriggered()
				)
			{
				m_InCardData = { m_PCardDataManager->Get_Data(i),Card_Rank_One };
				m_PullData = { m_PCardDataManager->Get_Data(i),Card_Rank_One };
			}
			if (!IsMouseLeftPressed() && m_PullData.m_Card != nullptr)
			{

				for (int j = 0; j < 20; j++)
				{
					if (
						mopos.x > DEK_STARTPOS_X + (float)((DEK_CARD_SIZE * 6.0f * (j % 5))) - DEK_CARD_SIZE * 3.0f &&
						mopos.x < DEK_STARTPOS_X + (float)((DEK_CARD_SIZE * 6.0f * (j % 5))) + DEK_CARD_SIZE * 3.0f &&
						mopos.y > DEK_STARTPOS_Y + (float)(DEK_CARD_SIZE * 11.0f) * (int)((float)j / 5.0f) - DEK_CARD_SIZE * 5.5f &&
						mopos.y < DEK_STARTPOS_Y + (float)(DEK_CARD_SIZE * 11.0f) * (int)((float)j / 5.0f) + DEK_CARD_SIZE * 5.5f)
					{
						if (Search(m_PullData) == true)
						{
							m_SameCard = true;
						}
						if (Search(m_PullData) == false)
						{
							m_PCardMenu_Manager->GetDeckCard(j)->m_Card = m_PullData.m_Card;
						}

					}
				}

				m_PullData = { nullptr,Card_Rank_One };
			}
		}
	}
	
	if (IsMouseLeftTriggered() && m_SameCard == true &&
		mopos.x > 895 && mopos.x < 995 && 
		mopos.y > 515 && mopos.y < 565)
	{
		m_SameCard = false;
	}
}
void CardMenu_Get::DrawUI()
{
	UI ui;
	for (int i = 0; i < 20; i++)
	{
		m_PCardMenu_Manager->GetDeckCard(i)->m_Card->DrawPreview({ 
			DEK_STARTPOS_X + (float)((DEK_CARD_SIZE *6.0f) * (i % 5)) ,
			DEK_STARTPOS_Y + (float)(DEK_CARD_SIZE * 11.0f ) * (int)((float)i / 5.0f) }, 
			DEK_CARD_SIZE, Card_Rank_One);
	}
	for (int i = 0; i < CARD_DATA_MAX; i++)
	{
		if (m_PCardDataManager->Get_Data(i) != nullptr)
		{
			m_PCardDataManager->Get_Data(i)->DrawPreview({ DATA_STARTPOS_X + (float)((DATA_CARD_SIZE * 6.0f) * (i % 5)),DATA_STARTPOS_Y + (float)(DATA_CARD_SIZE * 11.0f) * (int)((float)i / 5.0f) }, DATA_CARD_SIZE, Card_Rank_One);
		}
	}
	if (m_InCardData.m_Card != nullptr )
	{
		m_InCardData.m_Card->DrawPreview({ 150,350 }, 20, Card_Rank_One);
		m_InCardData.m_Card->DrawTextPreview({ 100,450, 550,1080 }, Card_Rank_One);
	}
	if (m_PullData.m_Card != nullptr)
	{
		m_InCardData.m_Card->DrawPreview(GetMousePos(), 15, Card_Rank_One);
	}

	if (m_SameCard)
	{
		ui = { D3DXVECTOR2(945,540) ,D3DXVECTOR2(500,300),D3DXVECTOR2(0.0f,0.0f),D3DXVECTOR2(0.5f ,0.5f),D3DXCOLOR(0.4f,0.4f,0.4f,1.0f) };
		DrawScreen(ui, RefImageMaterial().m_Hp);
		SetText({ 960-200 ,480,960+200 ,1080}, "同一のカードは２枚までしかデッキに入れられません");
		ui = { D3DXVECTOR2(945,540) ,D3DXVECTOR2(100,50),D3DXVECTOR2(0.0f,0.0f),D3DXVECTOR2(0.5f ,0.5f),D3DXCOLOR(0.6f,0.5f,0.3f,1.0f) };
		DrawScreen(ui, RefImageMaterial().m_Hp);
		SetText({ 960 - 30 ,530,960 + 200 ,1080 }, "OK");
	}
}

bool CardMenu_Get::Search(GameCard data)
{
	bool search = true;
	int count = 0;
	for (int  i = 0; i < 20; i++)
	{
		if (m_PCardMenu_Manager->GetDeckCard(i)->m_Card == data.m_Card)
		{
			count++;
		}
		
	}
	if (count < 2)
	{
		search = false;
	}
	return search;
}




