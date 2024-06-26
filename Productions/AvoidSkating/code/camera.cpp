//=============================================================================
//
// �J�������� [camera.cpp]
// Author : �ؓc�C���l
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	POS_X_CAM		(0.0f)			// �J�����̏����ʒu(X���W)
#define	POS_Y_CAM		(200.0f)		// �J�����̏����ʒu(Y���W)
#define	POS_Z_CAM		(-500.0f)		// �J�����̏����ʒu(Z���W)
#define	VIEW_ANGLE		(D3DXToRadian(45.0f))							// �r���[���ʂ̎���p
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��	
#define	VIEW_NEAR_Z		(10.0f)											// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z		(20000.0f)										// �r���[���ʂ�FarZ�l

#define	VALUE_MOVE_CAMERA	(20.0f)										// �J�����̈ړ���
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)							// �J�����̉�]��
#define VALUE_MOUSE_RATE	(5.0f)		//�}�E�X�̈ړ��ʔ{��

Camera* g_Camera;

//=============================================================================
// �����t���R���X�g���N�^
//=============================================================================
Camera::Camera()
{
	Init();
}

//=============================================================================
// ������
//=============================================================================
void Camera::Init(void)
{
	m_Pos = D3DXVECTOR3(POS_X_CAM, POS_Y_CAM, POS_Z_CAM);
	m_At = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���_�ƒ����_�̋������v�Z
	float vx, vz;
	vx = m_Pos.x - m_At.x;
	vz = m_Pos.z - m_At.z;
	m_Len = sqrtf(vx * vx + vz * vz);
}

//=============================================================================
// �X�V
//=============================================================================
void Camera::Update(void)
{

	if (GetKeyboardPress(DIK_Y))
	{// ���_�ړ��u��v
		m_Pos.y += VALUE_MOVE_CAMERA;
	}

	if (GetKeyboardPress(DIK_N))
	{// ���_�ړ��u���v
		m_Pos.y -= VALUE_MOVE_CAMERA;
	}

	m_At.x = m_Pos.x + cosf(-m_Rot.y + D3DXToRadian(90)) * cosf(m_Rot.x) * m_Len;
	m_At.z = m_Pos.z + sinf(-m_Rot.y + D3DXToRadian(90)) * cosf(m_Rot.x) * m_Len;
	m_At.y = m_Pos.y + sinf(m_Rot.x) * m_Len;

	// �J�����������ɖ߂�
	if (GetKeyboardPress(DIK_P))
	{
		Init();
	}
}

//=============================================================================
// �J�����̃Z�b�g
//=============================================================================
void Camera::SetCamera(void)
{
	// �r���[�}�g���b�N�X�ݒ�
	D3DXMatrixLookAtLH(&m_MtxView, &m_Pos, &m_At, &m_Up);

	SetViewMatrix(&m_MtxView);

	float det;
	D3DXMatrixInverse(&m_MtxInvView, &det, &m_MtxView);


	// �v���W�F�N�V�����}�g���b�N�X�ݒ�
	D3DXMatrixPerspectiveFovLH(&m_MtxProjection, 1.0f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, VIEW_NEAR_Z, VIEW_FAR_Z);

	SetProjectionMatrix(&m_MtxProjection);
}

//=============================================================================
// �J���������_�̃Z�b�g
//=============================================================================
void Camera::SetCameraAT(D3DXVECTOR3 pos)
{
	// �J�����̒����_���v���C���[�̍��W�ɂ��Ă݂�
	m_At = pos;

	// �J�����̎��_���J������Y����]�ɑΉ������Ă���
	m_Pos.x = m_At.x - sinf(m_Rot.y) * m_Len;
	m_Pos.z = m_At.z - cosf(m_Rot.y) * m_Len;
}

//=============================================================================
// �}�E�X�̈ړ���
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
// ���t�@�����X
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

