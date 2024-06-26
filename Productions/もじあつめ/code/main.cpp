/*==============================================================================

   テクスチャの描画 [main.cpp]
                                                         Author :切田 海畝斗 
                                                         Date   :2023/06/16 
--------------------------------------------------------------------------------

==============================================================================*/
#include <time.h>
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "game.h"
#include "title.h"
#include "result.h"
#include "wait.h"
#include "option.h"
#include "explanation.h"
#include "fade.h"
#include "image.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME			"GameWindow"				// ウインドウのクラス名
#define WINDOW_CAPTION		"ポリゴンの描画"			// ウインドウのキャプション名

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);


//*****************************************************************************
// グローバル変数:
//*****************************************************************************
SCENE g_scene;
#ifdef _DEBUG
int		g_CountFPS;							// FPSカウンタ
char	g_DebugStr[2048] = WINDOW_CAPTION;	// デバッグ文字表示用

#endif

//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）

	//ランダムシードの初期化
	srand((unsigned int)time(NULL));

	// 時間計測用
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	
	WNDCLASSEX	wcex = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW+1),
		NULL,
		CLASS_NAME,
		NULL
	};
	HWND		hWnd;
	MSG			msg;
	
	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	int window_width = 960;
	int window_height = 540;

	// ウィンドウの作成
	hWnd = CreateWindow(CLASS_NAME,
		WINDOW_CAPTION,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,																		// ウィンドウの左座標
		CW_USEDEFAULT,																		// ウィンドウの上座標
		window_width + GetSystemMetrics(SM_CXDLGFRAME) * 2,									// ウィンドウ横幅
		window_height + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),	// ウィンドウ縦幅
		NULL,
		NULL,
		hInstance,
		NULL);

	// DirectXの初期化(ウィンドウを作成してから行う)
	if(FAILED(Init(hInstance, hWnd, true)))
	{
		return -1;
	}

	// フレームカウント初期化
	timeBeginPeriod(1);	// 分解能を設定
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// システム時刻をミリ秒単位で取得
	dwCurrentTime = dwFrameCount = 0;
	
	// ウインドウの表示(Init()の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// メッセージループ
	while(1)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();					// システム時刻を取得

			if ((dwCurrentTime - dwFPSLastTime) >= 1000)	// 1秒ごとに実行
			{
#ifdef _DEBUG
				g_CountFPS = dwFrameCount;
#endif
				dwFPSLastTime = dwCurrentTime;				// FPSを測定した時刻を保存
				dwFrameCount = 0;							// カウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= ((float)1000 / 60))	// 1/60秒ごとに実行
			{
				dwExecLastTime = dwCurrentTime;	// 処理した時刻を保存

#ifdef _DEBUG	// デバッグ版の時だけFPSを表示する
				wsprintf(g_DebugStr, WINDOW_CAPTION);
				wsprintf(&g_DebugStr[strlen(g_DebugStr)], " FPS:%d", g_CountFPS);
				SetWindowText(hWnd, g_DebugStr);
#endif

				Update();			// 更新処理
				Draw();				// 描画処理

				dwFrameCount++;		// 処理回数のカウントを加算
			}
		}
	}
	
	timeEndPeriod(1);				// 分解能を戻す

	// 終了処理
	Uninit();

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch( message )
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:					// [ESC]キーが押された
			DestroyWindow(hWnd);		// ウィンドウを破棄するよう指示する
			break;
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// レンダリング処理の初期化
	InitRenderer(hInstance, hWnd, bWindow);

	// 入力処理の初期化
	InitInput(hInstance, hWnd);

	//サウンド処理の初期化
	InitSound(hWnd);

	// スプライトの初期化
	InitSprite();

	// イメージの初期化
	InitImage();

	//フェードの初期化
	InitFade();

	//カーソル非表示
	ShowCursor(false);

	//レコードの初期化
	LoadRecord();

	//ボリュームの初期化
	SetVolumeBGM(VOLUME_MAX);
	SetVolumeSE(VOLUME_MAX);

	//ランダムシードの設定
	srand((unsigned int)time(NULL));

	//シーンの初期化
	g_scene = SCENE_TITLE;
	switch (g_scene)
	{
	case SCENE_TITLE:
		InitTitle();
		break;	
	case SCENE_OPTION:
		InitOption();
		break;
	case SCENE_EXPLANATION:
		InitExplanation();
		break;
	case SCENE_WAIT:
		InitWait();
		break;
	case SCENE_GAME:
		InitGame();
		break;
	case SCENE_RESULT:
		InitResult();
		break;
	default:
		break;
	}

	return S_OK;
}


