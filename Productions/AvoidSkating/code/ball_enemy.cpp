//=============================================================================
//
// �{�[���G�l�~�[���� [bullet.cpp]
// Author : �ؓc�C���l
//
//=============================================================================
#include "ball_enemy.h"
#include "object_manager.h"
#include "circle_collision.h"
#include "material.h"
#include "sprite.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COLL_CIRCLE			(45.0f)						// �����蔻��̔��a
#define HORIZONTAL_SPEED	(15.0f)						// �����X�s�[�h
#define VERTICAl_SPEED		(7.0f)						// �����X�s�[�h
#define ACCELERATION		(1.0f)						// �����x

//=============================================================================
// �����t���R���X�g���N�^
//=============================================================================
Ball_Enemy::Ball_Enemy(D3DXVECTOR3 pos, int damage)
	:Base_Enemy(pos, NO_VECTOR3, { COLL_CIRCLE,COLL_CIRCLE,COLL_CIRCLE }, {0.0f,0.0f,-HORIZONTAL_SPEED }, { 1.0f,1.0f,0.0f,1.0f }, true, ball, damage)
{
	// �}�e���A���ݒ�
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = RefColor();
	GetMaterial()->Ambient = { 0.0f,0.0f,0.0f,1.0f };
	GetMaterial()->Emission = RefColor();
	GetMaterial()->noTexSampling = 0;

	SetColl(new Circle_Collision(RefPos(), COLL_CIRCLE));
}
//=============================================================================
// �X�V
//=============================================================================
void Ball_Enemy::Update(void)
{

	Fall();

	//�����蔻��̍Đݒ�
	for (Base_Collision* pColl : *GetColl())
	{
		if (auto at = dynamic_cast<Circle_Collision*>(pColl)) {
			at->SetPos(RefPos());
		}
	}

	//���W�̍X�V
	SetPos(RefPos() + RefVel());

	MoveRange(-100);
}
//=============================================================================
// �`��
//=============================================================================
void Ball_Enemy::Draw(void)
{
	Draw3DModel(*this, RefModelMaterial().m_Sphere);
}
//=============================================================================
// �Փ˔���f�B�X�p�b�`
//=============================================================================
void Ball_Enemy::CollDispatch(Base_Object* pObj)
{
	pObj->CollAction(this);
}
//=============================================================================
// �Փ˃A�N�V����
//=============================================================================
void Ball_Enemy::CollAction(Player* player)
{
}
//=============================================================================
// ����
//=============================================================================
void Ball_Enemy::Fall(void)
{
	if (RefVel().y > -5.0f) {
		RefVel().y -= 0.2f;
	}
}
//=============================================================================
// �o�E���h
//=============================================================================
void Ball_Enemy::Bound(void)
{
	RefVel().y = VERTICAl_SPEED;
}
//=============================================================================
// �ړ����E
//=============================================================================
void Ball_Enemy::MoveRange(float limit)
{
	//Y���̈ړ��͈�
	if (RefPos().y < 0 + RefScl().y) {
		SetPos({ RefPos().x,RefScl().y,RefPos().z });
		Bound();
	}

	if (RefPos().z < limit) {
		SetUse(false);
	}
}
