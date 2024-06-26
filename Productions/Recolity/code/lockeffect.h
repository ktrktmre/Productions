#pragma once
#include "baseeffect.h"
class LOCK :public BASEEFFECT
{
private:
	int m_life;
public:
	LOCK() { m_life = 0;  };
	~LOCK() {};
	void Update(void)override {
		m_life > 0 ? m_life-- : m_life = 0;
	};
	bool Draw(D2D1_RECT_F rect)override;
	bool GetEffectLock() {
		if (m_life > 0)
		{
			return true;
		}
		return false;
	};
	void SetLock(EffectStrngth str) {
		switch (str)
		{
		case low:m_life = (int)(LOCK_LOW * 60.0f);
			break;
		case mid:m_life = (int)(LOCK_MID * 60.0f);
			break;
		case high:m_life = (int)(LOCK_HIGH * 60.0f);
			break;
		default:
			break;
		}
	
	};
};
