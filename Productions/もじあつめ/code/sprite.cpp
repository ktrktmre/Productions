//=============================================================================
//
// スプライト処理 [sprite.cpp]
// Author :切田 海畝斗 
//
//=============================================================================
#include "sprite.h"
#include "renderer.h"
#include "texture.h"
#include "myfunction.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUM_VERTEX 4	//必要な頂点の数
#define CHAR_TEX_PART_X 14	//文字テクスチャ横分割数
#define CHAR_TEX_PART_Y 2 	//文字テクスチャ横分割数
#define CHAR_BUF 1024	//文字列バッファ


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer				*g_VertexBuffer = NULL;	// 頂点情報


//=============================================================================
// 初期化処理
//=============================================================================
void InitSprite(void)
{
	ID3D11Device *pDevice = GetDevice();

	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * NUM_VERTEX;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	pDevice->CreateBuffer(&bd, NULL, &g_VertexBuffer);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitSprite(void)
{
	// 頂点バッファの解放
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
}

//=============================================================================
// スプライトデータ設定
// 座標・サイズ・UV指定
//=============================================================================
//引数
//texNo : テクスチャの識別番号（texture.h, texture.cpp のLoadTexture関数の戻り値）
//pos	; X,Y座標
//size	; サイズ
//tex_v	; 可変テクスチャ座標
//tex_f	; 固定テクスチャ座標
void DrawSprite(int texNo, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 tex_v, D3DXVECTOR2 tex_f)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	float hw, hh;
	hw = size.x * 0.5f;
	hh = size.y * 0.5f;

	// 頂点０番（左上の頂点）
	vertex[0].Position = D3DXVECTOR3(pos.x- hw, pos.y - hh, 0.0f);
	vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(tex_v.x, tex_v.y);

	// 頂点１番（右上の頂点）
	vertex[1].Position = D3DXVECTOR3(pos.x + hw, pos.y - hh, 0.0f);
	vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(tex_v.x + tex_f.x, tex_v.y);

	// 頂点２番（左下の頂点）
	vertex[2].Position = D3DXVECTOR3(pos.x - hw, pos.y + hh, 0.0f);
	vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(tex_v.x, tex_v.y + tex_f.y);

	// 頂点３番（右下の頂点）
	vertex[3].Position = D3DXVECTOR3(pos.x + hw, pos.y + hh, 0.0f);
	vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(tex_v.x + tex_f.x, tex_v.y + tex_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_VERTEX, 0);
}

//=============================================================================
// スプライトデータ設定（左上指定）
// 座標・サイズ・UV指定
//=============================================================================
//引数
//texNo : テクスチャの識別番号（texture.h, texture.cpp のLoadTexture関数の戻り値）
//pos	; X,Y座標
//size	; サイズ
//tex_v	; 可変テクスチャ座標
//tex_f	; 固定テクスチャ座標
void DrawSpriteLeftTop(int texNo, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 tex_v, D3DXVECTOR2 tex_f)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	// 左上を原点として設定するプログラム
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

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_VERTEX, 0);
}


