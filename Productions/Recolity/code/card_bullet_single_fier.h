//===================================================
// ���A�˃J�[�h����
//===================================================
#pragma once
#include "card_base.h"
#include "Texture.h"
#include "sound.h"
class Bullet_Single_Fier :public Card_Base
{
private:
	Card_Type m_Type;//����
	
public:
	Bullet_Single_Fier( Card_Type type) : m_Type(type) {};
	~Bullet_Single_Fier() {};
	void Use(int rank) override;
	void DrawPreview(D3DXVECTOR2 pos, float size, Card_Rank Rank) override;
	void DrawTextPreview(D2D1_RECT_F rect, Card_Rank Rank) override ;
};