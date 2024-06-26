//=============================================================================
//
// �A�C�e������ [base_item.h]
// Author : �ؓc�C���l
//
//=============================================================================
#ifndef _BASE_ITEM_H_
#define _BASE_ITEM_H_
#pragma once

#include <d3dx9.h>
#include "base_object.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �񋓑̐錾
//*****************************************************************************
enum Item_Tag {
	torus,
	crystal
};

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class Base_Item:public Base_Object
{
private:
	Item_Tag m_Tag;		//�A�C�e���^�O
	int		m_Heal;
	int		m_Score;
public:
	Base_Item() = default;
	Base_Item(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use, Item_Tag tag, int heal, int score);
	virtual ~Base_Item() = default;
	void CollDispatch(Base_Object* pObj)override;
	virtual void MoveRange(float limit);

	//���t�@�����X
	const int& RefHeal(void) const;
	const int& RefScore(void) const;
};

#endif // !_BASE_ITEM_H_