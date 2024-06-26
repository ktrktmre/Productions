//=============================================================================
//
// スプライト処理 [sprite.h]
// Author : 切田海畝斗
//
//=============================================================================
#ifndef _SPRITE_H_
#define _SPRITE_H_
#pragma once
#include "model.h"
#include "base_object.h"
#include "camera.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NO_VECTOR2 {0.0f,0.0f};
#define FULL_COLOR (255.0f)

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
//*****************************************************************************
// UI
// pos,rot,scl,uv_v,uv_f,color
//*****************************************************************************
struct UI {
	D3DXVECTOR2		m_Pos;		// ユーザーインターフェースの位置
	float			m_Rot;		// ユーザーインターフェースの向き(回転)
	D3DXVECTOR2		m_Scl;		// ユーザーインターフェースの大きさ(スケール)
	D3DXVECTOR2		m_Uv_v;		// 可変UV値
	D3DXVECTOR2		m_Uv_f;		// 固定UV値
	D3DXCOLOR		m_Color;	// ユーザーインターフェースのカラー
};
//*****************************************************************************
// Object
// pos,rot,scl,uv_v,uv_f,color,material,matrix
//*****************************************************************************
struct Object {
	D3DXVECTOR3		m_Pos;			// オブジェクトの位置
	D3DXVECTOR3		m_Rot;			// オブジェクトの位置
	D3DXVECTOR3		m_Scl;			// オブジェクトの大きさ(スケール)
	D3DXVECTOR2		m_Uv_v;				// 可変UV値
	D3DXVECTOR2		m_Uv_f;				// 固定UV値
	D3DXCOLOR		m_Color;	// オブジェクトのカラー
	MATERIAL		m_Material;							// マテリアル
	D3DXMATRIX		m_Mtx;								// マトリックス

	Object() {
		m_Material.Diffuse = { 0.0f,0.0f,0.0f,1.0f };
		m_Material.Ambient = { 1.0f,1.0f,1.0f,1.0f };
		m_Material.Emission = { 0.0f,0.0f,0.0f,0.0f };
		m_Material.noTexSampling = 0;
	};
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSprite(void);
void UninitSprite(void);
void RegisterCamera(Camera* pCmamera);
void ReleaseCamera(void);
void DrawScreen(UI ui, int& tex);
void DrawScreenLT(UI ui, int& tex);
void DrawPolygon(Base_Object& obj, const int& tex, const D3DXVECTOR2 uv_v, const D3DXVECTOR2 uv_f);
void DrawPolygonCR(Base_Object& obj, const int& tex, const D3DXVECTOR2 uv_v, const D3DXVECTOR2 uv_f);
void DrawPolygonLT(Base_Object& obj, const int& tex, const D3DXVECTOR2 uv_v, const D3DXVECTOR2 uv_f);
void DrawPolygonZ(Base_Object& obj, const int& tex, const D3DXVECTOR2 uv_v, const D3DXVECTOR2 uv_f);
void DrawPolygonZCR(Base_Object& obj, const int& tex, const D3DXVECTOR2 uv_v, const D3DXVECTOR2 uv_f);
void DrawPolygonZLT(Base_Object& obj, const int& tex, const D3DXVECTOR2 uv_v, const D3DXVECTOR2 uv_f);
void DrawPolygonBill(Base_Object& obj, const int& tex, const D3DXVECTOR2 uv_v, const D3DXVECTOR2 uv_f);
void DrawPolygonBillCR(Base_Object& obj, const int& tex, const D3DXVECTOR2 uv_v, const D3DXVECTOR2 uv_f);
void DrawPolygonBillLT(Base_Object& obj, const int& tex, const D3DXVECTOR2 uv_v, const D3DXVECTOR2 uv_f);
void DrawPolygonAnyBill(Base_Object& obj,const int& tex, const D3DXVECTOR2 uv_v, const D3DXVECTOR2 uv_f, bool InX, bool InY, bool InZ);
void DrawPolygonAnyBillCR(Base_Object& obj,const int& tex, const D3DXVECTOR2 uv_v, const D3DXVECTOR2 uv_f, bool InX, bool InY, bool InZ);
void DrawPolygonAnyBillLT(Base_Object& obj,const int& tex, const D3DXVECTOR2 uv_v, const D3DXVECTOR2 uv_f, bool InX, bool InY, bool InZ);
void Draw3DModel(Base_Object& obj, DX11_MODEL& model);

//---------------------------------
// デバック用
//---------------------------------
void DrawPolygon(Object obj, const int& tex);
void DrawPolygonCR(Object obj, const int& tex);
void DrawPolygonLT(Object obj, const int& tex);
void DrawPolygonBill(Object obj, const int& tex);
void DrawPolygonBillCR(Object obj, const int& tex);
void DrawPolygonBillLT(Object obj, const int& tex);
void DrawPolygonAnyBill(Object obj, const int& tex, bool InX, bool InY, bool InZ);
void DrawPolygonAnyBillCR(Object obj, const int& tex, bool InX, bool InY, bool InZ);
void DrawPolygonAnyBillLT(Object obj, const int& tex, bool InX, bool InY, bool InZ);
void Draw3DModel(Object obj, DX11_MODEL& model);


#endif // !_SPRITE_H_