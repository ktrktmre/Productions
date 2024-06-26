#pragma once
#include "Texture.h"
struct POLYGON
{

	D3DXVECTOR3		pos;		// ポリゴンの位置
	D3DXVECTOR3		rot;		// ポリゴンの向き(回転)
	D3DXVECTOR3		scl;		// ポリゴンの大きさ(スケール)
	D3DXCOLOR		color;		// ポリゴンのカラー

	D3DXMATRIX		mtxWorld;	// ワールドマトリックス
};
enum Floor_Type
{
	Floor_Wall = 0,
	Floor_Nomal,
	Floor_Paper,
};
enum Floor_Adhere
{
	Floor_None = 0,
	Floor_flame,
	Floor_Water,
	Floor_Wind,
};
typedef struct {
	Floor_Type floor_type;//床のタイプ
	Floor_Adhere Adhere;//付着している属性
	int				tex;//テクスチャ
	int time;//属性が付着している時間
}FLOOR2;

void InitFloor(void);
void UnInitFloor(void);
void UpdateFloor(void);
void DrawFloor(void);
Floor_Type GetNowFloor(D3DXVECTOR3 pos);
Floor_Adhere GetNowAdhere(D3DXVECTOR3 pos);
void SetAdhere(D3DXVECTOR3 pos,Floor_Adhere ad, int time);