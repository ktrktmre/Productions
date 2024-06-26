//=============================================================================
//
// �������� [disappear.h]
// Author : �ؓc�C���l
//
//=============================================================================
#pragma once

#include "renderer.h"
#include "base_anime.h"

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class Disappear :public Base_Anime {
private:
public:
	Disappear() = delete;
	Disappear(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXCOLOR color);
	~Disappear() = default;

	void Update(void)override;
	void Draw(void)override;
};