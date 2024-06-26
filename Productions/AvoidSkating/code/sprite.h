//=============================================================================
//
// �X�v���C�g���� [sprite.h]
// Author : �ؓc�C���l
//
//=============================================================================
#ifndef _SPRITE_H_
#define _SPRITE_H_
#pragma once
#include "model.h"
#include "base_object.h"
#include "camera.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NO_VECTOR2 {0.0f,0.0f};
#define FULL_COLOR (255.0f)

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
//*****************************************************************************
// UI
// pos,rot,scl,uv_v,uv_f,color
//*****************************************************************************
struct UI {
	D3DXVECTOR2		m_Pos;		// ���[�U�[�C���^�[�t�F�[�X�̈ʒu
	float			m_Rot;		// ���[�U�[�C���^�[�t�F�[�X�̌���(��])
	D3DXVECTOR2		m_Scl;		// ���[�U�[�C���^�[�t�F�[�X�̑傫��(�X�P�[��)
	D3DXVECTOR2		m_Uv_v;		// ��UV�l
	D3DXVECTOR2		m_Uv_f;		// �Œ�UV�l
	D3DXCOLOR		m_Color;	// ���[�U�[�C���^�[�t�F�[�X�̃J���[
};
//*****************************************************************************
// Object
// pos,rot,scl,uv_v,uv_f,color,material,matrix
//*****************************************************************************
struct Object {
	D3DXVECTOR3		m_Pos;			// �I�u�W�F�N�g�̈ʒu
	D3DXVECTOR3		m_Rot;			// �I�u�W�F�N�g�̈ʒu
	D3DXVECTOR3		m_Scl;			// �I�u�W�F�N�g�̑傫��(�X�P�[��)
	D3DXVECTOR2		m_Uv_v;				// ��UV�l
	D3DXVECTOR2		m_Uv_f;				// �Œ�UV�l
	D3DXCOLOR		m_Color;	// �I�u�W�F�N�g�̃J���[
	MATERIAL		m_Material;							// �}�e���A��
	D3DXMATRIX		m_Mtx;								// �}�g���b�N�X

	Object() {
		m_Material.Diffuse = { 0.0f,0.0f,0.0f,1.0f };
		m_Material.Ambient = { 1.0f,1.0f,1.0f,1.0f };
		m_Material.Emission = { 0.0f,0.0f,0.0f,0.0f };
		m_Material.noTexSampling = 0;
	};
};

//*****************************************************************************
// �v���g�^�C�v�錾
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
// �f�o�b�N�p
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