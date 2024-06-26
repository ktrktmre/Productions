#include "Texture.h"
#include "Model_particle.h"
#include "material.h"
#include "sprite.h"
void Particle_Model::Draw() {
	if (this->m_ModelId != nullptr)
	{
		// 背面ポリゴンをカリング

		SetCullingMode(CULL_MODE_NONE);
		Draw3DModel(*this,  *this->m_ModelId);
		SetCullingMode(CULL_MODE_BACK);
	}
};