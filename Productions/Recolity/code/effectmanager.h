#pragma once
#include "baseeffect.h"
#include "sloweffect.h"
#include "slipdamage.h"
#include "lockeffect.h"
#include "regeneration.h"
#include "Flames fire.h"
#include "base_attribute.h"
#define NUM_EFFECT  5 //最大エフェクト数

class EFFECTMANAGER
{
private:

	BASEEFFECT* m_pbase[NUM_EFFECT];
	SLOWNESS m_slowness;
	LOCK m_lock;
	SLIPDAMAGE m_slipdamage;
	REGENERATION m_regene;
	FLAMESFIRE m_flamefire;

public:
	EFFECTMANAGER() {
		m_pbase[0] = &m_slowness;
		m_pbase[1] = &m_lock;
		m_pbase[2] = &m_slipdamage;
		m_pbase[3] = &m_regene;
		m_pbase[4] = &m_flamefire;
	};
	~EFFECTMANAGER() {};
	void DrawEffect() {
		D2D1_RECT_F rect = {600,0,2000,2000};
		for (int i = 0; i < NUM_EFFECT; i++)
		{
			if (m_pbase[i]->Draw(rect))
			{
				rect.top += 25;
			}
			
		}
	}
	void SetEffect(Effectname name, EffectStrngth strngth, int timeframe) {
		switch (name)
		{
		case slowness:m_slowness.SetSlowness(strngth, timeframe);
			break;
		case lock:m_lock.SetLock(strngth);
			break;
		case slipdamage:m_slipdamage.SetSlipdamage(strngth, timeframe);
			break;
		case regeneration:m_regene.Setregen(strngth, timeframe);
			break;
	
		default:
			break;
		}
	}
	void SetEffectBullet(Attribute_Type elemnt, EffectStrngth strngth);
	void Update(void) {
		for (int i = 0; i < NUM_EFFECT; i++)
		{
			m_pbase[i]->Update();
		}
	}
	float GetSlowness() { return m_slowness.GetEffectSlowness(); };
	bool GetLock() { return m_lock.GetEffectLock(); };
	float GetSlipdamage() { return m_slipdamage.GetEffectSlipdamage(); };
	float GetRegen() { return m_regene.GetEffectregen(); };
	void InitSound() {
	}
	FLAMESFIRE* GetFlameFier() { return &m_flamefire; };
};