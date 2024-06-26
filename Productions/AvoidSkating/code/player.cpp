//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : �ؓc�C���l
//
//=============================================================================
#include "player.h"
#include "object_manager.h"
#include "sprite.h"
#include "material.h"
#include "input.h"
#include "circle_collision.h"
#include "base_enemy.h"
#include "base_item.h"
#include "explosion.h"
#include "protect.h"
#include "tornado.h"
#include "sound.h"
#include "fade.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	VALUE_MOVE		(15.0f)						// �ړ���
#define	VALUE_JUMP		(15.0f)						// �W�����v��
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)			// ��]��
#define COLL_CIRCLE		(40.0f)						// �����蔻��̔��a
#define INVINCIBLE		(30)						// ���G�t���[����
#define AVOID			(15)						// �p���B�t���[����
#define DOUBLE_JAMP		(15)						// ��i�W�����v�t���[����
#define HIT_POINT		(300.0f)					// �q�b�g�|�C���g
#define AVOID_POINT		(300.0f)					// �p���B�|�C���g
#define VALUE_AVOID		(100.0f)					// �p���B��

//=============================================================================
// �����t���R���X�g���N�^
//=============================================================================
Player::Player()
	:Base_Object(player, NO_VECTOR3, NO_VECTOR3, { 9.0f,9.0f,9.0f }, NO_VECTOR3, { 1.0f,1.0f,1.0f,1.0f }, true)
	, m_InvincibleFrame(0), m_AvoidFrame(0), m_DJumpFrame(0), m_Index(0), m_Hp(HIT_POINT),m_Pp(AVOID_POINT), m_VSpeed(0.0f),
	m_JampFlag(false), m_DJampFlag(false), m_GroundFlag(true)
{
	// �}�e���A���ݒ�
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = RefColor();
	GetMaterial()->Ambient = { 0.8f,0.8f,0.8f,1.0f };
	GetMaterial()->Emission = { 0.0f,0.0f,0.0f,0.0f };
	GetMaterial()->noTexSampling = 0;

	SetColl(new Circle_Collision(RefPos(),COLL_CIRCLE));

	m_Table.push_back({ 0.0f, 0.0f, 100.0f });
	m_Table.push_back({ 500.0f, 0.0f, 100.0f });
	m_Table.push_back({ -500.0f, 0.0f, 100.0f });
	SetPos(m_Table[m_Index]);
}
//=============================================================================
// �X�V
//=============================================================================
void Player::Update(void)
{
	//�ړ�
	Move();

	//�����蔻��̍Đݒ�
	for (Base_Collision* pColl : *GetColl())
	{
		if (auto at = dynamic_cast<Circle_Collision*>(pColl)) {
			at->SetPos({
			RefPos().x,
			RefPos().y + 0.6f * RefScl().y * DISTANCE_DIFF,
			RefPos().z });
		}
	}

	//�e�t���[���̊Ǘ�
	EachFrame();

	//�q�b�g�|�C���g�̌���
	if (m_Hp > 0)
		m_Hp -= 0.1f;

	//�p���B�|�C���g�̑���
	if (m_Pp < AVOID_POINT)
		m_Pp += 0.5f;

	if (GetKeyboardTrigger(DIK_O))
		PlaySound("avoid",0,3.0f,0);
}
//=============================================================================
// �`��
//=============================================================================
void Player::Draw(void)
{
	Draw3DModel(*this, RefModelMaterial().m_Skateboard);

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
	std::stringstream ss;
	ss << "AvoidFrame:" << m_AvoidFrame;
	DebugTextOut(ss.str().c_str(), 10, 50);
#endif // _DEBUG

	//�^�C�����N�Q�[�W
	DrawScreenLT(UI{ {50,0},0.0f,{300 ,50},{0.0f,0.0f},{1.0f,1.0f},{1.0f,0.0f,0.0f,1.0f} }, RefImageMaterial().m_HpGauge);
	DrawScreenLT(UI{ {50,50},0.0f,{m_Hp * 2 ,30},{0.0f,0.0f},{1.0f,1.0f},{1.0f,0.0f,0.0f,1.0f} }, RefImageMaterial().m_White);
	DrawScreenLT(UI{ {50,50},0.0f,{HIT_POINT * 2 ,30},{0.0f,0.0f},{1.0f,1.0f},{0.4f,0.4f,0.4f,1.0f} }, RefImageMaterial().m_Frame);

	//�X���k�P�Q�[�W
	DrawScreenLT(UI{ {50,80},0.0f,{300 ,50},{0.0f,0.0f},{1.0f,1.0f},{233.0f / FULL_COLOR,188.0f / FULL_COLOR,0.0f,1.0f} }, RefImageMaterial().m_AvoidGauge);
	DrawScreenLT(UI{ {50,130},0.0f,{m_Pp * 2 ,30},{0.0f,0.0f},{1.0f,1.0f},{233.0f / FULL_COLOR,188.0f / FULL_COLOR,0.0f,1.0f} }, RefImageMaterial().m_White);
	for (int i = 0; i < 3; i++) {
		DrawScreenLT(UI{ {50 + i * VALUE_AVOID * 2,130},0.0f,{VALUE_AVOID * 2 ,30},{0.0f,0.0f},{1.0f,1.0f},{0.4f,0.4f,0.4f,1.0f} }, RefImageMaterial().m_Frame);
	}

	//�X�R�A
	m_Score.Draw();

}
//=============================================================================
// �Փ˔���f�B�X�p�b�`
//=============================================================================
void Player::CollDispatch(Base_Object* pObj)
{
	pObj->CollAction(this);
}
//=============================================================================
// �Փ˃A�N�V����
//=============================================================================
void Player::CollAction(Base_Enemy* enemy)
{
	//���G
	if (m_InvincibleFrame > 0)
		return;

	//���
	if (m_AvoidFrame > 0) {
		GetObjManager()->Accept(new Protect(this, { 150,150,0 }, { 0.0f,175.0f / FULL_COLOR,204.0f / FULL_COLOR,1.0f }));
		PlaySound("avoid", 0, 0.8f, 0);
		return;
	}

	//�Փ�
	m_InvincibleFrame = INVINCIBLE;
	GetObjManager()->Accept(new Explosion(
		{ RefPos().x,RefPos().y + 50.0f,RefPos().z },
		NO_VECTOR3, { 200.0f,200.0f,200.0f }, DEF_COLOR));
	m_Hp -= enemy->RefDamage();
	PlaySound("hit", 0, 0.8f, 0);
}
//=============================================================================
// ����
//=============================================================================
void Player::Move(void)
{
	//����
	Fall();

	//�A�N�V����
	Action();

	if (m_GroundFlag)
	{
		//���[���̕ύX
		if (GetKeyboardTrigger(DIK_A)) {
			--m_Index;
			if (m_Index < 0)m_Index = m_Table.size() - 1;
			SetPos(m_Table[m_Index]);
		}
		if (GetKeyboardTrigger(DIK_D)) {
			++m_Index;
			if (m_Index >= m_Table.size())m_Index = 0;
			SetPos(m_Table[m_Index]);
		}
		//�W�����v
		if (GetKeyboardTrigger(DIK_SPACE)) {
			m_JampFlag = true;
			m_VSpeed = VALUE_JUMP;
			PlaySound("jump", 0, 0.4f, 0);
		}
	}
	else {
		//��i�W�����v
		if (GetKeyboardTrigger(DIK_SPACE) && !m_DJampFlag) {
			GetObjManager()->Accept(new Tornado(this, { 200,200,0 }, DEF_COLOR));
			m_DJumpFrame = DOUBLE_JAMP;
			m_DJampFlag = true;
			PlaySound("rotate", 0, 0.6f, 0);
		}
	}

	//�ړ��x�N�g���̐ݒ�
	SetVel({ RefVel().x,m_VSpeed,RefVel().z });

	if (m_DJumpFrame <= 0) {
		//���W�̍X�V
		SetPos(RefPos() + RefVel());
	}
	else {
		//��]�̍X�V
		RefRot().y = RefRot().y < D3DX_PI*2.0f ? RefRot().y + 0.4f : RefRot().y;
	}

	//�ړ��͈͐���
	MoveRange();

	if (m_Hp <= 0) {
		//RESULT�ֈڍs����
		SceneTransition(SCENE_RESULT);
	}
}
//=============================================================================
// �A�r���e�B�A�N�V����
//=============================================================================
void Player::Action(void)
{
	if (m_Pp < VALUE_AVOID)
		return;

	//���
	if (GetKeyboardTrigger(DIK_S) && m_AvoidFrame <= 0) {
		GetMaterial()->Diffuse.a = 0.3f;
		m_AvoidFrame = AVOID;
		m_Pp -= VALUE_AVOID;
	}
}
//=============================================================================
// ����
//=============================================================================
void Player::Fall(void)
{
	if (RefPos().y > 0)
		m_GroundFlag = false;

	if (m_GroundFlag) {
		if (m_JampFlag) m_JampFlag = false;
		if (m_DJampFlag) m_DJampFlag = false;
		if (m_VSpeed < 0) m_VSpeed = 0;
		return;
	}

	if (m_DJumpFrame <= 0) {
		m_VSpeed = (m_VSpeed <= -15.0f ? -15.0f : m_VSpeed - 1.0f);
	}
}
//=============================================================================
// �ړ��͈�
//=============================================================================
void Player::MoveRange(void)
{
	//Y���̈ړ��͈�
	if (RefPos().y < 0) {
		SetPos({ RefPos().x,0.0f,RefPos().z });
		m_GroundFlag = true;
	}
}
//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void Player::AddScore(int value)
{
	m_Score.AddScore(value);
}
//=============================================================================
// �e�t���[������
//=============================================================================
void Player::EachFrame(void)
{
	//���G�t���[������
	if (m_InvincibleFrame > 0)
		--m_InvincibleFrame;

	//�p���B�t���[������
	if (m_AvoidFrame > 0)
		--m_AvoidFrame;
	else
		GetMaterial()->Diffuse.a = 1.0f;

	//��i�W�����v�t���[������
	if (m_DJumpFrame > 0) {
		--m_DJumpFrame;
		if (m_DJumpFrame <= 0) {
			RefRot().y = 0.0f;
		}
	}

}
//=============================================================================
// ���t�@�����X
//=============================================================================
const int& Player::RefHp(void) const
{
	return m_Hp;
}
const int& Player::RefParyyFrame(void) const
{
	return m_AvoidFrame;
}
//=============================================================================
// �Z�b�^�[
//=============================================================================
void Player::SetHp(int amount)
{
	m_Hp = amount;
}
