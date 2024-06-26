#include "Texture.h"
#include "nomal_polgon_particle.h"
#include "material.h"
#include "sprite.h"

Nomal_Polgon_Particle::Nomal_Polgon_Particle(int life, D3DXVECTOR3 pos, D3DXVECTOR3 vel, D3DXVECTOR3 size, D3DXCOLOR coler, float gravity, float AirResist, float Enlarge,bool groudstop):
	Baseparticle(pos, { 0.0f, 0.0f, 0.0f }, size, vel, coler), m_life(life) {
	m_U = D3DXVECTOR2(0.0f + (int)(frand() * 2.0f) * 0.5f, 0.0f + (int)(frand() * 2.0f) * 0.5f);
	m_V = D3DXVECTOR2(0.5f, 0.5f);
	m_startlife = life;
	m_Gravity = gravity;
	m_AirResist = AirResist;
	m_Enlarge = Enlarge; 
	m_graoudstop = groudstop;
	// マテリアル設定
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = RefColor();
	GetMaterial()->Ambient = RefColor();
	GetMaterial()->noTexSampling = 0;

}
void Nomal_Polgon_Particle::Update(void)
{
	{
		if (m_life > 0)
		{
			m_life--;
		}
		if (m_life <= 0)
		{
			SetUse(false);
		}
		SetPos({ RefPos().x + RefVel().x,RefPos().y + RefVel().y, RefPos().z + RefVel().z });//慣性を足す
		SetVel({ RefVel().x, RefVel().y - m_Gravity, RefVel().z });//重力
		SetVel(RefVel() * m_AirResist);//空気抵抗
		SetScl({ RefScl().x + m_Enlarge ,RefScl().y + m_Enlarge ,RefScl().z + m_Enlarge });
		if (RefPos().y < 0)
		{
			SetPos({ RefPos().x, 0, RefPos().z });
			if (m_graoudstop == true)
			{
				SetUse(false);
			}
		}
		if (RefScl().x < 0)
		{
			SetUse(false);
		}

	};
}
;

void Nomal_Polgon_Particle::Draw() {

	DrawPolygonBill(*this, RefImageMaterial().m_Flame, m_U, m_V);
};