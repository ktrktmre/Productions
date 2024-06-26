/*==============================================================================

   �v���C���[�Ǘ� [player.cpp]
														 Author :�ؓc �C���l
														 Date   :2023/06/16
--------------------------------------------------------------------------------

==============================================================================*/
#include "input.h"
#include "sprite.h"
#include "texture.h"
#include "myfunction.h"
#include "image.h"
#include "player.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CURSOR_SIZE 60.0f
#define SCORE_DIGIT 6

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
PLAYER g_Player;
POINT g_Cursor;
D3DXCOLOR g_UpdatePlayerColor;
bool g_OncePlayerColor = false;

//=============================================================================
// ����������
//=============================================================================
void InitPlayer(void)
{

	ID3D11Device* pDevice = GetDevice();


	//�}�E�X�̌��ݍ��W�̎擾
	GetCursorPos(&g_Cursor);

	//�v���C���[�̏�����
	g_Player.pos = D3DXVECTOR2(0.0f, 0.0f);
	g_Player.size = D3DXVECTOR2(0.0f, 0.0f);
	g_Player.tex_v = D3DXVECTOR2(0.0f, 0.0f);
	g_Player.tex_f = D3DXVECTOR2(0.0f, 0.0f);
	g_Player.color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	g_Player.coll = false;
	g_Player.shoot = false;
	g_Player.grab = false;
	g_Player.stuck = false;

	//�v���C���[�̃Z�b�g
	SetPlayer(D3DXVECTOR2(g_Cursor.x, g_Cursor.y), D3DXVECTOR2(CURSOR_SIZE, CURSOR_SIZE));
	if (!g_OncePlayerColor)	//���񂾂��Ńf�t�H���g�̐F�ŌĂяo��
	{
		SetPlayerColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f));
	}
	else
	{
		SetPlayerColor(g_UpdatePlayerColor);
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	if (!g_Player.stuck)
	{
		//�}�E�X�̌��ݍ��W�̎擾
		GetCursorPos(&g_Cursor);
		g_Player.pos = D3DXVECTOR2(g_Cursor.x, g_Cursor.y);
	}

	//�N���b�N����
	if (g_Player.coll)
	{
		if (IsMouseLeftTriggered()|| GetKeyboardTrigger(DIK_SPACE))
		{
			g_Player.shoot = true;
			SOUND_RECORD* pSoundRecord = GetSoundRecord();

			//�J�[�\���X�^�b�N
			SCENE* pScene = GetScene();
			if (*pScene != SCENE_GAME)
			{
				g_Player.stuck = true;
			}

			//�T�E���h
			if (*pScene != SCENE_GAME)
			{
				PlaySound(pSoundRecord->SEButtonID, 0);
			}
		}
	}
	if (IsMouseLeftPressed() || GetKeyboardPress(DIK_SPACE))
	{
		g_Player.grab = true;
	}
	else
	{
		g_Player.grab = false;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	SetSamplerState(FILTER_MODE_LINEAR, ADDRESS_MODE_WRAP);

	IMAGE* pImage = GetImage();

	//�v���C���[�̕`��
	DrawSpriteColor(pImage->TexCursorID,
		g_Player.pos,
		g_Player.size,
		g_Player.tex_v,
		g_Player.tex_f,
		g_Player.color);
}

//=============================================================================
// �v���C���[�Q�b�^�[
//=============================================================================
PLAYER* GetPlayer(void)
{
	return &g_Player;
}

//=============================================================================
// �v���C���[�Z�b�^�[
//=============================================================================
void SetPlayer(D3DXVECTOR2 pos, D3DXVECTOR2 size)
{
	g_Player.pos = pos;
	g_Player.size = size;
	g_Player.tex_v = D3DXVECTOR2(0.0f, 0.0f);
	g_Player.tex_f = D3DXVECTOR2(1.0f, 1.0f);
}

//=============================================================================
// �v���C���[�J���[�R�s�[
//=============================================================================
D3DXCOLOR CopyPlayerColor(void)
{
	return (D3DXCOLOR(g_Player.color.r * FULL_COLOR, g_Player.color.g * FULL_COLOR, g_Player.color.b * FULL_COLOR, g_Player.color.a));
}

//=============================================================================
// �v���C���[�J���[�Z�b�^�[
//=============================================================================
void SetPlayerColor(D3DXCOLOR color)
{
	//�v���C���[�J���[�̕ύX
	g_Player.color.r = color.r;
	g_Player.color.g = color.g;
	g_Player.color.b = color.b;
	g_Player.color.a = 1.0f;

	//�v���C���[�J���[�̕ۑ�
	g_UpdatePlayerColor = g_Player.color;

	g_OncePlayerColor = true;
}