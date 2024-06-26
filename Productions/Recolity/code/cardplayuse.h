#pragma once
#include "card_base.h"
#include "cardplaypdeckmanager.h"
#include <list>
#define CARD_SIZE (25)
class CardPlay_Use
{
private:
	std::list<GameCard*>	m_Yamafuda;//山札
	std::list<GameCard*>	m_Hand;//手札
	std::list<GameCard*>	m_Boti;//墓地カード
public:
	CardPlay_Use() {};
	~CardPlay_Use() {};
	//プレイデッキとのリンク
	void InitPlayUse(CardPlay_Manager* card) {
		for (int i = 0; i < CARD_DECKMAX; i++)
		{
			m_Yamafuda.push_back(card->GetCard(i));
		}
	
	}
	void Uninit() {
		m_Yamafuda.erase(m_Yamafuda.begin(), m_Yamafuda.end());
		m_Hand.erase(m_Hand.begin(), m_Hand.end());
		m_Boti.erase(m_Boti.begin(), m_Boti.end());
	}
	//山札からカードを引く
	void CardDraw() {
		if ((int)m_Yamafuda.size() == 0)
		{
			CardReset();
		}
		int index = -1;
		if ((int)m_Yamafuda.size() > 0)
		{
			index = (int)(frand() * (float)m_Yamafuda.size());
			if (index > -1)
			{
				m_Hand.push_back(*std::next(m_Yamafuda.begin(), index));
				m_Yamafuda.erase(std::next(m_Yamafuda.begin(), index));
			}
		}
	}
	//手札から墓地に捨てる
	//no:捨てるカードのイテレーター
	void CardDiscard(int no) {
		if (no < m_Hand.size())
		{
			GameCard* n = *std::next(m_Hand.begin(), no);
			n->m_Card->Use(n->rank);
			m_Boti.push_back(*std::next(m_Hand.begin(), no));
			m_Hand.erase(std::next(m_Hand.begin(), no));

		}
	};

	//山札がなくなったら墓地から山札へ移動
	//これはUpdateで必ずよびだすこと
	void CardReset() {
		if (m_Yamafuda.size() <= 0)
		{
			for (int i = 0; i < m_Boti.size(); i++)
			{
				m_Yamafuda.push_back(*std::next(m_Boti.begin(), i));
			}
			m_Boti.clear();
		}
	
	}
	//表示処理
	void Draw(int clect);
	//デバック用の表示山札手札墓地全部見える
	void DebugDraw(int clect) ;
	//カードのコスト取得
	int CardDiscardCost(int no) {
		GameCard* n = *std::next(m_Hand.begin(), no);
		return (int)n->rank;
	}
	//持っているカード枚数を取得する
	int CardGetHandNum() { return (int)m_Hand.size(); };
};
