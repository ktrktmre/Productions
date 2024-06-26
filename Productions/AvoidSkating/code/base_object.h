//=============================================================================
//
// �I�u�W�F�N�g���� [base_object.h]
// Author : �ؓc�C���l
//
//=============================================================================
#ifndef _BASE_OBJECT_H_
#define _BASE_OBJECT_H_
#pragma once

#include <d3dx9.h>
#include <vector>
#include "renderer.h"
#include "base_collision.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class Object_Manager;
class Player;
class Base_Enemy;
class Base_Item;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define DISTANCE_DIFF	(10.0f)					// maya�ƊJ�����̋����̍�
#define NO_VECTOR3		{0.0f,0.0f,0.0f}		// 3d�x�N�^�[��0������
#define NO_COLOR		{0.0f,0.0f,0.0f,0.0f}	// �J���[��0������
#define DEF_COLOR		{1.0f,1.0f,1.0f,1.0f}	// �f�t�H���g�J���[

//*****************************************************************************
// �񋓑�
//*****************************************************************************
enum Object_Tag {
	player,
	enemy,
	item,
	anime,
	ability,
	background,
	inviolability
};

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class Base_Object {
private:
	Object_Manager*					m_ObjManager;				// �}�l�[�W���[
	Object_Tag						m_ObjTag;					// �I�u�W�F�N�g�^�O
	D3DXVECTOR3						m_Pos;						// �|���S���̍��W
	D3DXVECTOR3						m_Rot;						// �|���S���̌���(��])
	D3DXVECTOR3						m_Scl;						// �|���S���̑傫��(�X�P�[��)
	D3DXVECTOR3						m_Vel;						// ���x
	D3DXCOLOR						m_Color;					// �|���S���̃J���[
	D3DXMATRIX						m_MtxWorld;					// ���[���h�}�g���b�N�X
	MATERIAL						m_Material;					// �}�e���A��
	std::vector<Base_Collision*>	m_Collision;				// �R���W����
	bool							m_Use;						// �g�p�t���O
public:
	Base_Object() = default;
	Base_Object(Object_Tag tag, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use);
	virtual ~Base_Object();

	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	//�Q�b�^�[
	Object_Manager* GetObjManager(void);
	D3DXMATRIX* GetMtx(void);
	MATERIAL* GetMaterial(void);
	const std::vector<Base_Collision*>* GetColl(void);
	Base_Collision* GetColl(int index);

	//���t�@�����X
	Object_Tag& RefTag(void);
	D3DXVECTOR3& RefPos(void);
	D3DXVECTOR3& RefRot(void);
	D3DXVECTOR3& RefScl(void);
	D3DXVECTOR3& RefVel(void);
	D3DXCOLOR& RefColor(void);
	const bool& RefUse(void) const;

	//�Z�b�^�[
	void SetObjManager(Object_Manager* manager);
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	void SetScl(D3DXVECTOR3 scl);
	void SetVel(D3DXVECTOR3 vel);
	void SetColor(D3DXCOLOR color);
	void SetUse(bool use);
	void SetColl(Base_Collision* coll);

	//�Փ˃A�N�V����
	virtual void CollDispatch(Base_Object* pObj) = 0;
	virtual void CollAction(Player* player);
	virtual void CollAction(Base_Enemy* enemy);
	virtual void CollAction(Base_Item* item);
};

#endif // !_BASE_OBJECT_H_