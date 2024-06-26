#pragma once
#include "base_object.h"
class Baseparticle:public Base_Object
{
public:
	Baseparticle() {};
	Baseparticle(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXVECTOR3	vel, D3DXCOLOR coler) :
		Base_Object(pos, rot, size, vel, coler, inviolability, true) {};
	~Baseparticle() {};

	virtual bool Life(void) = 0;
};


