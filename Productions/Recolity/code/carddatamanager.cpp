#include "carddatamanager.h"
#include "sound.h"

void CardDataManager::InitCard()
{
	//for (int i = 0; i < CARD_DATA_MAX; i++)
	//{
	//	if (m_card_data[i] != nullptr)
	//	{
	//		m_card_data[i]->Init();
	//	}
	//}
	LoadShareSound("fier");
	LoadShareSound("water");
	LoadShareSound("wind");
	LoadShareSound("heal");
}
