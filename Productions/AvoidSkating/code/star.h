//=============================================================================
//
// —¬‚ê¯ˆ— [star.h]
// Author : Ø“cŠC¤“l
//
//=============================================================================
#pragma once

#include "renderer.h"
#include "base_anime.h"

//*****************************************************************************
// ƒNƒ‰ƒXéŒ¾
//*****************************************************************************
class Star :public Base_Anime {
private:
	Base_Object* m_Target;
	float m_Length;
public:
	Star() = delete;
	Star(Base_Object* pObj, D3DXVECTOR3 scl, D3DXCOLOR color);
	~Star() = default;

	void Update(void)override;
	void Draw(void)override;
	void Animetion(void)override;
};