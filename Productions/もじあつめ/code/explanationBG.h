/*==============================================================================

   �������BG�Ǘ�[explanationBG.h]
														 Author :�ؓc �C���l
														 Date   :2023/09/15
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once
#ifndef _EXPLANATIONBG_H_
#define _EXPLANATIONBG_H_

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
struct EXPLANATIONBG {
	D3DXVECTOR2		pos;	//�ʒu�x�N�g��
	D3DXVECTOR2		size;	//�T�C�Y
	D3DXVECTOR2		tex_v;	//�σe�N�X�`�����W
	D3DXVECTOR2		tex_f;	//�Œ�e�N�X�`�����W
	D3DXCOLOR		color;	//�J���[
	float			rot;
	bool			coll;
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitExplanationBG(void);
void UninitExplanationBG(void);
void UpdateExplanationBG(void);
void DrawExplanationBG(void);
EXPLANATIONBG* GetExplanationBGButton(void);

#endif // !_EXPLANATIONBG_H_