//=============================================================================
// スプライトデータ設定
// 座標・サイズ・UV指定・頂点色
//=============================================================================
//引数
//texNo : テクスチャの識別番号（texture.h, texture.cpp のLoadTexture関数の戻り値）
//pos	; X,Y座標
//size	; サイズ
//tex_v	; 可変テクスチャ座標
//tex_f	; 固定テクスチャ座標
//color : 頂点の色（RGBA）
void DrawSpriteColor(int texNo, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 tex_v, D3DXVECTOR2 tex_f,D3DXCOLOR color)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	float hw, hh;
	hw = size.x * 0.5f;
	hh = size.y * 0.5f;

	// 頂点０番（左上の頂点）
	vertex[0].Position = D3DXVECTOR3(pos.x - hw, pos.y - hh, 0.0f);
	vertex[0].Diffuse = color;
	vertex[0].TexCoord = D3DXVECTOR2(tex_v.x, tex_v.y);

	// 頂点１番（右上の頂点）
	vertex[1].Position = D3DXVECTOR3(pos.x + hw, pos.y - hh, 0.0f);
	vertex[1].Diffuse = color;
	vertex[1].TexCoord = D3DXVECTOR2(tex_v.x + tex_f.x, tex_v.y);

	// 頂点２番（左下の頂点）
	vertex[2].Position = D3DXVECTOR3(pos.x - hw, pos.y + hh, 0.0f);
	vertex[2].Diffuse = color;
	vertex[2].TexCoord = D3DXVECTOR2(tex_v.x, tex_v.y + tex_f.y);

	// 頂点３番（右下の頂点）
	vertex[3].Position = D3DXVECTOR3(pos.x + hw, pos.y + hh, 0.0f);
	vertex[3].Diffuse = color;
	vertex[3].TexCoord = D3DXVECTOR2(tex_v.x + tex_f.x, tex_v.y + tex_f.y);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_VERTEX, 0);
}

//=============================================================================
// スプライトデータ設定（左上指定）
// 座標・サイズ・UV指定
//=============================================================================
//引数
//texNo : テクスチャの識別番号（texture.h, texture.cpp のLoadTexture関数の戻り値）
//pos	; X,Y座標
//size	; サイズ
//tex_v	; 可変テクスチャ座標
//tex_f	; 固定テクスチャ座標
//color	; 頂点カラー
void DrawSpriteLeftTopColor(int texNo, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 tex_v, D3DXVECTOR2 tex_f,D3DXCOLOR color)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	// 左上を原点として設定するプログラム
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

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_VERTEX, 0);
}


//=============================================================================
// スプライトデータ設定
// 座標・サイズ・UV指定・頂点色・回転角度
//=============================================================================
//引数
//texNo : テクスチャの識別番号（texture.h, texture.cpp のLoadTexture関数の戻り値）
//pos	; X,Y座標
//size	; サイズ
//tex_v	; 可変テクスチャ座標
//tex_f	; 固定テクスチャ座標
//color : 頂点の色（RGBA）
//Rot	: 回転角度（ラジアン値）
void DrawSpriteColorRotate(int texNo, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 tex_v, D3DXVECTOR2 tex_f, D3DXCOLOR color, float Rot)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	float hw, hh;
	hw = size.x * 0.5f;
	hh = size.x * 0.5f;

	// 座標変換
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

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_VERTEX, 0);
}

//=============================================================================
// スプライトデータ設定
// 座標・サイズ・UV指定・頂点色・回転角度
//=============================================================================
//引数
//texNo : テクスチャの識別番号（texture.h, texture.cpp のLoadTexture関数の戻り値）
//pos	; X,Y座標
//size	; サイズ
//dis	; 回転軸からの距離
//tex_v	; 可変テクスチャ座標
//tex_f	; 固定テクスチャ座標
//color : 頂点の色（RGBA）
//Rot	: 回転角度（ラジアン値）
void DrawSpriteColorRotateAxis(int texNo, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 dis,D3DXVECTOR2 tex_v, D3DXVECTOR2 tex_f, D3DXCOLOR color, float Rot)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	float hw, hh;
	hw = size.x * 0.5f;
	hh = size.y * 0.5f;

	//※CX,CYが回転軸と考える
	//回転軸を(0,0)の原点に移動するため、回転軸の座標の分だけ矩形全体の座標をマイナスし、その状態で回転を行う

	// 座標変換
	vertex[0].Position.x = (-dis.x - hw) * cosf(Rot) - (-dis.y - hh) * sinf(Rot);
	vertex[0].Position.y = (-dis.x - hw) * sinf(Rot) + (-dis.y - hh) * cosf(Rot);
	vertex[1].Position.x = (-dis.x + hw) * cosf(Rot) - (-dis.y - hh) * sinf(Rot);
	vertex[1].Position.y = (-dis.x + hw) * sinf(Rot) + (-dis.y - hh) * cosf(Rot);
	vertex[2].Position.x = (-dis.x - hw) * cosf(Rot) - (-dis.y + hh) * sinf(Rot);
	vertex[2].Position.y = (-dis.x - hw) * sinf(Rot) + (-dis.y + hh) * cosf(Rot);
	vertex[3].Position.x = (-dis.x + hw) * cosf(Rot) - (-dis.y + hh) * sinf(Rot);
	vertex[3].Position.y = (-dis.x + hw) * sinf(Rot) + (-dis.y + hh) * cosf(Rot);

	//回転の変換が終わった状態で回転軸の座標分プラスし、原点に戻す。さらに表示座標（X,Y）まで移動させる
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

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_VERTEX, 0);
}
//=============================================================================
// 文字スプライトデータ設定（左上指定）
// 座標・サイズ・UV指定
//=============================================================================
//引数
//texNo : テクスチャの識別番号（texture.h, texture.cpp のLoadTexture関数の戻り値）
// pos	: X,Y座標
//size	: フォントサイズ
//color	: 頂点色設定(RGBA)
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
			// 左上を原点として設定するプログラム
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

		// 頂点バッファ設定
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

		// プリミティブトポロジ設定
		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

		// ポリゴン描画
		GetDeviceContext()->Draw(NUM_VERTEX, 0);
	}

}

