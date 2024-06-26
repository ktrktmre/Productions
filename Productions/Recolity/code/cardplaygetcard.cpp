#include "cardplaygetcardh.h"
#include "material.h"
#include "sprite.h"
#include "Game.h"
#include "text.h"

void Card_GetCard::LinkData(CardPlay_Manager* card, DropCardManager* _drop)
{
	m_GetCardSound = LoadSound("paper");
	m_GetCardSound2 = LoadSound("bottun3");
		_pDropcardmanager = _drop;
		m_CardData = card;
		m_InCardData.m_Card = nullptr;
		m_InCardData.rank = Card_Rank_One;

	
}

bool Card_GetCard::InData()
{

		if (m_InCardData.m_Card != nullptr)
		{
			return true;
		}
		return false;
}

void Card_GetCard::GetCard(GameCard get)
{
	PlaySound(m_GetCardSound, 0, 1.0f);

		if (getcd == 0)
		{
			m_InCardData = get;
			m_swapdata = -1;
		}
}

void Card_GetCard::Uninit()
{
	StopSound(m_GetCardSound);
	StopSound(m_GetCardSound2);
}

void Card_GetCard::Update()
{
	if (getcd > 0)
	{
		getcd--;
	}
		if (m_InCardData.m_Card != nullptr)
		{
			CursprLock(false);
			D3DXVECTOR2 mousepos = GetMousePos();
			if (m_swapdata < 0)
			{
				for (int i = 0; i < CARD_DECKMAX; i++)
				{
					if (IsMouseLeftTriggered() &&
						(float)(CardPLAYDrawPos_X + (i % 5) * CardPLAYDrawPos_CREVICE_X) - CRADPLAY_SIZE * 5.7f * 0.5f < mousepos.x &&
						(float)(CardPLAYDrawPos_X + (i % 5) * CardPLAYDrawPos_CREVICE_X) + CRADPLAY_SIZE * 5.7f * 0.5f > mousepos.x &&
						(float)(CardPLAYDrawPos_Y + (float)(i / 5) * CardPLAYDrawPos_CREVICE_Y) - CRADPLAY_SIZE * 8.9f * 0.5f < mousepos.y &&
						(float)(CardPLAYDrawPos_Y + (float)(i / 5) * CardPLAYDrawPos_CREVICE_Y) + CRADPLAY_SIZE * 8.9f * 0.5f > mousepos.y)
					{
						m_swapdata = i;
						PlaySound(m_GetCardSound2, 0, 1.0f);
					}
				}
			}
			//捨てた場合足元に出る
			if (IsMouseLeftTriggered() &&
				mousepos.x > CARD_DISCARDPOS_X - 80 &&
				mousepos.x < CARD_DISCARDPOS_X + 80 &&
				mousepos.y > CARD_DISCARDPOS_Y - 30 &&
				mousepos.y < CARD_DISCARDPOS_Y + 30)
			{
				_pDropcardmanager->SetDropCard(m_InCardData,D3DXVECTOR3(GetPlayer()->GetPos().x,0.0f, GetPlayer()->GetPos().z));
				m_InCardData.m_Card = nullptr;
				getcd = 150;
			}
			if (m_swapdata > -1)
			{
				if (IsMouseLeftTriggered() &&
					mousepos.x > SCREEN_CENTER_X - 100 - 40 &&
					mousepos.x < SCREEN_CENTER_X - 100 + 40 &&
					mousepos.y > SCREEN_CENTER_Y + 40 - 20 &&
					mousepos.y < SCREEN_CENTER_Y + 40 + 20)
				{
					m_CardData->SetCard(m_swapdata, m_InCardData);
					m_swapdata = -1;
					m_InCardData.m_Card = nullptr;
					PlaySound(m_GetCardSound2, 0, 1.0f);
					CursprLock(true);
				}
				if (IsMouseLeftTriggered() &&
					mousepos.x > SCREEN_CENTER_X + 100 - 40 &&
					mousepos.x < SCREEN_CENTER_X + 100 + 40 &&
					mousepos.y > SCREEN_CENTER_Y + 40 - 20 &&
					mousepos.y < SCREEN_CENTER_Y + 40 + 20)
				{
					m_swapdata = -1;
					PlaySound(m_GetCardSound2, 0, 1.0f);
					CursprLock(true);
				}

			}
		}

	
}

