//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : 切田海畝斗
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	POS_X_CAM		(0.0f)			// カメラの初期位置(X座標)
#define	POS_Y_CAM		(200.0f)		// カメラの初期位置(Y座標)
#define	POS_Z_CAM		(-500.0f)		// カメラの初期位置(Z座標)
#define	VIEW_ANGLE		(D3DXToRadian(45.0f))							// ビュー平面の視野角
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比	
#define	VIEW_NEAR_Z		(10.0f)											// ビュー平面のNearZ値
#define	VIEW_FAR_Z		(20000.0f)										// ビュー平面のFarZ値

#define	VALUE_MOVE_CAMERA	(20.0f)										// カメラの移動量
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)							// カメラの回転量
#define VALUE_MOUSE_RATE	(5.0f)		//マウスの移動量倍率

Camera* g_Camera;

//=============================================================================
// 引数付きコンストラクタ
//=============================================================================
Camera::Camera()
{
	Init();
}

//=============================================================================
// 初期化
//=============================================================================
void Camera::Init(void)
{
	m_Pos = D3DXVECTOR3(POS_X_CAM, POS_Y_CAM, POS_Z_CAM);
	m_At = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 視点と注視点の距離を計算
	float vx, vz;
	vx = m_Pos.x - m_At.x;
	vz = m_Pos.z - m_At.z;
	m_Len = sqrtf(vx * vx + vz * vz);
}

//=============================================================================
// 更新
//=============================================================================
void Camera::Update(void)
{

	if (GetKeyboardPress(DIK_Y))
	{// 視点移動「上」
		m_Pos.y += VALUE_MOVE_CAMERA;
	}

	if (GetKeyboardPress(DIK_N))
	{// 視点移動「下」
		m_Pos.y -= VALUE_MOVE_CAMERA;
	}

	m_At.x = m_Pos.x + cosf(-m_Rot.y + D3DXToRadian(90)) * cosf(m_Rot.x) * m_Len;
	m_At.z = m_Pos.z + sinf(-m_Rot.y + D3DXToRadian(90)) * cosf(m_Rot.x) * m_Len;
	m_At.y = m_Pos.y + sinf(m_Rot.x) * m_Len;

	// カメラを初期に戻す
	if (GetKeyboardPress(DIK_P))
	{
		Init();
	}
}

//=============================================================================
// カメラのセット
//=============================================================================
void Camera::SetCamera(void)
{
	// ビューマトリックス設定
	D3DXMatrixLookAtLH(&m_MtxView, &m_Pos, &m_At, &m_Up);

	SetViewMatrix(&m_MtxView);

	float det;
	D3DXMatrixInverse(&m_MtxInvView, &det, &m_MtxView);


	// プロジェクションマトリックス設定
	D3DXMatrixPerspectiveFovLH(&m_MtxProjection, 1.0f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, VIEW_NEAR_Z, VIEW_FAR_Z);

	SetProjectionMatrix(&m_MtxProjection);
}

//=============================================================================
// カメラ注視点のセット
//=============================================================================
void Camera::SetCameraAT(D3DXVECTOR3 pos)
{
	// カメラの注視点をプレイヤーの座標にしてみる
	m_At = pos;

	// カメラの視点をカメラのY軸回転に対応させている
	m_Pos.x = m_At.x - sinf(m_Rot.y) * m_Len;
	m_Pos.z = m_At.z - cosf(m_Rot.y) * m_Len;
}

//=============================================================================
// マウスの移動量
//=============================================================================
float Camera::MouseValue(long value, float rate)
{
	value = fabs(value);
	rate = fabs(rate);

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

//=============================================================================
// リファレンス
//=============================================================================
D3DXVECTOR3& Camera::RefPos(void)
{
	return m_Pos;
}
D3DXVECTOR3& Camera::RefAt(void)
{
	return m_At;
}
D3DXVECTOR3& Camera::RefUp(void)
{
	return m_Up;
}
D3DXVECTOR3& Camera::RefRot(void)
{
	return m_Rot;
}
float& Camera::RefLen(void)
{
	return m_Len;
}
D3DXMATRIX& Camera::RefMtxView(void)
{
	return m_MtxView;
}
D3DXMATRIX& Camera::RefMtxInvView(void)
{
	return m_MtxInvView;
}

void InitCamera(void)
{
	g_Camera = new Camera;
}

void UninitCamera(void)
{
	delete g_Camera;
}

Camera* GetCamera(void)
{
	return g_Camera;
}

