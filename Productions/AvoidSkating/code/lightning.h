//=============================================================================
//
// ライトニング処理 [lightning.h]
// Author : 切田海畝斗
//
//=============================================================================
#pragma once

#include "renderer.h"
#include "base_anime.h"

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class Lightning :public Base_Anime {
private:
	Base_Object* m_Target;
public:
	Lightning() = delete;
	Lightning(Base_Object* pObj, D3DXVECTOR3 scl, D3DXCOLOR color);
	~Lightning() = default;

	void Update(void)override;
	void Draw(void)override;
	void Animetion(void)override;
};