//=============================================================================
//
// ライト処理 [light.cpp]
// Author : 切田海畝斗
//
//=============================================================================
#include "light.h"

//=============================================================================
// コンストラクタ
//=============================================================================
Light::Light()
{
	m_LightArray.reserve(LIGHT_NUM);
	// 並行光源の設定（世界を照らす光）
	LIGHT light;
	light.Type = LIGHT_TYPE_DIRECTIONAL;						// 並行光源
	light.Direction = D3DXVECTOR4(0.0f, -1.0f, 0.0f, 0.0f);	// 光の向き
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// 光の色
	light.Ambient = D3DXCOLOR(1.0f, 1.0f,1.0f, 1.0f);		// 光の色
	light.Enable = true;
	m_LightArray.push_back(light);

	for (int index = 0; index < m_LightArray.size(); index++)
	{
		SetLight(index, &m_LightArray[index]);
	}
}

Light::~Light()
{
	return;
}

