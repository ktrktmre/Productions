//=============================================================================
//
// �Q�[������ [gamen.h]
// Author : �ؓc�C���l
//
//=============================================================================

#include "game.h"
#include "main.h"
#include "input.h"
#include "sprite.h"
#include "fade.h"
#include "player.h"
#include "meshfield.h"
#include "meshsky.h"
#include "sound.h"
#include "camera.h"
#include "shadow.h"
#include "object_manager.h"
#include "light.h"
#include "enemy_manager.h"
#include "item_manager.h"


/*------------------------------------------------------------------------------
   �O���[�o���ϐ��̒�`
------------------------------------------------------------------------------*/
static int g_BGMNo = 0;
bool g_Pause = false;
UINT32 CurrentSample = 0;
Player* g_Player;
Object_Manager* g_ObjectManager;
Field* g_Field;
Sky* g_Sky;
Light* g_Light;
Enemy_Manager* g_EnemyManager;
Item_Manager* g_ItemManager;


/*------------------------------------------------------------------------------
   �������֐�
------------------------------------------------------------------------------*/
void InitGame(void)
{
	// �n�ʂ̏�����
	g_Field = new Field(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 0.0f, 500.0f), 3, 100);

	// ��̏�����
	g_Sky = new Sky(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 4000.0f, 16, 8, false);

	// �v���C���[�̏�����
	g_Player = new Player;

	// �I�u�W�F�N�g�}�l�[�W���[�̏�����
	g_ObjectManager = new Object_Manager(g_Player);

	// �G�l�~�[�}�l�[�W���[�̏�����
	g_EnemyManager = new Enemy_Manager(g_ObjectManager);

	// �A�C�e���}�l�[�W���[�̏�����
	g_ItemManager = new Item_Manager(g_ObjectManager);

	// ���C�g�̏�����
	g_Light = new Light;

	SetLightEnable(true);

	SetAlphaTestEnable(false);

	PlaySound("game_bgm", -1, 0.2f, 0);
}

/*------------------------------------------------------------------------------
   �I������������֐�
------------------------------------------------------------------------------*/
void UninitGame()
{
	StopSoundAll();
	//�������Ƃ͋t���ɏI���������s��
	delete g_Light;
	delete g_ItemManager;
	delete g_EnemyManager;
	delete g_ObjectManager;
	delete g_Sky;
	delete g_Field;

}

/*------------------------------------------------------------------------------
   �X�V����������֐�
------------------------------------------------------------------------------*/
void UpdateGame(void)
{
	GetCamera()->Update();
	g_Field->Update();
	g_Sky->Update();
	g_ItemManager->Update();
	g_EnemyManager->Update();
	g_ObjectManager->Update();

#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_RETURN) && GetFadeState() == FADE_NONE)
	{
		SceneTransition(SCENE_RESULT);
	}
#endif // _DEBUG
}

/*------------------------------------------------------------------------------
   �`�揈��������֐�
------------------------------------------------------------------------------*/
void DrawGame(void)
{
	// �v���C���[���_
	D3DXVECTOR3 pos = g_Player->RefPos();
	pos.y = 0.0f;			// �J����������h�����߂ɃN���A���Ă���
	GetCamera()->SetCameraAT(pos);
	GetCamera()->SetCamera();

	// �[�x�e�X�g�L��
	SetDepthEnable(true);

	// �n�ʂ̕`�揈��
	g_Sky->Draw();
	g_Field->Draw();

	g_ObjectManager->Draw();
}

