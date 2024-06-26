//=============================================================================
//
// メッシュ山処理 [meshmountain.cpp]
// Author : 切田海畝斗
//
//=============================================================================
#include "meshmountain.h"
#include "Texture.h"
#include "material.h"
#include "sprite.h"

//=============================================================================
// 引数付きコンストラクタ
//=============================================================================
Mountain::Mountain(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR2 size, int numBlockH, int numBlockV, D3DXVECTOR2 uv)
	:Base_Object(background, pos, rot, NO_VECTOR3, NO_VECTOR3, { 1.0f,1.0f,1.0f,1.0f }, true)
{
	ID3D11Device* pDevice = GetDevice();

	// マテリアル設定
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = RefColor();
	GetMaterial()->Ambient = { 0.0f,0.0f,0.0f,0.0f };
	GetMaterial()->Emission = { 0.0f,0.0f,0.0f,0.0f };
	GetMaterial()->noTexSampling = 0;

	// 頂点数の設定
	m_Mesh.m_NumVertex = (numBlockH + 1) * (numBlockV + 1);

	// インデックス数の設定
	m_Mesh.m_NumIndex = (numBlockH + 1) * (numBlockV * 2) + (numBlockV - 1);

	// 一時頂点配列を生成
	VERTEX_3D* pVertexWk = new VERTEX_3D[m_Mesh.m_NumVertex];

	// 一時インデックス配列を生成
	int* pIndexWk = new int[m_Mesh.m_NumIndex];

	// 頂点配列の中身を埋める
	VERTEX_3D* pVtx = pVertexWk;
	const float ANGLE_H = (D3DX_PI * 2) / numBlockH;

	for (int vt = 0; vt < (numBlockV + 1); vt++) {
		for (int hr = 0; hr < (numBlockH + 1); hr++) {
			// 頂点座標の設定
			pVtx->Position.x = sinf(ANGLE_H * hr) * size.x;
			pVtx->Position.y = vt * size.y;
			pVtx->Position.z = cosf(ANGLE_H * hr) * size.x;

			// 法線の設定
			pVtx->Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// 反射光の設定
			pVtx->Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx->TexCoord.x = hr * uv.x;
			pVtx->TexCoord.y = 0.975f - vt * 0.95f * uv.y;

			pVtx++;
		}
	}

	// インデックス配列の中身を埋める
	int* pIdx = pIndexWk;

	for (int vt = 0; vt < numBlockV; vt++) {
		for (int hr = 0; hr < (numBlockH + 1); hr++) {
			*pIdx = vt * (numBlockH + 1) + hr;
			pIdx++;

			*pIdx = (vt + 1) * (numBlockH + 1) + hr;
			pIdx++;
		}
	}

	// 頂点バッファ生成
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


	// インデックスバッファ生成
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(int) * m_Mesh.m_NumIndex;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;

	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = pIndexWk;

	GetDevice()->CreateBuffer(&bd, &sd, &m_Mesh.m_IndexBuffer);


	// 一時配列の解放
	delete[] pIndexWk;
	delete[] pVertexWk;
}

//=============================================================================
// デストラクタ
//=============================================================================
Mountain::~Mountain()
{
	//インデックスバッファの解放
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
void Mountain::Update(void)
{
}

//=============================================================================
// 描画
//=============================================================================
void Mountain::Draw(void)
{
	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &m_Mesh.m_VertexBuffer, &stride, &offset);

	// インデックスバッファ設定
	GetDeviceContext()->IASetIndexBuffer(m_Mesh.m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// マテリアル設定
	SetMaterial(*GetMaterial());

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(RefImageMaterial().m_Mountain));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(GetMtx());

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,RefRot().y,RefRot().x,RefRot().z);
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
void Mountain::CollDispatch(Base_Object* pObj)
{
}
