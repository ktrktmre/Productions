//=============================================================================
//
// �X�R�A���� [score.h]
// Author : �ؓc�C���l
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class Score {
private:
	D3DXVECTOR2 m_Pos;
	D3DXVECTOR2 m_Scl;
	D3DXCOLOR m_Color;
	int m_Score;
public:
	Score();
	~Score();

	void AddScore(int value);
	void Draw(void);
};