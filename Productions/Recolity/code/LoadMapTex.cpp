#include "LoadMapTex.h"
#include "model.h"
#include "material.h"
#include "sprite.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Game.h"
#define	VALUE_MOVE		(5.0f)					// 移動量
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)		// 回転量
//*****************************************************************************
// グローバル変数
//*****************************************************************************
static DX11_MODEL		g_Model;			// モデル読み込み
static MAPOBJECTMODEL g_MapObjectModel[MAX_MAPOBJECTMODEL_NUM];
static int				g_MapObjectModelCount = 0;		//3Dモデルの個数カウント
static int				g_MapObjectModelSelect = 0;			//ターゲット中の3Dモデルのカウント
HRESULT InitMapModelObject(void)
{
	//char filePath[] = "data/MODEL/Lowpoly_tree_sample.obj";


	for (int i = 1; i <= MAX_MAPOBJECTMODEL_NUM; i++)
	{
		//g_MapObjectModel[i].modelpass = filePath;
		g_MapObjectModel[i].pos = D3DXVECTOR3(0.0f, 100.0f, 0.0f);
		g_MapObjectModel[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MapObjectModel[i].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_MapObjectModel[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_MapObjectModel[i].use = false;

	}





	return S_OK;
}
void LoadModelMap(void)
{
	const char* MapFilePath = "";  // ファイルパス
	if (GetStageSelect() == Tutorial)
	{
		MapFilePath = "data/MAP/MapFileModel_tutorial.txt";  // ファイルパス
	}
	if (GetStageSelect() == Stage1)
	{
		MapFilePath = "data/MAP/MapFileModel_stage1.txt";  // ファイルパス
	}
	if (GetStageSelect() == Stage2)
	{
		MapFilePath = "data/MAP/MapFileModel_stage2.txt";  // ファイルパス
	}
	std::ifstream ifs(MapFilePath);

	if (!ifs.is_open())
	{
		MessageBoxA(NULL, "ファイルを開けませんでした！", "エラー", MB_ICONERROR | MB_OK);
	}
	else if (ifs.is_open())
	{
		int nua = 0;
		ifs >> nua;
		for (int i = 0; i <= MAX_MAPOBJECTMODEL_NUM; i++)
		{

			ifs >> g_MapObjectModel[i].use;
			ifs >> g_MapObjectModel[i].pos.x >> g_MapObjectModel[i].pos.y >> g_MapObjectModel[i].pos.z;
			ifs >> g_MapObjectModel[i].rot.x >> g_MapObjectModel[i].rot.y >> g_MapObjectModel[i].rot.z;
			ifs >> g_MapObjectModel[i].scl.x >> g_MapObjectModel[i].scl.y >> g_MapObjectModel[i].scl.z;
			ifs >> g_MapObjectModel[i].color.r >> g_MapObjectModel[i].color.g >> g_MapObjectModel[i].color.b >> g_MapObjectModel[i].color.a;



			for (int row = 0; row < 4; row++)
			{
				for (int col = 0; col < 4; col++)
				{
					ifs >> g_MapObjectModel[i].mtxWorld(row, col);
				}
			}
			ifs >> g_MapObjectModel[i].num;
		}
		ifs.close();
	}
}
void DrawMapModelObject()
{
	SetAlphaTestEnable(true);
	MATERIAL mtl;
	ZeroMemory(&mtl, sizeof(mtl));
	mtl.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//拡散色
	mtl.Ambient = D3DXCOLOR(1.0f, 1.0f,	1.0f, 1.0f) * 0.3f;//環境色
	mtl.Emission = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) * 0.3f;//影のところ色
	mtl.noTexSampling = 0;							//テクスチャ有り:0 or テクスチャ無し:1
	
	for (int i = 0; i <= MAX_MAPOBJECTMODEL_NUM; i++)
	{
		if (g_MapObjectModel[i].use == true)
		{

			D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
			D3DXMATRIX mtxWorld;
			// ワールドマトリックスの初期化（単位行列を作る関数）
			D3DXMatrixIdentity(&g_MapObjectModel[i].mtxWorld);

			// スケールを反映
			D3DXMatrixScaling(&mtxScl, g_MapObjectModel[i].scl.x, g_MapObjectModel[i].scl.y, g_MapObjectModel[i].scl.z);

			//第1引数 ＝          第2引数      ＊    第3引数
			D3DXMatrixMultiply(&g_MapObjectModel[i].mtxWorld, &g_MapObjectModel[i].mtxWorld, &mtxScl);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MapObjectModel[i].rot.y, g_MapObjectModel[i].rot.x, g_MapObjectModel[i].rot.z);
			D3DXMatrixMultiply(&g_MapObjectModel[i].mtxWorld, &g_MapObjectModel[i].mtxWorld, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, g_MapObjectModel[i].pos.x, g_MapObjectModel[i].pos.y, g_MapObjectModel[i].pos.z);
			D3DXMatrixMultiply(&g_MapObjectModel[i].mtxWorld, &g_MapObjectModel[i].mtxWorld, &mtxTranslate);

			// ワールドマトリックスの設定
			SetWorldMatrix(&g_MapObjectModel[i].mtxWorld);

			//objモデルの描画
			DrawModel(&RefModelMaterial().MapModel[g_MapObjectModel[i].num],mtl);
		}
	}

}
