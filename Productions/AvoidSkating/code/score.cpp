
//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : �ؓc�C���l
//
//=============================================================================
#include <fstream>
#include "score.h"
#include "texture.h"
#include "sprite.h"
#include "material.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCORE_MAX			(99999)		// �X�R�A�̍ő�l
#define SCORE_DIGIT			(5)			// ����
#define CHARA_SIZE			(100.0f)
#define PART_X				(5)
#define PART_Y				(2)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Score::Score()
	:m_Pos({ SCREEN_WIDTH - CHARA_SIZE,0.0f }), m_Scl({ CHARA_SIZE,CHARA_SIZE }), m_Color({0.0f,1.0f,0.0f,1.0f}), m_Score(0)
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
Score::~Score()
{
	std::ofstream ofs("data/SAVE/scoredata.txt");
	if (ofs.fail())
		return;

	ofs << m_Score;
}

//=============================================================================
// ���Z
//=============================================================================
void Score::AddScore(int value)
{
	m_Score += value;

	if (m_Score > SCORE_MAX)
	{
		m_Score = SCORE_MAX;
	}
}

//=============================================================================
// �`��
//=============================================================================
void Score::Draw(void)
{
	// ��������������
	int number = m_Score;
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		// ����\�����錅�̐���
		int x = (number % 10);

		// �X�R�A�̈ʒu��e�N�X�`���[���W�𔽉f
		float px = m_Pos.x - m_Scl.x * i;	// �\���ʒuX

		// �e�N�X�`�����W
		float v_x = (x % PART_X) * (1.0f / (float)PART_X);
		float v_y = (x / PART_X) * (1.0f / (float)PART_Y);

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		DrawScreenLT(UI{ {px ,m_Pos.y},0.0f,m_Scl,{v_x,v_y},
			{1.0f / (float)PART_X,1.0f / (float)PART_Y},m_Color },RefImageMaterial().m_BauNumber);

		// ���̌���
		number /= 10;
	}
}