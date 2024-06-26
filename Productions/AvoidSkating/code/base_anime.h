//=============================================================================
//
// �A�j���[�V�������� [base_anime.h]
// Author : 
//
//=============================================================================
#pragma once

#include "renderer.h"
#include "base_object.h"
#include <deque>

//*****************************************************************************
// �e���v���[�g
//*****************************************************************************

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
struct UV {
	D3DXVECTOR2 m_Uv_v;
	D3DXVECTOR2 m_Uv_f;
};

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class Base_Anime :public Base_Object {
protected:
	int m_Frame;
	UV m_Uv;
	std::deque<int> m_KeyFrame;
public:
	Base_Anime() = delete;
	Base_Anime(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color);
	void CollDispatch(Base_Object* pObj)override;

	virtual void Animetion(void);

	//�Z�b�^�[
	void SetKeyFrame(std::initializer_list<int> list);
};