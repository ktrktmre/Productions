/*==============================================================================

   テクスチャの描画 [main.h]
                                                         Author :切田 海畝斗 
                                                         Date   :2023/06/16 
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once
#ifndef _MAIN_H_
#define _MAIN_H_

#pragma warning(push)
#pragma warning(disable:4005)

#define _CRT_SECURE_NO_WARNINGS			// scanf のwarning防止
#include <stdio.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800		// 警告対処
#include "dinput.h"
#include "mmsystem.h"

#pragma warning(pop)


//*****************************************************************************
// ライブラリのリンク
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
// マクロ定義
//*****************************************************************************
#define SCREEN_WIDTH	(1920)				// ウインドウの幅
#define SCREEN_HEIGHT	(1080)				// ウインドウの高さ
#define SCREEN_H_WIDTH	(SCREEN_WIDTH/2)	// ウインドウ半分の幅
#define SCREEN_H_HEIGHT	(SCREEN_HEIGHT/2)	// ウインドウ半分の高さ
#define SCREEN_Q_WIDTH	(SCREEN_WIDTH/4)	// ウインドウ1/4の幅
#define SCREEN_Q_HEIGHT	(SCREEN_HEIGHT/4)	// ウインドウ1/4の高さ
#define FPS	(60)							// フレーム毎秒

//*****************************************************************************
// 列挙体宣言
//*****************************************************************************
enum SCENE { //シーン管理用列挙体
    SCENE_TITLE = 0,
    SCENE_OPTION,
    SCENE_EXPLANATION,
    SCENE_WAIT,
    SCENE_GAME,
    SCENE_RESULT,
    SCENE_MAX,
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
float frand(void);
void SetScene(SCENE scene);
SCENE* GetScene(void);

#endif // !_MAIN_H_