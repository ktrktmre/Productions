//=============================================================================
//
// �e���� [shadow.h]
// Author : �ؓc�C���l
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"
#include "base_object.h"

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class Shadow :public Base_Object {
private:
	Base_Object* m_Target;
	Object_Tag m_TargetTag;
public:
	Shadow() = delete;
	Shadow(Base_Object* pTarget);
	~Shadow() = default;

	void Update(void)override;
	void Draw(void)override;
	void CollDispatch(Base_Object* pObj)override;
};