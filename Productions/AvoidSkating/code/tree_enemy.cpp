//=============================================================================
//
// �G���� [tree_enemy.cpp]
// Author : �ؓc�C���l
//
//=============================================================================
#include "object_manager.h"
#include "tree_enemy.h"
#include "shadow.h"
#include "material.h"
#include "sprite.h"
#include "circle_collision.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)			// ��]��
#define COLL_CIRCLE		(40.0f)						// �����蔻��̔��a


//=============================================================================
// �R���X�g���N�^
//=============================================================================
Tree_Enemy::Tree_Enemy(D3DXVECTOR3 pos, int damage)
	:Base_Enemy(pos, { 0.0f, 0.0f, 0.0f }, { 30.0f,30.0f,30.0f }, { 0.0f, 0.0f,-20.0f },
		{ 1.0f,1.0f,1.0f,1.0f }, true, tree, damage)
{
	// �}�e���A���ݒ�
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = RefColor();
	GetMaterial()->Ambient = { 0.0f,0.0f,0.0f,0.0f };
	GetMaterial()->Emission = { 0.0f,0.0f,0.0f,0.0f };
	GetMaterial()->noTexSampling = 0;

	SetColl(new Circle_Collision(RefPos(),COLL_CIRCLE));
	SetColl(new Circle_Collision(RefPos(),COLL_CIRCLE));
	SetColl(new Circle_Collision(RefPos(),COLL_CIRCLE));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Tree_Enemy::~Tree_Enemy()
{
}

//=============================================================================
// �X�V
//=============================================================================
void Tree_Enemy::Update(void)
{

	//���W�̍X�V
	SetPos(RefPos() + RefVel());
	//��]�̍X�V
	SetRot({ RefRot().x - 0.05f,0.0f,0.0f });
	//�ړ��͈�
	MoveRange(0);

	//�����蔻��̍Đݒ�
	for (int index = 0; index < GetColl()->size(); index++)
	{
		Base_Collision* pColl = GetColl(index);
		if (auto at = dynamic_cast<Circle_Collision*>(pColl)) {
			float init_pos = (0.37f * DISTANCE_DIFF * RefScl().x);
			at->SetPos({
			RefPos().x - init_pos + init_pos * index,
			RefPos().y,
			RefPos().z });
		}
	}
}

//=============================================================================
// �`��
//=============================================================================
void Tree_Enemy::Draw(void)
{
	Draw3DModel(*this, RefModelMaterial().m_Tree);

#if _DEBUG
	//�����蔻�苅�̐ݒ�
	for (Base_Collision* pColl : *GetColl())
	{
		if (auto at = dynamic_cast<Circle_Collision*>(pColl)) {
			Object sphere;
			sphere.m_Pos = at->RefPos();
			sphere.m_Scl = { COLL_CIRCLE ,COLL_CIRCLE ,COLL_CIRCLE };
			sphere.m_Rot = RefRot();
			sphere.m_Color = { 1.0f ,1.0f ,1.0f,0.2f };
			sphere.m_Material.Diffuse = sphere.m_Color;
			Draw3DModel(sphere, RefModelMaterial().m_Sphere);
		}
	}
#endif // _DEBUG
}