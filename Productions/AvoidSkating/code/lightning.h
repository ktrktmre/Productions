//=============================================================================
//
// ���C�g�j���O���� [lightning.h]
// Author : �ؓc�C���l
//
//=============================================================================
#pragma once

#include "renderer.h"
#include "base_anime.h"

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class Lightning :public Base_Anime {
private:
	Base_Object* m_Target;
public:
	Lightning() = delete;
	Lightning(Base_Object* pObj, D3DXVECTOR3 scl, D3DXCOLOR color);
	~Lightning() = default;

	void Update(void)override;
	void Draw(void)override;
	void Animetion(void)override;
};