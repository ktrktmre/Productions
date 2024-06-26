//=============================================================================
//
// �������� [explosion.cpp]
// Author : �ؓc�C���l
//
//=============================================================================
#include "explosion.h"
#include "material.h"
#include "sprite.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PART_X (1.0f/5.0f)

//=============================================================================
// �����t���R���X�g���N�^
//=============================================================================
Explosion::Explosion(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXCOLOR color)
	:Base_Anime(pos, rot, scl, NO_VECTOR3, color)
{
	// �}�e���A���ݒ�
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = color;
	GetMaterial()->Ambient = color;
	GetMaterial()->Emission = color;
	GetMaterial()->noTexSampling = 0;

	//UV�̐ݒ�
	m_Uv = (UV{ {0.0f,0.0f},{PART_X,1.0f} });
	SetKeyFrame({ 5, 10, 15, 20, 25 });
}

//=============================================================================
// �X�V����
//=============================================================================
void Explosion::Update(void)
{
	Animetion();
}

//=============================================================================
// �`�揈��
//=============================================================================
void Explosion::Draw(void)
{
	DrawPolygonBillCR(*this, RefImageMaterial().m_ExplosionBule, m_Uv.m_Uv_v, m_Uv.m_Uv_f);
}
