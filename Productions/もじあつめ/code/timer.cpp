/*==============================================================================

   �^�C�}�[�Ǘ� [timer.cpp]
														 Author :�ؓc �C���l
														 Date   :2023/06/16
--------------------------------------------------------------------------------

==============================================================================*/
#include "sprite.h"
#include "texture.h"
#include "myfunction.h"
#include "timer.h"
#include "game.h"
#include "fade.h"
#include "image.h"
#include "sound.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define GAME_TIME 30
#define GAME_END_INTERVAL 2
#define TIME_DIGIT 3
#define TIMER_NUM_SIZE (NUM_SIZE*4)

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
int g_Timer;
int g_IntervalTimer;
int g_TimerFrame;

//=============================================================================
// ����������
//=============================================================================
void InitTimer(void)
{
	//�^�C�}�[������
	g_TimerFrame = g_Timer = g_IntervalTimer =0;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTimer(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTimer(void)
{
	SOUND_RECORD* pSoundRecord = GetSoundRecord();
	g_TimerFrame++;
	if (g_TimerFrame >= FPS)
	{
		g_TimerFrame = 0;

		if (g_Timer < GAME_TIME)
		{
			g_Timer++;
			if (g_Timer == GAME_TIME)
			{
				PlaySound(pSoundRecord->SEGameEndID, 0);
				SetPause(true);
			}
		}
		else
		{
			g_IntervalTimer++;
		}
	}
	if (g_IntervalTimer> GAME_END_INTERVAL)
	{
		//�V�[���̐؂�ւ�
		{
			//�t�F�[�h���N���Ă��Ȃ�������
			MODE_FADE* pFade = GetFade();
			if (*pFade == FADE_NOT)
			{
				SetFade(FADE_OUT);
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTimer(void)
{
	IMAGE* pImage = GetImage();

	int time = g_Timer;
	for (int timeCnt = 0; timeCnt < TIME_DIGIT; timeCnt++)
	{
		int bottom = BottomDigit(time);
		time /= 10;

		DrawSpriteLeftTopColor(pImage->TexDefNumID,
			D3DXVECTOR2((NUM_SIZE * 2) - NUM_SIZE * timeCnt, 0.0f),
			D3DXVECTOR2(NUM_SIZE, NUM_SIZE),
			D3DXVECTOR2(bottom % NUM_PART_X * TEX_PART(NUM_PART_X), bottom / NUM_PART_X * TEX_PART(NUM_PART_Y)),
			D3DXVECTOR2(TEX_PART(NUM_PART_X), TEX_PART(NUM_PART_Y)),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	if (g_Timer >= GAME_TIME)
	{
		DrawWord(pImage->TexDefChrID,
			D3DXVECTOR2(SCREEN_H_WIDTH - TIMER_NUM_SIZE * 3.0f, SCREEN_H_HEIGHT - TIMER_NUM_SIZE * 0.5f),
			"finish",
			TIMER_NUM_SIZE,
			D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)
		);
	}
}