#pragma once
#include "baseeffect.h"
class SLOWNESS:public BASEEFFECT
{
private:
	int m_life;
	int m_strength;
public:
	SLOWNESS() { m_life = 0;  m_strength = 0; };
	~SLOWNESS() {};
	void Update(void)override {
		m_life > 0 ? m_life-- : m_life = 0;
	};
	bool Draw(D2D1_RECT_F rect)override;
	float GetEffectSlowness() {
		if (m_life > 0)
		{
			switch (m_strength)
			{
			case 1:return SLOWNESS_LOW * 0.01f;
				break;
			case 2:return SLOWNESS_MID * 0.01f;
				break;
			case 3:return SLOWNESS_HIGH * 0.01f;
				break;
			default:
				break;
			}
		}
		return 0.0f;
	};
	void SetSlowness(EffectStrngth str,int timef) {
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


