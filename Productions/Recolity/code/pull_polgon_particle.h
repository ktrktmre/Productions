#pragma once
#include "baseparticle.h"
#include "material.h"
#include "main.h"
class Pull_Polgon_Particle :public Baseparticle
{
private:
	D3DXVECTOR3 m_PullPoint;//引き寄せられる座標
	float		berak_circle;//引き寄せられた時にどのくらいの距離で消えるか(マイナス値で無効化)
	unsigned int m_life;//寿命
	float		m_AirResist;//空気抵抗
	float		m_Enlarge;//フレーム単位の拡大率
	int* m_tex;//テクスチャ
	D3DXVECTOR2 m_U;//UV
	D3DXVECTOR2 m_V;//UV
public:
	//=====================================
	// life寿命
	// pos生成位置
	// sizeパーティクルの大きさ
	// coler色
	// AirResist空気抵抗0～1
	// Enlargeフレーム毎の拡大
	//=====================================
	Pull_Polgon_Particle(int life, D3DXVECTOR3 pos, D3DXVECTOR3 goal, D3DXVECTOR3 size, D3DXCOLOR coler, float spd ,float delrange, float AirResist, float Enlarge, int* tex);

	~Pull_Polgon_Particle() = default;
	void Update(void) override;
	bool Life(void) override {
		if (m_life == 0)
		{
			return  true;
		}
		return false;
	}

	HRESULT Init() override { return 0; };
	void Uninit() override {};
	void Draw(void) override;


};

