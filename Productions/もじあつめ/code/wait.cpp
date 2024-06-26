/*==============================================================================

   �ҋ@�Ǘ� [wait.cpp]
														 Author :�ؓc �C���l
														 Date   :2023/06/16
--------------------------------------------------------------------------------

==============================================================================*/
#include "sprite.h"
#include "texture.h"
#include "myfunction.h"
#include "wait.h"
#include "image.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define WAIT_TIME 3
#define WAIT_DIGIT 1
#define WAIT_NUM_SIZE (NUM_SIZE*5)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int g_WaitFrame;
int g_WaitTimer;

//=============================================================================
// ����������
//=============================================================================
void InitWait(void)
{
	//�ҋ@�^�C�}�[������
	g_WaitTimer = WAIT_TIME;
	g_WaitFrame = 0;

	//�I�[�f�B�I�̏�����
	SOUND_RECORD* pSoundRecord = GetSoundRecord();
	PlaySound(pSoundRecord->SEWaitID, 0);
}

//=============================================================================
// �I������
//=============================================================================
void UninitWait(void)
{
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateWait(void)
{
	g_WaitFrame++;
	if (g_WaitFrame >= FPS)
	{
		g_WaitFrame = 0;
		g_WaitTimer--;
	}
	if (g_WaitTimer < 0)
	{
		//�V�[���̐؂�ւ�
		SetScene(SCENE_GAME);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawWait(void)
{
	IMAGE* pImage = GetImage();

	//�w�i�`��
	DrawSpriteLeftTopColor(pImage->TexBlackBoardID,
		D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT),
		D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f, 1.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//�ҋ@���ԕ`��
	if (g_WaitTimer > 0)
	{
		int time = g_WaitTimer;
		for (int waitCnt = 0; waitCnt < WAIT_DIGIT; waitCnt++)
		{
			int bottom = BottomDigit(time);

			time /= 10;

			DrawSpriteColor(pImage->TexDefNumID,
				D3DXVECTOR2(SCREEN_H_WIDTH, SCREEN_H_HEIGHT),
				D3DXVECTOR2(WAIT_NUM_SIZE, WAIT_NUM_SIZE),
				D3DXVECTOR2(bottom % NUM_PART_X * TEX_PART(NUM_PART_X), bottom / NUM_PART_X * TEX_PART(NUM_PART_Y)),
				D3DXVECTOR2(TEX_PART(NUM_PART_X), TEX_PART(NUM_PART_Y)),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			);
		}
	}
	else
	{
		DrawWord(pImage->TexDefChrID,
			D3DXVECTOR2(SCREEN_H_WIDTH - WAIT_NUM_SIZE * 2.5f, SCREEN_H_HEIGHT - WAIT_NUM_SIZE * 0.5f),
			"start",
			WAIT_NUM_SIZE,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
		);
	}
}