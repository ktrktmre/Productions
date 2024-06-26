//=============================================================================
//
// スプライト処理 [sprite.cpp]
// Author : 切田海畝斗
//
//=============================================================================
#include "main.h"
#include "base_object.h"
#include "sprite.h"
#include "renderer.h"
#include "Texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	NUM_2DVERTEX		(4)							// 頂点数

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer* g_VertexBuffer = NULL;	// 頂点情報
Camera* g_GameCamera = nullptr;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitSprite(void)
{
	// 頂点バッファ生成
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
// 終了処理
//=============================================================================
void UninitSprite(void)
{
	// 頂点バッファの解放
	if (g_VertexBuffer) {
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
}

//=============================================================================
// カメラの登録
//=============================================================================
void RegisterCamera(Camera* pCmamera)
{
	g_GameCamera = pCmamera;
}

//=============================================================================
// カメラの解放
//=============================================================================
void ReleaseCamera(void)
{
	g_GameCamera = nullptr;
}


//=============================================================================
// 画面描画(中心指定)
//=============================================================================
void DrawScreen(UI ui, int& tex)
{

	// 頂点バッファへのポインタを取得
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;


	float hw, hh;
	hw = ui.m_Scl.x * 0.5f;
	hh = ui.m_Scl.y * 0.5f;

	// 座標変換
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

	// 頂点バッファ設定
	UINT	 stride = sizeof(VERTEX_3D);
	UINT	 offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// マテリアルのセット
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = { 1.0f,1.0f,1.0f,1.0f };
	material.noTexSampling = 0;
	SetMaterial(material);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));

	// ライト
	SetLightEnable(false);

	// マトリクス設定
	SetWorldViewProjection2D();//座標の2D変換

	// 2D描画なので深度無効
	SetDepthEnable(false);

	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	// Z比較あり
	SetDepthEnable(true);

	// ライト
	SetLightEnable(true);

	g_GameCamera->SetCamera();
}

//=============================================================================
// 画面描画(左上指定)
//=============================================================================
void DrawScreenLT(UI ui, int& tex)
{

	// 頂点バッファへのポインタを取得
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;


	float hw, hh;
	hw = ui.m_Scl.x;
	hh = ui.m_Scl.y;

	// 座標変換
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

	// 頂点バッファ設定
	UINT	 stride = sizeof(VERTEX_3D);
	UINT	 offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// マテリアルのセット
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = { 1.0f,1.0f,1.0f,1.0f };
	material.noTexSampling = 0;
	SetMaterial(material);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));

	// ライト
	SetLightEnable(false);

	// マトリクス設定
	SetWorldViewProjection2D();//座標の2D変換

	// 2D描画なので深度無効
	SetDepthEnable(false);

	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	// Z比較あり
	SetDepthEnable(true);

	// ライト
	SetLightEnable(true);

	g_GameCamera->SetCamera();
}

//=============================================================================
// ポリゴン描画(中心下指定)
//=============================================================================
void DrawPolygon(Base_Object& obj,const int& tex, const D3DXVECTOR2 uv_v, const D3DXVECTOR2 uv_f)
{
	//αテストを有効化
	SetAlphaTestEnable(true);

	// 頂点バッファへのポインタを取得
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

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// マテリアルのセット
	SetMaterial(*obj.GetMaterial());

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(obj.GetMtx());

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.RefRot().y, obj.RefRot().x, obj.RefRot().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(obj.GetMtx());

	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//αテストを有効化
	SetAlphaTestEnable(false);
}

//=============================================================================
// ポリゴン描画(中心指定)
//=============================================================================
void DrawPolygonCR(Base_Object& obj, const int& tex, const D3DXVECTOR2 uv_v, const D3DXVECTOR2 uv_f)
{
	//αテストを有効化
	SetAlphaTestEnable(true);

	// 頂点バッファへのポインタを取得
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

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// マテリアルのセット
	SetMaterial(*obj.GetMaterial());

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(obj.GetMtx());

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.RefRot().y, obj.RefRot().x, obj.RefRot().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(obj.GetMtx());

	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//αテストを有効化
	SetAlphaTestEnable(false);

}

