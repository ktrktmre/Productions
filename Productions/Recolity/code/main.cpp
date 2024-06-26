//=============================================================================
//
// メイン処理 [main.cpp]
// Author : 
//
//=============================================================================
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "main.h"
#include "material.h"
#include "renderer.h"
#include "texture.h"
#include "input.h"
#include "sound.h"
#include "scene.h"
#include "fade.h"
#include "sprite.h"
#include "text.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME		"AppClass"				// ウインドウのクラス名
#define WINDOW_NAME		"Recolity"		// ウインドウのキャプション名
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
long g_MouseX = 0;
long g_MouseY = 0;
MSG g_msg;
HWND hWnd;
int obi = 0;
int cd = 0;
POINT p;
RECT rect;
D3DXVECTOR2 mosepos;
float g_Dpi;
bool corsorlock = false;
#ifdef _DEBUG
int		g_CountFPS;							// FPSカウンタ
char	g_DebugStr[2048] = WINDOW_NAME;		// デバッグ文字表示用

#endif


//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//メモリリーク検知
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）

	// 時間計測用
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;


	//ランダムシードの初期化
	srand((unsigned int)time(NULL));

	WNDCLASSEX	wcex = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	
	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	int window_width = 960;
	int window_height = 540;

	// ウィンドウの作成
	hWnd = CreateWindow(CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,																		// ウィンドウの左座標
		CW_USEDEFAULT,																		// ウィンドウの上座標
		window_width + GetSystemMetrics(SM_CXDLGFRAME) * 2,									// ウィンドウ横幅
		window_height + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),	// ウィンドウ縦幅
		NULL,
		NULL,
		hInstance,
		NULL);

	// 初期化処理(ウィンドウを作成してから行う)
	if(FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}
	g_Dpi = (float)GetDpiForWindow(hWnd);

	// フレームカウント初期化
	timeBeginPeriod(1);	// 分解能を設定
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// システム時刻をミリ秒単位で取得
	dwCurrentTime = dwFrameCount = 0;

	// ウインドウの表示(初期化処理の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	RECT wndrect;
	int cursornum = 0;
	// メッセージループ
	while(1)
	{
		obi = GetSystemMetrics(SM_CYCAPTION);
		GetWindowRect(hWnd, &wndrect);
		if (corsorlock)
		{
			SetCursorPos((int)((wndrect.right - wndrect.left) * 0.5) + wndrect.left, (int)((wndrect.bottom - wndrect.top) * 0.5) + wndrect.top);
			if (cursornum >= 0)
			{
				cursornum = ShowCursor(false);
			}
			
		}
		else
		{
			if (cursornum < 0)
			{
				cursornum = ShowCursor(true);
			}
			
		}

        if(PeekMessage(&g_msg, NULL, 0, 0, PM_REMOVE))
		{
			if(g_msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳と送出
				TranslateMessage(&g_msg);
				DispatchMessage(&g_msg);
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 1000)	// 1秒ごとに実行
			{
#ifdef _DEBUG
				g_CountFPS = dwFrameCount;
#endif
				dwFPSLastTime = dwCurrentTime;				// FPSを測定した時刻を保存
				dwFrameCount = 0;							// カウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))	// 1/60秒ごとに実行
			{
				dwExecLastTime = dwCurrentTime;	// 処理した時刻を保存

#ifdef _DEBUG	// デバッグ版の時だけFPSを表示する
				wsprintf(g_DebugStr, WINDOW_NAME);
				wsprintf(&g_DebugStr[strlen(g_DebugStr)], " FPS:%d", g_CountFPS);
#endif
				GetWindowRect(hWnd, &rect);
				GetCursorPos(&p);
				Update();			// 更新処理
				Draw();				// 描画処理
				cd > 0 ? cd-- : cd = 0;

				CheckScene();
				


#ifdef _DEBUG	// デバッグ版の時だけ表示する
				wsprintf(&g_DebugStr[strlen(g_DebugStr)], "windowRECT top%dbottom%dleft%dright%d", wndrect.top, wndrect.bottom, wndrect.left, wndrect.right);
				SetWindowText(hWnd, g_DebugStr);
#endif

				dwFrameCount++;
			}
		}
	}

	timeEndPeriod(1);				// 分解能を戻す

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// 終了処理
	Uninit();
	return (int)g_msg.wParam;
}

//=============================================================================
// プロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_F5:
			DestroyWindow(hWnd);
			break;
		}
		break;

	case WM_MOUSEMOVE:
		g_MouseX = LOWORD(lParam);
		g_MouseY = HIWORD(lParam);
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
	InitRenderer(hInstance, hWnd, bWindow);
	InitInput(hInstance, hWnd);
	InitSound(hWnd);
	LoadMaterial();
	InitSprite();
	InitFade();
	SetSamplerState(FILTER_MODE_POINT, ADDRESS_MODE_WRAP);
	SetCullingMode(CULL_MODE_BACK);
	SetFadeColor(0.0f, 0.0f, 0.0f);
	SceneFadeIn(SCENE_TITLE);
	ShowCursor(false);
	InitText();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	UninitText();
	UninitScene();
	ShowCursor(true);
	UninitFade();
	UninitTexture();
	UninitSprite();
	UninitSound();
	ReleaseMaterial();
	UninitInput();
	UninitRenderer();
}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	// 入力の更新処理
	UpdateInput();
	
	UpdateScene();

}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// バックバッファクリア
	Clear();

	// シーンの描画処理
	DrawScene();

	// バックバッファ、フロントバッファ入れ替え
	Present();
}


long GetMousePosX(void)
{
	return g_MouseX;
}


long GetMousePosY(void)
{
	return g_MouseY;
}


#ifdef _DEBUG
char* GetDebugStr(void)
{
	return g_DebugStr;
}
MSG* GetMsg() {
	return &g_msg;
}
#endif
float frand(void)
{

	return (float)rand() / RAND_MAX;
}
void CursprLock(bool swith) {
	corsorlock = swith;
}
D3DXVECTOR2 GetMousePos() {

	mosepos.x = (float)p.x * SCREEN_WIDTH / (rect.right - rect.left) - rect.left * 2;
	mosepos.y = (float)p.y * SCREEN_HEIGHT / (rect.bottom ) - rect.top * 2;

	return mosepos;
}

bool WndYesorNo(std::string text) {
	if (cd == 0)
	{
		cd = 2;
		return MessageBox(hWnd, (LPCTSTR)text.c_str(), "確認", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK;
	}
	return false;
}
float GeyDPI() {
	return (float)GetDpiForWindow(hWnd);
}