//=============================================================================
//
// �X�v���C�g���� [sprite.cpp]
// Author : �ؓc�C���l
//
//=============================================================================
#include "main.h"
#include "base_object.h"
#include "sprite.h"
#include "renderer.h"
#include "Texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	NUM_2DVERTEX		(4)							// ���_��

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer* g_VertexBuffer = NULL;	// ���_���
Camera* g_GameCamera = nullptr;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitSprite(void)
{
	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * NUM_2DVERTEX;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitSprite(void)
{
	// ���_�o�b�t�@�̉��
	if (g_VertexBuffer) {
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
}

//=============================================================================
// �J�����̓o�^
//=============================================================================
void RegisterCamera(Camera* pCmamera)
{
	g_GameCamera = pCmamera;
}

//=============================================================================
// �J�����̉��
//=============================================================================
void ReleaseCamera(void)
{
	g_GameCamera = nullptr;
}


//=============================================================================
// ��ʕ`��(���S�w��)
//=============================================================================
void DrawScreen(UI ui, int& tex)
{

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;


	float hw, hh;
	hw = ui.m_Scl.x * 0.5f;
	hh = ui.m_Scl.y * 0.5f;

	// ���W�ϊ�
	pVtx[0].Position.x = (-hw) * cosf(ui.m_Rot) - (-hh) * sinf(ui.m_Rot) + ui.m_Pos.x;
	pVtx[0].Position.y = (-hw) * sinf(ui.m_Rot) + (-hh) * cosf(ui.m_Rot) + ui.m_Pos.y;
	pVtx[1].Position.x = (hw)*cosf(ui.m_Rot) - (-hh) * sinf(ui.m_Rot) + ui.m_Pos.x;
	pVtx[1].Position.y = (hw)*sinf(ui.m_Rot) + (-hh) * cosf(ui.m_Rot) + ui.m_Pos.y;
	pVtx[2].Position.x = (-hw) * cosf(ui.m_Rot) - (hh)*sinf(ui.m_Rot) + ui.m_Pos.x;
	pVtx[2].Position.y = (-hw) * sinf(ui.m_Rot) + (hh)*cosf(ui.m_Rot) + ui.m_Pos.y;
	pVtx[3].Position.x = (hw)*cosf(ui.m_Rot) - (hh)*sinf(ui.m_Rot) + ui.m_Pos.x;
	pVtx[3].Position.y = (hw)*sinf(ui.m_Rot) + (hh)*cosf(ui.m_Rot) + ui.m_Pos.y;

	for (int i = 0; i < 4; i++)
	{
		pVtx[i].Position.z = 0.0f;
	}

	pVtx[0].Diffuse = ui.m_Color;
	pVtx[1].Diffuse = ui.m_Color;
	pVtx[2].Diffuse = ui.m_Color;
	pVtx[3].Diffuse = ui.m_Color;

	pVtx[0].TexCoord = D3DXVECTOR2(ui.m_Uv_v.x, ui.m_Uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(ui.m_Uv_v.x + ui.m_Uv_f.x, ui.m_Uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(ui.m_Uv_v.x, ui.m_Uv_v.y + ui.m_Uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(ui.m_Uv_v.x + ui.m_Uv_f.x, ui.m_Uv_v.y + ui.m_Uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT	 stride = sizeof(VERTEX_3D);
	UINT	 offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �}�e���A���̃Z�b�g
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = { 1.0f,1.0f,1.0f,1.0f };
	material.noTexSampling = 0;
	SetMaterial(material);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));

	// ���C�g
	SetLightEnable(false);

	// �}�g���N�X�ݒ�
	SetWorldViewProjection2D();//���W��2D�ϊ�

	// 2D�`��Ȃ̂Ő[�x����
	SetDepthEnable(false);

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	// Z��r����
	SetDepthEnable(true);

	// ���C�g
	SetLightEnable(true);

	g_GameCamera->SetCamera();
}

//=============================================================================
// ��ʕ`��(����w��)
//=============================================================================
void DrawScreenLT(UI ui, int& tex)
{

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;


	float hw, hh;
	hw = ui.m_Scl.x;
	hh = ui.m_Scl.y;

	// ���W�ϊ�
	pVtx[0].Position.x = ui.m_Pos.x;
	pVtx[0].Position.y = ui.m_Pos.y;
	pVtx[1].Position.x = (hw)*cosf(ui.m_Rot) + ui.m_Pos.x;
	pVtx[1].Position.y = (hw)*sinf(ui.m_Rot) + ui.m_Pos.y;
	pVtx[2].Position.x = - (hh)*sinf(ui.m_Rot) + ui.m_Pos.x;
	pVtx[2].Position.y = + (hh)*cosf(ui.m_Rot) + ui.m_Pos.y;
	pVtx[3].Position.x = (hw)*cosf(ui.m_Rot) - (hh)*sinf(ui.m_Rot) + ui.m_Pos.x;
	pVtx[3].Position.y = (hw)*sinf(ui.m_Rot) + (hh)*cosf(ui.m_Rot) + ui.m_Pos.y;

	for (int i = 0; i < 4; i++)
	{
		pVtx[i].Position.z = 0.0f;
	}

	pVtx[0].Diffuse = ui.m_Color;
	pVtx[1].Diffuse = ui.m_Color;
	pVtx[2].Diffuse = ui.m_Color;
	pVtx[3].Diffuse = ui.m_Color;

	pVtx[0].TexCoord = D3DXVECTOR2(ui.m_Uv_v.x, ui.m_Uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(ui.m_Uv_v.x + ui.m_Uv_f.x, ui.m_Uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(ui.m_Uv_v.x, ui.m_Uv_v.y + ui.m_Uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(ui.m_Uv_v.x + ui.m_Uv_f.x, ui.m_Uv_v.y + ui.m_Uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT	 stride = sizeof(VERTEX_3D);
	UINT	 offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �}�e���A���̃Z�b�g
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = { 1.0f,1.0f,1.0f,1.0f };
	material.noTexSampling = 0;
	SetMaterial(material);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));

	// ���C�g
	SetLightEnable(false);

	// �}�g���N�X�ݒ�
	SetWorldViewProjection2D();//���W��2D�ϊ�

	// 2D�`��Ȃ̂Ő[�x����
	SetDepthEnable(false);

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	// Z��r����
	SetDepthEnable(true);

	// ���C�g
	SetLightEnable(true);

	g_GameCamera->SetCamera();
}

//=============================================================================
// �|���S���`��(���S���w��)
//=============================================================================
void DrawPolygon(Base_Object& obj,const int& tex, const D3DXVECTOR2 uv_v, const D3DXVECTOR2 uv_f)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(-obj.RefScl().x * 0.5f, obj.RefScl().y, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.RefScl().x * 0.5f, obj.RefScl().y, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(-obj.RefScl().x * 0.5f, 0.0f, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.RefScl().x * 0.5f, 0.0f, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.RefColor();
	pVtx[1].Diffuse = obj.RefColor();
	pVtx[2].Diffuse = obj.RefColor();
	pVtx[3].Diffuse = obj.RefColor();

	pVtx[0].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y + uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y + uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(*obj.GetMaterial());

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(obj.GetMtx());

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.RefRot().y, obj.RefRot().x, obj.RefRot().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(obj.GetMtx());

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}

//=============================================================================
// �|���S���`��(���S�w��)
//=============================================================================
void DrawPolygonCR(Base_Object& obj, const int& tex, const D3DXVECTOR2 uv_v, const D3DXVECTOR2 uv_f)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(-obj.RefScl().x * 0.5f, obj.RefScl().y * 0.5f, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.RefScl().x * 0.5f, obj.RefScl().y * 0.5f, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(-obj.RefScl().x * 0.5f, -obj.RefScl().y * 0.5f, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.RefScl().x * 0.5f, -obj.RefScl().y * 0.5f, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.RefColor();
	pVtx[1].Diffuse = obj.RefColor();
	pVtx[2].Diffuse = obj.RefColor();
	pVtx[3].Diffuse = obj.RefColor();

	pVtx[0].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y + uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y + uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(*obj.GetMaterial());

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(obj.GetMtx());

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.RefRot().y, obj.RefRot().x, obj.RefRot().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(obj.GetMtx());

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);

}

//=============================================================================
// �|���S���`��(����w��)
//=============================================================================
void DrawPolygonLT(Base_Object& obj, const int& tex, const D3DXVECTOR2 uv_v, const D3DXVECTOR2 uv_f)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.RefScl().x, 0.0f, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(0.0f, -obj.RefScl().y, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.RefScl().x, -obj.RefScl().y, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.RefColor();
	pVtx[1].Diffuse = obj.RefColor();
	pVtx[2].Diffuse = obj.RefColor();
	pVtx[3].Diffuse = obj.RefColor();

	pVtx[0].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y + uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y + uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(*obj.GetMaterial());

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(obj.GetMtx());

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.RefRot().y, obj.RefRot().x, obj.RefRot().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(obj.GetMtx());

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}

//=============================================================================
// �|���S���`��XZ����(���S���w��)
//=============================================================================
void DrawPolygonZ(Base_Object& obj, const int& tex, const D3DXVECTOR2 uv_v, const D3DXVECTOR2 uv_f)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(-obj.RefScl().x * 0.5f, 0.0f, obj.RefScl().z);
	pVtx[1].Position = D3DXVECTOR3(obj.RefScl().x * 0.5f,0.0f, obj.RefScl().z);
	pVtx[2].Position = D3DXVECTOR3(-obj.RefScl().x * 0.5f, 0.0f, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.RefScl().x * 0.5f, 0.0f, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.RefColor();
	pVtx[1].Diffuse = obj.RefColor();
	pVtx[2].Diffuse = obj.RefColor();
	pVtx[3].Diffuse = obj.RefColor();

	pVtx[0].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y + uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y + uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(*obj.GetMaterial());

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(obj.GetMtx());

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.RefRot().y, obj.RefRot().x, obj.RefRot().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(obj.GetMtx());

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}

//=============================================================================
// �|���S���`��XZ����(���S�w��)
//=============================================================================
void DrawPolygonZCR(Base_Object& obj, const int& tex, const D3DXVECTOR2 uv_v, const D3DXVECTOR2 uv_f)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(-obj.RefScl().x * 0.5f, 0.0f, obj.RefScl().z * 0.5f);
	pVtx[1].Position = D3DXVECTOR3( obj.RefScl().x * 0.5f, 0.0f, obj.RefScl().z * 0.5f);
	pVtx[2].Position = D3DXVECTOR3(-obj.RefScl().x * 0.5f, 0.0f,-obj.RefScl().z * 0.5f);
	pVtx[3].Position = D3DXVECTOR3( obj.RefScl().x * 0.5f, 0.0f,-obj.RefScl().z * 0.5f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.RefColor();
	pVtx[1].Diffuse = obj.RefColor();
	pVtx[2].Diffuse = obj.RefColor();
	pVtx[3].Diffuse = obj.RefColor();

	pVtx[0].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y + uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y + uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(*obj.GetMaterial());

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(obj.GetMtx());

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.RefRot().y, obj.RefRot().x, obj.RefRot().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(obj.GetMtx());

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}

//=============================================================================
// �|���S���`��XZ����(����w��)
//=============================================================================
void DrawPolygonZLT(Base_Object& obj, const int& tex, const D3DXVECTOR2 uv_v, const D3DXVECTOR2 uv_f)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.RefScl().x, 0.0f, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(0.0f, 0.0f, -obj.RefScl().z);
	pVtx[3].Position = D3DXVECTOR3(obj.RefScl().x, 0.0f, -obj.RefScl().z);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.RefColor();
	pVtx[1].Diffuse = obj.RefColor();
	pVtx[2].Diffuse = obj.RefColor();
	pVtx[3].Diffuse = obj.RefColor();

	pVtx[0].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y + uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y + uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(*obj.GetMaterial());

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(obj.GetMtx());

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.RefRot().y, obj.RefRot().x, obj.RefRot().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(obj.GetMtx());

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}

//=============================================================================
// �|���S���r���{�[�h�`��(���S���w��)
//=============================================================================
void DrawPolygonBill(Base_Object& obj,const int& tex, const D3DXVECTOR2 uv_v, const D3DXVECTOR2 uv_f)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(-obj.RefScl().x * 0.5f, obj.RefScl().y, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.RefScl().x * 0.5f, obj.RefScl().y, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(-obj.RefScl().x * 0.5f, 0.0f, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.RefScl().x * 0.5f, 0.0f, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.RefColor();
	pVtx[1].Diffuse = obj.RefColor();
	pVtx[2].Diffuse = obj.RefColor();
	pVtx[3].Diffuse = obj.RefColor();

	pVtx[0].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y + uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y + uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(*obj.GetMaterial());

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(obj.GetMtx());

	
	//�r���[�}�g���b�N�X�̋t�s����擾
	*obj.GetMtx() = g_GameCamera->RefMtxInvView();
	obj.GetMtx()->_41 = 0.0f;
	obj.GetMtx()->_42 = 0.0f;
	obj.GetMtx()->_43 = 0.0f;

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(obj.GetMtx());

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}

//=============================================================================
// �|���S���r���{�[�h�`��(���S�w��)
//=============================================================================
void DrawPolygonBillCR(Base_Object& obj, const int& tex, const D3DXVECTOR2 uv_v, const D3DXVECTOR2 uv_f)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(-obj.RefScl().x * 0.5f, obj.RefScl().y * 0.5f, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.RefScl().x * 0.5f, obj.RefScl().y * 0.5f, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(-obj.RefScl().x * 0.5f, -obj.RefScl().y * 0.5f, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.RefScl().x * 0.5f, -obj.RefScl().y * 0.5f, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.RefColor();
	pVtx[1].Diffuse = obj.RefColor();
	pVtx[2].Diffuse = obj.RefColor();
	pVtx[3].Diffuse = obj.RefColor();

	pVtx[0].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y + uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y + uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(*obj.GetMaterial());

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(obj.GetMtx());

	
	//�r���[�}�g���b�N�X�̋t�s����擾
	*obj.GetMtx() = g_GameCamera->RefMtxInvView();
	obj.GetMtx()->_41 = 0.0f;
	obj.GetMtx()->_42 = 0.0f;
	obj.GetMtx()->_43 = 0.0f;

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(obj.GetMtx());

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}

//=============================================================================
// �|���S���r���{�[�h�`��(����w��)
//=============================================================================
void DrawPolygonBillLT(Base_Object& obj, const int& tex, const D3DXVECTOR2 uv_v, const D3DXVECTOR2 uv_f)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.RefScl().x, 0.0f, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(0.0f, -obj.RefScl().y, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.RefScl().x, -obj.RefScl().y, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.RefColor();
	pVtx[1].Diffuse = obj.RefColor();
	pVtx[2].Diffuse = obj.RefColor();
	pVtx[3].Diffuse = obj.RefColor();

	pVtx[0].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y + uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y + uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(*obj.GetMaterial());

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(obj.GetMtx());

	
	//�r���[�}�g���b�N�X�̋t�s����擾
	*obj.GetMtx() = g_GameCamera->RefMtxInvView();
	obj.GetMtx()->_41 = 0.0f;
	obj.GetMtx()->_42 = 0.0f;
	obj.GetMtx()->_43 = 0.0f;

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(obj.GetMtx());

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}

//=============================================================================
// �|���S���r���{�[�h�`��(���S���w��)
//=============================================================================
void DrawPolygonAnyBill(Base_Object& obj, const int& tex, const D3DXVECTOR2 uv_v, const D3DXVECTOR2 uv_f, bool InX, bool InY, bool InZ)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(-obj.RefScl().x * 0.5f, obj.RefScl().y, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.RefScl().x * 0.5f, obj.RefScl().y, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(-obj.RefScl().x * 0.5f, 0.0f, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.RefScl().x * 0.5f, 0.0f, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.RefColor();
	pVtx[1].Diffuse = obj.RefColor();
	pVtx[2].Diffuse = obj.RefColor();
	pVtx[3].Diffuse = obj.RefColor();

	pVtx[0].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y + uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y + uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);
	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(*obj.GetMaterial());

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(obj.GetMtx());

	
	//�C�ӂ̎��̓]�u�s��
	if (InX)
	{
		obj.GetMtx()->_11 = g_GameCamera->RefMtxView()._11;
		obj.GetMtx()->_12 = g_GameCamera->RefMtxView()._21;
		obj.GetMtx()->_13 = g_GameCamera->RefMtxView()._31;
	}
	if (InY)
	{
		obj.GetMtx()->_21 = g_GameCamera->RefMtxView()._12;
		obj.GetMtx()->_22 = g_GameCamera->RefMtxView()._22;
		obj.GetMtx()->_23 = g_GameCamera->RefMtxView()._32;
	}
	if (InZ)
	{
		obj.GetMtx()->_31 = g_GameCamera->RefMtxView()._13;
		obj.GetMtx()->_32 = g_GameCamera->RefMtxView()._23;
		obj.GetMtx()->_33 = g_GameCamera->RefMtxView()._33;
	}


	obj.GetMtx()->_41 = 0.0f;
	obj.GetMtx()->_42 = 0.0f;
	obj.GetMtx()->_43 = 0.0f;

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(obj.GetMtx());

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}

//=============================================================================
// �|���S���r���{�[�h�`��(���S�w��)
//=============================================================================
void DrawPolygonAnyBillCR(Base_Object& obj, const int& tex, const D3DXVECTOR2 uv_v, const D3DXVECTOR2 uv_f, bool InX, bool InY, bool InZ)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(-obj.RefScl().x * 0.5f, obj.RefScl().y * 0.5f, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.RefScl().x * 0.5f, obj.RefScl().y * 0.5f, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(-obj.RefScl().x * 0.5f, -obj.RefScl().y * 0.5f, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.RefScl().x * 0.5f, -obj.RefScl().y * 0.5f, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.RefColor();
	pVtx[1].Diffuse = obj.RefColor();
	pVtx[2].Diffuse = obj.RefColor();
	pVtx[3].Diffuse = obj.RefColor();

	pVtx[0].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y + uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y + uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);
	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(*obj.GetMaterial());

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(obj.GetMtx());

	
	//�C�ӂ̎��̓]�u�s��
	if (InX)
	{
		obj.GetMtx()->_11 = g_GameCamera->RefMtxView()._11;
		obj.GetMtx()->_12 = g_GameCamera->RefMtxView()._21;
		obj.GetMtx()->_13 = g_GameCamera->RefMtxView()._31;
	}
	if (InY)
	{
		obj.GetMtx()->_21 = g_GameCamera->RefMtxView()._12;
		obj.GetMtx()->_22 = g_GameCamera->RefMtxView()._22;
		obj.GetMtx()->_23 = g_GameCamera->RefMtxView()._32;
	}
	if (InZ)
	{
		obj.GetMtx()->_31 = g_GameCamera->RefMtxView()._13;
		obj.GetMtx()->_32 = g_GameCamera->RefMtxView()._23;
		obj.GetMtx()->_33 = g_GameCamera->RefMtxView()._33;
	}


	obj.GetMtx()->_41 = 0.0f;
	obj.GetMtx()->_42 = 0.0f;
	obj.GetMtx()->_43 = 0.0f;

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(obj.GetMtx());

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}

//=============================================================================
// �|���S���r���{�[�h�`��(����w��)
//=============================================================================
void DrawPolygonAnyBillLT(Base_Object& obj, const int& tex, const D3DXVECTOR2 uv_v, const D3DXVECTOR2 uv_f, bool InX, bool InY, bool InZ)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.RefScl().x, 0.0f, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(0.0f, -obj.RefScl().y, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.RefScl().x, -obj.RefScl().y, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.RefColor();
	pVtx[1].Diffuse = obj.RefColor();
	pVtx[2].Diffuse = obj.RefColor();
	pVtx[3].Diffuse = obj.RefColor();

	pVtx[0].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(uv_v.x, uv_v.y + uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(uv_v.x + uv_f.x, uv_v.y + uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);
	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(*obj.GetMaterial());

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(obj.GetMtx());

	
	//�C�ӂ̎��̓]�u�s��
	if (InX)
	{
		obj.GetMtx()->_11 = g_GameCamera->RefMtxView()._11;
		obj.GetMtx()->_12 = g_GameCamera->RefMtxView()._21;
		obj.GetMtx()->_13 = g_GameCamera->RefMtxView()._31;
	}
	if (InY)
	{
		obj.GetMtx()->_21 = g_GameCamera->RefMtxView()._12;
		obj.GetMtx()->_22 = g_GameCamera->RefMtxView()._22;
		obj.GetMtx()->_23 = g_GameCamera->RefMtxView()._32;
	}
	if (InZ)
	{
		obj.GetMtx()->_31 = g_GameCamera->RefMtxView()._13;
		obj.GetMtx()->_32 = g_GameCamera->RefMtxView()._23;
		obj.GetMtx()->_33 = g_GameCamera->RefMtxView()._33;
	}


	obj.GetMtx()->_41 = 0.0f;
	obj.GetMtx()->_42 = 0.0f;
	obj.GetMtx()->_43 = 0.0f;

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(obj.GetMtx());

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}

//=============================================================================
// ���f���`��
//=============================================================================
void Draw3DModel(Base_Object& obj, DX11_MODEL& model)
{
	// �}�e���A���ݒ�
	SetMaterial(*obj.GetMaterial());

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &model.VertexBuffer, &stride, &offset);

	// �C���f�b�N�X�o�b�t�@�ݒ�
	GetDeviceContext()->IASetIndexBuffer(model.IndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ���[���h�}�g���b�N�X�̏������i�P�ʍs������֐��j
	D3DXMatrixIdentity(obj.GetMtx());

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, obj.RefScl().x, obj.RefScl().y, obj.RefScl().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.RefRot().y, obj.RefRot().x, obj.RefRot().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(obj.GetMtx());

	for (unsigned short i = 0; i < model.SubsetNum; i++)
	{

		// �e�N�X�`���ݒ�
		if (model.SubsetArray[i].Material.Material.noTexSampling == 0)
			GetDeviceContext()->PSSetShaderResources(0, 1, &model.SubsetArray[i].Material.Texture);

		// �|���S���`��
		GetDeviceContext()->DrawIndexed(model.SubsetArray[i].IndexNum, model.SubsetArray[i].StartIndex, 0);
	}
}

//---------------------------------
// �f�o�b�N�p
//---------------------------------
void DrawPolygon(Object obj, const int& tex)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(-obj.m_Scl.x * 0.5f, obj.m_Scl.y, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.m_Scl.x * 0.5f, obj.m_Scl.y, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(-obj.m_Scl.x * 0.5f, 0.0f, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.m_Scl.x * 0.5f, 0.0f, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.m_Color;
	pVtx[1].Diffuse = obj.m_Color;
	pVtx[2].Diffuse = obj.m_Color;
	pVtx[3].Diffuse = obj.m_Color;

	pVtx[0].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y + obj.m_Uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y + obj.m_Uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(obj.m_Material);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&obj.m_Mtx);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, obj.m_Scl.x, obj.m_Scl.y, obj.m_Scl.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.m_Rot.y, obj.m_Rot.x, obj.m_Rot.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.m_Pos.x, obj.m_Pos.y, obj.m_Pos.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&obj.m_Mtx);

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}
void DrawPolygonCR(Object obj, const int& tex)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(-obj.m_Scl.x * 0.5f, obj.m_Scl.y * 0.5f, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.m_Scl.x * 0.5f, obj.m_Scl.y * 0.5f, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(-obj.m_Scl.x * 0.5f, -obj.m_Scl.y * 0.5f, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.m_Scl.x * 0.5f, -obj.m_Scl.y * 0.5f, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.m_Color;
	pVtx[1].Diffuse = obj.m_Color;
	pVtx[2].Diffuse = obj.m_Color;
	pVtx[3].Diffuse = obj.m_Color;

	pVtx[0].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y + obj.m_Uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y + obj.m_Uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(obj.m_Material);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&obj.m_Mtx);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, obj.m_Scl.x, obj.m_Scl.y, obj.m_Scl.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.m_Rot.y, obj.m_Rot.x, obj.m_Rot.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.m_Pos.x, obj.m_Pos.y, obj.m_Pos.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&obj.m_Mtx);

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}
void DrawPolygonLT(Object obj, const int& tex)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.m_Scl.x, 0.0f, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(0.0f, -obj.m_Scl.y, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.m_Scl.x, -obj.m_Scl.y, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.m_Color;
	pVtx[1].Diffuse = obj.m_Color;
	pVtx[2].Diffuse = obj.m_Color;
	pVtx[3].Diffuse = obj.m_Color;

	pVtx[0].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y + obj.m_Uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y + obj.m_Uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(obj.m_Material);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&obj.m_Mtx);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, obj.m_Scl.x, obj.m_Scl.y, obj.m_Scl.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.m_Rot.y, obj.m_Rot.x, obj.m_Rot.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.m_Pos.x, obj.m_Pos.y, obj.m_Pos.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&obj.m_Mtx);

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}
void DrawPolygonBill(Object obj, const int& tex)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(-obj.m_Scl.x * 0.5f, obj.m_Scl.y, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.m_Scl.x * 0.5f, obj.m_Scl.y, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(-obj.m_Scl.x * 0.5f, 0.0f, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.m_Scl.x * 0.5f, 0.0f, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.m_Color;
	pVtx[1].Diffuse = obj.m_Color;
	pVtx[2].Diffuse = obj.m_Color;
	pVtx[3].Diffuse = obj.m_Color;

	pVtx[0].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y + obj.m_Uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y + obj.m_Uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(obj.m_Material);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&obj.m_Mtx);

	//�r���[�}�g���b�N�X�̋t�s����擾
	obj.m_Mtx = g_GameCamera->RefMtxInvView();
	obj.m_Mtx._41 = 0.0f;
	obj.m_Mtx._42 = 0.0f;
	obj.m_Mtx._43 = 0.0f;

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.m_Rot.y, obj.m_Rot.x, obj.m_Rot.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.m_Pos.x, obj.m_Pos.y, obj.m_Pos.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&obj.m_Mtx);

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}
void DrawPolygonBillCR(Object obj, const int& tex)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(-obj.m_Scl.x * 0.5f, obj.m_Scl.y * 0.5f, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.m_Scl.x * 0.5f, obj.m_Scl.y * 0.5f, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(-obj.m_Scl.x * 0.5f, -obj.m_Scl.y * 0.5f, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.m_Scl.x * 0.5f, -obj.m_Scl.y * 0.5f, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.m_Color;
	pVtx[1].Diffuse = obj.m_Color;
	pVtx[2].Diffuse = obj.m_Color;
	pVtx[3].Diffuse = obj.m_Color;

	pVtx[0].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y + obj.m_Uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y + obj.m_Uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(obj.m_Material);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&obj.m_Mtx);

	
	//�r���[�}�g���b�N�X�̋t�s����擾
	obj.m_Mtx = g_GameCamera->RefMtxInvView();
	obj.m_Mtx._41 = 0.0f;
	obj.m_Mtx._42 = 0.0f;
	obj.m_Mtx._43 = 0.0f;

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.m_Rot.y, obj.m_Rot.x, obj.m_Rot.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.m_Pos.x, obj.m_Pos.y, obj.m_Pos.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&obj.m_Mtx);

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}
void DrawPolygonBillLT(Object obj, const int& tex)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.m_Scl.x, 0.0f, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(0.0f, -obj.m_Scl.y, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.m_Scl.x, -obj.m_Scl.y, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.m_Color;
	pVtx[1].Diffuse = obj.m_Color;
	pVtx[2].Diffuse = obj.m_Color;
	pVtx[3].Diffuse = obj.m_Color;

	pVtx[0].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y + obj.m_Uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y + obj.m_Uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(obj.m_Material);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&obj.m_Mtx);

	
	//�r���[�}�g���b�N�X�̋t�s����擾
	obj.m_Mtx = g_GameCamera->RefMtxInvView();
	obj.m_Mtx._41 = 0.0f;
	obj.m_Mtx._42 = 0.0f;
	obj.m_Mtx._43 = 0.0f;

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.m_Rot.y, obj.m_Rot.x, obj.m_Rot.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.m_Pos.x, obj.m_Pos.y, obj.m_Pos.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&obj.m_Mtx);

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}
void DrawPolygonAnyBill(Object obj, const int& tex, bool InX, bool InY, bool InZ)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(-obj.m_Scl.x * 0.5f, obj.m_Scl.y, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.m_Scl.x * 0.5f, obj.m_Scl.y, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(-obj.m_Scl.x * 0.5f, 0.0f, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.m_Scl.x * 0.5f, 0.0f, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.m_Color;
	pVtx[1].Diffuse = obj.m_Color;
	pVtx[2].Diffuse = obj.m_Color;
	pVtx[3].Diffuse = obj.m_Color;

	pVtx[0].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y + obj.m_Uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y + obj.m_Uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(obj.m_Material);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&obj.m_Mtx);

	
	//�C�ӂ̎��̓]�u�s��
	if (InX)
	{
		
		obj.m_Mtx._11 = g_GameCamera->RefMtxView()._11;
		obj.m_Mtx._12 = g_GameCamera->RefMtxView()._21;
		obj.m_Mtx._13 = g_GameCamera->RefMtxView()._31;
	}
	if (InY)
	{
		obj.m_Mtx._21 = g_GameCamera->RefMtxView()._12;
		obj.m_Mtx._22 = g_GameCamera->RefMtxView()._22;
		obj.m_Mtx._23 = g_GameCamera->RefMtxView()._32;
	}
	if (InZ)
	{
		obj.m_Mtx._31 = g_GameCamera->RefMtxView()._13;
		obj.m_Mtx._32 = g_GameCamera->RefMtxView()._23;
		obj.m_Mtx._33 = g_GameCamera->RefMtxView()._33;
	}

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, obj.m_Scl.x, obj.m_Scl.y, obj.m_Scl.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.m_Rot.y, obj.m_Rot.x, obj.m_Rot.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.m_Pos.x, obj.m_Pos.y, obj.m_Pos.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&obj.m_Mtx);

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}
void DrawPolygonAnyBillCR(Object obj, const int& tex, bool InX, bool InY, bool InZ)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(-obj.m_Scl.x * 0.5f, obj.m_Scl.y * 0.5f, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.m_Scl.x * 0.5f, obj.m_Scl.y * 0.5f, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(-obj.m_Scl.x * 0.5f, -obj.m_Scl.y * 0.5f, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.m_Scl.x * 0.5f, -obj.m_Scl.y * 0.5f, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.m_Color;
	pVtx[1].Diffuse = obj.m_Color;
	pVtx[2].Diffuse = obj.m_Color;
	pVtx[3].Diffuse = obj.m_Color;

	pVtx[0].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y + obj.m_Uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y + obj.m_Uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(obj.m_Material);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&obj.m_Mtx);

	
	//�C�ӂ̎��̓]�u�s��
	if (InX)
	{
		obj.m_Mtx._11 = g_GameCamera->RefMtxView()._11;
		obj.m_Mtx._12 = g_GameCamera->RefMtxView()._21;
		obj.m_Mtx._13 = g_GameCamera->RefMtxView()._31;
	}
	if (InY)
	{
		obj.m_Mtx._21 = g_GameCamera->RefMtxView()._12;
		obj.m_Mtx._22 = g_GameCamera->RefMtxView()._22;
		obj.m_Mtx._23 = g_GameCamera->RefMtxView()._32;
	}
	if (InZ)
	{
		obj.m_Mtx._31 = g_GameCamera->RefMtxView()._13;
		obj.m_Mtx._32 = g_GameCamera->RefMtxView()._23;
		obj.m_Mtx._33 = g_GameCamera->RefMtxView()._33;
	}

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, obj.m_Scl.x, obj.m_Scl.y, obj.m_Scl.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.m_Rot.y, obj.m_Rot.x, obj.m_Rot.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.m_Pos.x, obj.m_Pos.y, obj.m_Pos.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&obj.m_Mtx);

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}
void DrawPolygonAnyBillLT(Object obj, const int& tex, bool InX, bool InY, bool InZ)
{
	//���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	pVtx[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].Position = D3DXVECTOR3(obj.m_Scl.x, 0.0f, 0.0f);
	pVtx[2].Position = D3DXVECTOR3(0.0f, -obj.m_Scl.y, 0.0f);
	pVtx[3].Position = D3DXVECTOR3(obj.m_Scl.x, -obj.m_Scl.y, 0.0f);

	pVtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].Diffuse = obj.m_Color;
	pVtx[1].Diffuse = obj.m_Color;
	pVtx[2].Diffuse = obj.m_Color;
	pVtx[3].Diffuse = obj.m_Color;

	pVtx[0].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y);
	pVtx[1].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y);
	pVtx[2].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x, obj.m_Uv_v.y + obj.m_Uv_f.y);
	pVtx[3].TexCoord = D3DXVECTOR2(obj.m_Uv_v.x + obj.m_Uv_f.x, obj.m_Uv_v.y + obj.m_Uv_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �}�e���A���̃Z�b�g
	SetMaterial(obj.m_Material);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&obj.m_Mtx);

	
	//�C�ӂ̎��̓]�u�s��
	if (InX)
	{
		obj.m_Mtx._11 = g_GameCamera->RefMtxView()._11;
		obj.m_Mtx._12 = g_GameCamera->RefMtxView()._21;
		obj.m_Mtx._13 = g_GameCamera->RefMtxView()._31;
	}
	if (InY)
	{
		obj.m_Mtx._21 = g_GameCamera->RefMtxView()._12;
		obj.m_Mtx._22 = g_GameCamera->RefMtxView()._22;
		obj.m_Mtx._23 = g_GameCamera->RefMtxView()._32;
	}
	if (InZ)
	{
		obj.m_Mtx._31 = g_GameCamera->RefMtxView()._13;
		obj.m_Mtx._32 = g_GameCamera->RefMtxView()._23;
		obj.m_Mtx._33 = g_GameCamera->RefMtxView()._33;
	}

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, obj.m_Scl.x, obj.m_Scl.y, obj.m_Scl.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.m_Rot.y, obj.m_Rot.x, obj.m_Rot.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.m_Pos.x, obj.m_Pos.y, obj.m_Pos.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&obj.m_Mtx);

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//���e�X�g��L����
	SetAlphaTestEnable(false);
}
void Draw3DModel(Object obj, DX11_MODEL& model)
{
	// �}�e���A���ݒ�
	SetMaterial(obj.m_Material);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &model.VertexBuffer, &stride, &offset);

	// �C���f�b�N�X�o�b�t�@�ݒ�
	GetDeviceContext()->IASetIndexBuffer(model.IndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ���[���h�}�g���b�N�X�̏������i�P�ʍs������֐��j
	D3DXMatrixIdentity(&obj.m_Mtx);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, obj.m_Scl.x, obj.m_Scl.y, obj.m_Scl.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.m_Rot.y, obj.m_Rot.x, obj.m_Rot.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, obj.m_Pos.x, obj.m_Pos.y, obj.m_Pos.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&obj.m_Mtx);

	for (unsigned short i = 0; i < model.SubsetNum; i++)
	{
		// �e�N�X�`���ݒ�
		if (model.SubsetArray[i].Material.Material.noTexSampling == 0)
			GetDeviceContext()->PSSetShaderResources(0, 1, &model.SubsetArray[i].Material.Texture);

		// �|���S���`��
		GetDeviceContext()->DrawIndexed(model.SubsetArray[i].IndexNum, model.SubsetArray[i].StartIndex, 0);
	}
}