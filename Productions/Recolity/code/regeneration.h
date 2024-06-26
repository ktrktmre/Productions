#pragma once
#pragma once
#include "baseeffect.h"
class REGENERATION :public BASEEFFECT
{
private:
	int m_life;
	int m_strength;
public:
	REGENERATION() { m_life = 0;  m_strength = 0; };
	~REGENERATION() {};
	void Update(void)override {
		m_life > 0 ? m_life-- : m_life = 0;
	};
	bool Draw(D2D1_RECT_F rect)override;
	float GetEffectregen();
	void Setregen(EffectStrngth str, int timef) {
		switch (str)
		{
		case low:m_strength = str;
			break;
		case mid:m_strength = str;
			break;
		case high:m_strength = str;
			break;
		default:
			break;
		}
		m_life = timef;
	};
};

#pragma once
