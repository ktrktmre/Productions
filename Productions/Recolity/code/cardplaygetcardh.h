#pragma once

#include "main.h"
#include "card_bullet_single_fier.h"
#include "carddatamanager.h"
#include "card_base.h"
#include "cardplaypdeckmanager.h"
#include "input.h"
#include "dropcard.h"

#define DRAW_CARDPOS D3DXVECTOR2(300,540)
#define CardPLAYDrawPos_X (1150) //カード表示座標の始まりの地点 X
#define CardPLAYDrawPos_Y (160) //カード表示座標の始まりの地点 Y
#define CardPLAYDrawPos_CREVICE_X (170) //カード同氏の隙間 X
#define CardPLAYDrawPos_CREVICE_Y (250) //カード同氏の隙間 X
#define CRADPLAY_SIZE (27)//カード表示のサイズ
#define CRAD_SIZE (60)//カード表示のサイズ

#define CARD_DISCARDPOS_X (250)
#define CARD_DISCARDPOS_Y (850)
class DropCardManager;
class Card_GetCard
{
private:
	CardPlay_Manager* m_CardData;
	DropCardManager* _pDropcardmanager;
	GameCard m_InCardData;//入ってきたカードデータ
	int m_swapdata;
	int getcd;//カード取得した後捨てた時のクールタイム
	int		m_GetCardSound;//サウンド
	int		m_GetCardSound2;//サウンド
public:
	Card_GetCard() { m_InCardData.m_Card = nullptr; m_InCardData.rank = Card_Rank_One; };
	~Card_GetCard() {};
	void LinkData(CardPlay_Manager* card, DropCardManager* _drop);
	bool InData();
	void GetCard(GameCard get);
	void Uninit();
	void Update();
	void DrawUI();
	int Getgetcd() { return getcd; }
};