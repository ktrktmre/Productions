//=============================================================================
//
// ���ꐯ���� [explosion.cpp]
// Author : �ؓc�C���l
//
//=============================================================================
#include "explosion.h"
#include "material.h"
#include "sprite.h"
#include "star.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PART_X (1.0f/5.0f)
#define PART_Y (1.0f/4.0f)

//=============================================================================
// �����t���R���X�g���N�^
//=============================================================================
Star::Star(Base_Object* pObj, D3DXVECTOR3 scl, D3DXCOLOR color)
	:Base_Anime(NO_VECTOR3, NO_VECTOR3, scl, NO_VECTOR3, color), m_Target(pObj)
{
	SetPos({
		m_Target->RefPos().x + m_Length * sinf(RefRot().y),
		m_Target->RefPos().y,
		m_Target->RefPos().z + m_Length * cosf(RefRot().y),
		}
	);

	// �}�e���A���ݒ�
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = color;
	GetMaterial()->Ambient = color;
	GetMaterial()->Emission = color;
	GetMaterial()->noTexSampling = 0;

	//UV�̐ݒ�
	m_Uv = (UV{ {0.0f,0.0f},{PART_X,PART_Y} });

	m_Length = 100.0f;
	SetKeyFrame({ 300 });
}

//=============================================================================
// �X�V����
//=============================================================================
void Star::Update(void)
{
	Animetion();

	SetRot({ 0.0f,RefRot().y + 0.1f,0.0f });

	SetPos({
		m_Target->RefPos().x + m_Length * sinf(RefRot().y),
		m_Target->RefPos().y,
		m_Target->RefPos().z + m_Length * cosf(RefRot().y),
		}
	);
}

//=============================================================================
// �`�揈��
//=============================================================================
void Star::Draw(void)
{
	DrawPolygonBill(*this, RefImageMaterial().m_StarGreen, m_Uv.m_Uv_v, m_Uv.m_Uv_f);
}

//=============================================================================
// �A�j���[�V����
//=============================================================================
void Star::Animetion(void)
{
	if (!(m_Frame % 10)) {
		m_Uv.m_Uv_v += m_Uv.m_Uv_f;
	}
	++m_Frame;

	if (m_Frame == m_KeyFrame.front())
		SetUse(false);
}
