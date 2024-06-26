//=============================================================================
//
// ���b�V���n�ʂ̏��� [meshfield.h]
// Author : �ؓc�C���l
//
//=============================================================================
#pragma once

#include "base_mesh.h"
#include "base_object.h"

//*****************************************************************************
// �N���X�錾
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