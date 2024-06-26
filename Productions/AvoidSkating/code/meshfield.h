//=============================================================================
//
// メッシュ地面の処理 [meshfield.h]
// Author : 切田海畝斗
//
//=============================================================================
#pragma once

#include "base_mesh.h"
#include "base_object.h"

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class Field :public Base_Object {
private:
	Mesh m_Mesh;
public:
	Field() = delete;
	Field(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, int numBlockX, int numBlockZ);
	~Field();
	void Update(void)override;
	void Draw(void)override;
	void CollDispatch(Base_Object* pObj)override;

};