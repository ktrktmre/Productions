#include "card_bullet_Slug_fire.h"
#include "sprite.h"
#include "main.h"
#include "material.h"
#include "text.h"
#include "Game.h"
#include "player.h"
#include "bullet_management.h"
#include "bullet_interface.h"
#include "camera.h"
#include "sound.h"
#define DAMAGE_RANK1 (6)
#define DAMAGE_RANK2 (14)
#define DAMAGE_RANK3 (38)
#define RANGE (1000)
void Bullet_Slug_Fier::Use(int rank) {

	PlaySound("fier", 0.75f);
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

	Attribute_Element element = FIER_ATTRIBUTE;

	float ra = -D3DX_PI + D3DX_PI * frand() * 2.0f;
	float ran = frand() * 0.03f;
	GetBulletInterface()->SetNBullet(bullet, player, pos, D3DXVECTOR3(GetCamera()->rot.x + cosf(ra) * ran, GetCamera()->rot.y +  sinf(ra) * ran, GetCamera()->rot.z), { 10.0f,10.0f,10.0f },
		{ 1.0f,1.0f,1.0f,1.0f },
		Damage, 45, 0.0f, 1.0f, RANGE,
		fire, element,
		&RefImageMaterial().m_Cannon_Bullet);
	for (int i = 0; i < 6; i++)
	{
		float ran = D3DX_PI / 3.0f * (float)i;
		float ranm =  0.1f;

		float ran2 = -D3DX_PI + D3DX_PI * frand() * 2.0f;
		float ranm2 = frand() * 0.03f;
		GetBulletInterface()->SetNBullet(bullet, player, pos, D3DXVECTOR3(GetCamera()->rot.x + cosf(ran) * ranm + cosf(ran2) * ranm2, GetCamera()->rot.y + sinf(ran) * ranm + sinf(ran2) * ranm2, GetCamera()->rot.z), { 10.0f,10.0f,10.0f },
			{ 1.0f,1.0f,1.0f,1.0f },
			Damage, 45, 0.0f, 1.0f, 1500,
			fire, element,
			&RefImageMaterial().m_Cannon_Bullet);
	}
}
void Bullet_Slug_Fier::DrawTextPreview(D2D1_RECT_F rect, Card_Rank Rank) {
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
	text += "視点方向に7発の弾をランダムに発射し" + std::to_string(Damage * 7) + "ダメージを与え当たった対象に燃焼を10秒間与える。また、地面に当たるもしくは最大射程の時に下の床が紙の場合床を燃焼状態にする";
	text += "\n\n";
	text += "ランク毎の1発当たりのダメージ:" + std::to_string(DAMAGE_RANK1) + "/" + std::to_string(DAMAGE_RANK2) + "/" + std::to_string(DAMAGE_RANK3);
	SetText(rect, text);
}
void Bullet_Slug_Fier::DrawPreview(D3DXVECTOR2 pos, float size, Card_Rank Rank) {

	UI ui = { pos ,D3DXVECTOR2(5.7f * size,8.9f * size),D3DXVECTOR2(0.0f,0.0f),D3DXVECTOR2(1.0f,1.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f) ,0.0f };
	DrawScreen(ui, RefImageMaterial().m_Card_Bullet_Slug_Fire);
	if (Rank > 0)
	{
		ui = { pos ,D3DXVECTOR2(5.7f * size,8.9f * size),D3DXVECTOR2(((float)(Rank - 1)) / 3.0f,0.0f),D3DXVECTOR2(1.0f / 3.0f,1.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f) ,0.0f };
		DrawScreen(ui, RefImageMaterial().m_CardFlame);
		ui = { D3DXVECTOR2(pos.x - 5.7f * size * 0.32f,pos.y - 8.9f * size * 0.35f) ,D3DXVECTOR2(1.4f * size,1.4f * size),D3DXVECTOR2(((float)(Rank - 1)) / 3.0f,0.0f),D3DXVECTOR2(1.0f / 3.0f,1.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f) ,0.0f };
		DrawScreen(ui, RefImageMaterial().m_Star);
	}
};