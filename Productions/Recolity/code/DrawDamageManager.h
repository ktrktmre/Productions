#pragma once
#include "main.h"
#include <list>
class DrawDmage;
class DrawDmageManager
{
private:
	std::list<DrawDmage*> m_DamageList;
public:
	DrawDmageManager();
	~DrawDmageManager();
	void SetDamage(int damage, D3DXVECTOR3 pos, D3DXCOLOR coler);
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

};




