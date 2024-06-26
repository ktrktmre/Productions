//=============================================================================
//
// �v���C���[���� [player.h]
// Author : �ؓc�C���l
//
//=============================================================================
#pragma once

#include <d3dx9.h>
#include <vector>
#include "base_object.h"
#include "score.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
class Player :public Base_Object {
private:
	Score m_Score;
	std::vector<D3DXVECTOR3> m_Table;
	int m_InvincibleFrame;
	int m_AvoidFrame;
	int m_DJumpFrame;
	int m_Index;
	float m_Hp;
	float m_Pp;
	float m_VSpeed;
	bool m_JampFlag;
	bool m_DJampFlag;
	bool m_GroundFlag;
public:
	Player();
	~Player() = default;

	void Update(void)override;
	void Draw(void)override;
	void CollDispatch(Base_Object* pObj)override;
	void CollAction(Base_Enemy* enemy)override;
	void Move(void);
	void Action(void);
	void Fall(void);
	void MoveRange(void);
	void AddScore(int value);
	void EachFrame(void);

	//���t�@�����X
	const int& RefHp(void) const;
	const int& RefParyyFrame(void) const;

	//�Z�b�^�[
	void SetHp(int amount);
};