//=============================================================================
// ポリゴン描画(左上指定)
//=============================================================================
void DrawPolygonLT(Base_Object& obj, const int& tex, const D3DXVECTOR2 uv_v, const D3DXVECTOR2 uv_f)
{
	//αテストを有効化
	SetAlphaTestEnable(true);

	// 頂点バッファへのポインタを取得
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

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// マテリアルのセット
	SetMaterial(*obj.GetMaterial());

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(obj.GetMtx());

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.RefRot().y, obj.RefRot().x, obj.RefRot().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(obj.GetMtx());

	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//αテストを有効化
	SetAlphaTestEnable(false);
}

//=============================================================================
// ポリゴン描画XZ平面(中心下指定)
//=============================================================================
void DrawPolygonZ(Base_Object& obj, const int& tex, const D3DXVECTOR2 uv_v, const D3DXVECTOR2 uv_f)
{
	//αテストを有効化
	SetAlphaTestEnable(true);

	// 頂点バッファへのポインタを取得
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

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// マテリアルのセット
	SetMaterial(*obj.GetMaterial());

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(obj.GetMtx());

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.RefRot().y, obj.RefRot().x, obj.RefRot().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(obj.GetMtx());

	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//αテストを有効化
	SetAlphaTestEnable(false);
}

//=============================================================================
// ポリゴン描画XZ平面(中心指定)
//=============================================================================
void DrawPolygonZCR(Base_Object& obj, const int& tex, const D3DXVECTOR2 uv_v, const D3DXVECTOR2 uv_f)
{
	//αテストを有効化
	SetAlphaTestEnable(true);

	// 頂点バッファへのポインタを取得
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

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// マテリアルのセット
	SetMaterial(*obj.GetMaterial());

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(obj.GetMtx());

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.RefRot().y, obj.RefRot().x, obj.RefRot().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(obj.GetMtx());

	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//αテストを有効化
	SetAlphaTestEnable(false);
}

//=============================================================================
// ポリゴン描画XZ平面(左上指定)
//=============================================================================
void DrawPolygonZLT(Base_Object& obj, const int& tex, const D3DXVECTOR2 uv_v, const D3DXVECTOR2 uv_f)
{
	//αテストを有効化
	SetAlphaTestEnable(true);

	// 頂点バッファへのポインタを取得
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

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// マテリアルのセット
	SetMaterial(*obj.GetMaterial());

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(obj.GetMtx());

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.RefRot().y, obj.RefRot().x, obj.RefRot().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(obj.GetMtx());

	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//αテストを有効化
	SetAlphaTestEnable(false);
}

//=============================================================================
// ポリゴンビルボード描画(中心下指定)
//=============================================================================
void DrawPolygonBill(Base_Object& obj,const int& tex, const D3DXVECTOR2 uv_v, const D3DXVECTOR2 uv_f)
{
	//αテストを有効化
	SetAlphaTestEnable(true);

	// 頂点バッファへのポインタを取得
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

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// マテリアルのセット
	SetMaterial(*obj.GetMaterial());

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(obj.GetMtx());

	
	//ビューマトリックスの逆行列を取得
	*obj.GetMtx() = g_GameCamera->RefMtxInvView();
	obj.GetMtx()->_41 = 0.0f;
	obj.GetMtx()->_42 = 0.0f;
	obj.GetMtx()->_43 = 0.0f;

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(obj.GetMtx());

	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//αテストを有効化
	SetAlphaTestEnable(false);
}

//=============================================================================
// ポリゴンビルボード描画(中心指定)
//=============================================================================
void DrawPolygonBillCR(Base_Object& obj, const int& tex, const D3DXVECTOR2 uv_v, const D3DXVECTOR2 uv_f)
{
	//αテストを有効化
	SetAlphaTestEnable(true);

	// 頂点バッファへのポインタを取得
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

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// マテリアルのセット
	SetMaterial(*obj.GetMaterial());

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(obj.GetMtx());

	
	//ビューマトリックスの逆行列を取得
	*obj.GetMtx() = g_GameCamera->RefMtxInvView();
	obj.GetMtx()->_41 = 0.0f;
	obj.GetMtx()->_42 = 0.0f;
	obj.GetMtx()->_43 = 0.0f;

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(obj.GetMtx());

	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//αテストを有効化
	SetAlphaTestEnable(false);
}

