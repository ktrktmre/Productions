#include "DrawDamageManager.h"
#include "DrawDamage.h"
DrawDmageManager::DrawDmageManager()
{
}
DrawDmageManager::~DrawDmageManager()
{
}
void DrawDmageManager::SetDamage(int damage,D3DXVECTOR3 pos,D3DXCOLOR coler) {
	m_DamageList.push_back(new DrawDmage(damage,pos, coler));
	m_DamageList.sort([](DrawDmage* p1, DrawDmage* p2) {
		return p1->GetLength() > p2->GetLength();
		});
}
void DrawDmageManager::Init(void) {
	for (DrawDmage* pDamageList : m_DamageList)
	{
		delete pDamageList;
	}
	m_DamageList.clear();
}
void DrawDmageManager::Uninit(void) {
	//I—¹
	for (DrawDmage* pDamageList : m_DamageList)
	{
		delete pDamageList;
	}
	m_DamageList.clear();
}
void DrawDmageManager::Update(void) {
	m_DamageList.sort([](DrawDmage* p1, DrawDmage* p2) {
		return p1->GetLength() > p2->GetLength();
		});
	//m_DamageList.sort(std::greater<>());//~‡
	for (DrawDmage* pDamageList : m_DamageList)
	{
		pDamageList->Update();
	}
	m_DamageList.remove_if([](DrawDmage* pEnemy) {
		if (!pEnemy->RefUse()) {
			delete pEnemy;
			return true;
		}
		return false; }
	);
}
void DrawDmageManager::Draw(void) {
	for (DrawDmage* pDamageList : m_DamageList)
	{
		pDamageList->Draw();
	}
}