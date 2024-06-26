//=============================================================================
//
// ���C�g�j���O���� [lightning.cpp]
// Author : �ؓc�C���l
//
//=============================================================================
#include "lightning.h"
#include "material.h"
#include "sprite.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PART_X (1.0f*0.25f)

//=============================================================================
// �����t���R���X�g���N�^
//=============================================================================
Lightning::Lightning(Base_Object* pObj, D3DXVECTOR3 scl, D3DXCOLOR color)
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
}

//=============================================================================
// �X�V����
//=============================================================================
void Lightning::Update(void)
{
	SetPos(m_Target->RefPos());
	Animetion();
}

//=============================================================================
// �`�揈��
//=============================================================================
void Lightning::Draw(void)
{
	DrawPolygonBillCR(*this, RefImageMaterial().m_Lightning, m_Uv.m_Uv_v, m_Uv.m_Uv_f);
}

//=============================================================================
// �A�j���[�V����
//=============================================================================
void Lightning::Animetion(void)
{
	if (!m_Target->RefUse())
		SetUse(false);

	if (!(m_Frame % 10)) {
		m_Uv.m_Uv_v += m_Uv.m_Uv_f;
	}
	++m_Frame;
}
