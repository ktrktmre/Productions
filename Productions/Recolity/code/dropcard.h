#pragma once
#include "card_base.h"
#include "carddatamanager.h"
#include "cardplaygetcardh.h"

#include <list>
typedef struct {
	D3DXVECTOR3 Droppos;
	GameCard	carddata;

}Dropcard; 
class Card_GetCard;
class CardPlay_Manager;
class DropCardManager
{
	std::list<Dropcard>		m_DropList;
	CardDataManager*		_pCarddata;
	CardPlay_Manager*		m_PlayDeck;
	Card_GetCard*			_pGetcard;
private:

public:
	DropCardManager(CardDataManager* pCardData, Card_GetCard* pGetCard, CardPlay_Manager* playdek);
	DropCardManager() = delete;
	~DropCardManager() = default;
	void Uninit();
	void Update();
	void Draw();
	void SetDropCard(int no, Card_Rank rank, D3DXVECTOR3 pos);
	void SetDropCard(GameCard gamecard, D3DXVECTOR3 pos);
	void NoHaveCardDrop(D3DXVECTOR3 pos, float ranc2drop);
};