//=============================================================================
// ポリゴンビルボード描画(左上指定)
//=============================================================================
void DrawPolygonBillLT(Base_Object& obj, const int& tex, const D3DXVECTOR2 uv_v, const D3DXVECTOR2 uv_f)
{
	//αテストを有効化
	SetAlphaTestEnable(true);

	// 頂点バッファへのポインタを取得
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

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// マテリアルのセット
	SetMaterial(*obj.GetMaterial());

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(obj.GetMtx());

	
	//ビューマトリックスの逆行列を取得
	*obj.GetMtx() = g_GameCamera->RefMtxInvView();
	obj.GetMtx()->_41 = 0.0f;
	obj.GetMtx()->_42 = 0.0f;
	obj.GetMtx()->_43 = 0.0f;

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(obj.GetMtx());

	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//αテストを有効化
	SetAlphaTestEnable(false);
}

//=============================================================================
// ポリゴンビルボード描画(中心下指定)
//=============================================================================
void DrawPolygonAnyBill(Base_Object& obj, const int& tex, const D3DXVECTOR2 uv_v, const D3DXVECTOR2 uv_f, bool InX, bool InY, bool InZ)
{
	//αテストを有効化
	SetAlphaTestEnable(true);

	// 頂点バッファへのポインタを取得
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
	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// マテリアルのセット
	SetMaterial(*obj.GetMaterial());

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(obj.GetMtx());

	
	//任意の軸の転置行列
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

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(obj.GetMtx());

	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//αテストを有効化
	SetAlphaTestEnable(false);
}

//=============================================================================
// ポリゴンビルボード描画(中心指定)
//=============================================================================
void DrawPolygonAnyBillCR(Base_Object& obj, const int& tex, const D3DXVECTOR2 uv_v, const D3DXVECTOR2 uv_f, bool InX, bool InY, bool InZ)
{
	//αテストを有効化
	SetAlphaTestEnable(true);

	// 頂点バッファへのポインタを取得
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
	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// マテリアルのセット
	SetMaterial(*obj.GetMaterial());

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(obj.GetMtx());

	
	//任意の軸の転置行列
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

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(obj.GetMtx());

	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//αテストを有効化
	SetAlphaTestEnable(false);
}

//=============================================================================
// ポリゴンビルボード描画(左上指定)
//=============================================================================
void DrawPolygonAnyBillLT(Base_Object& obj, const int& tex, const D3DXVECTOR2 uv_v, const D3DXVECTOR2 uv_f, bool InX, bool InY, bool InZ)
{
	//αテストを有効化
	SetAlphaTestEnable(true);

	// 頂点バッファへのポインタを取得
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
	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// マテリアルのセット
	SetMaterial(*obj.GetMaterial());

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(obj.GetMtx());

	
	//任意の軸の転置行列
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

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(obj.GetMtx());

	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//αテストを有効化
	SetAlphaTestEnable(false);
}

//=============================================================================
// モデル描画
//=============================================================================
void Draw3DModel(Base_Object& obj, DX11_MODEL& model)
{
	// マテリアル設定
	SetMaterial(*obj.GetMaterial());

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &model.VertexBuffer, &stride, &offset);

	// インデックスバッファ設定
	GetDeviceContext()->IASetIndexBuffer(model.IndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ワールドマトリックスの初期化（単位行列を作る関数）
	D3DXMatrixIdentity(obj.GetMtx());

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, obj.RefScl().x, obj.RefScl().y, obj.RefScl().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.RefRot().y, obj.RefRot().x, obj.RefRot().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, obj.RefPos().x, obj.RefPos().y, obj.RefPos().z);
	D3DXMatrixMultiply(obj.GetMtx(), obj.GetMtx(), &mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(obj.GetMtx());

	for (unsigned short i = 0; i < model.SubsetNum; i++)
	{

		// テクスチャ設定
		if (model.SubsetArray[i].Material.Material.noTexSampling == 0)
			GetDeviceContext()->PSSetShaderResources(0, 1, &model.SubsetArray[i].Material.Texture);

		// ポリゴン描画
		GetDeviceContext()->DrawIndexed(model.SubsetArray[i].IndexNum, model.SubsetArray[i].StartIndex, 0);
	}
}

