#include "card_bullet_five_water.h"
#include "text.h"
#include "Game.h"
#include "sprite.h"
#include "material.h"
#include "sound.h"
#define DAMAGE_RANK1 (3)
#define DAMAGE_RANK2 (7)
#define DAMAGE_RANK3 (16)

void Bullet_Five_Water::Use(int rank) {

	switch (rank)
	{
	case 1://ランクごとの効果
		GetPlayer()->effect.SetEffectBullet(water, low);
		break;
	case 2:
		GetPlayer()->effect.SetEffectBullet(water, mid);
		break;
	case 3:
		GetPlayer()->effect.SetEffectBullet(water, high);
		break;
	default:
		break;
	}
}
void Bullet_Five_Water::DrawTextPreview(D2D1_RECT_F rect, Card_Rank Rank) {
	int Damage = 1;
	switch (Rank)
	{
	case Card_Rank_One:Damage = DAMAGE_RANK1;
		break;
	case Card_Rank_Twe:Damage = DAMAGE_RANK2;
		break;
	case Card_Rank_Three:Damage = DAMAGE_RANK3;
		break;
	default:
		break;
	}
	std::string text;
	text += "視点方向に５発球を連続で発射し1発当たり" + std::to_string(Damage * 5) + "ダメージを与え当たった対象に浸潤を3.5秒間与える。また、地面に当たるもしくは最大射程の時に下の床が紙の場合床を浸潤状態にする";
	text += "\n\n";
	text += "ランク毎の1発当たりのダメージ:" + std::to_string(DAMAGE_RANK1) + "/" + std::to_string(DAMAGE_RANK2) + "/" + std::to_string(DAMAGE_RANK3);
	SetText(rect, text);
}
void Bullet_Five_Water::DrawPreview(D3DXVECTOR2 pos, float size, Card_Rank Rank) {
	UI ui = { pos ,D3DXVECTOR2(5.7f * size,8.9f * size),D3DXVECTOR2(0.0f,0.0f),D3DXVECTOR2(1.0f,1.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f) ,0.0f };
	DrawScreen(ui, RefImageMaterial().m_Card_Bullet_Rapid_Water);
	if (Rank > 0)
	{
		ui = { pos ,D3DXVECTOR2(5.7f * size,8.9f * size),D3DXVECTOR2(((float)(Rank - 1)) / 3.0f,0.0f),D3DXVECTOR2(1.0f / 3.0f,1.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f) ,0.0f };
		DrawScreen(ui, RefImageMaterial().m_CardFlame);
		ui = { D3DXVECTOR2(pos.x - 5.7f * size * 0.32f,pos.y - 8.9f * size * 0.35f) ,D3DXVECTOR2(1.4f * size,1.4f * size),D3DXVECTOR2(((float)(Rank - 1)) / 3.0f,0.0f),D3DXVECTOR2(1.0f / 3.0f,1.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f) ,0.0f };
		DrawScreen(ui, RefImageMaterial().m_Star);
	}

};

