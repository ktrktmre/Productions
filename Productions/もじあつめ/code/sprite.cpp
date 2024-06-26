//=============================================================================
//
// �X�v���C�g���� [sprite.cpp]
// Author :�ؓc �C���l 
//
//=============================================================================
#include "sprite.h"
#include "renderer.h"
#include "texture.h"
#include "myfunction.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUM_VERTEX 4	//�K�v�Ȓ��_�̐�
#define CHAR_TEX_PART_X 14	//�����e�N�X�`����������
#define CHAR_TEX_PART_Y 2 	//�����e�N�X�`����������
#define CHAR_BUF 1024	//������o�b�t�@


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer				*g_VertexBuffer = NULL;	// ���_���


//=============================================================================
// ����������
//=============================================================================
void InitSprite(void)
{
	ID3D11Device *pDevice = GetDevice();

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * NUM_VERTEX;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	pDevice->CreateBuffer(&bd, NULL, &g_VertexBuffer);
}

//=============================================================================
// �I������
//=============================================================================
void UninitSprite(void)
{
	// ���_�o�b�t�@�̉��
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
}

//=============================================================================
// �X�v���C�g�f�[�^�ݒ�
// ���W�E�T�C�Y�EUV�w��
//=============================================================================
//����
//texNo : �e�N�X�`���̎��ʔԍ��itexture.h, texture.cpp ��LoadTexture�֐��̖߂�l�j
//pos	; X,Y���W
//size	; �T�C�Y
//tex_v	; �σe�N�X�`�����W
//tex_f	; �Œ�e�N�X�`�����W
void DrawSprite(int texNo, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 tex_v, D3DXVECTOR2 tex_f)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	float hw, hh;
	hw = size.x * 0.5f;
	hh = size.y * 0.5f;

	// ���_�O�ԁi����̒��_�j
	vertex[0].Position = D3DXVECTOR3(pos.x- hw, pos.y - hh, 0.0f);
	vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(tex_v.x, tex_v.y);

	// ���_�P�ԁi�E��̒��_�j
	vertex[1].Position = D3DXVECTOR3(pos.x + hw, pos.y - hh, 0.0f);
	vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(tex_v.x + tex_f.x, tex_v.y);

	// ���_�Q�ԁi�����̒��_�j
	vertex[2].Position = D3DXVECTOR3(pos.x - hw, pos.y + hh, 0.0f);
	vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(tex_v.x, tex_v.y + tex_f.y);

	// ���_�R�ԁi�E���̒��_�j
	vertex[3].Position = D3DXVECTOR3(pos.x + hw, pos.y + hh, 0.0f);
	vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(tex_v.x + tex_f.x, tex_v.y + tex_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_VERTEX, 0);
}

//=============================================================================
// �X�v���C�g�f�[�^�ݒ�i����w��j
// ���W�E�T�C�Y�EUV�w��
//=============================================================================
//����
//texNo : �e�N�X�`���̎��ʔԍ��itexture.h, texture.cpp ��LoadTexture�֐��̖߂�l�j
//pos	; X,Y���W
//size	; �T�C�Y
//tex_v	; �σe�N�X�`�����W
//tex_f	; �Œ�e�N�X�`�����W
void DrawSpriteLeftTop(int texNo, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 tex_v, D3DXVECTOR2 tex_f)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	// ��������_�Ƃ��Đݒ肷��v���O����
	vertex[0].Position = D3DXVECTOR3(pos.x, pos.y, 0.0f);
	vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(tex_v.x, tex_v.y);

	vertex[1].Position = D3DXVECTOR3(pos.x + size.x, pos.y, 0.0f);
	vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(tex_v.x + tex_f.x, tex_v.y);

	vertex[2].Position = D3DXVECTOR3(pos.x, pos.y + size.y, 0.0f);
	vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(tex_v.x, tex_f.y + tex_v.y);

	vertex[3].Position = D3DXVECTOR3(pos.x + size.x, pos.y + size.y, 0.0f);
	vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(tex_v.x + tex_f.x, tex_v.y + tex_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_VERTEX, 0);
}


