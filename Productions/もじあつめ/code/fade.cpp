/*==============================================================================

   �t�F�[�h�Ǘ� [fade.cpp]
														 Author :�ؓc �C���l
														 Date   :2023/06/16
--------------------------------------------------------------------------------

==============================================================================*/
#include "main.h"
#include "fade.h"
#include "sprite.h"
#include "texture.h"
#include "result.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FADE_SPEED 0.02f

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
FADE g_Fade;	//����
MODE_FADE g_Mode_Fade;	//�t�F�[�h���[�h
int g_FadeTexNo = 0;	//�e�N�X�`��ID
float g_FadeAlpha = 0;	//�t�F�[�h�A���t�@�l
//=============================================================================
// ����������
//=============================================================================
void InitFade(void)
{
	ID3D11Device* pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	g_FadeTexNo = LoadTexture((char*)"data/TEXTURE/fade.png");

	//�t�F�[�h�̏�����
	g_Fade.pos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	g_Fade.size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	g_Fade.tex_v = D3DXVECTOR2(0.0f, 0.0f);
	g_Fade.tex_f = D3DXVECTOR2(1.0f, 1.0f);
	g_Fade.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�t�F�[�h�A���t�@�l�̏�����
	g_FadeAlpha = 0.0f;

	//�t�F�[�h���[�h�̏�����
	g_Mode_Fade = FADE_NOT;
}

//=============================================================================
// �I������
//=============================================================================
void UninitFade(void)
{
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateFade(void)
{
	//�t�F�[�h���[�h����
	switch (g_Mode_Fade)
	{
	case FADE_NOT:
		break;
	case FADE_IN:
		g_FadeAlpha -= FADE_SPEED;

		//�t�F�[�h�̏I��
		if (g_FadeAlpha <= 0.0f)
		{
			g_Mode_Fade = FADE_NOT;
		}

		break;
	case FADE_OUT:
		g_FadeAlpha += FADE_SPEED;

		if (g_FadeAlpha >= 1.0f)
		{
			g_Mode_Fade = FADE_IN;

			//�V�[���̐؂�ւ�
			SCENE* pScene = GetScene();

			switch (*pScene)
			{
			case SCENE_TITLE:
			{
				GAME_DIFF* pGameDiff = GetGameDiff();
				if (*pGameDiff <= FULL)
				{
					SetScene(SCENE_WAIT);
				}
				else if (*pGameDiff == OPTION)
				{
					SetScene(SCENE_OPTION);
				}
				else
				{
					SetScene(SCENE_EXPLANATION);
				}
				break;
			}
			case SCENE_OPTION:
				SetScene(SCENE_TITLE);
				break;
			case SCENE_EXPLANATION:
				SetScene(SCENE_TITLE);
				break;
			case SCENE_WAIT:
				SetScene(SCENE_GAME);
				break;
			case SCENE_GAME:
				SetScene(SCENE_RESULT);
				break;
			case SCENE_RESULT:
			{
				RESULT_MODE* pResultMode = GetResultMode();
				if (*pResultMode == RETURN)
				{
					SetScene(SCENE_TITLE);
				}
				else if (*pResultMode == REPLAY)
				{
					SetScene(SCENE_WAIT);
				}
			}
				break;
			default:
				break;
			}
		}

		break;
	case FADE_MAX:
		g_FadeAlpha = 1.0f;
		break;
	default:
		break;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawFade(void)
{
	SetSamplerState(FILTER_MODE_LINEAR, ADDRESS_MODE_WRAP);
	//�t�F�[�h�̕`��
	DrawSpriteColor(g_FadeTexNo,
		g_Fade.pos,
		g_Fade.size,
		g_Fade.tex_v,
		g_Fade.tex_f,
		D3DXCOLOR(g_Fade.color.r, g_Fade.color.g, g_Fade.color.b, g_FadeAlpha)
	);
}

//=============================================================================
// �t�F�[�h�Z�b�g�֐�
//=============================================================================
void SetFade(MODE_FADE mode)
{
	//�t�F�[�h���[�h�̃Z�b�g
	g_Mode_Fade = mode;

	//�t�F�[�h�A���t�@�l�̏�����
	if (g_Mode_Fade == FADE_IN)
	{
		g_FadeAlpha = 1.0f;
	}
	else if (g_Mode_Fade == FADE_OUT)
	{
		g_FadeAlpha = 0.0f;
	}
}

//=============================================================================
// �t�F�[�h�Q�b�g�֐�
//=============================================================================
MODE_FADE* GetFade(void)
{
	return &g_Mode_Fade;
}