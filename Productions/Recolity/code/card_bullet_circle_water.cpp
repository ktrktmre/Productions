#include "card_bullet_circle_water.h"
#include "material.h"
#include "text.h"
#include "Game.h"
#include "camera.h"
#include "sprite.h"
#include "player.h"

#include "sound.h"
#define DAMAGE_RANK1 (14)
#define DAMAGE_RANK2 (32)
#define DAMAGE_RANK3 (66)
void Bullet_Circle_Water::Use(int rank) {

	PlaySound("water",0.75f);
	//======================
	// カードのダメージ設定
	//======================
	int Damage = 1;
	switch (rank)
	{
	case 1:Damage = DAMAGE_RANK1;
		break;
	case 2:Damage = DAMAGE_RANK2;
		break;
	case 3:Damage = DAMAGE_RANK3;
		break;
	default:
		break;
	}
	D3DXVECTOR3 pos = GetPlayer()->GetPos();
	pos.y -= 4.5f;
	float spd = 30;
	D3DXVECTOR3 ro(
		sinf(GetCamera()->rot.y) * cosf(GetCamera()->rot.x) * spd,
		sinf(GetCamera()->rot.x) * spd,
		cosf(GetCamera()->rot.y) * cosf(GetCamera()->rot.x) * spd
	);

	Attribute_Element element = WATER_ATTRIBUTE;

	GetBulletInterface()->SetNBullet(life_penetration, player, pos, D3DXVECTOR3(GetCamera()->rot.x, GetCamera()->rot.y, GetCamera()->rot.z), { 10.0f,10.0f,10.0f },
		{ 1.0f,1.0f,1.0f,1.0f },
		Damage,
		45, 0.75f, 0.999f, 9999999,
		water, element,
		&RefImageMaterial().m_Water_Bullet, 800);
	Emitta(1, GetCamera()->pos);
}
void Bullet_Circle_Water::DrawTextPreview(D2D1_RECT_F rect, Card_Rank Rank) {
	//カード効果説明
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
	text += "自身を中心に範囲攻撃し" + std::to_string(Damage) + "ダメージを与え当たった対象に浸潤を3.5秒間与える。また、自身を中心に3マス浸潤状態にする";
	text += "\n\n";
	text += "ランク毎のダメージ:" + std::to_string(DAMAGE_RANK1) + "/" + std::to_string(DAMAGE_RANK2) + "/" + std::to_string(DAMAGE_RANK3);
	SetText(rect, text);
}
void Bullet_Circle_Water::DrawPreview(D3DXVECTOR2 pos, float size, Card_Rank Rank) {


	UI ui = { pos ,D3DXVECTOR2(5.7f * size,8.9f * size),D3DXVECTOR2(0.0f,0.0f),D3DXVECTOR2(1.0f,1.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f) ,0.0f };
	DrawScreen(ui, RefImageMaterial().m_Card_Bullet_Circle_Water);
	if (Rank > 0)
	{
		ui = { pos ,D3DXVECTOR2(5.7f * size,8.9f * size),D3DXVECTOR2(((float)(Rank - 1)) / 3.0f,0.0f),D3DXVECTOR2(1.0f / 3.0f,1.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f) ,0.0f };
		DrawScreen(ui, RefImageMaterial().m_CardFlame);
		ui = { D3DXVECTOR2(pos.x - 5.7f * size * 0.32f,pos.y - 8.9f * size * 0.35f) ,D3DXVECTOR2(1.6f * size,1.6f * size),D3DXVECTOR2(((float)(Rank - 1)) / 3.0f,0.0f),D3DXVECTOR2(1.0f / 3.0f,1.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f) ,0.0f };
		DrawScreen(ui, RefImageMaterial().m_Star);
	}
};