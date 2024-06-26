/*==============================================================================

   �Q�[��BG�Ǘ� [gameBG.cpp]																	  Date   :2023/06/16
														 Author :�ؓc �C���l
														 Date   :2023/06/16
--------------------------------------------------------------------------------

==============================================================================*/
#include "input.h"
#include "sprite.h"
#include "texture.h"
#include "gameBG.h"
#include "image.h"
#include "myfunction.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define DAYSHIFT_SIZE 150

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
GAMEBG g_GameBG;
GAMEBG g_DayShift;
int g_DayShiftID;
//=============================================================================
// ����������
//=============================================================================
void InitGameBG(void)
{
	ID3D11Device* pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	g_DayShiftID = LoadTexture((char*)"data/TEXTURE/dayshift.png");

	//������
	g_GameBG.pos = D3DXVECTOR2(0.0f, 0.0f);
	g_GameBG.size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	g_GameBG.tex_v = D3DXVECTOR2(0.0f, 0.0f);
	g_GameBG.tex_f = D3DXVECTOR2(1.0f, 1.0f);
	g_GameBG.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_GameBG.rot = 0.0f;

	g_DayShift.pos = D3DXVECTOR2(SCREEN_WIDTH - DAYSHIFT_SIZE, SCREEN_HEIGHT - DAYSHIFT_SIZE * 3);
	g_DayShift.size = D3DXVECTOR2(DAYSHIFT_SIZE, DAYSHIFT_SIZE * Contrast(619, 356));
	g_DayShift.tex_v = D3DXVECTOR2(0.0f, 0.0f);
	g_DayShift.tex_f = D3DXVECTOR2(1.0f, 1.0f);
	g_DayShift.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_DayShift.rot = 0.0f;
}

//=============================================================================
// �I������
//=============================================================================
void UninitGameBG(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGameBG(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGameBG(void)
{
	SetSamplerState(FILTER_MODE_LINEAR, ADDRESS_MODE_WRAP);
	IMAGE* pImage = GetImage();

	//�^�C�g��BG�̕`��
	DrawSpriteLeftTop(pImage->TexBlackBoardID,
		g_GameBG.pos,
		g_GameBG.size,
		g_GameBG.tex_v,
		g_GameBG.tex_f);

	//�����̕`��
	DrawSpriteLeftTop(g_DayShiftID,
		g_DayShift.pos,
		g_DayShift.size,
		g_DayShift.tex_v,
		g_DayShift.tex_f);
}