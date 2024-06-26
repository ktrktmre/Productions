#include "sloweffect.h"
#include "text.h"
bool SLOWNESS::Draw(D2D1_RECT_F rect)
{
	
		if (m_life > 0) {
			SetText(rect, "slowness RANK" + std::to_string(m_strength) + "  " + std::to_string(m_life) + "." + std::to_string((m_life * 10) % 10));
			return true;
		}
		else
			return false;
	
}
