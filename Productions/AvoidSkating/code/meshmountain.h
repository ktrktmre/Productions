//=============================================================================
//
// ���b�V���R���� [meshmountain.h]
// Author : �ؓc�C���l
//
//=============================================================================
#pragma once

#include "base_mesh.h"
#include "base_object.h"

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class Mountain:public Base_Object {
private:
	Mesh m_Mesh;
public:
	Mountain() = delete;
	Mountain(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR2 size, int numBlockH, int numBlockV, D3DXVECTOR2 uv);
	~Mountain();
	void Update(void)override;
	void Draw(void)override;
	void CollDispatch(Base_Object* pObj)override;
};