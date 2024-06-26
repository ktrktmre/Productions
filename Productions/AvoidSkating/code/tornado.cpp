//=============================================================================
//
// �g���l�[�h�G�t�F�N�g���� [tornado.cpp]
// Author : �ؓc�C���l
//
//=============================================================================
#include "tornado.h"
#include "material.h"
#include "sprite.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PART_X (1.0f/8.0f)

//=============================================================================
// �����t���R���X�g���N�^
//=============================================================================
Tornado::Tornado(Base_Object* pObj, D3DXVECTOR3 scl, D3DXCOLOR color)
	:Base_Anime(NO_VECTOR3, NO_VECTOR3, scl, NO_VECTOR3, color), m_Target(pObj)
{
	SetPos(pObj->RefPos());

	// �}�e���A���ݒ�
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = color;
	GetMaterial()->Ambient = color;
	GetMaterial()->Emission = color;
	GetMaterial()->noTexSampling = 0;

	//UV�̐ݒ�
	m_Uv = (UV{ {0.0f,0.0f},{PART_X,1.0f} });
	SetKeyFrame({ 3,6,9,12,15,18,21,24 });
}

//=============================================================================
// �X�V����
//=============================================================================
void Tornado::Update(void)
{
	Animetion();

	SetPos(m_Target->RefPos());
}

//=============================================================================
// �`�揈��
//=============================================================================
void Tornado::Draw(void)
{
	DrawPolygonBill(*this, RefImageMaterial().m_Tornado, m_Uv.m_Uv_v, m_Uv.m_Uv_f);
}