//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	//フェードの終了
	UninitFade();

	//シーンの終了
	switch (g_scene)
	{
	case SCENE_TITLE:
		UninitTitle();
		break;
	case SCENE_OPTION:
		UninitOption();
		break;
	case SCENE_EXPLANATION:
		UninitExplanation();
		break;
	case SCENE_WAIT:
		UninitWait();
		break;
	case SCENE_GAME:
		UninitGame();
		break;
	case SCENE_RESULT:
		UninitResult();
		break;
	default:
		break;
	}

	//カーソル表示
	ShowCursor(true);

	// スプライトの終了処理
	UninitSprite();

	//サウンド処理の終了処理
	UninitSound();

	// テクスチャの全解放
	UninitTexture();

	// 入力処理の終了処理
	UninitInput();

	// レンダリングの終了処理
	UninitRenderer();
}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	// 入力処理の更新処理
	UpdateInput();

	//フェードの更新
	UpdateFade();

	//シーンの更新
	switch (g_scene)
	{
	case SCENE_TITLE:
		UpdateTitle();
		break;
	case SCENE_OPTION:
		UpdateOption();
		break;
	case SCENE_EXPLANATION:
		UpdateExplanation();
		break;
	case SCENE_WAIT:
		UpdateWait();
		break;
	case SCENE_GAME:
		UpdateGame();
		break;
	case SCENE_RESULT:
		UpdateResult();
		break;
	default:
		break;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// バックバッファクリア
	Clear();

	// マトリクス設定
	SetWorldViewProjection2D();//座標の2D変換

	// 2D描画なので深度無効
	SetDepthEnable(false);

	//シーンの描画
	switch (g_scene)
	{
	case SCENE_TITLE:
		DrawTitle();
		break;
	case SCENE_OPTION:
		DrawOption();
		break;
	case SCENE_EXPLANATION:
		DrawExplanation();
		break;
	case SCENE_WAIT:
		DrawWait();
		break;
	case SCENE_GAME:
		DrawGame();
		break;
	case SCENE_RESULT:
		DrawResult();
		break;
	default:
		break;
	}

	//フェードの描画
	DrawFade();

	// バックバッファ、フロントバッファ入れ替え
	Present();
}

//=============================================================================
// ランダム:0or1
//=============================================================================
float frand(void)
{
	return (float)rand() / RAND_MAX;
}

//=============================================================================
// シーンの切り替え
//=============================================================================
void SetScene(SCENE scene)
{
	//シーンの終了
	switch (g_scene)
	{
	case SCENE_TITLE:
		UninitTitle();
		break;
	case SCENE_OPTION:
		UninitOption();
		break;
	case SCENE_EXPLANATION:
		UninitExplanation();
		break;
	case SCENE_WAIT:
		UninitWait();
		break;
	case SCENE_GAME:
		UninitGame();
		break;
	case SCENE_RESULT:
		UninitResult();
		break;
	default:
		break;
	}

	//シーン切り替え
	g_scene = scene;

	//レコードの再読み込み
	LoadRecord();

	//シーンの初期化
	switch (g_scene)
	{
	case SCENE_TITLE:
		InitTitle();
		break;
	case SCENE_OPTION:
		InitOption();
		break;
	case SCENE_EXPLANATION:
		InitExplanation();
		break;
	case SCENE_WAIT:
		InitWait();
		break;
	case SCENE_GAME:
		InitGame();
		break;
	case SCENE_RESULT:
		InitResult();
		break;
	default:
		break;
	}
}

//=============================================================================
// シーンゲット関数
//=============================================================================
SCENE* GetScene(void)
{
	return  &g_scene;
}