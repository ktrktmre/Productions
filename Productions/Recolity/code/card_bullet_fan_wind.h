#pragma once
//===================================================
// ‰Šî”­ËƒJ[ƒhˆ—
//===================================================
#pragma once
#include "card_base.h"
#include "Texture.h"

class Bullet_Fun_Wind :public Card_Base
{
private:
	Card_Type m_Type;//‘®«
	
public:
	Bullet_Fun_Wind(Card_Type type) : m_Type(type) {};
	~Bullet_Fun_Wind() {};
	void Use(int rank) override;
	void DrawPreview(D3DXVECTOR2 pos, float size, Card_Rank Rank) override;
	void DrawTextPreview(D2D1_RECT_F rect, Card_Rank Rank) override;
};