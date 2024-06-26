#include "slipdamage.h"
#include "text.h"
bool SLIPDAMAGE::Draw(D2D1_RECT_F rect)
{
	
		if (m_life > 0) {
			SetText(rect, "slipdamage RANK" + std::to_string(m_strength) + "  " + std::to_string(m_life) + "." + std::to_string((m_life * 10) % 10));
			return true;
		}
		else
			return false;
	
}
