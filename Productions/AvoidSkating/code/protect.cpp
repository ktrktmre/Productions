//=============================================================================
//
// �v���e�N�g�G�t�F�N�g���� [explosion.cpp]
// Author : �ؓc�C���l
//
//=============================================================================
#include "explosion.h"
#include "material.h"
#include "sprite.h"
#include "protect.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PART_X (1.0f/5.0f)

//=============================================================================
// �����t���R���X�g���N�^
//=============================================================================
Protect::Protect(Base_Object* pObj, D3DXVECTOR3 scl, D3DXCOLOR color)
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
	SetKeyFrame({ 2, 4, 6, 8, 10 });
}

//=============================================================================
// �X�V����
//=============================================================================
void Protect::Update(void)
{
	Animetion();

	SetPos(m_Target->RefPos());
}

//=============================================================================
// �`�揈��
//=============================================================================
void Protect::Draw(void)
{
	DrawPolygonBill(*this, RefImageMaterial().m_Parry, m_Uv.m_Uv_v, m_Uv.m_Uv_f);
}