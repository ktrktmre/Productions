/*==============================================================================

   �e�N�X�`���̕`�� [main.h]
                                                         Author :�ؓc �C���l 
                                                         Date   :2023/06/16 
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once
#ifndef _MAIN_H_
#define _MAIN_H_

#pragma warning(push)
#pragma warning(disable:4005)

#define _CRT_SECURE_NO_WARNINGS			// scanf ��warning�h�~
#include <stdio.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800		// �x���Ώ�
#include "dinput.h"
#include "mmsystem.h"

#pragma warning(pop)


//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************
#pragma comment (lib, "d3d11.lib")		
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "d3dx11.lib")	
#pragma comment (lib, "d3dx9.lib")	
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dxerr.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH	(1920)				// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(1080)				// �E�C���h�E�̍���
#define SCREEN_H_WIDTH	(SCREEN_WIDTH/2)	// �E�C���h�E�����̕�
#define SCREEN_H_HEIGHT	(SCREEN_HEIGHT/2)	// �E�C���h�E�����̍���
#define SCREEN_Q_WIDTH	(SCREEN_WIDTH/4)	// �E�C���h�E1/4�̕�
#define SCREEN_Q_HEIGHT	(SCREEN_HEIGHT/4)	// �E�C���h�E1/4�̍���
#define FPS	(60)							// �t���[�����b

//*****************************************************************************
// �񋓑̐錾
//*****************************************************************************
enum SCENE { //�V�[���Ǘ��p�񋓑�
    SCENE_TITLE = 0,
    SCENE_OPTION,
    SCENE_EXPLANATION,
    SCENE_WAIT,
    SCENE_GAME,
    SCENE_RESULT,
    SCENE_MAX,
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
float frand(void);
void SetScene(SCENE scene);
SCENE* GetScene(void);

#endif // !_MAIN_H_