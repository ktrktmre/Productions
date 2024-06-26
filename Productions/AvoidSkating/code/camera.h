//=============================================================================
//
// �J�������� [camera.h]
// Author : �ؓc�C���l
//
//=============================================================================
#pragma once


//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <d3dx9.h>
#include "renderer.h"


//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class Camera {
private:
	D3DXVECTOR3			m_Pos;				// �J�����̎��_(�ʒu)
	D3DXVECTOR3			m_At;				// �J�����̒����_
	D3DXVECTOR3			m_Up;				// �J�����̏�����x�N�g��
	D3DXVECTOR3			m_Rot;				// �J�����̉�]
	float				m_Len;				// �J�����̎��_�ƒ����_�̋���
	D3DXMATRIX			m_MtxView;			// �r���[�}�g���b�N�X
	D3DXMATRIX			m_MtxInvView;		// �r���[�}�g���b�N�X
	D3DXMATRIX			m_MtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	DIMOUSESTATE2		m_Mouse;
public:
	Camera();
	~Camera() = default;
	void Init(void);
	void Update(void);
	void SetCamera(void);
	void SetCameraAT(D3DXVECTOR3 pos);
	float MouseValue(long value, float rate);

	//���t�@�����X
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