//=============================================================================
// �X�v���C�g�f�[�^�ݒ�
// ���W�E�T�C�Y�EUV�w��E���_�F
//=============================================================================
//����
//texNo : �e�N�X�`���̎��ʔԍ��itexture.h, texture.cpp ��LoadTexture�֐��̖߂�l�j
//pos	; X,Y���W
//size	; �T�C�Y
//tex_v	; �σe�N�X�`�����W
//tex_f	; �Œ�e�N�X�`�����W
//color : ���_�̐F�iRGBA�j
void DrawSpriteColor(int texNo, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 tex_v, D3DXVECTOR2 tex_f,D3DXCOLOR color)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	float hw, hh;
	hw = size.x * 0.5f;
	hh = size.y * 0.5f;

	// ���_�O�ԁi����̒��_�j
	vertex[0].Position = D3DXVECTOR3(pos.x - hw, pos.y - hh, 0.0f);
	vertex[0].Diffuse = color;
	vertex[0].TexCoord = D3DXVECTOR2(tex_v.x, tex_v.y);

	// ���_�P�ԁi�E��̒��_�j
	vertex[1].Position = D3DXVECTOR3(pos.x + hw, pos.y - hh, 0.0f);
	vertex[1].Diffuse = color;
	vertex[1].TexCoord = D3DXVECTOR2(tex_v.x + tex_f.x, tex_v.y);

	// ���_�Q�ԁi�����̒��_�j
	vertex[2].Position = D3DXVECTOR3(pos.x - hw, pos.y + hh, 0.0f);
	vertex[2].Diffuse = color;
	vertex[2].TexCoord = D3DXVECTOR2(tex_v.x, tex_v.y + tex_f.y);

	// ���_�R�ԁi�E���̒��_�j
	vertex[3].Position = D3DXVECTOR3(pos.x + hw, pos.y + hh, 0.0f);
	vertex[3].Diffuse = color;
	vertex[3].TexCoord = D3DXVECTOR2(tex_v.x + tex_f.x, tex_v.y + tex_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_VERTEX, 0);
}

//=============================================================================
// �X�v���C�g�f�[�^�ݒ�i����w��j
// ���W�E�T�C�Y�EUV�w��
//=============================================================================
//����
//texNo : �e�N�X�`���̎��ʔԍ��itexture.h, texture.cpp ��LoadTexture�֐��̖߂�l�j
//pos	; X,Y���W
//size	; �T�C�Y
//tex_v	; �σe�N�X�`�����W
//tex_f	; �Œ�e�N�X�`�����W
//color	; ���_�J���[
void DrawSpriteLeftTopColor(int texNo, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 tex_v, D3DXVECTOR2 tex_f,D3DXCOLOR color)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	// ��������_�Ƃ��Đݒ肷��v���O����
	vertex[0].Position = D3DXVECTOR3(pos.x, pos.y, 0.0f);
	vertex[1].Position = D3DXVECTOR3(pos.x + size.x, pos.y, 0.0f);
	vertex[2].Position = D3DXVECTOR3(pos.x, pos.y + size.y, 0.0f);
	vertex[3].Position = D3DXVECTOR3(pos.x + size.x, pos.y + size.y, 0.0f);

	vertex[0].TexCoord = D3DXVECTOR2(tex_v.x, tex_v.y);
	vertex[1].TexCoord = D3DXVECTOR2(tex_v.x + tex_f.x, tex_v.y);
	vertex[2].TexCoord = D3DXVECTOR2(tex_v.x, tex_f.y + tex_v.y);
	vertex[3].TexCoord = D3DXVECTOR2(tex_v.x + tex_f.x, tex_v.y + tex_f.y);

	for (int i = 0; i < NUM_VERTEX; i++)
	{
		vertex[i].Diffuse = D3DXCOLOR(color.r, color.g, color.b, color.a);
	}

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_VERTEX, 0);
}


//=============================================================================
// �X�v���C�g�f�[�^�ݒ�
// ���W�E�T�C�Y�EUV�w��E���_�F�E��]�p�x
//=============================================================================
//����
//texNo : �e�N�X�`���̎��ʔԍ��itexture.h, texture.cpp ��LoadTexture�֐��̖߂�l�j
//pos	; X,Y���W
//size	; �T�C�Y
//tex_v	; �σe�N�X�`�����W
//tex_f	; �Œ�e�N�X�`�����W
//color : ���_�̐F�iRGBA�j
//Rot	: ��]�p�x�i���W�A���l�j
void DrawSpriteColorRotate(int texNo, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 tex_v, D3DXVECTOR2 tex_f, D3DXCOLOR color, float Rot)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	float hw, hh;
	hw = size.x * 0.5f;
	hh = size.x * 0.5f;

	// ���W�ϊ�
	vertex[0].Position.x = (-hw) * cosf(Rot) - (-hh) * sinf(Rot) + pos.x;
	vertex[0].Position.y = (-hw) * sinf(Rot) + (-hh) * cosf(Rot) + pos.y;
	vertex[1].Position.x = ( hw) * cosf(Rot) - (-hh) * sinf(Rot) + pos.x;
	vertex[1].Position.y = ( hw) * sinf(Rot) + (-hh) * cosf(Rot) + pos.y;
	vertex[2].Position.x = (-hw) * cosf(Rot) - ( hh) * sinf(Rot) + pos.x;
	vertex[2].Position.y = (-hw) * sinf(Rot) + ( hh) * cosf(Rot) + pos.y;
	vertex[3].Position.x = ( hw) * cosf(Rot) - ( hh) * sinf(Rot) + pos.x;
	vertex[3].Position.y = ( hw) * sinf(Rot) + ( hh) * cosf(Rot) + pos.y;

	
	vertex[0].Diffuse = color;
	vertex[1].Diffuse = color;
	vertex[2].Diffuse = color;
	vertex[3].Diffuse = color;

	vertex[0].TexCoord = D3DXVECTOR2(tex_v.x, tex_v.y);
	vertex[1].TexCoord = D3DXVECTOR2(tex_v.x + tex_f.x, tex_v.y);
	vertex[2].TexCoord = D3DXVECTOR2(tex_v.x, tex_v.y + tex_f.y);
	vertex[3].TexCoord = D3DXVECTOR2(tex_v.x + tex_f.x, tex_v.y + tex_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_VERTEX, 0);
}

