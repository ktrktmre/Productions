//=================================================
// カードの大本
// ここからカード効果を継承させて使う
//=================================================
#pragma once
#include "main.h"
enum Card_Rank
{
	Card_Rank_One = 1,
	Card_Rank_Twe ,
	Card_Rank_Three ,
};
enum Card_Type
{
	Card_Type_Fier = 1,	//炎
	Card_Type_Water,	//水
	Card_Type_Wind,		//風
};
class Card_Base
{
protected:
public:
	Card_Base() {};
	~Card_Base() {};
	virtual void Use(int rank) = 0;//使った時の効果
	virtual void DrawPreview(D3DXVECTOR2 pos, float size,Card_Rank Rank) = 0;//カードの強さを選んで表示
	virtual void DrawTextPreview( D2D1_RECT_F rect,  Card_Rank Rank) = 0;//カードの効果説明
};
//=============================
// カードマネージャが持つ構造体
//=============================
typedef struct {
	Card_Base* m_Card;
	Card_Rank rank;
}GameCard;

