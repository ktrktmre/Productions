/*==============================================================================

   ��������Ǘ� [explanation.cpp]
														 Author :�ؓc �C���l
														 Date   :2023/06/16
--------------------------------------------------------------------------------

==============================================================================*/
#include "input.h"
#include "sprite.h"
#include "texture.h"
#include "explanation.h"
#include "explanationBG.h"
#include "player.h"
#include "collision.h"
#include "sound.h"


//=============================================================================
// ����������
//=============================================================================
void InitExplanation(void)
{
	InitExplanationBG();
	InitPlayer();

	//�I�[�f�B�I�̏�����
	SOUND_RECORD* pSoundRecord = GetSoundRecord();
	PlaySound(pSoundRecord->BGMGameID, SOUND_LOOP);
}

//=============================================================================
// �I������
//=============================================================================
void UninitExplanation(void)
{
	UninitExplanationBG();
	UninitPlayer();

	//�I�[�f�B�I�̏I��
	StopSoundAll();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateExplanation(void)
{
	UpdateExplanationBG();
	UpdatePlayer();
	UpdateCollision();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawExplanation(void)
{
	DrawExplanationBG();
	DrawPlayer();
}