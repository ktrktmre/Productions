//=============================================================================
//
// ���b�V����̏��� [meshsky.h]
// Author : �ؓc�C���l
//
//=============================================================================
#pragma once

#include "base_mesh.h"
#include "base_object.h"

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class Sky :public Base_Object {
private:
	Mesh m_Mesh[2];
	bool m_TransParent;
	bool m_Reverse;
public:
	Sky() = delete;
	Sky(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float radius, int numBlockH, int numBlockV, bool reverse);
	~Sky();
	void Update(void)override;
	void Draw(void)override;
	void CollDispatch(Base_Object* pObj)override;
};