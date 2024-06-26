//=============================================================================
//
// ���b�V���n�ʂ̏��� [meshfield.cpp]
// Author : �ؓc�C���l
//
//=============================================================================
#include "main.h"
#include "texture.h"
#include "meshfield.h"
#include "sprite.h"
#include "material.h"

//=============================================================================
// �����t���R���X�g���N�^
//=============================================================================
Field::Field(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, int numBlockX, int numBlockZ)
	:Base_Object(background, pos, rot, scl, { 0.0f,0.0f,0.0f }, {1.0f,1.0f,1.0f,1.0f},true)
{
	m_Mesh.m_NumVertex = (numBlockX + 1) * (numBlockZ + 1);
	m_Mesh.m_NumIndex = (numBlockX + 1) * 2 * numBlockZ + (numBlockZ - 1) * 2;

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * m_Mesh.m_NumVertex;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	GetDevice()->CreateBuffer(&bd, NULL, &m_Mesh.m_VertexBuffer);


	// �C���f�b�N�X�o�b�t�@����
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(unsigned short) * m_Mesh.m_NumIndex;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	GetDevice()->CreateBuffer(&bd, NULL, &m_Mesh.m_IndexBuffer);


	{//���_�o�b�t�@�̒��g�𖄂߂�

		// ���_�o�b�t�@�ւ̃|�C���^���擾
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(m_Mesh.m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

		for (int y = 0; y < (numBlockZ + 1); y++)
		{
			for (int x = 0; x < (numBlockX + 1); x++)
			{
				//�z��̃C���f�b�N�X���v�Z����
				int i = y * (numBlockX + 1) + x;

				// ���_���W�̐ݒ�
				pVtx[i].Position = D3DXVECTOR3(-(numBlockX / 2.0f) * scl.x + x * scl.x, 0.0f, (numBlockZ / 2.0f) * scl.z - y * scl.z);
				// UV�l�̐ݒ�
				pVtx[i].TexCoord = D3DXVECTOR2(x * 1.0f, y * 1.0f);

				// �@���̐ݒ�
				pVtx[i].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				// ���_�J���[�̐ݒ�
				pVtx[i].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
		}
		GetDeviceContext()->Unmap(m_Mesh.m_VertexBuffer, 0);
	}

	{//�C���f�b�N�X�o�b�t�@�̒��g�𖄂߂�

		// �C���f�b�N�X�o�b�t�@�̃|�C���^���擾
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(m_Mesh.m_IndexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		unsigned short* pIdx = (unsigned short*)msr.pData;

		int idx = 0;

		for (int y = 0; y < numBlockZ; y++)
		{
			//y�s�ڂ̃|���S���̃C���f�b�N�X
			for (int x = 0; x < (numBlockX + 1); x++)
			{
				pIdx[idx] = (numBlockX + 1) + x + (numBlockX + 1) * y;
				idx++;
				pIdx[idx] = 0 + x + (numBlockX + 1) * y;
				idx++;
			}

			//�k�ރ|���S�����̃C���f�b�N�X
			if (y < (numBlockZ - 1))
			{
				pIdx[idx] = numBlockX + (numBlockX + 1) * y;
				idx++;
				pIdx[idx] = (numBlockX + 1) * 2 + (numBlockX + 1) * y;
				idx++;
			}
		}

		GetDeviceContext()->Unmap(m_Mesh.m_IndexBuffer, 0);
	}

	// �}�e���A���ݒ�
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = RefColor();
	GetMaterial()->Ambient = { 0.0f,0.0f,0.0f,0.0f };
	GetMaterial()->Emission = { 0.0f,0.0f,0.0f,0.0f };
	GetMaterial()->noTexSampling = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Field::~Field()
{
	// �C���f�b�N�X�o�b�t�@�̉��
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
void Field::Update(void)
{
}

//=============================================================================
// �`��
//=============================================================================
void Field::Draw(void)
{
	SetCullingMode(CULL_MODE_BACK);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &m_Mesh.m_VertexBuffer, &stride, &offset);

	// �C���f�b�N�X�o�b�t�@�ݒ�
	GetDeviceContext()->IASetIndexBuffer(m_Mesh.m_IndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �}�e���A���ݒ�
	SetMaterial(*GetMaterial());

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(RefImageMaterial().m_Lane));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(GetMtx());

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, RefRot().y, RefRot().x, RefRot().z);
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
void Field::CollDispatch(Base_Object* pObj)
{
}
