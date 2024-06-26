//=============================================================================
//
// îöî≠èàóù [explosion.h]
// Author : êÿìcäCê§ìl
//
//=============================================================================
#pragma once

#include "renderer.h"
#include "base_anime.h"

//*****************************************************************************
// ÉNÉâÉXêÈåæ
//*****************************************************************************
class Explosion :public Base_Anime {
private:
public:
	Explosion() = delete;
	Explosion(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXCOLOR color);
	~Explosion() = default;

	void Update(void)override;
	void Draw(void)override;
};