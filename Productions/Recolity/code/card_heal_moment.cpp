#include "card_heal_moment.h"
#include "sprite.h"
#include "main.h"
#include "material.h"
#include "Game.h"
#include "text.h"
#include "player.h"
#include "bullet_management.h"
#include "bullet_interface.h"
#include "camera.h"
#include "sound.h"
#define CARD_BASE_HEAL (20.0f)
#define CARD_SCALE (20.0f)

void Heal_Moment::Use(int rank) {
	PlaySound("heal", 0.75f);
	GetPlayer()->PlayerHeal(CARD_BASE_HEAL + CARD_SCALE * (rank -1));
}
void Heal_Moment::DrawTextPreview(D2D1_RECT_F rect, Card_Rank Rank) {
	std::string text ;
	text += "Ž©g‚ð‘¦À‚É" + std::to_string((int)CARD_BASE_HEAL + (Rank - 1) * (int)CARD_SCALE) + "‰ñ•œ‚·‚é\n\n";
	text += "ƒ‰ƒ“ƒN–ˆ‚Ì‰ñ•œHP:" + std::to_string((int)CARD_BASE_HEAL) + "/" + std::to_string((int)CARD_BASE_HEAL + (int)CARD_SCALE) + "/" + std::to_string((int)CARD_BASE_HEAL + (int)CARD_SCALE * 2);
	SetText(rect, text);
}
void Heal_Moment::DrawPreview(D3DXVECTOR2 pos, float size, Card_Rank Rank) {

	UI ui = { pos ,D3DXVECTOR2(5.7f * size,8.9f * size),D3DXVECTOR2(0.0f,0.0f),D3DXVECTOR2(1.0f,1.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f) ,0.0f };
	DrawScreen(ui, RefImageMaterial().m_Card_Heal_Moment);
	if (Rank > 0)
	{
		ui = { pos ,D3DXVECTOR2(5.7f * size,8.9f * size),D3DXVECTOR2(((float)(Rank - 1)) / 3.0f,0.0f),D3DXVECTOR2(1.0f / 3.0f,1.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f) ,0.0f };
		DrawScreen(ui, RefImageMaterial().m_CardFlame);
		ui = { D3DXVECTOR2(pos.x - 5.7f * size * 0.32f,pos.y - 8.9f * size * 0.35f) ,D3DXVECTOR2(1.4f * size,1.4f * size),D3DXVECTOR2(((float)(Rank - 1)) / 3.0f,0.0f),D3DXVECTOR2(1.0f / 3.0f,1.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f) ,0.0f };
		DrawScreen(ui, RefImageMaterial().m_Star);
	}
};