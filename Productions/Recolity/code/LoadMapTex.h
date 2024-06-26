#pragma once
#include "main.h"


typedef struct {

	bool            use;        //使っているか
	int             num;        //モデルの使用番号
	D3DXVECTOR3     pos;        // ポリゴンの位置
	D3DXVECTOR3     rot;        // ポリゴンの向き(回転)
	D3DXVECTOR3     scl;        // ポリゴンの大きさ(スケール)
	D3DXCOLOR       color;        // ポリゴンのカラー
	D3DXMATRIX      mtxWorld;    // ワールドマトリックス

}MAPOBJECTMODEL;
#define MAX_MAPOBJECTMODEL_NUM (1024)	//3DModelの最大数
HRESULT InitMapModelObject(void);
void LoadModelMap(void);
void DrawMapModelObject();