void Card_GetCard::DrawUI() {
	if (m_InCardData.m_Card != nullptr)
	{
		UI ui;

		ui = { D3DXVECTOR2(SCREEN_CENTER_X,SCREEN_CENTER_Y) ,D3DXVECTOR2(SCREEN_WIDTH,SCREEN_HEIGHT),D3DXVECTOR2(0.0f,0.0f),D3DXVECTOR2(0.5f ,0.5f),D3DXCOLOR(0.3f,0.3f,0.3f,0.5f) ,0.0f };
		DrawScreen(ui, RefImageMaterial().m_Hp);
		//手に入れたカード表示
		m_InCardData.m_Card->DrawPreview(DRAW_CARDPOS, CRAD_SIZE, m_InCardData.rank);
		m_InCardData.m_Card->DrawTextPreview(D2D1_RECT_F{ 500,400,1050,SCREEN_HEIGHT }, m_InCardData.rank);

		//マウスカーソルがあっているところを取る
		int tr = -1;
		D3DXVECTOR2 mousepos = GetMousePos();
		for (int i = 0; i < CARD_DECKMAX; i++)
		{
			if ((float)(CardPLAYDrawPos_X + (i % 5) * CardPLAYDrawPos_CREVICE_X) - CRADPLAY_SIZE * 5.7f * 0.5f < mousepos.x &&
				(float)(CardPLAYDrawPos_X + (i % 5) * CardPLAYDrawPos_CREVICE_X) + CRADPLAY_SIZE * 5.7f * 0.5f > mousepos.x &&
				(float)(CardPLAYDrawPos_Y + (float)(i / 5) * CardPLAYDrawPos_CREVICE_Y) - CRADPLAY_SIZE * 8.9f * 0.5f < mousepos.y &&
				(float)(CardPLAYDrawPos_Y + (float)(i / 5) * CardPLAYDrawPos_CREVICE_Y) + CRADPLAY_SIZE * 8.9f * 0.5f > mousepos.y)
			{
				tr = i;
			}

			//所持カードの表示
			m_CardData->DrawCard(i, D3DXVECTOR2((float)(CardPLAYDrawPos_X + (i % 5) * CardPLAYDrawPos_CREVICE_X), CardPLAYDrawPos_Y + (float)(i / 5) * CardPLAYDrawPos_CREVICE_Y), CRADPLAY_SIZE);

		}
		ui = { D3DXVECTOR2(CARD_DISCARDPOS_X ,CARD_DISCARDPOS_Y) ,D3DXVECTOR2(160,60),D3DXVECTOR2(0.0f,0.0f),D3DXVECTOR2(0.5f ,0.5f),D3DXCOLOR(0.8f,0.8f,0.8f,1.0f) ,0.0f };
		DrawScreen(ui, RefImageMaterial().m_Hp);
		SetText({ CARD_DISCARDPOS_X - 33,CARD_DISCARDPOS_Y - 15,SCREEN_WIDTH ,SCREEN_HEIGHT }, "捨てる");

		//マウスポインターに追従してくるテキスト説明
		if (tr >= 0)
		{
			D3DXVECTOR2 mousepos = GetMousePos();
			if (mousepos.x > SCREEN_WIDTH - 351)
			{
				mousepos.x -= 351;
			}
			if (mousepos.y > SCREEN_HEIGHT - 541)
			{
				mousepos.y = SCREEN_HEIGHT - 541;
			}
			 ui = { D3DXVECTOR2(mousepos.x + 350,mousepos.y + 270) ,D3DXVECTOR2(700,560),D3DXVECTOR2(0.0f,0.0f),D3DXVECTOR2(1.0f ,1.0f),D3DXCOLOR(0.3f,0.3f,0.3f,0.5f) };
			DrawScreen(ui, RefImageMaterial().m_Hp);

			m_CardData->DrawCardText(tr, D2D1_RECT_F{ mousepos.x, mousepos.y, mousepos.x + 350, mousepos.y + 540 });

		}
		//選択したカードを入れ替えるか質問するテキストボックス
		if (m_swapdata > -1)
		{
			UI ui = { D3DXVECTOR2(SCREEN_CENTER_X,SCREEN_CENTER_Y) ,D3DXVECTOR2(600,400),D3DXVECTOR2(0.0f,0.0f),D3DXVECTOR2(0.5f ,0.5f),D3DXCOLOR(0.3f,0.3f,0.3f,1.0f) ,0.0f };
			DrawScreen(ui, RefImageMaterial().m_Hp);
			SetText({ SCREEN_CENTER_X  - 150,SCREEN_CENTER_Y -100,SCREEN_CENTER_X + 250 ,SCREEN_CENTER_Y + 200 },"選択したカードと入れ替えますか？");
			ui = { D3DXVECTOR2(SCREEN_CENTER_X - 100,SCREEN_CENTER_Y + 40) ,D3DXVECTOR2(80,40),D3DXVECTOR2(0.0f,0.0f),D3DXVECTOR2(0.5f ,0.5f),D3DXCOLOR(0.7f,0.35f,0.5f,1.0f) ,0.0f };
			DrawScreen(ui, RefImageMaterial().m_Hp);
			ui = { D3DXVECTOR2(SCREEN_CENTER_X + 100,SCREEN_CENTER_Y + 40) ,D3DXVECTOR2(80,40),D3DXVECTOR2(0.0f,0.0f),D3DXVECTOR2(0.5f ,0.5f),D3DXCOLOR(0.1f,0.4f,0.8f,1.0f) ,0.0f };
			DrawScreen(ui, RefImageMaterial().m_Hp);
			SetText({ SCREEN_CENTER_X - 120,SCREEN_CENTER_Y + 30,SCREEN_WIDTH ,SCREEN_HEIGHT }, "はい");
			SetText({ SCREEN_CENTER_X + 73,SCREEN_CENTER_Y + 30,SCREEN_WIDTH ,SCREEN_HEIGHT }, "いいえ");
		}
		ui = { D3DXVECTOR2(GetMousePos().x + 16,GetMousePos().y + 16) ,D3DXVECTOR2(32,32),D3DXVECTOR2(0.0f,0.0f),D3DXVECTOR2(1.0f ,1.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f) };
		DrawScreen(ui, RefImageMaterial().m_Cursor);
	}
};