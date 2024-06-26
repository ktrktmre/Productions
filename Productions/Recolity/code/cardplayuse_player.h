#pragma once
#include "input.h"
class CardPlay_Use_Play
{
private:

	int m_select = 0;//選択しているカード
public:

	CardPlay_Use_Play() {};
	~CardPlay_Use_Play() {};
	void Update(int cardnum) {
		if (GetMouseZ() > 0)
		{
			m_select--;
		}
		if (GetMouseZ() < 0)
		{
			m_select++;
		}
		if (m_select < 0)
		{
			m_select = 0;
		}
		if (m_select > cardnum - 1)
		{
			m_select = cardnum - 1;
		}
	};
	int SclectNo() { return m_select; };



};

