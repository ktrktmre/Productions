//=============================================================================
//
// �G���� [base_enemy.h]
// Author : �ؓc�C���l
//
//=============================================================================
#ifndef _BASE_ENEMY_H_
#define _BASE_ENEMY_H_
#pragma once

#include <d3dx9.h>
#include "base_object.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define VALUE_ADD_DAMAGE	(5)
#define VALUE_ADD_TIME		(5)

//*****************************************************************************
// �񋓑̐錾
//*****************************************************************************
enum Enemy_Tag {	//�G�l�~�[�^�C�v
	tree,
	lightning,
	ball
};

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class Base_Enemy:public Base_Object
{
private:
	Enemy_Tag			m_Tag;				// �G�l�~�[�̃^�C�v
	int					m_Damage;			// �_���[�W
public:
	Base_Enemy() = default;
	Base_Enemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use, Enemy_Tag tag, int damage);
	virtual ~Base_Enemy() = default;
	void CollDispatch(Base_Object* pObj)override;
	virtual void MoveRange(float limit);

	//���t�@�����X
	const Enemy_Tag& RefType(void) const;
	const int& RefDamage(void) const;

	//�Z�b�^�[
	void SetType(Enemy_Tag tag);
};

#endif // !_BASE_ENEMY_H_