/*==============================================================================

   �V�[���Ǘ� [scene.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/

#include "scene.h"
#include "title.h"
#include "menu.h"
#include "menu_deck.h"
#include "menu_stage.h"
#include "game.h"
#include "result.h"
#include "fade.h"


/*------------------------------------------------------------------------------
   �萔��`
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   �\���̐錾
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   �v���g�^�C�v�錾
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   �O���[�o���ϐ��̒�`
------------------------------------------------------------------------------*/
static SCENE g_SceneIndex = SCENE_NONE;
static SCENE g_SceneNextIndex = g_SceneIndex;


/*------------------------------------------------------------------------------
   �������֐�
------------------------------------------------------------------------------*/
void InitScene(SCENE index)
{
	g_SceneIndex = g_SceneNextIndex = index;

	switch (g_SceneIndex)
	{
	case SCENE_NONE:
		break;

	case SCENE_TITLE:
		InitTitle();
		break;

	case SCENE_MENU:
		InitMenu();
		break;

	case SCENE_DECK:
		InitMenuDeck();
		break;

	case SCENE_STAGE:
		InitMenuStage();
		break;

	case SCENE_GAME:
		InitGame();
		break;

	case SCENE_RESULT:
		InitResult();
		break;
	}
}

/*------------------------------------------------------------------------------
   �I������������֐�
------------------------------------------------------------------------------*/
void UninitScene(void)
{
	switch (g_SceneIndex)
	{
	case SCENE_NONE:
		break;

	case SCENE_TITLE:
		UninitTitle();
		break;

	case SCENE_MENU:
		UninitMenu();
		break;

	case SCENE_DECK:
		UninitMenuDeck();
		break;

	case SCENE_STAGE:
		UninitMenuStage();
		break;

	case SCENE_GAME:
		UninitGame();
		break;

	case SCENE_RESULT:
		UninitResult();
		break;
	}
}

/*------------------------------------------------------------------------------
   �X�V����������֐�
------------------------------------------------------------------------------*/
void UpdateScene(void)
{
	switch( g_SceneIndex ) 
	{
	case SCENE_NONE:
		break;

	case SCENE_TITLE:
		UpdateTitle();
		break;

	case SCENE_MENU:
		UpdateMenu();
		break;

	case SCENE_DECK:
		UpdateMenuDeck();
		break;

	case SCENE_STAGE:
		UpdateMenuStage();
		break;

	case SCENE_GAME:
		UpdateGame();
		break;

	case SCENE_RESULT:
		UpdateResult();
		break;
	}

	UpdateFade();
}

/*------------------------------------------------------------------------------
   �`�揈��������֐�
------------------------------------------------------------------------------*/
void DrawScene(void)
{
	switch( g_SceneIndex )
	{
	case SCENE_NONE:
		break;

	case SCENE_TITLE:
		DrawTitle();
		break;

	case SCENE_MENU:
		DrawMenu();
		break;

	case SCENE_DECK:
		DrawMenuDeck();
		break;

	case SCENE_STAGE:
		DrawMenuStage();
		break;

	case SCENE_GAME:
		DrawGame();
		break;

	case SCENE_RESULT:
		DrawResult();
		break;
	}

	DrawFade();
}

/*------------------------------------------------------------------------------
   �V�[���J�ڂ�v������֐�
------------------------------------------------------------------------------*/
void SetScene(SCENE index)
{
	//�J�ڐ�V�[����ݒ肷��
	g_SceneNextIndex = index;
}

/*------------------------------------------------------------------------------
   �J�ڂ�v��������ꍇ�ɃV�[����؂�ւ���֐�
------------------------------------------------------------------------------*/
void CheckScene(void)
{
	//���݂̃V�[���ƑJ�ڐ�V�[��������Ă�����
	if( g_SceneIndex != g_SceneNextIndex )
	{
		//���݂̃V�[�����I��������
		UninitScene();
		
		//�J�ڐ�V�[���̏������������s��
		InitScene(g_SceneNextIndex);
	}
}