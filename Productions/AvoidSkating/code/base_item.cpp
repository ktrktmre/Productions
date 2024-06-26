//=============================================================================
//
// �A�C�e������ [base_item.cpp]
// Author : �ؓc�C���l
//
//=============================================================================
#include "base_item.h"

//=============================================================================
// �����t���R���X�g���N�^
//=============================================================================
Base_Item::Base_Item(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use, Item_Tag tag, int heal, int score)
	:Base_Object(item, pos, rot, scl, vel, color, use), m_Tag(tag), m_Heal(heal), m_Score(score)
{
}
//=============================================================================
// �Փ˔���f�B�X�p�b�`
//=============================================================================
void Base_Item::CollDispatch(Base_Object* pObj)
{
	pObj->CollAction(this);
}
//=============================================================================
// �ړ��͈�
//=============================================================================
void Base_Item::MoveRange(float limit)
{
	if (RefPos().z <= limit)
		SetUse(false);
}
//=============================================================================
// ���t�@�����X
//=============================================================================
const int& Base_Item::RefHeal(void) const
{
	return m_Heal;
}
const int& Base_Item::RefScore(void) const
{
	return m_Score;
}
