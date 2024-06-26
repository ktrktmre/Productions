//=============================================================================
//
// 壁処理 [wall.h]
// Author : 切田海畝斗
//
//=============================================================================
#ifndef _WALL_H_
#define _WALL_H_
#pragma once

#include <d3dx9.h>
#include "base_object.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class Wall:public Base_Object
{
private:
	D3DXVECTOR2 m_Uv_v;			//可変UV値
	D3DXVECTOR2 m_Uv_f;			//固定UV値
	float		m_UvValue;	//UV値の可変量
public:
	Wall() = delete;
	Wall(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	~Wall() = default;
	void Update(void);
	void Draw(void);
	void CollDispatch(Base_Object* pObj)override;
};

#endif // !_WALL_H_