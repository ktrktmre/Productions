#include "dropcard.h"
#include "sprite.h"
#include "material.h"
#include "Game.h"
float rotecard = 0.0f;
DropCardManager::DropCardManager(CardDataManager* pCardData, Card_GetCard* pGetCard, CardPlay_Manager* playdek)
{
	_pCarddata	= pCardData;
	_pGetcard	= pGetCard;
	m_PlayDeck = playdek;
}

void DropCardManager::Uninit()
{
	m_DropList.erase(m_DropList.begin(), m_DropList.end());
}

void DropCardManager::Update()
{

	rotecard += 0.02f;
	D3DXVECTOR3 plpos = GetPlayer()->GetPos();
	Card_GetCard *card = _pGetcard;
	if (_pGetcard->Getgetcd() == 0)
	{
		auto it = std::find_if(m_DropList.begin(), m_DropList.end(), [plpos, card](Dropcard p) {
			if (pow(p.Droppos.x - plpos.x, 2) + pow(p.Droppos.z - plpos.z, 2) < 2500)
			{

				card->GetCard(p.carddata);

				return true;
			}
			return false;
			});
		if (it == m_DropList.end()) return;

		m_DropList.erase(it);
	}
	
}
void DropCardManager::Draw()
{
	for (Dropcard a : m_DropList) {
		Object obj;
		obj.m_Rot.x = 0.0f;
		obj.m_Pos = a.Droppos;
		obj.m_Scl = { 1.0f ,1.0f ,1.0f };
		Draw3DModel(obj, RefModelMaterial().m_Carddai);
		obj.m_Pos.y += 70.0f;
		obj.m_Scl = { 7.0f ,7.0f ,7.0f };
		obj.m_Rot.y = rotecard;
		Draw3DModel(obj, RefModelMaterial().m_Carddai_Card);
	}
}

void DropCardManager::SetDropCard(int no, Card_Rank rank, D3DXVECTOR3 pos)
{
	m_DropList.push_back({ pos, {_pCarddata->Get_Data(no),rank } });
}

void DropCardManager::SetDropCard(GameCard gamecard, D3DXVECTOR3 pos)
{
	m_DropList.push_back({ pos, gamecard });
}

void DropCardManager::NoHaveCardDrop(D3DXVECTOR3 pos,float ranc2drop)
{
	std::list< GameCard> aki;
	float ch = frand();
	if (ch < ranc2drop)
	{
		for (int i = 0; i < 17; i++)
		{
			aki.push_back({ _pCarddata->Get_Data(i),Card_Rank_Twe });
		}
	}
	else
	{
		for (int i = 0; i < 17; i++)
		{
			aki.push_back({ _pCarddata->Get_Data(i),Card_Rank_Three });
		}
	}

	int s = 0;
	for (int i = aki.size() -1; i > -1; i--)
	{
		int num = 0;//カード枚数
		GameCard a = *std::next(aki.begin(), i);
		//デッキのカード検索
		for (int i = 0; i < 20; i++)
		{
			if (m_PlayDeck->GetCard(i)->m_Card == a.m_Card &&
				m_PlayDeck->GetCard(i)->rank == a.rank)
			{
				num++;
			}
		}
		for (Dropcard b : m_DropList)
		{
			if (b.carddata.m_Card == a.m_Card &&
				b.carddata.rank == a.rank)
			{
				num++;
			}

		}
		if (num > 1)
		{
			aki.erase(std::next(aki.begin(), i));
		}
	}
	 
	 if (aki.size() > 0)
	 {
		 int ra = (int)rand() % (int)aki.size();
		GameCard g = *std::next(aki.begin(), ra);
		SetDropCard(g, { pos.x,0.0f,pos.z});
	 }
}



