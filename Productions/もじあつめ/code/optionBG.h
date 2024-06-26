/*==============================================================================

  �ݒ�BG�Ǘ�[option.h]
														Author :�ؓc �C���l
														Date   :2023/09/11
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once
#ifndef _OPTIONBG_H_
#define _OPTIONBG_H_

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ADJUSTMENT_NUM 8
#define SETTING_NUM 6
//*****************************************************************************
// �\���̐錾
//*****************************************************************************
struct OPTION {
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
void InitOptionBG(void);
void UninitOptionBG(void);
void UpdateOptionBG(void);
void DrawOptionBG(void);
OPTION* GetAdCursor(void);
OPTION* GetOptionBGButton(void);

#endif // !_OPTIONBG_H_
