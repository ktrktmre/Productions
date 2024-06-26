#pragma once
#pragma once
#include "baseeffect.h"
#include "base_attribute.h"
typedef struct
{
	bool use;
	int time;
}FlameSoud;
class FLAMESFIRE :public BASEEFFECT
{
private:
	int m_life;
	EffectStrngth m_strength;
	int m_timer;
	Attribute_Type m_elemrnt;
	FlameSoud m_Soundfier[5];
	FlameSoud m_Soundwater[5];
	FlameSoud m_Soundwind[5];
public:

	FLAMESFIRE(){ m_life = 0; m_timer = 0; };
	~FLAMESFIRE() {};
	void Update(void)override;
	bool Draw(D2D1_RECT_F rect)override;

	bool GetEffectflamefire() {
		if (m_timer == FLAMESFIRE_TICK && m_life > 0)
		{
		return	true;
		}
		return false;
	};
	EffectStrngth GetStrengh() { return m_strength; };
	void SetFlameFire(EffectStrngth str, Attribute_Type element);
	void PlayerSound(Attribute_Type element);
};


