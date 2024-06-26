#include "card_bullet_single_water.h"
#include "material.h"
#include "Game.h"
#include "text.h"
#include "bullet_management.h"
#include "bullet_interface.h"
#include "camera.h"
#include "sprite.h"
#include "player.h"
#include "sound.h"
#define DAMAGE_RANK1 (12)
#define DAMAGE_RANK2 (27)
#define DAMAGE_RANK3 (60)
#define RANGE (1500)
void Bullet_Single_Water::Use(int rank) {

	PlaySound("water", 0.75f);
	//======================
	// �J�[�h�̃_���[�W�ݒ�
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

	GetBulletInterface()->SetNBullet(bullet, player, pos, D3DXVECTOR3(GetCamera()->rot.x, GetCamera()->rot.y, GetCamera()->rot.z), { 10.0f,10.0f,10.0f },
		{ 1.0f,1.0f,1.0f,1.0f },
		Damage, 45, 0.0f, 1.0f, RANGE,
		water, element,
		&RefImageMaterial().m_Water_Bullet);
}

void Bullet_Single_Water::DrawPreview(D3DXVECTOR2 pos, float size, Card_Rank Rank) {
	UI ui = { pos ,D3DXVECTOR2(5.7f * size,8.9f * size),D3DXVECTOR2(0.0f,0.0f),D3DXVECTOR2(1.0f,1.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f) ,0.0f };
	DrawScreen(ui, RefImageMaterial().m_Card_Bullet_Single_Water);
	if (Rank > 0)
	{
		ui = { pos ,D3DXVECTOR2(5.7f * size,8.9f * size),D3DXVECTOR2(((float)(Rank - 1)) / 3.0f,0.0f),D3DXVECTOR2(1.0f / 3.0f,1.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f) ,0.0f };
		DrawScreen(ui, RefImageMaterial().m_CardFlame);
		ui = { D3DXVECTOR2(pos.x - 5.7f * size * 0.32f,pos.y - 8.9f * size * 0.35f) ,D3DXVECTOR2(1.4f * size,1.4f * size),D3DXVECTOR2(((float)(Rank - 1)) / 3.0f,0.0f),D3DXVECTOR2(1.0f / 3.0f,1.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f) ,0.0f };
		DrawScreen(ui, RefImageMaterial().m_Star);
	}

};
void Bullet_Single_Water::DrawTextPreview(D2D1_RECT_F rect, Card_Rank Rank) {
	//�J�[�h���ʐ���
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
	text += "���_�����ɋ��𔭎˂�" + std::to_string(Damage) + "�_���[�W��^�����������ΏۂɐZ����3.5�b�ԗ^����B�܂��A�n�ʂɓ�����������͍ő�˒��̎��ɉ��̏������̏ꍇ����Z����Ԃɂ���";
	text += "\n\n";
	text += "�����N���̃_���[�W:" + std::to_string(DAMAGE_RANK1) + "/" + std::to_string(DAMAGE_RANK2) + "/" + std::to_string(DAMAGE_RANK3);
	SetText(rect, text);
}