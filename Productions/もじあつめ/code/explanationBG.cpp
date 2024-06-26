/*==============================================================================

   �������BG�Ǘ� [explanationBG.cpp]
														 Author :�ؓc �C���l
														 Date   :2023/06/16
--------------------------------------------------------------------------------

==============================================================================*/
#include "input.h"
#include "sprite.h"
#include "texture.h"
#include "player.h"
#include "fade.h"
#include "myfunction.h"
#include "explanationBG.h"
#include "image.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define EXPLANATION_BUTTON_SIZE 80

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
EXPLANATIONBG g_ExplanationBG;
EXPLANATIONBG g_ExplanationBGButton;
int g_TexExplanationBGID;

//=============================================================================
// ����������
//=============================================================================
void InitExplanationBG(void)
{
	ID3D11Device* pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	g_TexExplanationBGID = LoadTexture((char*)"data/TEXTURE/explanation_text.png");

	//�w�i�̏�����
	g_ExplanationBG.pos = D3DXVECTOR2(0.0f, 0.0f);
	g_ExplanationBG.size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	g_ExplanationBG.tex_v = D3DXVECTOR2(0.0f, 0.0f);
	g_ExplanationBG.tex_f = D3DXVECTOR2(1.0f, 1.0f);
	g_ExplanationBG.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_ExplanationBG.rot = 0.0f;
	g_ExplanationBG.coll = false;

	//�{�^���̏�����
	g_ExplanationBGButton.pos = D3DXVECTOR2(Contrast(422, 257) * EXPLANATION_BUTTON_SIZE, EXPLANATION_BUTTON_SIZE);
	g_ExplanationBGButton.size = D3DXVECTOR2(Contrast(422, 257) * EXPLANATION_BUTTON_SIZE, EXPLANATION_BUTTON_SIZE);
	g_ExplanationBGButton.tex_v = D3DXVECTOR2(0.0f, 0.0f);
	g_ExplanationBGButton.tex_f = D3DXVECTOR2(1.0f, 1.0f);
	g_ExplanationBGButton.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_ExplanationBGButton.rot = 0.0f;
	g_ExplanationBGButton.coll = false;
}

//=============================================================================
// �I������
//=============================================================================
void UninitExplanationBG(void)
{
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateExplanationBG(void)
{
	PLAYER* pPlayer = GetPlayer();
	if (g_ExplanationBGButton.coll && pPlayer->shoot)
	{
		//�t�F�[�h���N���Ă��Ȃ�������
		MODE_FADE* pFade = GetFade();
		if (*pFade == FADE_NOT)
		{
			SetFade(FADE_OUT);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawExplanationBG(void)
{
	SetSamplerState(FILTER_MODE_LINEAR, ADDRESS_MODE_WRAP);

	IMAGE* pImage = GetImage();

	//�������BG�̕`��
	DrawSpriteLeftTop(g_TexExplanationBGID,
		g_ExplanationBG.pos,
		g_ExplanationBG.size,
		g_ExplanationBG.tex_v,
		g_ExplanationBG.tex_f);

	//�{�^���̕`��
	DrawSpriteColor(pImage->TexReturnID,
		g_ExplanationBGButton.pos,
		g_ExplanationBGButton.size,
		g_ExplanationBGButton.tex_v,
		g_ExplanationBGButton.tex_f,
		g_ExplanationBGButton.color
	);
}

//=============================================================================
// �{�^���Q�b�g�֐�
//=============================================================================
EXPLANATIONBG* GetExplanationBGButton(void)
{
	return &g_ExplanationBGButton;
}