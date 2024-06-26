#include "regeneration.h"
#include "text.h"
bool REGENERATION::Draw(D2D1_RECT_F rect)
{
	
		if (m_life > 0) {
			SetText(rect, "regenertion RANK" + std::to_string(m_strength) + "  " + std::to_string(m_life) + "." + std::to_string((m_life * 10) % 10));
			return true;
		}
		else
			return false;

	
}

float REGENERATION::GetEffectregen()
{
	
		if (m_life > 0)
		{
			switch (m_strength)
			{
			case 1:return REGEN_LOW;
				break;
			case 2:return REGEN_MID;
				break;
			case 3:return REGEN_HIGH;
				break;
			default:
				break;
			}
		}
		return 0.0f;
	
}
