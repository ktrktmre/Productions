#pragma once
#include "baseeffect.h"
class SLIPDAMAGE :public BASEEFFECT
{
private:
	int m_life;
	int m_strength;
public:
	SLIPDAMAGE() { m_life = 0;  m_strength = 0; };
	~SLIPDAMAGE() {};
	void Update(void)override {
		m_life > 0 ? m_life-- : m_life = 0;
	};
	bool Draw(D2D1_RECT_F rect)override;
	float GetEffectSlipdamage() {
		if (m_life > 0)
		{
			switch (m_strength)
			{
			case 1:return SLIPDAMAGE_LOW ;
				break;
			case 2:return SLIPDAMAGE_MID ;
				break;
			case 3:return SLIPDAMAGE_HIGH ;
				break;
			default:
				break;
			}
		}
		return 0.0f;
	};
	void SetSlipdamage(EffectStrngth str, int timef) {
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