//=============================================================================
// �X�v���C�g�f�[�^�ݒ�
// ���W�E�T�C�Y�EUV�w��E���_�F�E��]�p�x
//=============================================================================
//����
//texNo : �e�N�X�`���̎��ʔԍ��itexture.h, texture.cpp ��LoadTexture�֐��̖߂�l�j
//pos	; X,Y���W
//size	; �T�C�Y
//dis	; ��]������̋���
//tex_v	; �σe�N�X�`�����W
//tex_f	; �Œ�e�N�X�`�����W
//color : ���_�̐F�iRGBA�j
//Rot	: ��]�p�x�i���W�A���l�j
void DrawSpriteColorRotateAxis(int texNo, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 dis,D3DXVECTOR2 tex_v, D3DXVECTOR2 tex_f, D3DXCOLOR color, float Rot)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	float hw, hh;
	hw = size.x * 0.5f;
	hh = size.y * 0.5f;

	//��CX,CY����]���ƍl����
	//��]����(0,0)�̌��_�Ɉړ����邽�߁A��]���̍��W�̕�������`�S�̂̍��W���}�C�i�X���A���̏�Ԃŉ�]���s��

	// ���W�ϊ�
	vertex[0].Position.x = (-dis.x - hw) * cosf(Rot) - (-dis.y - hh) * sinf(Rot);
	vertex[0].Position.y = (-dis.x - hw) * sinf(Rot) + (-dis.y - hh) * cosf(Rot);
	vertex[1].Position.x = (-dis.x + hw) * cosf(Rot) - (-dis.y - hh) * sinf(Rot);
	vertex[1].Position.y = (-dis.x + hw) * sinf(Rot) + (-dis.y - hh) * cosf(Rot);
	vertex[2].Position.x = (-dis.x - hw) * cosf(Rot) - (-dis.y + hh) * sinf(Rot);
	vertex[2].Position.y = (-dis.x - hw) * sinf(Rot) + (-dis.y + hh) * cosf(Rot);
	vertex[3].Position.x = (-dis.x + hw) * cosf(Rot) - (-dis.y + hh) * sinf(Rot);
	vertex[3].Position.y = (-dis.x + hw) * sinf(Rot) + (-dis.y + hh) * cosf(Rot);

	//��]�̕ϊ����I�������Ԃŉ�]���̍��W���v���X���A���_�ɖ߂��B����ɕ\�����W�iX,Y�j�܂ňړ�������
	vertex[0].Position.x += pos.x;
	vertex[0].Position.y += pos.y;
	vertex[1].Position.x += pos.x;
	vertex[1].Position.y += pos.y;
	vertex[2].Position.x += pos.x;
	vertex[2].Position.y += pos.y;
	vertex[3].Position.x += pos.x;
	vertex[3].Position.y += pos.y;

	vertex[0].Diffuse = color;
	vertex[1].Diffuse = color;
	vertex[2].Diffuse = color;
	vertex[3].Diffuse = color;

	vertex[0].TexCoord = D3DXVECTOR2(tex_v.x, tex_v.y);
	vertex[1].TexCoord = D3DXVECTOR2(tex_v.x + tex_f.x, tex_v.y);
	vertex[2].TexCoord = D3DXVECTOR2(tex_v.x, tex_v.y + tex_f.y);
	vertex[3].TexCoord = D3DXVECTOR2(tex_v.x + tex_f.x, tex_v.y + tex_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_VERTEX, 0);
}
//=============================================================================
// �����X�v���C�g�f�[�^�ݒ�i����w��j
// ���W�E�T�C�Y�EUV�w��
//=============================================================================
//����
//texNo : �e�N�X�`���̎��ʔԍ��itexture.h, texture.cpp ��LoadTexture�֐��̖߂�l�j
// pos	: X,Y���W
//size	: �t�H���g�T�C�Y
//color	: ���_�F�ݒ�(RGBA)
void DrawWord(int texNo, D3DXVECTOR2 pos, const char chr[], float size, D3DXCOLOR color)
{
	const char alpha[29] = {
		"a""b""c""d""e""f""g"
		"h""i""j""k""l""m""n"
		"o""p""q""r""s""t""u"
		"v""w""x""y""z"" ""/"
	};
	int chr_len = strlen(chr);
	int chr_n[CHAR_BUF] = {};
	for (int i = 0; i < chr_len; i++)
	{
		for (int j = 0; j < 29; j++)
		{
			if (chr[i] == alpha[j])
			{
				chr_n[i] = j;
			}
		}
	}

	float U, V;
	float old_X = pos.x;

	for (int i = 0; i < chr_len; i++)
	{
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		U = chr_n[i] % CHAR_TEX_PART_X * TEX_PART(CHAR_TEX_PART_X);
		V = chr_n[i] / CHAR_TEX_PART_X * TEX_PART(CHAR_TEX_PART_Y);

		if (chr_n[i] == 27)
		{
			pos.y += size;
			pos.x = old_X;
		}
		else
		{
			// ��������_�Ƃ��Đݒ肷��v���O����
			vertex[0].Position = D3DXVECTOR3(pos.x, pos.y, 0.0f);
			vertex[0].Diffuse = D3DXCOLOR(color.r, color.g, color.b, color.a);
			vertex[0].TexCoord = D3DXVECTOR2(U, V);

			vertex[1].Position = D3DXVECTOR3(pos.x + size, pos.y, 0.0f);
			vertex[1].Diffuse = D3DXCOLOR(color.r, color.g, color.b, color.a);
			vertex[1].TexCoord = D3DXVECTOR2(U + TEX_PART(CHAR_TEX_PART_X), V);

			vertex[2].Position = D3DXVECTOR3(pos.x, pos.y + size, 0.0f);
			vertex[2].Diffuse = D3DXCOLOR(color.r, color.g, color.b, color.a);
			vertex[2].TexCoord = D3DXVECTOR2(U, V + TEX_PART(CHAR_TEX_PART_Y));

			vertex[3].Position = D3DXVECTOR3(pos.x + size, pos.y + size, 0.0f);
			vertex[3].Diffuse = D3DXCOLOR(color.r, color.g, color.b, color.a);
			vertex[3].TexCoord = D3DXVECTOR2(U + TEX_PART(CHAR_TEX_PART_X), V + TEX_PART(CHAR_TEX_PART_Y));

			pos.x += size;
		}

		GetDeviceContext()->Unmap(g_VertexBuffer, 0);

		// ���_�o�b�t�@�ݒ�
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

		// �v���~�e�B�u�g�|���W�ݒ�
		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

		// �|���S���`��
		GetDeviceContext()->Draw(NUM_VERTEX, 0);
	}

}

