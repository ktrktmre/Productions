//=============================================================================
//
// �{�[���G�l�~�[���� [bullet.h]
// Author : �ؓc�C���l
//
//=============================================================================
#ifndef _BALL_ENEMY_H_
#define _BALL_ENEMY_H_
#pragma once

#include <d3dx9.h>
#include "Base_enemy.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class Ball_Enemy:public Base_Enemy
{
private:
public:
	Ball_Enemy() = default;
	Ball_Enemy(D3DXVECTOR3 pos, int damage);
	~Ball_Enemy() = default;
	void Update(void)override;
	void Draw(void)override;
	void CollDispatch(Base_Object* pObj)override;
	void CollAction(Player* player)override;
	void Fall(void);
	void Bound(void);
	void MoveRange(float limit)override;
};

#endif // !_BALL_ENEMY_H_