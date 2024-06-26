#include "Texture.h"
#include "flameparticle.h"
#include "material.h"
#include "sprite.h"

void Particle_Flame::Draw() {

	DrawPolygonBill(*this, RefImageMaterial().m_Flame, m_U, m_V);
};