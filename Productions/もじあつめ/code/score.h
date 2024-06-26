/*==============================================================================

   �X�R�A�Ǘ�[score.h]
														 Author :�ؓc �C���l
														 Date   :2023/06/16
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"
#include "renderer.h"
#include "myfunction.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SUCCESS_POINT 100
#define SCORE_NUM 5
#define SCORE_DIGIT 6

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
struct SCORE {
	D3DXVECTOR2		pos;	//�ʒu�x�N�g��
	D3DXVECTOR2		size;	//�T�C�Y
	D3DXVECTOR2		tex_f;	//�Œ�e�N�X�`�����W
	D3DXCOLOR		color;	//�J���[
	int				score;
	bool			newrecord;	//�V�L�^�t���O
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(int point);
SCORE* GetScore(void);
int* GetScoreData(void);
int ScoreDataNum(void);
void LoadScore(std::string failename);
void SaveScore(std::string filename);

#endif // !_SCORE_H_