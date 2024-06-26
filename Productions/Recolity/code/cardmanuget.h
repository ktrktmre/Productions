#pragma once
#include "main.h"
#include "carddatamanager.h"
#include "card_base.h"
#include "cardmenumanager.h"
class CardMenu_Manager;
class CardMenu_Get
{
private:
	CardMenu_Manager*	m_PCardMenu_Manager;//メニューマネージャのポインター
	CardDataManager*	m_PCardDataManager;//カードのデータマネージャのポインター
	GameCard			m_InCardData;//入ってきたカードデータ
	GameCard			m_PullData;//つかんでるデータ
	bool				m_SameCard;//同じカードが2枚以上入っているかのテキストを出す 
public:
	CardMenu_Get(CardMenu_Manager* pmnager, CardDataManager* pdata);
	CardMenu_Get()=delete;
	~CardMenu_Get();
	void Update();
	void DrawUI();
	bool InData() {
		if (m_InCardData.m_Card != nullptr)
		{
			return true;
		}
		return false;
	};
	void GetCard(GameCard get) {
			m_InCardData = get;
	}
	//============================
	// 同じカードがデッキに2毎以上入っているか検知してくれる
	//============================
	bool Search(GameCard data);
};