//=============================================================================
// 1文字スプライトデータ設定（左上指定）
// 座標・サイズ・UV指定
//=============================================================================
//引数
//texNo : テクスチャの識別番号（texture.h, texture.cpp のLoadTexture関数の戻り値）
// pos	: X,Y座標
//size	: フォントサイズ
//color	: 頂点色設定(RGBA)
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
		// 左上を原点として設定するプログラム
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

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_VERTEX, 0);

}


//=============================================================================
// 1文字スプライトデータ設定（中心指定）
// 座標・サイズ・UV指定
//=============================================================================
//引数
//texNo : テクスチャの識別番号（texture.h, texture.cpp のLoadTexture関数の戻り値）
// pos	: X,Y座標
//size	: フォントサイズ
//color	: 頂点色設定(RGBA)
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
		// 座標変換
		vertex[0].Position.x = (-hs) * cosf(rot) - (-hs) * sinf(rot) + pos.x;
		vertex[0].Position.y = (-hs) * sinf(rot) + (-hs) * cosf(rot) + pos.y;
		vertex[1].Position.x = (hs)*cosf(rot) - (-hs) * sinf(rot) + pos.x;
		vertex[1].Position.y = (hs)*sinf(rot) + (-hs) * cosf(rot) + pos.y;
		vertex[2].Position.x = (-hs) * cosf(rot) - (hs)*sinf(rot) + pos.x;
		vertex[2].Position.y = (-hs) * sinf(rot) + (hs)*cosf(rot) + pos.y;
		vertex[3].Position.x = (hs)*cosf(rot) - (hs)*sinf(rot) + pos.x;
		vertex[3].Position.y = (hs)*sinf(rot) + (hs)*cosf(rot) + pos.y;

		// 頂点カラー
		vertex[0].Diffuse = D3DXCOLOR(color.r, color.g, color.b, color.a);
		vertex[1].Diffuse = D3DXCOLOR(color.r, color.g, color.b, color.a);
		vertex[2].Diffuse = D3DXCOLOR(color.r, color.g, color.b, color.a);
		vertex[3].Diffuse = D3DXCOLOR(color.r, color.g, color.b, color.a);

		// テックスコード
		vertex[0].TexCoord = D3DXVECTOR2(U, V);
		vertex[1].TexCoord = D3DXVECTOR2(U + TEX_PART(CHAR_TEX_PART_X), V);
		vertex[2].TexCoord = D3DXVECTOR2(U, V + TEX_PART(CHAR_TEX_PART_Y));
		vertex[3].TexCoord = D3DXVECTOR2(U + TEX_PART(CHAR_TEX_PART_X), V + TEX_PART(CHAR_TEX_PART_Y));

		pos.x += size;
	}

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_VERTEX, 0);

}