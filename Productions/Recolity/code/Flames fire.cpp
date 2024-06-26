#include "Flames fire.h"
#include "Game.h"
#include "text.h"
#include "bullet_management.h"
#include "bullet_interface.h"
#include "camera.h"
#include "material.h"
#include "sound.h"
#define RANGE (1500)
#define DAMAGE_RANK1 (3)
#define DAMAGE_RANK2 (7)
#define DAMAGE_RANK3 (16)
void FLAMESFIRE::Update(void)
{
	if (m_life > 0)
	{
		m_timer++;
	}
	if (m_timer > FLAMESFIRE_TICK)
	{
		if (m_life > 0)
		{
//======================
// カードのダメージ設定
//======================

//基本ダメージ
			float damage = 1.0f;
			switch (m_strength)
			{
			case low:damage = (float)DAMAGE_RANK1;
				break;
			case mid:damage = (float)DAMAGE_RANK2;
				break;
			case high:damage = (float)DAMAGE_RANK3;
				break;
			default:
				break;
			}
			PlayerSound(m_elemrnt);
			D3DXVECTOR3 po = GetCamera()->pos;
			po.y -= 4.5;
			int* tex = &RefImageMaterial().m_Cannon_Bullet;
			Attribute_Element element = FIER_ATTRIBUTE;
			if (m_elemrnt == fire)
			{
				element = FIER_ATTRIBUTE;
				tex = &RefImageMaterial().m_Cannon_Bullet;
			}
			if (m_elemrnt == water)
			{
				element = WATER_ATTRIBUTE;
				tex = &RefImageMaterial().m_Water_Bullet;
			}
			if (m_elemrnt == wind)
			{
				element = WIND_ATTRIBUTE;
				tex = &RefImageMaterial().m_Wind_Bullet;
			}
			 

			GetBulletInterface()->SetNBullet(bullet, player, po, GetCamera()->rot, { 10.0f,10.0f,10.0f },
				{ 1.0f,1.0f,1.0f,1.0f },
				damage,
				45, 0.0f, 1.0f, RANGE,
				m_elemrnt, element,
				tex);
		}
		m_life--;
		m_timer = 0;
	}

	for (int i = 0; i < 5; i++)
	{
		if (m_Soundfier[i].time > 0)
		{
			m_Soundfier[i].time--;
		}
		if (m_Soundfier[i].time <= 0)
		{
			m_Soundfier[i].use = false;
		}

		if (m_Soundwater[i].time > 0)
		{
			m_Soundwater[i].time--;
		}
		if (m_Soundwater[i].time <= 0)
		{
			m_Soundwater[i].use = false;
		}

		if (m_Soundwind[i].time > 0)
		{
			m_Soundwind[i].time--;
		}
		if (m_Soundwind[i].time <= 0)
		{
			m_Soundwind[i].use = false;
		}
	}
}
bool FLAMESFIRE::Draw(D2D1_RECT_F rect)
{
	
		if (m_life > 0) {
			SetText(rect, "flamefire ammo" + std::to_string(m_life));
			return true;
		}
		else
			return false;
	
}

void FLAMESFIRE::SetFlameFire(EffectStrngth str, Attribute_Type element)
{
	m_strength = str;
	m_elemrnt = element;
	m_timer = 0;
	m_life = 5;
}

void FLAMESFIRE::PlayerSound(Attribute_Type element)
{

	if (element == fire)
	{
		for (int i = 0; i < 5; i++)
		{
			PlaySound("fier", 0.75f);
			if (m_Soundfier[i].use == false)
			{
				m_Soundfier[i].time = 80;
				m_Soundfier[i].use = true;
				break;
			}

		}
	}
	if (element == water)
	{
		PlaySound("water", 0.75f);
		for (int i = 0; i < 5; i++)
		{
			if (m_Soundwater[i].use == false)
			{
				m_Soundwater[i].time = 80;
				m_Soundwater[i].use = true;
				break;
			}

		}
	}
	if (element == wind)
	{
		PlaySound("wind", 0.75f);
		for (int i = 0; i < 5; i++)
		{
			if (m_Soundwind[i].use == false)
			{
				m_Soundwind[i].time = 80;
				m_Soundwind[i].use = true;
				break;
			}

		}
	}
}