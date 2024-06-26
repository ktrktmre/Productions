#include "card_bullet_five_fire.h"
#include "Game.h"
#include "text.h"
#include "sprite.h"
#include "material.h"
#include "sound.h"
#define DAMAGE_RANK1 (3)
#define DAMAGE_RANK2 (7)
#define DAMAGE_RANK3 (16)
void Bullet_Five_Fier::Use(int rank) {

	switch (rank)
	{
	case 1://ƒ‰ƒ“ƒN‚²‚Æ‚ÌŒø‰Ê
		GetPlayer()->effect.SetEffectBullet(fire,low);
		break;
	case 2:
		GetPlayer()->effect.SetEffectBullet(fire, mid);
		break;
	case 3:
		GetPlayer()->effect.SetEffectBullet(fire, high);
		break;
	default:
		break;
	}
}
void Bullet_Five_Fier::DrawTextPreview(D2D1_RECT_F rect,  Card_Rank Rank) {
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
	text += "Ž‹“_•ûŒü‚É‚T”­‹…‚ð˜A‘±‚Å”­ŽË‚µ1”­“–‚½‚è" + std::to_string(Damage * 5) + "ƒ_ƒ[ƒW‚ð—^‚¦“–‚½‚Á‚½‘ÎÛ‚É”RÄ‚ð10•bŠÔ—^‚¦‚éB‚Ü‚½A’n–Ê‚É“–‚½‚é‚à‚µ‚­‚ÍÅ‘åŽË’ö‚ÌŽž‚É‰º‚Ì°‚ªŽ†‚Ìê‡°‚ð”RÄó‘Ô‚É‚·‚é";
	text += "\n\n";
	text += "ƒ‰ƒ“ƒN–ˆ‚Ì1”­“–‚½‚è‚Ìƒ_ƒ[ƒW:" + std::to_string(DAMAGE_RANK1) + "/" + std::to_string(DAMAGE_RANK2) + "/" + std::to_string(DAMAGE_RANK3);
	SetText(rect,text);
}
void Bullet_Five_Fier::DrawPreview(D3DXVECTOR2 pos, float size, Card_Rank Rank) {
	UI ui = { pos ,D3DXVECTOR2(5.7f * size,8.9f * size),D3DXVECTOR2(0.0f,0.0f),D3DXVECTOR2(1.0f,1.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f) ,0.0f };
	DrawScreen(ui, RefImageMaterial().m_RapidFire);
	if (Rank > 0)
	{
		ui = { pos ,D3DXVECTOR2(5.7f * size,8.9f * size),D3DXVECTOR2(((float)(Rank - 1)) / 3.0f,0.0f),D3DXVECTOR2(1.0f / 3.0f,1.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f) ,0.0f };
		DrawScreen(ui, RefImageMaterial().m_CardFlame);
		ui = { D3DXVECTOR2(pos.x - 5.7f * size * 0.32f,pos.y - 8.9f * size * 0.35f) ,D3DXVECTOR2(1.4f * size,1.4f * size),D3DXVECTOR2(((float)(Rank - 1)) / 3.0f,0.0f),D3DXVECTOR2(1.0f / 3.0f,1.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f) ,0.0f };
		DrawScreen(ui, RefImageMaterial().m_Star);
	}

};

