//=============================================================================
//
// メッシュ空の処理 [meshsky.cpp]
// Author : 切田海畝斗
//
//=============================================================================
#include "meshsky.h"
#include "Texture.h"
#include "material.h"
#include "sprite.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	SKY_HEIGHT_RATE			(2.0f)		// 空ドームの高さ係数
#define	TEX_COUNT_LOOP			(1)			// テクスチャの繰り返し回数

//=============================================================================
// 引数付きコンストラクタ
//=============================================================================
Sky::Sky(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float radius, int numBlockH, int numBlockV, bool reverse)
	:Base_Object(background, pos, rot, NO_VECTOR3, NO_VECTOR3, { 1.0f,1.0f,1.0f,1.0f }, true)
{
	ID3D11Device* pDevice = GetDevice();

	m_TransParent = false;
	m_Reverse = reverse;

	// マテリアル設定
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = RefColor();
	GetMaterial()->Ambient = { 0.0f,0.0f,0.0f,0.0f };
	GetMaterial()->Emission = { 0.0f,0.0f,0.0f,0.0f };
	GetMaterial()->noTexSampling = 0;

	// 頂点数の設定
	m_Mesh[0].m_NumVertex = (numBlockH + 1) * (numBlockV + 1);
	m_Mesh[1].m_NumVertex = numBlockH + 1;

	// インデックス数の設定
	m_Mesh[0].m_NumIndex = (numBlockH * (numBlockV * 2) + numBlockV * 2 + (numBlockV - 1) * 2);
	m_Mesh[1].m_NumIndex = numBlockH * 3;

	// 一時頂点配列を生成
	VERTEX_3D* pVertexWk = new VERTEX_3D[m_Mesh[0].m_NumVertex];
	VERTEX_3D* pVertexTopWk = new VERTEX_3D[m_Mesh[1].m_NumVertex];

	// 一時インデックス配列を生成
	int* pIndexWk = new int[m_Mesh[0].m_NumIndex];
	int* pIndexTopWk = new int[m_Mesh[1].m_NumIndex];

	// 頂点配列の中身を埋める
	VERTEX_3D* pVtx = pVertexWk;
	const float ANGLE_H = (D3DX_PI * 2) / numBlockH;
	const float ANGLE_V = (D3DX_PI / 8) / (numBlockV + 1);
	const float WIDTH = 1.0f / numBlockH;
	const float HEIGHT = 1.0f / numBlockV;
	float lengthXZ;

	for (int vt = 0; vt < (numBlockV + 1); vt++) {
		lengthXZ = cosf(ANGLE_V * vt) * radius;

		for (int hr = 0; hr < (numBlockH + 1); hr++) {
			// 頂点座標の設定
			pVtx->Position.x = sinf(ANGLE_H * hr) * lengthXZ;
			if (m_Reverse) {
				pVtx->Position.y = -sinf(ANGLE_V * vt) * radius * SKY_HEIGHT_RATE;
			}
			else {
				pVtx->Position.y = sinf(ANGLE_V * vt) * radius * SKY_HEIGHT_RATE;
			}
			pVtx->Position.z = cosf(ANGLE_H * hr) * lengthXZ;

			// 法線の設定
			pVtx->Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// 反射光の設定
			if (m_Reverse) {
				pVtx->Diffuse = D3DXCOLOR(0.0625f, 0.0625f, 0.375f, 0.5f);
			}
			else {
				pVtx->Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}

			// テクスチャ座標の設定
			pVtx->TexCoord.x = hr * WIDTH * TEX_COUNT_LOOP;
			if (vt == numBlockV) {
				pVtx->TexCoord.y = 0.01f;
			}
			else {
				pVtx->TexCoord.y = 1.0f - vt * HEIGHT;
			}

			pVtx++;
		}
	}

	pVtx = pVertexTopWk;

	// 頂点座標の設定
	pVtx->Position.x = 0.0f;
	if (m_Reverse) {
		pVtx->Position.y = -sinf(ANGLE_V * (numBlockV + 1)) * radius * SKY_HEIGHT_RATE;
	}
	else {
		pVtx->Position.y = sinf(ANGLE_V * (numBlockV + 1)) * radius * SKY_HEIGHT_RATE;
	}
	pVtx->Position.z = 0.0f;

	// 法線の設定
	pVtx->Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// 頂点カラーの設定
	if (m_Reverse) {
		pVtx->Diffuse = D3DXCOLOR(0.0675f, 0.0675f, 0.375f, 0.5f);
	}
	else {
		pVtx->Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	// テクスチャ座標の設定
	pVtx->TexCoord.x = 0.01f;
	pVtx->TexCoord.y = 0.01f;

	pVtx++;

	lengthXZ = cosf(ANGLE_V * numBlockV) * radius;
	for (int hr = 0; hr < numBlockH; hr++) {
		// 頂点座標の設定
		pVtx->Position.x = -sinf(ANGLE_H * hr) * lengthXZ;
		if (m_Reverse) {
			pVtx->Position.y = -sinf(ANGLE_V * numBlockV) * radius * SKY_HEIGHT_RATE;
		}
		else {
			pVtx->Position.y = sinf(ANGLE_V * numBlockV) * radius * SKY_HEIGHT_RATE;
		}
		pVtx->Position.z = cosf(ANGLE_H * hr) * lengthXZ;

		// 法線の設定
		pVtx->Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// 頂点カラーの設定
		if (m_Reverse) {
			pVtx->Diffuse = D3DXCOLOR(0.0675f, 0.0675f, 0.375f, 0.5f);
		}
		else {
			pVtx->Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		// テクスチャ座標の設定
		pVtx->TexCoord.x = 0.01f;
		pVtx->TexCoord.y = 0.01f;

		pVtx++;
	}

	// インデックス配列の中身を埋める
	int* pIdx = pIndexWk;

	for (int vt = 0; vt < numBlockV; vt++) {
		if (vt != 0) {
			*pIdx = vt * (numBlockH + 1);
			pIdx++;
		}

		for (int hr = 0; hr < numBlockH + 1; hr++) {
			*pIdx = vt * (numBlockH + 1) + hr;
			pIdx++;

			*pIdx = (vt + 1) * (numBlockH + 1) + hr;
			pIdx++;
		}

		if (vt != (numBlockV - 1)) {
			*pIdx = (vt + 1) * (numBlockH + 1);
			pIdx++;
		}
	}

	pIdx = pIndexTopWk;
	for (int hr = 1; hr < numBlockH + 1; hr++) {
		*pIdx = 0;
		++pIdx;
		*pIdx = hr;
		++pIdx;
		if (hr < numBlockH) {
			*pIdx = hr + 1;
		}
		else {
			*pIdx = 1;
		}
		++pIdx;
	}

	//周回部分の頂点バッファ・インデックスバッファ作成
	{
		// 頂点バッファ生成
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * m_Mesh[0].m_NumVertex;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = pVertexWk;

		GetDevice()->CreateBuffer(&bd, &sd, &m_Mesh[0].m_VertexBuffer);

		// インデックスバッファ生成
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(int) * m_Mesh[0].m_NumIndex;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = pIndexWk;

		GetDevice()->CreateBuffer(&bd, &sd, &m_Mesh[0].m_IndexBuffer);
	}

	//天頂部分の頂点バッファ・インデックスバッファ作成
	{
		// 頂点バッファ生成
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3D) * m_Mesh[1].m_NumVertex;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = pVertexTopWk;

		GetDevice()->CreateBuffer(&bd, &sd, &m_Mesh[1].m_VertexBuffer);

		// インデックスバッファ生成
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(int) * m_Mesh[1].m_NumIndex;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = pIndexTopWk;

		GetDevice()->CreateBuffer(&bd, &sd, &m_Mesh[1].m_IndexBuffer);
	}

	// 一時配列を解放
	delete[] pIndexTopWk;
	delete[] pIndexWk;
	delete[] pVertexTopWk;
	delete[] pVertexWk;
}

//=============================================================================
// デストラクタ
//=============================================================================
Sky::~Sky()
{
	// 周回部分メッシュの解放
	if (m_Mesh[0].m_IndexBuffer != NULL)
	{
		m_Mesh[0].m_IndexBuffer->Release();
		m_Mesh[0].m_IndexBuffer = NULL;
	}

	if (m_Mesh[0].m_VertexBuffer != NULL)
	{
		m_Mesh[0].m_VertexBuffer->Release();
		m_Mesh[0].m_VertexBuffer = NULL;
	}

	// 天頂部分メッシュの解放
	if (m_Mesh[1].m_IndexBuffer != NULL)
	{
		m_Mesh[1].m_IndexBuffer->Release();
		m_Mesh[1].m_IndexBuffer = NULL;
	}

	if (m_Mesh[1].m_VertexBuffer != NULL)
	{
		m_Mesh[1].m_VertexBuffer->Release();
		m_Mesh[1].m_VertexBuffer = NULL;
	}
}

//=============================================================================
// 更新
//=============================================================================
void Sky::Update(void)
{
}

//=============================================================================
// 描画
//=============================================================================
void Sky::Draw(void)
{
	if (m_Reverse)
	{
		SetCullingMode(CULL_MODE_FRONT);	// 前面カリング
	}
	else
	{
		SetCullingMode(CULL_MODE_BACK);		// 背面カリング
	}

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(RefImageMaterial().m_SkyNight));

	//周回部分の描画
	{
		// 頂点バッファ設定
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		GetDeviceContext()->IASetVertexBuffers(0, 1, &m_Mesh[0].m_VertexBuffer, &stride, &offset);

		// インデックスバッファ設定
		GetDeviceContext()->IASetIndexBuffer(m_Mesh[0].m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		// プリミティブトポロジ設定
		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// マテリアル設定
		SetMaterial(*GetMaterial());


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
		GetDeviceContext()->DrawIndexed(m_Mesh[0].m_NumIndex, 0, 0);
	}

	//天頂部分の描画
	{
		// 頂点バッファ設定
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		GetDeviceContext()->IASetVertexBuffers(0, 1, &m_Mesh[1].m_VertexBuffer, &stride, &offset);

		// インデックスバッファ設定
		GetDeviceContext()->IASetIndexBuffer(m_Mesh[1].m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		// プリミティブトポロジ設定
		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// マテリアル設定
		SetMaterial(*GetMaterial());


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
		GetDeviceContext()->DrawIndexed(m_Mesh[1].m_NumIndex, 0, 0);
	}

	SetCullingMode(CULL_MODE_BACK);		// 背面カリング
}
//=============================================================================
// 衝突判定ディスパッチ
//=============================================================================
void Sky::CollDispatch(Base_Object* pObj)
{
}