//=============================================================================
// 1�����X�v���C�g�f�[�^�ݒ�i����w��j
// ���W�E�T�C�Y�EUV�w��
//=============================================================================
//����
//texNo : �e�N�X�`���̎��ʔԍ��itexture.h, texture.cpp ��LoadTexture�֐��̖߂�l�j
// pos	: X,Y���W
//size	: �t�H���g�T�C�Y
//color	: ���_�F�ݒ�(RGBA)
void DrawChar(int texNo, D3DXVECTOR2 pos, const char chr[], float size, D3DXCOLOR color)
{
	std::string alpha = "abcdefghijklmnopqrstuvwxyz /";

	int chr_n;
	for (int j = 0; j < 29; j++)
	{
		if (*chr == alpha[j])
		{
			chr_n = j;
		}
	}

	float U, V;
	float old_X = pos.x;

	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	U = chr_n % CHAR_TEX_PART_X * TEX_PART(CHAR_TEX_PART_X);
	V = chr_n / CHAR_TEX_PART_X * TEX_PART(CHAR_TEX_PART_Y);

	if (chr_n == 27)
	{
		pos.y += size;
		pos.x = old_X;
	}
	else
	{
		// ��������_�Ƃ��Đݒ肷��v���O����
		vertex[0].Position = D3DXVECTOR3(pos.x, pos.y, 0.0f);
		vertex[0].Diffuse = D3DXCOLOR(color.r, color.g, color.b, color.a);
		vertex[0].TexCoord = D3DXVECTOR2(U, V);

		vertex[1].Position = D3DXVECTOR3(pos.x + size, pos.y, 0.0f);
		vertex[1].Diffuse = D3DXCOLOR(color.r, color.g, color.b, color.a);
		vertex[1].TexCoord = D3DXVECTOR2(U + TEX_PART(CHAR_TEX_PART_X), V);

		vertex[2].Position = D3DXVECTOR3(pos.x, pos.y + size, 0.0f);
		vertex[2].Diffuse = D3DXCOLOR(color.r, color.g, color.b, color.a);
		vertex[2].TexCoord = D3DXVECTOR2(U, V + TEX_PART(CHAR_TEX_PART_Y));

		vertex[3].Position = D3DXVECTOR3(pos.x + size, pos.y + size, 0.0f);
		vertex[3].Diffuse = D3DXCOLOR(color.r, color.g, color.b, color.a);
		vertex[3].TexCoord = D3DXVECTOR2(U + TEX_PART(CHAR_TEX_PART_X), V + TEX_PART(CHAR_TEX_PART_Y));

		pos.x += size;
	}

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_VERTEX, 0);

}


