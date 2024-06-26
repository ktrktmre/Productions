#pragma once
#pragma once
#include "baseparticle.h"
#include "main.h"
class Nomal_Polgon_Particle :public Baseparticle
{
private:
	unsigned int m_life;//寿命
	unsigned int m_startlife;//寿命の開始
	float		m_Gravity;//重力
	float		m_AirResist;//空気抵抗
	float		m_Enlarge;//フレーム単位の拡大率
	bool		m_graoudstop;//地面についたときに止まるか

	D3DXVECTOR2 m_U;//UV
	D3DXVECTOR2 m_V;//UV
public:
	Nomal_Polgon_Particle(int life, D3DXVECTOR3 pos, D3DXVECTOR3 vel, D3DXVECTOR3 size, D3DXCOLOR coler, float gravity, float AirResist, float Enlarge, bool groudstop = false);
		
	~Nomal_Polgon_Particle() = default;
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

