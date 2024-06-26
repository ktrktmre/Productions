//=============================================================================
//
// ���ꐯ���� [star.h]
// Author : �ؓc�C���l
//
//=============================================================================
#pragma once

#include "renderer.h"
#include "base_anime.h"

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class Star :public Base_Anime {
private:
	Base_Object* m_Target;
	float m_Length;
public:
	Star() = delete;
	Star(Base_Object* pObj, D3DXVECTOR3 scl, D3DXCOLOR color);
	~Star() = default;

	void Update(void)override;
	void Draw(void)override;
	void Animetion(void)override;
};