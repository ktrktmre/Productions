#pragma once
#pragma once
#pragma once
#include "baseparticle.h"
#include "main.h"
class Particle_SetScl_Model :public Baseparticle
{
private:
	unsigned int m_life;//寿命
	unsigned int m_startlife;//寿命の開始
	float		m_Gravity;//重力
	float		m_AirResist;//空気抵抗
	float		m_Bound;//跳ねる
	float		m_Enlarge = 0.0f;//フレーム単位の拡大率
	D3DXVECTOR3	m_GoalSize;
	DX11_MODEL* m_ModelId;	//モデルID
public:
	
	Particle_SetScl_Model(
		int life, D3DXVECTOR3 pos, D3DXVECTOR3 vel, D3DXVECTOR3	modelrot, D3DXVECTOR3 size, D3DXCOLOR coler, float gravity, float AirResist, float Bound, float enlarge, D3DXVECTOR3 goalsize,DX11_MODEL* model) :
		Baseparticle(pos, modelrot, size, vel, coler),
		m_life(life), m_startlife(life),
		m_Gravity(gravity),
		m_AirResist(AirResist),
		m_Bound(Bound), m_ModelId(model), m_Enlarge(enlarge),m_GoalSize(goalsize) {

		// マテリアル設定
		ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
		GetMaterial()->Diffuse = RefColor();	//拡散色
		GetMaterial()->Ambient = RefColor();	//環境色
		GetMaterial()->Emission = RefColor();	//自己発光色
		GetMaterial()->noTexSampling = 0;
	};
	~Particle_SetScl_Model() {};
	void Update(void) override {
		if (m_life > 0)
		{
			m_life--;
		}
		this->SetPos({ this->RefPos().x + this->RefVel().x,this->RefPos().y + this->RefVel().y, this->RefPos().z + this->RefVel().z });//慣性を足す
		this->SetVel({ this->RefVel().x, this->RefVel().y - m_Gravity, this->RefVel().z });//重力
		this->SetVel(this->RefVel() * m_AirResist);//空気抵抗

		SetScl({ (RefScl().x + m_Enlarge), (RefScl().y + m_Enlarge) ,(RefScl().z + m_Enlarge) });
		if (m_GoalSize.x < RefScl().x)
		{
			SetScl({ m_GoalSize.x,RefScl().y,RefScl().z });
		}
		if (m_GoalSize.y < RefScl().y)
		{
			SetScl({ RefScl().x, m_GoalSize.y,RefScl().z });
		}
		if (m_GoalSize.z < RefScl().z)
		{
			SetScl({ RefScl().x,RefScl().y, m_GoalSize.z });
		}
		if (this->RefPos().y < 0)//y座標がマイナスにならないように
		{
			this->SetPos({ this->RefPos().x, 0, this->RefPos().z });
			this->SetVel({ this->RefVel().x * this->m_Bound, this->RefVel().y * this->m_Bound * -1.0f, this->RefVel().z * this->m_Bound });

		}

		if (Life()) {
			SetUse(false);
		}
	};
	bool Life(void) override {
		if (m_life == 0)
		{
			return  true;
		}
		return false;
	}
	void Draw(void) override;
	HRESULT Init() override { return 0; };
	void Uninit() override {};

};