//---------------------------------
// デバック用
//---------------------------------
void DrawPolygon(Object obj, const int& tex)
{
	//αテストを有効化
	SetAlphaTestEnable(true);

	// 頂点バッファへのポインタを取得
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

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// マテリアルのセット
	SetMaterial(obj.m_Material);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&obj.m_Mtx);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, obj.m_Scl.x, obj.m_Scl.y, obj.m_Scl.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.m_Rot.y, obj.m_Rot.x, obj.m_Rot.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, obj.m_Pos.x, obj.m_Pos.y, obj.m_Pos.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(&obj.m_Mtx);

	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//αテストを有効化
	SetAlphaTestEnable(false);
}
void DrawPolygonCR(Object obj, const int& tex)
{
	//αテストを有効化
	SetAlphaTestEnable(true);

	// 頂点バッファへのポインタを取得
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

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// マテリアルのセット
	SetMaterial(obj.m_Material);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&obj.m_Mtx);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, obj.m_Scl.x, obj.m_Scl.y, obj.m_Scl.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.m_Rot.y, obj.m_Rot.x, obj.m_Rot.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, obj.m_Pos.x, obj.m_Pos.y, obj.m_Pos.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(&obj.m_Mtx);

	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//αテストを有効化
	SetAlphaTestEnable(false);
}
void DrawPolygonLT(Object obj, const int& tex)
{
	//αテストを有効化
	SetAlphaTestEnable(true);

	// 頂点バッファへのポインタを取得
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

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// マテリアルのセット
	SetMaterial(obj.m_Material);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&obj.m_Mtx);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, obj.m_Scl.x, obj.m_Scl.y, obj.m_Scl.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.m_Rot.y, obj.m_Rot.x, obj.m_Rot.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, obj.m_Pos.x, obj.m_Pos.y, obj.m_Pos.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(&obj.m_Mtx);

	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//αテストを有効化
	SetAlphaTestEnable(false);
}
void DrawPolygonBill(Object obj, const int& tex)
{
	//αテストを有効化
	SetAlphaTestEnable(true);

	// 頂点バッファへのポインタを取得
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

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// マテリアルのセット
	SetMaterial(obj.m_Material);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&obj.m_Mtx);

	//ビューマトリックスの逆行列を取得
	obj.m_Mtx = g_GameCamera->RefMtxInvView();
	obj.m_Mtx._41 = 0.0f;
	obj.m_Mtx._42 = 0.0f;
	obj.m_Mtx._43 = 0.0f;

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.m_Rot.y, obj.m_Rot.x, obj.m_Rot.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, obj.m_Pos.x, obj.m_Pos.y, obj.m_Pos.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(&obj.m_Mtx);

	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//αテストを有効化
	SetAlphaTestEnable(false);
}
void DrawPolygonBillCR(Object obj, const int& tex)
{
	//αテストを有効化
	SetAlphaTestEnable(true);

	// 頂点バッファへのポインタを取得
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

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// マテリアルのセット
	SetMaterial(obj.m_Material);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&obj.m_Mtx);

	
	//ビューマトリックスの逆行列を取得
	obj.m_Mtx = g_GameCamera->RefMtxInvView();
	obj.m_Mtx._41 = 0.0f;
	obj.m_Mtx._42 = 0.0f;
	obj.m_Mtx._43 = 0.0f;

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.m_Rot.y, obj.m_Rot.x, obj.m_Rot.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, obj.m_Pos.x, obj.m_Pos.y, obj.m_Pos.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(&obj.m_Mtx);

	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//αテストを有効化
	SetAlphaTestEnable(false);
}
void DrawPolygonBillLT(Object obj, const int& tex)
{
	//αテストを有効化
	SetAlphaTestEnable(true);

	// 頂点バッファへのポインタを取得
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

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// マテリアルのセット
	SetMaterial(obj.m_Material);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&obj.m_Mtx);

	
	//ビューマトリックスの逆行列を取得
	obj.m_Mtx = g_GameCamera->RefMtxInvView();
	obj.m_Mtx._41 = 0.0f;
	obj.m_Mtx._42 = 0.0f;
	obj.m_Mtx._43 = 0.0f;

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.m_Rot.y, obj.m_Rot.x, obj.m_Rot.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, obj.m_Pos.x, obj.m_Pos.y, obj.m_Pos.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(&obj.m_Mtx);

	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//αテストを有効化
	SetAlphaTestEnable(false);
}
void DrawPolygonAnyBill(Object obj, const int& tex, bool InX, bool InY, bool InZ)
{
	//αテストを有効化
	SetAlphaTestEnable(true);

	// 頂点バッファへのポインタを取得
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

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// マテリアルのセット
	SetMaterial(obj.m_Material);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&obj.m_Mtx);

	
	//任意の軸の転置行列
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

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, obj.m_Scl.x, obj.m_Scl.y, obj.m_Scl.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.m_Rot.y, obj.m_Rot.x, obj.m_Rot.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, obj.m_Pos.x, obj.m_Pos.y, obj.m_Pos.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(&obj.m_Mtx);

	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//αテストを有効化
	SetAlphaTestEnable(false);
}
void DrawPolygonAnyBillCR(Object obj, const int& tex, bool InX, bool InY, bool InZ)
{
	//αテストを有効化
	SetAlphaTestEnable(true);

	// 頂点バッファへのポインタを取得
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

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// マテリアルのセット
	SetMaterial(obj.m_Material);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&obj.m_Mtx);

	
	//任意の軸の転置行列
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

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, obj.m_Scl.x, obj.m_Scl.y, obj.m_Scl.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.m_Rot.y, obj.m_Rot.x, obj.m_Rot.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, obj.m_Pos.x, obj.m_Pos.y, obj.m_Pos.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(&obj.m_Mtx);

	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//αテストを有効化
	SetAlphaTestEnable(false);
}
void DrawPolygonAnyBillLT(Object obj, const int& tex, bool InX, bool InY, bool InZ)
{
	//αテストを有効化
	SetAlphaTestEnable(true);

	// 頂点バッファへのポインタを取得
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

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(tex));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// マテリアルのセット
	SetMaterial(obj.m_Material);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&obj.m_Mtx);

	
	//任意の軸の転置行列
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

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, obj.m_Scl.x, obj.m_Scl.y, obj.m_Scl.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.m_Rot.y, obj.m_Rot.x, obj.m_Rot.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, obj.m_Pos.x, obj.m_Pos.y, obj.m_Pos.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(&obj.m_Mtx);

	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_2DVERTEX, 0);

	//αテストを有効化
	SetAlphaTestEnable(false);
}
void Draw3DModel(Object obj, DX11_MODEL& model)
{
	// マテリアル設定
	SetMaterial(obj.m_Material);

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &model.VertexBuffer, &stride, &offset);

	// インデックスバッファ設定
	GetDeviceContext()->IASetIndexBuffer(model.IndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ワールドマトリックスの初期化（単位行列を作る関数）
	D3DXMatrixIdentity(&obj.m_Mtx);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, obj.m_Scl.x, obj.m_Scl.y, obj.m_Scl.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, obj.m_Rot.y, obj.m_Rot.x, obj.m_Rot.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, obj.m_Pos.x, obj.m_Pos.y, obj.m_Pos.z);
	D3DXMatrixMultiply(&obj.m_Mtx, &obj.m_Mtx, &mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(&obj.m_Mtx);

	for (unsigned short i = 0; i < model.SubsetNum; i++)
	{
		// テクスチャ設定
		if (model.SubsetArray[i].Material.Material.noTexSampling == 0)
			GetDeviceContext()->PSSetShaderResources(0, 1, &model.SubsetArray[i].Material.Texture);

		// ポリゴン描画
		GetDeviceContext()->DrawIndexed(model.SubsetArray[i].IndexNum, model.SubsetArray[i].StartIndex, 0);
	}
}