//=============================================================================
// 1�����X�v���C�g�f�[�^�ݒ�i���S�w��j
// ���W�E�T�C�Y�EUV�w��
//=============================================================================
//����
//texNo : �e�N�X�`���̎��ʔԍ��itexture.h, texture.cpp ��LoadTexture�֐��̖߂�l�j
// pos	: X,Y���W
//size	: �t�H���g�T�C�Y
//color	: ���_�F�ݒ�(RGBA)
void DrawCharRot(int texNo, D3DXVECTOR2 pos, char chr[], float size, D3DXCOLOR color, float rot)
{
	std::string alpha = "abcdefghijklmnopqrstuvwxyz /";
	int chr_n;
	for (int j = 0; j < 29; j++)
	{
		if (*chr == alpha[j])
		{
			chr_n = j;
		}
	}

	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	float U, V;
	float old_X = pos.x;
	float hs;
	U = chr_n % CHAR_TEX_PART_X * TEX_PART(CHAR_TEX_PART_X);
	V = chr_n / CHAR_TEX_PART_X * TEX_PART(CHAR_TEX_PART_Y);
	hs = size / 2;

	if (chr_n == 27)
	{
		pos.y += size;
		pos.x = old_X;
	}
	else
	{
		// ���W�ϊ�
		vertex[0].Position.x = (-hs) * cosf(rot) - (-hs) * sinf(rot) + pos.x;
		vertex[0].Position.y = (-hs) * sinf(rot) + (-hs) * cosf(rot) + pos.y;
		vertex[1].Position.x = (hs)*cosf(rot) - (-hs) * sinf(rot) + pos.x;
		vertex[1].Position.y = (hs)*sinf(rot) + (-hs) * cosf(rot) + pos.y;
		vertex[2].Position.x = (-hs) * cosf(rot) - (hs)*sinf(rot) + pos.x;
		vertex[2].Position.y = (-hs) * sinf(rot) + (hs)*cosf(rot) + pos.y;
		vertex[3].Position.x = (hs)*cosf(rot) - (hs)*sinf(rot) + pos.x;
		vertex[3].Position.y = (hs)*sinf(rot) + (hs)*cosf(rot) + pos.y;

		// ���_�J���[
		vertex[0].Diffuse = D3DXCOLOR(color.r, color.g, color.b, color.a);
		vertex[1].Diffuse = D3DXCOLOR(color.r, color.g, color.b, color.a);
		vertex[2].Diffuse = D3DXCOLOR(color.r, color.g, color.b, color.a);
		vertex[3].Diffuse = D3DXCOLOR(color.r, color.g, color.b, color.a);

		// �e�b�N�X�R�[�h
		vertex[0].TexCoord = D3DXVECTOR2(U, V);
		vertex[1].TexCoord = D3DXVECTOR2(U + TEX_PART(CHAR_TEX_PART_X), V);
		vertex[2].TexCoord = D3DXVECTOR2(U, V + TEX_PART(CHAR_TEX_PART_Y));
		vertex[3].TexCoord = D3DXVECTOR2(U + TEX_PART(CHAR_TEX_PART_X), V + TEX_PART(CHAR_TEX_PART_Y));

		pos.x += size;
	}

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_VERTEX, 0);

}