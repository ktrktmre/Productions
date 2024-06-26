//=============================================================================
//
// ƒJ[ƒ\ƒ‹ˆ— [cursor.cpp]
// Author : Ø“cŠC¤“l
//
//=============================================================================
#include "cursor.h"
#include "input.h"

D3DXVECTOR2& Cursor::RefCorsor(void)
{
	return m_Pos;
}

void Cursor::MoveCursor(int value)
{
	//ƒ}ƒEƒX‚ÌŽ‹“_ˆÚ“®ˆ—
	DIMOUSESTATE2 Mouse;
	Mouse.lX = GetMouseX();
	Mouse.lY = GetMouseY();
	//‰¡‰ñ“]
	if (Mouse.lX != 0)
	{
		m_Pos.x += value * Mouse.lX;
	}
	//c‰ñ“]
	if (Mouse.lY != 0)
	{
		m_Pos.y += value * Mouse.lY;
	}

	if (m_Pos.x > 1920.0f)
		m_Pos.x = 1920.0f;
	if (m_Pos.x < 0.0f)
		m_Pos.x = 0.0f;
	if (m_Pos.y > 1080.0f)
		m_Pos.y = 1080.0f;
	if (m_Pos.y < 0.0f)
		m_Pos.y = 0.0f;
}
