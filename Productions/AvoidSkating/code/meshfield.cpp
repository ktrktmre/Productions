//=============================================================================
//
// メッシュ地面の処理 [meshfield.cpp]
// Author : 切田海畝斗
//
//=============================================================================
#include "main.h"
#include "texture.h"
#include "meshfield.h"
#include "sprite.h"
#include "material.h"

//=============================================================================
// 引数付きコンストラクタ
//=============================================================================
Field::Field(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, int numBlockX, int numBlockZ)
	:Base_Object(background, pos, rot, scl, { 0.0f,0.0f,0.0f }, {1.0f,1.0f,1.0f,1.0f},true)
{
	m_Mesh.m_NumVertex = (numBlockX + 1) * (numBlockZ + 1);
	m_Mesh.m_NumIndex = (numBlockX + 1) * 2 * numBlockZ + (numBlockZ - 1) * 2;

	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * m_Mesh.m_NumVertex;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	GetDevice()->CreateBuffer(&bd, NULL, &m_Mesh.m_VertexBuffer);


	// インデックスバッファ生成
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(unsigned short) * m_Mesh.m_NumIndex;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	GetDevice()->CreateBuffer(&bd, NULL, &m_Mesh.m_IndexBuffer);


	{//頂点バッファの中身を埋める

		// 頂点バッファへのポインタを取得
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(m_Mesh.m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

		for (int y = 0; y < (numBlockZ + 1); y++)
		{
			for (int x = 0; x < (numBlockX + 1); x++)
			{
				//配列のインデックスを計算する
				int i = y * (numBlockX + 1) + x;

				// 頂点座標の設定
				pVtx[i].Position = D3DXVECTOR3(-(numBlockX / 2.0f) * scl.x + x * scl.x, 0.0f, (numBlockZ / 2.0f) * scl.z - y * scl.z);
				// UV値の設定
				pVtx[i].TexCoord = D3DXVECTOR2(x * 1.0f, y * 1.0f);

				// 法線の設定
				pVtx[i].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				// 頂点カラーの設定
				pVtx[i].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
		}
		GetDeviceContext()->Unmap(m_Mesh.m_VertexBuffer, 0);
	}

	{//インデックスバッファの中身を埋める

		// インデックスバッファのポインタを取得
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(m_Mesh.m_IndexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		unsigned short* pIdx = (unsigned short*)msr.pData;

		int idx = 0;

		for (int y = 0; y < numBlockZ; y++)
		{
			//y行目のポリゴンのインデックス
			for (int x = 0; x < (numBlockX + 1); x++)
			{
				pIdx[idx] = (numBlockX + 1) + x + (numBlockX + 1) * y;
				idx++;
				pIdx[idx] = 0 + x + (numBlockX + 1) * y;
				idx++;
			}

			//縮退ポリゴン分のインデックス
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

	// マテリアル設定
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = RefColor();
	GetMaterial()->Ambient = { 0.0f,0.0f,0.0f,0.0f };
	GetMaterial()->Emission = { 0.0f,0.0f,0.0f,0.0f };
	GetMaterial()->noTexSampling = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
Field::~Field()
{
	// インデックスバッファの解放
	if (m_Mesh.m_IndexBuffer != NULL)
	{
		m_Mesh.m_IndexBuffer->Release();
		m_Mesh.m_IndexBuffer = NULL;
	}

	//頂点バッファの解放
	if (m_Mesh.m_VertexBuffer != NULL)
	{
		m_Mesh.m_VertexBuffer->Release();
		m_Mesh.m_VertexBuffer = NULL;
	}
}

//=============================================================================
// 更新
//=============================================================================
void Field::Update(void)
{
}

//=============================================================================
// 描画
//=============================================================================
void Field::Draw(void)
{
	SetCullingMode(CULL_MODE_BACK);

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &m_Mesh.m_VertexBuffer, &stride, &offset);

	// インデックスバッファ設定
	GetDeviceContext()->IASetIndexBuffer(m_Mesh.m_IndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// マテリアル設定
	SetMaterial(*GetMaterial());

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(RefImageMaterial().m_Lane));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(GetMtx());

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, RefRot().y, RefRot().x, RefRot().z);
	D3DXMatrixMultiply(GetMtx(), GetMtx(), &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, RefPos().x, RefPos().y, RefPos().z);
	D3DXMatrixMultiply(GetMtx(), GetMtx(), &mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(GetMtx());

	// ポリゴンの描画
	GetDeviceContext()->DrawIndexed(m_Mesh.m_NumIndex, 0, 0);
}
//=============================================================================
// 衝突判定ディスパッチ
//=============================================================================
void Field::CollDispatch(Base_Object* pObj)
{
}
