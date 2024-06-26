//=============================================================================
//
// �e���� [shadow.cpp]
// Author : �ؓc�C���l
//
//=============================================================================
#include "shadow.h"
#include "material.h"
#include "sprite.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//=============================================================================
// �����t���R���X�g���N�^
//=============================================================================
Shadow::Shadow(Base_Object* pTarget)
	:Base_Object(inviolability, { 0.0f,0.1f,0.0f }, NO_VECTOR3, { 80.0f,0.0f,80.0f }, NO_VECTOR3, {0.5f,0.5f,0.5f,0.7f}, true), m_Target(pTarget)
{
	// �}�e���A���ݒ�
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = DEF_COLOR;
	GetMaterial()->Ambient = { 0.0f,0.0f,0.0f,0.0f };
	GetMaterial()->Emission = { 0.0f,0.0f,0.0f,0.0f };
	GetMaterial()->noTexSampling = 0;

	m_TargetTag = pTarget->RefTag();
}

//=============================================================================
// �X�V����
//=============================================================================
void Shadow::Update(void)
{
	SetPos({
		m_Target->RefPos().x,
		0.0f,
		m_Target->RefPos().z
		});

	if (!m_Target->RefUse() || m_Target->RefTag() != m_TargetTag)
 		SetUse(false);
}

//=============================================================================
// �`�揈��
//=============================================================================
void Shadow::Draw(void)
{
	// ���Z����
	SetBlendState(BLEND_MODE_SUBTRACT);
	// Z��r�Ȃ�
	SetDepthEnable(false);

	DrawPolygonZCR(*this, RefImageMaterial().m_Shadow, { 0.0f,0.0f }, { 1.0f,1.0f });

	// Z��r����
	SetDepthEnable(true);
	// �ʏ�u�����h
	SetBlendState(BLEND_MODE_ALPHABLEND);
}
//=============================================================================
// �Փ˔���f�B�X�p�b�`
//=============================================================================
void Shadow::CollDispatch(Base_Object* pObj)
{
}
