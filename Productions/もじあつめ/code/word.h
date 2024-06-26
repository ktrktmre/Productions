/*==============================================================================

   �����Ǘ�[word.h]
														 Author :�ؓc �C���l
														 Date   :2023/06/16
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once
#ifndef _WORD_H_
#define _WORD_H_

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define WORD_NUM 20
#define NORMAL_MODE_NUM 4;
#define HARD_MODE_NUM 5;
#define GAME_MODE_NUM 7;

//*****************************************************************************
// �񋓑̐錾
//*****************************************************************************
enum GAME_MODE {
	ALIGNMENT=0,
	ALIGNMENT_MOVE,
	ALIGNMENT_ROTATE,
	ALIGNMENT_ROT_MOVE,
	DIRECTION,
	FOUNTAIN,
	RAIN,
};

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
struct WORDS {
	D3DXVECTOR2		pos;		//�ʒu�x�N�g��
	D3DXVECTOR2		size;		//�T�C�Y
	D3DXVECTOR2		vel;		//���x�x�N�g��
	D3DXVECTOR2		tex_v;		//�σe�N�X�`�����W
	D3DXVECTOR2		tex_f;		//�Œ�e�N�X�`�����W
	D3DXCOLOR		color;		//�J���[
	int				frame;
	char			chr;
	float			rot;		//��]�p�x
	float			rot_speed;	//��]���x
	bool			coll;
	bool			use;
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitWord(void);
void UninitWord(void);
void UpdateWord(void);
void DrawWord(void);
WORDS* GetWord(void);
void SetWord(D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR color, char chr);

#endif // !_WORD_H_