//=============================================================================
//
// プロテクトエフェクト処理 [star.h]
// Author : 
//
//=============================================================================
#ifndef _PROTECT_H_
#define _PROTECT_H_
#pragma once

#include "renderer.h"
#include "base_anime.h"

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class Protect :public Base_Anime {
private:
	Base_Object* m_Target;
public:
	Protect() = delete;
	Protect(Base_Object* pObj, D3DXVECTOR3 scl, D3DXCOLOR color);
	~Protect() = default;

	void Update(void)override;
	void Draw(void)override;
};
#endif // !_PROTECT_H_