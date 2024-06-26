#include "Texture.h"
#include "pull_polgon_particle.h"
#include "material.h"
#include "sprite.h"

//Pull_Polgon_Particle::Nomal_Polgon_Particle(int life, D3DXVECTOR3 pos, D3DXVECTOR3 vel, D3DXVECTOR3 size, D3DXCOLOR coler, float gravity, float AirResist, float Enlarge, bool groudstop) :
//	Baseparticle(pos, { 0.0f, 0.0f, 0.0f }, size, vel, coler), m_life(life) {
//	m_U = D3DXVECTOR2(0.0f + (int)(frand() * 2.0f) * 0.5f, 0.0f + (int)(frand() * 2.0f) * 0.5f);
//	m_V = D3DXVECTOR2(0.5f, 0.5f);
//	m_startlife = life;
//	m_Gravity = gravity;
//	m_AirResist = AirResist;
//	m_Enlarge = Enlarge;
//	m_graoudstop = groudstop;
//	// マテリアル設定
//	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
//	GetMaterial()->Diffuse = RefColor();
//	GetMaterial()->Ambient = RefColor();
//	GetMaterial()->noTexSampling = 0;
//
//}
Pull_Polgon_Particle::Pull_Polgon_Particle(int life, D3DXVECTOR3 pos, D3DXVECTOR3 goal, D3DXVECTOR3 size, D3DXCOLOR coler, float spd, float delrange, float AirResist, float Enlarge, int* tex) :
	Baseparticle(pos, { 0.0f, 0.0f, 0.0f }, size, {0.0f,0.0f,0.0f}, coler), m_life(life)
{
	m_U = D3DXVECTOR2(0.0f , 0.0f );
	m_V = D3DXVECTOR2(1.0f,1.0f);
	m_tex = tex;
	m_PullPoint = goal;
	berak_circle = delrange;
	D3DXVECTOR3 len =  goal - pos;
	D3DXVec3Normalize(&len, &len);
	SetVel(len* spd );
	// マテリアル設定
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = RefColor();
	GetMaterial()->Ambient = RefColor();
	GetMaterial()->noTexSampling = 0;
}
void Pull_Polgon_Particle::Update(void)
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
		SetScl({ RefScl().x + m_Enlarge ,RefScl().y + m_Enlarge ,RefScl().z + m_Enlarge });
		if (RefScl().x < 0)
		{
			SetUse(false);
		}
		D3DXVECTOR3 a = m_PullPoint - RefPos();
		if (D3DXVec3LengthSq(&a) < berak_circle * berak_circle)
		{
			SetUse(false);
		}
	
}
;

void Pull_Polgon_Particle::Draw() {

	DrawPolygonBill(*this, *m_tex, m_U, m_V);
};