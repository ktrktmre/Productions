//=============================================================================
//
// �g���l�[�h�G�t�F�N�g���� [tornado.h]
// Author : �ؓc�C���l
//
//=============================================================================
#ifndef _TORNADO_H_
#define _TORNADO_H_
#pragma once

#include "renderer.h"
#include "base_anime.h"

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class Tornado :public Base_Anime {
private:
	Base_Object* m_Target;
public:
	Tornado() = delete;
	Tornado(Base_Object* pObj, D3DXVECTOR3 scl, D3DXCOLOR color);
	~Tornado() = default;

	void Update(void)override;
	void Draw(void)override;
};
#endif // !_TORNADO_H_