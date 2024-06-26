#include "card_bullet_fan_wind.h"
#include "sprite.h"
#include "material.h"
#include "Game.h"
#include "text.h"
#include "player.h"
#include "bullet_management.h"
#include "bullet_interface.h"
#include "camera.h"
#include "sound.h"
#define DAMAGE_RANK1 (8)
#define DAMAGE_RANK2 (17)
#define DAMAGE_RANK3 (36)
#define RANGE (1500)
void Bullet_Fun_Wind::Use(int rank) {
	
	PlaySound("wind", 0.75f);
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

	Attribute_Element element = WIND_ATTRIBUTE;
	for (int i = 0; i < 5; i++)
	{
		GetBulletInterface()->SetNBullet(bullet, player, pos, D3DXVECTOR3(GetCamera()->rot.x, GetCamera()->rot.y + (float)i * 0.035f - 0.07f, GetCamera()->rot.z), { 10.0f,10.0f,10.0f },
			{ 1.0f,1.0f,1.0f,1.0f },
			Damage, 
			45, 0.0f, 1.0f, RANGE,
			wind, element,
			&RefImageMaterial().m_Wind_Bullet);
	}

}
void Bullet_Fun_Wind::DrawTextPreview(D2D1_RECT_F rect, Card_Rank Rank) {
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
	text += "視点方向に5発の弾を扇状に発射し" + std::to_string(Damage * 5) + "ダメージを与え当たった対象に気流状態を与える。また、地面に当たるもしくは最大射程の時に下の床が紙の場合床を気流状態にする";
	text += "\n\n";
	text += "ランク毎の1発当たりのダメージ:" + std::to_string(DAMAGE_RANK1) + "/" + std::to_string(DAMAGE_RANK2) + "/" + std::to_string(DAMAGE_RANK3);
	SetText(rect, text);
}
void Bullet_Fun_Wind::DrawPreview(D3DXVECTOR2 pos, float size, Card_Rank Rank) {

	UI ui = { pos ,D3DXVECTOR2(5.7f * size,8.9f * size),D3DXVECTOR2(0.0f,0.0f),D3DXVECTOR2(1.0f,1.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f) ,0.0f };
	DrawScreen(ui, RefImageMaterial().m_Card_Bullet_Fun_Wind);
	if (Rank > 0)
	{
		ui = { pos ,D3DXVECTOR2(5.7f * size,8.9f * size),D3DXVECTOR2(((float)(Rank - 1)) / 3.0f,0.0f),D3DXVECTOR2(1.0f / 3.0f,1.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f) ,0.0f };
		DrawScreen(ui, RefImageMaterial().m_CardFlame);
		ui = { D3DXVECTOR2(pos.x - 5.7f * size * 0.32f,pos.y - 8.9f * size * 0.35f) ,D3DXVECTOR2(1.4f * size,1.4f * size),D3DXVECTOR2(((float)(Rank - 1)) / 3.0f,0.0f),D3DXVECTOR2(1.0f / 3.0f,1.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f) ,0.0f };
		DrawScreen(ui, RefImageMaterial().m_Star);
	}
};