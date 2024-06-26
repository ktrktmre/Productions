//=============================================================================
//
// ���U���g��ʏ��� [result.cpp]
// Author : �ؓc�C���l
//
//=============================================================================
#include <fstream>
#include "result.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "material.h"
#include "fade.h"
#include "sound.h"
#include "cursor.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCORE_DIGIT			(5)			// ����
#define CHARA_SIZE			(100.0f)
#define PART_X				(5)
#define PART_Y				(2)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Cursor* g_ResultCursor;
D3DXVECTOR2 g_NextPos;
D3DXVECTOR2 g_ReturnPos;
D3DXVECTOR2 g_ScorePos;
D3DXVECTOR2 g_ScoreScl;
bool g_Next;
bool g_Return;
int g_Score;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitResult(void)
{
	g_ResultCursor = new Cursor;

	std::fstream ifs("data/SAVE/scoredata.txt");
	if (!ifs.fail()) {
		ifs >> g_Score;
		g_ScoreScl = { 100.0f,100.0f };
		g_ScorePos = { SCREEN_CENTER_X + g_ScoreScl.x * 1.5f,SCREEN_CENTER_Y - g_ScoreScl.y };
	}

	g_Next = false;
	g_Return = false;

	g_NextPos = { SCREEN_CENTER_X + 500,SCREEN_CENTER_Y + 300 };
	g_ReturnPos = { SCREEN_CENTER_X - 500,SCREEN_CENTER_Y + 300 };

	PlaySound("result", 0, 0.2f, 0);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitResult(void)
{
	StopSoundAll();
	delete g_ResultCursor;
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateResult(void)
{
	g_ResultCursor->MoveCursor(VALUE_CURSOR);

	g_Next = false;
	g_Return = false;
	if (g_ResultCursor->RefCorsor().x >= (g_NextPos.x - BASE_BUTTON_HSIZE_X) && g_ResultCursor->RefCorsor().x <= (g_NextPos.x + BASE_BUTTON_HSIZE_X) &&
		g_ResultCursor->RefCorsor().y <= (g_NextPos.y + BASE_BUTTON_HSIZE_Y) && g_ResultCursor->RefCorsor().y >= (g_NextPos.y - BASE_BUTTON_HSIZE_Y))
		g_Next = true;
	if (g_ResultCursor->RefCorsor().x >= (g_ReturnPos.x - BASE_BUTTON_HSIZE_X) && g_ResultCursor->RefCorsor().x <= (g_ReturnPos.x + BASE_BUTTON_HSIZE_X) &&
		g_ResultCursor->RefCorsor().y <= (g_ReturnPos.y + BASE_BUTTON_HSIZE_Y) && g_ResultCursor->RefCorsor().y >= (g_ReturnPos.y - BASE_BUTTON_HSIZE_Y))
		g_Return = true;

	if (GetKeyboardTrigger(DIK_RETURN) && GetFadeState() == FADE_NONE)
	{
		SceneTransition(SCENE_TITLE);
	}
	if (IsMouseLeftTriggered() && g_Next && GetFadeState() == FADE_NONE) {
		SceneTransition(SCENE_TITLE);
	}
	if (IsMouseLeftTriggered() && g_Return && GetFadeState() == FADE_NONE) {
		SceneTransition(SCENE_GAME);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawResult(void)
{
	DrawScreenLT(UI{ { 0.0f,0.0f }, 0, { SCREEN_WIDTH, SCREEN_HEIGHT },  { 0.0f, 0.0f}, {1.0f, 1.0f,}, DEF_COLOR },
		RefImageMaterial().m_White);

	DrawScreen(UI{ { SCREEN_CENTER_X,SCREEN_CENTER_Y - 300 }, 0, { 386, 94 },  { 0.0f, 0.0f}, {1.0f, 1.0f,}, {0,0,0,1.0f} },
		RefImageMaterial().m_Score);

	// ��������������
	int number = g_Score;
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		// ����\�����錅�̐���
		int x = (number % 10);

		// �X�R�A�̈ʒu��e�N�X�`���[���W�𔽉f
		float px = g_ScorePos.x - g_ScoreScl.x * i;	// �\���ʒuX

		// �e�N�X�`�����W
		float v_x = (x % PART_X) * (1.0f / (float)PART_X);
		float v_y = (x / PART_X) * (1.0f / (float)PART_Y);

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		DrawScreenLT(UI{ {px ,g_ScorePos.y},0.0f,g_ScoreScl,{v_x,v_y},
			{1.0f / (float)PART_X,1.0f / (float)PART_Y},{0,0,0,1} }, RefImageMaterial().m_BauNumber);

		// ���̌���
		number /= 10;
	}

	D3DXCOLOR color;
	color = g_Next ? D3DXCOLOR(1, 1, 0, 1) : D3DXCOLOR(0, 0, 0, 1);
	DrawScreen(UI{ g_NextPos, 0, { BASE_BUTTON_SIZE_X, BASE_BUTTON_SIZE_Y },  { 0.0f, 0.0f}, {1.0f, 1.0f,}, color },
		RefImageMaterial().m_Title);
	color = g_Return ? D3DXCOLOR(1, 1, 0, 1) : D3DXCOLOR(0, 0, 0, 1);
	DrawScreen(UI{ g_ReturnPos, 0, { BASE_BUTTON_SIZE_X, BASE_BUTTON_SIZE_Y },  { 0.0f, 0.0f}, {1.0f, 1.0f,}, color },
		RefImageMaterial().m_Return);

	DrawScreenLT(UI{ g_ResultCursor->RefCorsor(), 0, { 100, 100 },  { 0.0f, 0.0f}, {1.0f, 1.0f,}, DEF_COLOR },
		RefImageMaterial().m_Cursor);
}
