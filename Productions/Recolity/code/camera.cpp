//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "camera.h"
#include "Game.h"
#include "input.h"
#include "card.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	POS_X_CAM		(0.0f)			// カメラの初期位置(X座標)
#define	POS_Y_CAM		(200.0f)		// カメラの初期位置(Y座標)
#define	POS_Z_CAM		(-400.0f)		// カメラの初期位置(Z座標)

#define	VIEW_ANGLE		(D3DXToRadian(45.0f))							// ビュー平面の視野角
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比	
#define	VIEW_NEAR_Z		(10.0f)											// ビュー平面のNearZ値
#define	VIEW_FAR_Z		(40000.0f)										// ビュー平面のFarZ値

#define	VALUE_MOVE_CAMERA	(20.0f)										// カメラの移動量
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)							// カメラの回転量

#define VALUE_MOUSE_RATE	(5.0f)		//マウスの移動量倍率
#define CAMERA_VEL		(10.0f)			//カメラの移動速度
#define JUMP_VEL		(10.0f)			//カメラのジャンプ速度


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
float CameraMouse(long value, float rate);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static CAMERA			g_Camera;		// カメラデータ
static CAMERA			g_oldCamera;		// カメラデータ
POINT					g_Point;
POINT					g_oldPoint;
DIMOUSESTATE2			g_CurrentMouse;
bool					g_JumpTrigger;
unsigned int			g_FrameCount;
float					g_Jumprot;
float					g_MouseKando = 5.0f;

//=============================================================================
// 初期化処理
//=============================================================================
void InitCamera(void)
{
	
	g_Camera.pos = D3DXVECTOR3(POS_X_CAM, POS_Y_CAM, POS_Z_CAM);
	g_Camera.at = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_Camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_oldCamera = g_Camera;

	// 視点と注視点の距離を計算
	float vx, vz;
	vx = g_Camera.pos.x - g_Camera.at.x;
	vz = g_Camera.pos.z - g_Camera.at.z;
	g_Camera.len = sqrtf(vx * vx + vz * vz);

	g_JumpTrigger = false;
	g_FrameCount = 0;
	g_Jumprot = D3DXToRadian(90);
}


//=============================================================================
// カメラの終了処理
//=============================================================================
void UninitCamera(void)
{

}


//=============================================================================
// カメラの更新処理
//=============================================================================
void UpdateCamera(void)
{
	if (g_MouseKando < 0.1f)
	{
		g_MouseKando = 0.1f;
	}
	if (GetCardflug() == false)
	{
		//マウスの視点移動処理
		g_CurrentMouse.lX = GetMouseX();
		g_CurrentMouse.lY = GetMouseY();
		//横回転
		if (g_CurrentMouse.lX != 0)
		{
			if (g_CurrentMouse.lX > 0)
			{
				g_Camera.rot.y += CameraMouse(g_CurrentMouse.lX, g_MouseKando);
				if (g_Camera.rot.y > D3DX_PI)
				{
					g_Camera.rot.y -= D3DX_PI * 2.0f;
				}
			}
			else
			{
				g_Camera.rot.y -= CameraMouse(g_CurrentMouse.lX, g_MouseKando);
				if (g_Camera.rot.y < -D3DX_PI)
				{
					g_Camera.rot.y += D3DX_PI * 2.0f;
				}
			}
		}
		//縦回転
		if (g_CurrentMouse.lY != 0)
		{
			if (g_CurrentMouse.lY > 0)
			{
				g_Camera.rot.x -= CameraMouse(g_CurrentMouse.lY, g_MouseKando);
				if (g_Camera.rot.x < (-D3DX_PI / 2 + 0.01f))
				{
					g_Camera.rot.x = (-D3DX_PI / 2 + 0.01f);
				}
			}
			else
			{
				g_Camera.rot.x += CameraMouse(g_CurrentMouse.lY, g_MouseKando);
				if (g_Camera.rot.x > (D3DX_PI / 2 - 0.01f))
				{
					g_Camera.rot.x = (D3DX_PI / 2 - 0.01f);
				}
			}

		}



		g_Camera.pos = GetPlayer()->GetPos();
		g_Camera.pos.y = GetPlayer()->GetPos().y - (50.0f * (float)GetPlayer()->Get_Sneak());
		g_Camera.at.x = g_Camera.pos.x + sinf(g_Camera.rot.y) * cosf(g_Camera.rot.x) * g_Camera.len;
		g_Camera.at.z = g_Camera.pos.z + cosf(g_Camera.rot.y) * cosf(g_Camera.rot.x) * g_Camera.len;
		g_Camera.at.y = g_Camera.pos.y + sinf(g_Camera.rot.x) * g_Camera.len;
	}
	

}


//=============================================================================
// カメラの更新
//=============================================================================
void SetCamera(void) 
{
	// ビューマトリックス設定
	D3DXMatrixLookAtLH(&g_Camera.mtxView, &g_Camera.pos, &g_Camera.at, &g_Camera.up);

	SetViewMatrix(&g_Camera.mtxView);
	

	float det;
	D3DXMatrixInverse(&g_Camera.mtxInvView, &det, &g_Camera.mtxView);


	// プロジェクションマトリックス設定
	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection, 1.0f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, VIEW_NEAR_Z, VIEW_FAR_Z);

	SetProjectionMatrix(&g_Camera.mtxProjection);
}


//=============================================================================
// カメラの取得
//=============================================================================
CAMERA *GetCamera(void) 
{
	return &g_Camera;
}

//=============================================================================
// カメラの視点と注視点をセット
//=============================================================================
void SetCameraAT(D3DXVECTOR3 pos)
{
	// カメラの注視点をプレイヤーの座標にしてみる
	g_Camera.at = pos;

	// カメラの視点をカメラのY軸回転に対応させている
	g_Camera.pos.x = g_Camera.at.x - sinf(g_Camera.rot.y) * g_Camera.len;
	g_Camera.pos.z = g_Camera.at.z - cosf(g_Camera.rot.y) * g_Camera.len;
}

//=============================================================================
// マウスを使ったカメラの移動
// value	移動量
// rate		倍率
//=============================================================================
float CameraMouse(long value,float rate)
{
	value = (long)fabs(value);
	rate = (float)fabs(rate);

	if (value > 360)
	{
		value = 360;
	}
	if (rate > 100)
	{
		rate = 100;
	}

	rate /= 100.0f;

	return D3DXToRadian(value) * rate;
}


// カメラと対峙する回転行列を取得
D3DXMATRIX GetInvRotateMat()
{
	D3DXMATRIX Inv;
	D3DXVECTOR3 pos = D3DXVECTOR3(0, 0, 0);
	D3DXMatrixIdentity(&Inv);
	D3DXMatrixLookAtLH(&Inv, &pos, &g_Camera.at, &g_Camera.up);
	D3DXMatrixInverse(&Inv, NULL, &Inv);

	return Inv;
}

float* GetMouseKando() {
	return &g_MouseKando;
}