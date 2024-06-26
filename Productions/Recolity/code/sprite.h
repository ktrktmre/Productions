//=============================================================================
//
// スプライト処理 [sprite.h]
// Author : 
//
//=============================================================================
#ifndef _SPRITE_H_
#define _SPRITE_H_
#pragma once
#include "model.h"
#include "base_object.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define UI_PRSET_UV1 D3DXVECTOR2(0.0f,0.0f),D3DXVECTOR2(1.0f,1.0f)


//*****************************************************************************
// 構造体宣言
//*****************************************************************************
struct UI {	//ユーザーインターフェース用構造体
	D3DXVECTOR2		m_Pos;		// ユーザーインターフェースの位置
	D3DXVECTOR2		m_Scl;		// ユーザーインターフェースの大きさ(スケール)
	D3DXVECTOR2		m_Uv_v;		// 可変UV値
	D3DXVECTOR2		m_Uv_f;		// 固定UV値
	D3DXCOLOR		m_Color;	// ユーザーインターフェースのカラー
	float			m_Rot;		// ユーザーインターフェースの向き(回転)
};

struct Object {	//簡易オブジェクト用構造体
	D3DXVECTOR3		m_Pos = {0.0f,0.0f,0.0f};			// オブジェクトの位置
	D3DXVECTOR3		m_Rot = { 0.0f,0.0f,0.0f };			// オブジェクトの位置
	D3DXVECTOR3		m_Scl = { 0.0f,0.0f,0.0f };			// オブジェクトの大きさ(スケール)
	D3DXVECTOR2		m_Uv_v = { 0.0f,0.0f};				// 可変UV値
	D3DXVECTOR2		m_Uv_f = { 1.0f,1.0f};				// 固定UV値
	D3DXCOLOR		m_Color = { 1.0f,1.0f,1.0f,1.0f };	// オブジェクトのカラー
	MATERIAL		m_Material;	
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
void DrawNomber(D3DXVECTOR3 pos, float size, int Drawtext);
void DrawScreenCircle(D3DXVECTOR2 pos, D3DXVECTOR2 tex_pos, float radius, float rate, D3DXCOLOR color, int& tex);
void DrawScreen(UI& ui, int& tex);
void DrawScreenLT(UI& ui, int& tex);
void DrawPolygon(Base_Object& obj, const int& tex, const D3DXVECTOR2& uv_v, const D3DXVECTOR2& uv_f);
void DrawPolygonCR(Base_Object& obj, const int& tex, const D3DXVECTOR2& uv_v, const D3DXVECTOR2& uv_f);
void DrawPolygonLT(Base_Object& obj, const int& tex, const D3DXVECTOR2& uv_v, const D3DXVECTOR2& uv_f);
void DrawPolygonBill(Base_Object& obj, const int& tex, const D3DXVECTOR2& uv_v, const D3DXVECTOR2& uv_f);
void DrawPolygonBillX(Base_Object& obj, const int& tex, const D3DXVECTOR2& uv_v, const D3DXVECTOR2& uv_f ,float WID_X);
void DrawPolygonBillCR(Base_Object& obj, const int& tex, const D3DXVECTOR2& uv_v, const D3DXVECTOR2& uv_f);
void DrawPolygonBillLT(Base_Object& obj, const int& tex, const D3DXVECTOR2& uv_v, const D3DXVECTOR2& uv_f);
void DrawPolygonAnyBill(Base_Object& obj,const int& tex, const D3DXVECTOR2& uv_v, const D3DXVECTOR2& uv_f, bool InX, bool InY, bool InZ);
void DrawPolygonAnyBillCR(Base_Object& obj,const int& tex, const D3DXVECTOR2& uv_v, const D3DXVECTOR2& uv_f, bool InX, bool InY, bool InZ);
void DrawPolygonAnyBillLT(Base_Object& obj,const int& tex, const D3DXVECTOR2& uv_v, const D3DXVECTOR2& uv_f, bool InX, bool InY, bool InZ);
void Draw3DModel(Base_Object& obj, DX11_MODEL& model);

//---------------------------------
// デバック用
//---------------------------------
void DrawPolygon(Object& obj, const int& tex);
void DrawPolygonCR(Object& obj, const int& tex);
void DrawPolygonLT(Object& obj, const int& tex);
void DrawPolygonBill(Object& obj, const int& tex);
void DrawPolygonBillX(Object& obj, const int& tex,float WID_X);
void DrawPolygonBillXY(Object& obj, const int& tex, float WID_X, float WID_Y);
void DrawPolygonBillCR(Object& obj, const int& tex);
void DrawPolygonBillLT(Object& obj, const int& tex);
void DrawPolygonAnyBill(Object& obj, const int& tex, bool InX, bool InY, bool InZ);
void DrawPolygonAnyBillCR(Object& obj, const int& tex, bool InX, bool InY, bool InZ);
void DrawPolygonAnyBillLT(Object& obj, const int& tex, bool InX, bool InY, bool InZ);
void Draw3DModel(Object& obj, DX11_MODEL& model);


#endif // !_SPRITE_H_