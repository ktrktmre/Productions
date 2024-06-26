//=============================================================================
//
// ���b�V���R���� [meshmountain.cpp]
// Author : �ؓc�C���l
//
//=============================================================================
#include "meshmountain.h"
#include "Texture.h"
#include "material.h"
#include "sprite.h"

//=============================================================================
// �����t���R���X�g���N�^
//=============================================================================
Mountain::Mountain(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR2 size, int numBlockH, int numBlockV, D3DXVECTOR2 uv)
	:Base_Object(background, pos, rot, NO_VECTOR3, NO_VECTOR3, { 1.0f,1.0f,1.0f,1.0f }, true)
{
	ID3D11Device* pDevice = GetDevice();

	// �}�e���A���ݒ�
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = RefColor();
	GetMaterial()->Ambient = { 0.0f,0.0f,0.0f,0.0f };
	GetMaterial()->Emission = { 0.0f,0.0f,0.0f,0.0f };
	GetMaterial()->noTexSampling = 0;

	// ���_���̐ݒ�
	m_Mesh.m_NumVertex = (numBlockH + 1) * (numBlockV + 1);

	// �C���f�b�N�X���̐ݒ�
	m_Mesh.m_NumIndex = (numBlockH + 1) * (numBlockV * 2) + (numBlockV - 1);

	// �ꎞ���_�z��𐶐�
	VERTEX_3D* pVertexWk = new VERTEX_3D[m_Mesh.m_NumVertex];

	// �ꎞ�C���f�b�N�X�z��𐶐�
	int* pIndexWk = new int[m_Mesh.m_NumIndex];

	// ���_�z��̒��g�𖄂߂�
	VERTEX_3D* pVtx = pVertexWk;
	const float ANGLE_H = (D3DX_PI * 2) / numBlockH;

	for (int vt = 0; vt < (numBlockV + 1); vt++) {
		for (int hr = 0; hr < (numBlockH + 1); hr++) {
			// ���_���W�̐ݒ�
			pVtx->Position.x = sinf(ANGLE_H * hr) * size.x;
			pVtx->Position.y = vt * size.y;
			pVtx->Position.z = cosf(ANGLE_H * hr) * size.x;

			// �@���̐ݒ�
			pVtx->Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// ���ˌ��̐ݒ�
			pVtx->Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx->TexCoord.x = hr * uv.x;
			pVtx->TexCoord.y = 0.975f - vt * 0.95f * uv.y;

			pVtx++;
		}
	}

	// �C���f�b�N�X�z��̒��g�𖄂߂�
	int* pIdx = pIndexWk;

	for (int vt = 0; vt < numBlockV; vt++) {
		for (int hr = 0; hr < (numBlockH + 1); hr++) {
			*pIdx = vt * (numBlockH + 1) + hr;
			pIdx++;

			*pIdx = (vt + 1) * (numBlockH + 1) + hr;
			pIdx++;
		}
	}

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * m_Mesh.m_NumVertex;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = pVertexWk;

	GetDevice()->CreateBuffer(&bd, &sd, &m_Mesh.m_VertexBuffer);


	// �C���f�b�N�X�o�b�t�@����
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(int) * m_Mesh.m_NumIndex;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;

	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = pIndexWk;

	GetDevice()->CreateBuffer(&bd, &sd, &m_Mesh.m_IndexBuffer);


	// �ꎞ�z��̉��
	delete[] pIndexWk;
	delete[] pVertexWk;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Mountain::~Mountain()
{
	//�C���f�b�N�X�o�b�t�@�̉��
	if (m_Mesh.m_IndexBuffer != NULL)
	{
		m_Mesh.m_IndexBuffer->Release();
		m_Mesh.m_IndexBuffer = NULL;
	}

	//���_�o�b�t�@�̉��
	if (m_Mesh.m_VertexBuffer != NULL)
	{
		m_Mesh.m_VertexBuffer->Release();
		m_Mesh.m_VertexBuffer = NULL;
	}
}

//=============================================================================
// �X�V
//=============================================================================
void Mountain::Update(void)
{
}

//=============================================================================
// �`��
//=============================================================================
void Mountain::Draw(void)
{
	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &m_Mesh.m_VertexBuffer, &stride, &offset);

	// �C���f�b�N�X�o�b�t�@�ݒ�
	GetDeviceContext()->IASetIndexBuffer(m_Mesh.m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �}�e���A���ݒ�
	SetMaterial(*GetMaterial());

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(RefImageMaterial().m_Mountain));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(GetMtx());

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,RefRot().y,RefRot().x,RefRot().z);
	D3DXMatrixMultiply(GetMtx(), GetMtx(), &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, RefPos().x, RefPos().y, RefPos().z);
	D3DXMatrixMultiply(GetMtx(), GetMtx(), &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(GetMtx());

	// �|���S���̕`��
	GetDeviceContext()->DrawIndexed(m_Mesh.m_NumIndex, 0, 0);
}
//=============================================================================
// �Փ˔���f�B�X�p�b�`
//=============================================================================
void Mountain::CollDispatch(Base_Object* pObj)
{
}
