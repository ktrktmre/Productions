//=============================================================================
//
// キャラクター処理 [base_character.cpp]
// Author : 
//
//=============================================================================
#include "base_character.h"
#include "Game.h"
#include "DrawDamageDot.h"
#include "floor.h"

//=============================================================================
// 引数付きコンストラクタ
//=============================================================================
Base_Character::Base_Character(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, int hp, bool use)
	:Base_Object(pos, rot, scl, vel, color, character, use), m_Hp((float)hp), m_HitFrame(0),m_Stuck(false)
{
	SetOldPos();
}
//=============================================================================
// ダメージを受ける
//=============================================================================
void Base_Character::IsDamage(float damage)
{
	m_Hp -= damage;
	if (m_Hp <= 0)
		IsDiscard();
}
//=============================================================================
// ダメージを受ける(ドット)
//=============================================================================
void Base_Character::IsDamageDot(float damage)
{
	m_DrawDotDamage.IsDamageDot(damage);
	m_Hp -= damage;
	if (m_Hp <= 0)
		IsDiscard();
}
//=============================================================================
// ダメージを受けた時のアクション
//=============================================================================
void Base_Character::DamageAction(int frame)
{
}
//=============================================================================
// リファレンス
//=============================================================================
const float& Base_Character::RefHp(void) const
{
	return m_Hp;
}
const int& Base_Character::RefHitFrame(void) const
{
	return m_HitFrame;
}
const bool& Base_Character::RefStuck(void) const
{
	return m_Stuck;
}
const int& Base_Character::RefFootSteps(void) const
{
	return m_FootSteps;
}
//=============================================================================
// セッター
//=============================================================================
void Base_Character::SetHp(float hp)
{
	m_Hp = hp;
}
void Base_Character::SetHitFrame(int frame)
{
	m_HitFrame = frame;
}
void Base_Character::SetStuck(bool stuck)
{
	m_Stuck = stuck;
}
void Base_Character::SetFootSteps(int foot)
{
	m_FootSteps = foot;
}

void Base_Character::Update_DotDamage()
{
	m_DrawDotDamage.Update(RefPos());
}

void Base_Character::Draw_DotDamage()
{
	m_DrawDotDamage.Draw();
}
//=============================================================================
// フロア処理
//=============================================================================
void Base_Character::GetFloorPos()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			float in = 1.0f;
			float jn = 1.0f;
			if (i == 1)
			{
				in = -1.0f;

			}
			if (j == 1)
			{
				jn = -1.0f;
			}
			if ((int)GetNowFloor({ RefPos().x + 30.0f * in,RefPos().y,RefOldPos().z + 30.0f * jn }) == 0)
			{
				SetPos({ RefOldPos().x, RefPos().y, RefPos().z });
			}
			if ((int)GetNowFloor({ RefOldPos().x + 30.0f * in,RefPos().y,RefPos().z + 30.0f * jn }) == 0)
			{
				SetPos({ RefPos().x, RefPos().y, RefOldPos().z });
			}

		}
	}
	if (RefPos().x < 0)
	{
		SetPos({ 0.0f,RefPos().y,RefPos().z });
	}
	if (RefPos().z < 0)
	{
		SetPos({ RefPos().x,RefPos().y,0.0f });
	}
	if (RefPos().x > 10000){
		SetPos({ 10000,RefPos().y,RefPos().z });
	}
	if (RefPos().z > 10000){
		SetPos({ RefPos().x,RefPos().y,10000 });
	}
}
