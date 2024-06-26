#include "card_heal_regen.h"
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
void Heal_Regen::Use(int rank) {
	PlaySound("heal", 0.75f);
	GetPlayer()->effect.SetEffect(regeneration, low, 60 * (5 * rank));
}
void Heal_Regen::DrawTextPreview(D2D1_RECT_F rect, Card_Rank Rank) {
	std::string text = "–ˆ•b5‰ñ•œ‚·‚éÄ¶‚ðŽ©g‚É" + std::to_string(5 + (Rank - 1) * 5) + "•b•t—^‚·‚é\n\n";
	text += "ƒ‰ƒ“ƒN–ˆ‚ÌŒø‰ÊŽžŠÔ:5/10/15";
	SetText(rect, text);
}
void Heal_Regen::DrawPreview(D3DXVECTOR2 pos, float size, Card_Rank Rank) {

	UI ui = { pos ,D3DXVECTOR2(5.7f * size,8.9f * size),D3DXVECTOR2(0.0f,0.0f),D3DXVECTOR2(1.0f,1.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f) ,0.0f };
	DrawScreen(ui, RefImageMaterial().m_Card_Heal_Regen);
	if (Rank > 0)
	{
		ui = { pos ,D3DXVECTOR2(5.7f * size,8.9f * size),D3DXVECTOR2(((float)(Rank - 1)) / 3.0f,0.0f),D3DXVECTOR2(1.0f / 3.0f,1.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f) ,0.0f };
		DrawScreen(ui, RefImageMaterial().m_CardFlame);
		ui = { D3DXVECTOR2(pos.x - 5.7f * size * 0.32f,pos.y - 8.9f * size * 0.35f) ,D3DXVECTOR2(1.4f * size,1.4f * size),D3DXVECTOR2(((float)(Rank - 1)) / 3.0f,0.0f),D3DXVECTOR2(1.0f / 3.0f,1.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f) ,0.0f };
		DrawScreen(ui, RefImageMaterial().m_Star);
	}
};