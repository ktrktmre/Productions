//=============================================================================
//
// カメラ処理 [camera.h]
// Author : 切田海畝斗
//
//=============================================================================
#pragma once


//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <d3dx9.h>
#include "renderer.h"


//*****************************************************************************
// クラス宣言
//*****************************************************************************
class Camera {
private:
	D3DXVECTOR3			m_Pos;				// カメラの視点(位置)
	D3DXVECTOR3			m_At;				// カメラの注視点
	D3DXVECTOR3			m_Up;				// カメラの上方向ベクトル
	D3DXVECTOR3			m_Rot;				// カメラの回転
	float				m_Len;				// カメラの視点と注視点の距離
	D3DXMATRIX			m_MtxView;			// ビューマトリックス
	D3DXMATRIX			m_MtxInvView;		// ビューマトリックス
	D3DXMATRIX			m_MtxProjection;	// プロジェクションマトリックス
	DIMOUSESTATE2		m_Mouse;
public:
	Camera();
	~Camera() = default;
	void Init(void);
	void Update(void);
	void SetCamera(void);
	void SetCameraAT(D3DXVECTOR3 pos);
	float MouseValue(long value, float rate);

	//リファレンス
	D3DXVECTOR3& RefPos(void);
	D3DXVECTOR3& RefAt(void);
	D3DXVECTOR3& RefUp(void);
	D3DXVECTOR3& RefRot(void);
	float& RefLen(void);
	D3DXMATRIX& RefMtxView(void);
	D3DXMATRIX& RefMtxInvView(void);
};

void InitCamera(void);
void UninitCamera(void);
Camera* GetCamera(void);