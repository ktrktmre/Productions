#pragma once
#include <list>
#include "baseparticle.h"
#include "flameparticle.h"
#include "Model_particle.h"
#include "nomal_polgon_particle.h"
#include "nomal_polgon_particle_CR.h"
#include "pull_polgon_particle.h"
#include "Model_SetScl_particle.h"
#include "material.h"

class Particle_Manager
{
private:
	std::list< Baseparticle*> m_Listparticle;
public:
	Particle_Manager() { 
	};
	~Particle_Manager() {
		Uninit();
	};
	void Init() {
		for (Baseparticle* p : m_Listparticle)
		{
			delete p;
		}
		m_Listparticle.clear();
	}
	void Uninit() {
		for (Baseparticle* p : m_Listparticle)
		{
			delete p;

		}
		m_Listparticle.clear();
	}
	void Update() {
		for (Baseparticle* p : m_Listparticle)
		{
			p->Update();
		}
		m_Listparticle.remove_if([](Baseparticle* particle) {
			if (!particle->RefUse()) {
				delete particle;
				return true;
			}
			return false; }
		);
	};
	void Draw() {
		for (Baseparticle* p : m_Listparticle)
		{
			p->Draw();
		}
#if _DEBUG
		int count = 0;
		count += (int)m_Listparticle.size();
#endif // _DEBUG
	};

	//後で消す
	void Fier(D3DXVECTOR3 pos) {
		//パーティクルの生成
		float randroty = -D3DX_PI + frand() * D3DX_PI * 2.0f;
		float randrotx = -D3DX_PI * 0.5f + frand() * D3DX_PI;
		float randsize = 20;
		D3DXVECTOR3 posr(pos.x - randsize + randsize * 2.0f * frand(), pos.y - randsize + randsize * 2.0f * frand(), pos.z - randsize + randsize * 2.0f * frand());
		float spd = 10.0f;
		float size = 40;

		//パーティクルの登録
		m_Listparticle.push_back(new Particle_Flame(80, { posr.x ,posr.y,posr.z }, { sinf(randroty) * cosf(randrotx) * spd, sinf(randrotx) * spd, cosf(randroty) * cosf(randrotx) * spd },
			{ size,size ,size }, D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.8f + frand() * 0.2f),
			-0.6f, 0.96f, 0.0f));
	}

	void Brust(D3DXVECTOR3 pos) {
		for (int j = 0; j < 32; j++){
			float randroty = -D3DX_PI + frand() * D3DX_PI * 2.0f;
			float randrotx = -D3DX_PI * 0.5f + frand() * D3DX_PI;
			float spd = 7.0f;
			float size = 20;

			m_Listparticle.push_back(new Particle_Flame(40, { pos.x ,pos.y,pos.z }, { sinf(randroty) * cosf(randrotx) * spd, sinf(randrotx) * spd, cosf(randroty) * cosf(randrotx) * spd }, { size,size ,size }, D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.8f + frand() * 0.2f), 0, 0.95f, 2.5f));
		}

	}
	void Brust2(D3DXVECTOR3 pos) {

		for (int i = 0; i < 4; i++)
		{
			Fier(D3DXVECTOR3(pos.x - 20 + frand() * 80, pos.y - 20 + frand() * 40, pos.z - 20 + frand() * 80));
		}
	}
	void Brust3(D3DXVECTOR3 pos) {
		for (int j = 0; j < 256; j++)
		{
			float randroty = -D3DX_PI + frand() * D3DX_PI * 2.0f;
			float randrotx = -D3DX_PI * 0.1f + frand() * D3DX_PI * 0.2f;
			float spd = 70.0f * frand();
			float size = 20;
			float randsize = 20;

			m_Listparticle.push_back(new Particle_Flame(100, { pos.x ,pos.y - 190,pos.z }, { sinf(randroty) * cosf(randrotx) * spd, sinf(randrotx) * spd, cosf(randroty) * cosf(randrotx) * spd },
				{ size,size ,size }, D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.9f + frand() * 0.4f), 0, 0.90f, 1.3f));
		}

	}
	void WaterBrast(D3DXVECTOR3 pos) {
	
		//生成個数
		int cretenum = 250;
		//寿命
		int life = 60;
		//速度
		float spd = 70.0f * frand();
		//パーティクルのサイズ
		float size = 20;
		//色
		D3DXCOLOR	coler = { 0.0f,0.0f,1.0f,0.8f };
		//重力
		float gravity = 0.75f;
		//空気抵抗
		float Air_Resistance = 0.10f;
		//フレーム毎のサイズ拡大
		float TickScl = 1.3f;
		//地面についたときに止まるか
		bool stopgrond = true;
		for (int i = 0; i < cretenum; i++)
		{
			coler= D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.9f + frand() * 0.4f);
			float randroty = -D3DX_PI + frand() * D3DX_PI * 2.0f;
			float randrotx = -D3DX_PI * 0.1f + frand() * D3DX_PI * 0.2f;
			if (Air_Resistance > 1.0f)
			{
				Air_Resistance = 1.0f;
			}
			if (Air_Resistance < 0.0f)
			{
				Air_Resistance = 0.0f;
			}
			//実際の反映値
			float propagated_Air_Resistance = 1.0f - Air_Resistance;

			m_Listparticle.push_back(new Nomal_Polgon_Particle(life, pos, { sinf(randroty) * cosf(randrotx) * spd, sinf(randrotx) * spd, cosf(randroty) * cosf(randrotx) * spd }, { size,size,size }, coler, gravity, propagated_Air_Resistance, TickScl, stopgrond));
		}
	
	}
	void SetCardMordParticle(D3DXVECTOR3 pos) {
		for (int j = 0; j < 20; j++)
		{
			//パーティクルの生成
			float randroty = -D3DX_PI + frand() * D3DX_PI * 2.0f;
			float randrotx = -D3DX_PI * 0.5f + frand() * D3DX_PI;
			float randmodelroty = -D3DX_PI + frand() * D3DX_PI * 2.0f;
			float randmodelrotx = -D3DX_PI * 0.5f + frand() * D3DX_PI;
			float spd = 10.0f;
			D3DXVECTOR3 vel = D3DXVECTOR3(sinf(randroty) * cosf(randrotx) * spd, sinf(randrotx) * spd, cosf(randroty) * cosf(randrotx) * spd);
			float size = 2.0f;
			DX11_MODEL* model = &RefModelMaterial().m_CardBoard1;
			if (frand() > 0.5f)
			{
				model = &RefModelMaterial().m_CardBoard2;
			}

			//パーティクルの登録
			m_Listparticle.push_back(new Particle_Model(150 + (int)(frand() * 60.0f),
				pos, vel,
				{ randmodelrotx,randmodelroty,0.0f },
				{ size,size ,size }, DIK_COLER_WHITE,
				0.75f, 0.9999f, 0.2f, model));
		}

	}
	void SetCircleEffect(D3DXVECTOR3 pos) {
		float size = 6.0f;
		DX11_MODEL* model = &RefModelMaterial().m_Damage_Circle;

		//パーティクルの登録
		m_Listparticle.push_back(new Particle_Model(60,
			{ pos.x,pos.y + 1  , pos.z }, { 0.0f,0.0f,0.0f },
			{ 0.0f,0.0f,0.0f },
			{ size,size ,size }, DIK_COLER_WHITE,
			0.0f, 1.0f, 0.0f, 0.0f, model));
	}
	void SetCircleEffect2(D3DXVECTOR3 pos) {
		float size = 1.5f;
		DX11_MODEL* model = &RefModelMaterial().m_Damage_Circle;
		//パーティクルの登録
		m_Listparticle.push_back(new Particle_SetScl_Model(150,
			{ pos.x,pos.y + 1  , pos.z }, { 0.0f,0.0f,0.0f },
			{ 0.0f,0.0f,0.0f },
			{ 0,0 ,0 }, DIK_COLER_WHITE,
			0.0f, 1.0f, 0.0f, 0.12f, { size,size ,size }, model));
	}
	void SetCircleEffect3(D3DXVECTOR3 pos) {
		float size = 4.0f;
		DX11_MODEL* model = &RefModelMaterial().m_Damage_Circle;

		//パーティクルの登録
		m_Listparticle.push_back(new Particle_SetScl_Model(150,
			{ pos.x,pos.y + 1  , pos.z }, { 0.0f,0.0f,0.0f },
			{ 0.0f,0.0f,0.0f },
			{ 0,0 ,0 }, DIK_COLER_WHITE,
			0.0f, 1.0f, 0.0f, 0.12f, { size,size ,size }, model));
	}
	void Water1(D3DXVECTOR3 pos) {

		//生成個数
		int cretenum = 10;
		//寿命
		int life = 60;
		//速度
		float spd = 10.0f;
		//パーティクルのサイズ
		float size = 50;
		//色
		D3DXCOLOR	coler = {0.0f,0.0f,1.0f,0.8f };
		//重力
		float gravity = 0.75f;
		//空気抵抗
		float Air_Resistance = 0.10f;
		//フレーム毎のサイズ拡大
		float TickScl = -0.5f;
		//地面についたときに止まるか
		bool stopgrond = true;
		for (int i = 0; i < cretenum; i++)
		{
			coler.a = 0.75f + frand() * 0.1f;
			float randroty = -D3DX_PI + frand() * D3DX_PI * 2.0f;
			float randrotx = -D3DX_PI * 0.5f + frand() * D3DX_PI;
			if (Air_Resistance > 1.0f)
			{
				Air_Resistance = 1.0f;
			}
			if (Air_Resistance < 0.0f)
			{
				Air_Resistance = 0.0f;
			}
			//実際の反映値
			float propagated_Air_Resistance = 1.0f - Air_Resistance;

			m_Listparticle.push_back(new Nomal_Polgon_Particle(life, pos, { sinf(randroty) * cosf(randrotx) * spd, sinf(randrotx) * spd, cosf(randroty) * cosf(randrotx) * spd }, { size,size,size }, coler, gravity, propagated_Air_Resistance, TickScl, stopgrond));
		}
	}
	void Wind1(D3DXVECTOR3 pos) {

		//生成個数
		int cretenum = 10;
		//寿命
		int life = 60;
		//速度
		float spd = 25.0f;
		//パーティクルのサイズ
		float size = 90;
		//色
		D3DXCOLOR	coler = { 0.5f,0.6f,1.0f,0.8f };
		//重力
		float gravity = -0.75f;
		//空気抵抗
		float Air_Resistance = 0.30f;
		//フレーム毎のサイズ拡大
		float TickScl = 0.0f;
		//地面についたときに止まるか
		bool stopgrond = true;
		for (int i = 0; i < cretenum; i++)
		{
			coler.a = 0.75f + frand() * 0.1f;
			float randroty = -D3DX_PI + frand() * D3DX_PI * 2.0f;
			float randrotx = -D3DX_PI * 0.5f + frand() * D3DX_PI;
			if (Air_Resistance > 1.0f)
			{
				Air_Resistance = 1.0f;
			}
			if (Air_Resistance < 0.0f)
			{
				Air_Resistance = 0.0f;
			}
			//実際の反映値
			float propagated_Air_Resistance = 1.0f - Air_Resistance;

			m_Listparticle.push_back(new Nomal_Polgon_Particle(life, pos, { sinf(randroty) * cosf(randrotx) * spd, sinf(randrotx) * spd, cosf(randroty) * cosf(randrotx) * spd }, { size,size,size }, coler, gravity, propagated_Air_Resistance, TickScl, stopgrond));
		}
	}
	void Pull1(D3DXVECTOR3 pos) {

		//生成個数
		int cretenum = 1;
		//寿命
		int life = 160;
		//速度
		float spd = 4.0f;
		//パーティクルのサイズ
		float size = 15;
		//色
		D3DXCOLOR	coler = { 0.9f,0.3f,0.0f,1.0f };
		//空気抵抗
		float Air_Resistance = -0.40f;
		//消す領域
		float range = 10;
		//フレーム毎のサイズ拡大
		float TickScl = 0.0f;
		for (int i = 0; i < cretenum; i++)
		{
			float randroty = -D3DX_PI + frand() * D3DX_PI * 2.0f;
			float randrotx = -D3DX_PI * 0.5f + frand() * D3DX_PI;
			if (Air_Resistance > 1.0f)
			{
				Air_Resistance = 1.0f;
			}
	
			//実際の反映値
			float propagated_Air_Resistance = 1.0f - Air_Resistance;

			m_Listparticle.push_back(new Pull_Polgon_Particle(life, { pos.x - frand() * 200.0f + 100.0f ,pos.y - frand() * 200.0f + 100.0f,pos.z - frand() * 200.0f + 100.0f }, pos, { size,size,size },
				coler, spd, range, propagated_Air_Resistance,
				TickScl, &RefImageMaterial().m_Eye));
		}
	}
	void Pull2(D3DXVECTOR3 pos) {

		//生成個数
		int cretenum = 1;
		//寿命
		int life = 160;
		//速度
		float spd = 4.0f;
		//パーティクルのサイズ
		float size = 15;
		//色
		D3DXCOLOR	coler = { 0.0f,0.1f,0.9f,1.0f };
		//空気抵抗
		float Air_Resistance = -0.40f;
		//消す領域
		float range = 10;
		//フレーム毎のサイズ拡大
		float TickScl = 0.0f;
		for (int i = 0; i < cretenum; i++)
		{
			float randroty = -D3DX_PI + frand() * D3DX_PI * 2.0f;
			float randrotx = -D3DX_PI * 0.5f + frand() * D3DX_PI;
			if (Air_Resistance > 1.0f)
			{
				Air_Resistance = 1.0f;
			}

			//実際の反映値
			float propagated_Air_Resistance = 1.0f - Air_Resistance;

			m_Listparticle.push_back(new Pull_Polgon_Particle(life, { pos.x - frand() * 200.0f + 100.0f ,pos.y - frand() * 200.0f + 100.0f,pos.z - frand() * 200.0f + 100.0f }, pos, { size,size,size },
				coler, spd, range, propagated_Air_Resistance,
				TickScl, &RefImageMaterial().m_Eye));
		}
	}
	void BossBlust(D3DXVECTOR3 pos) {
		//生成個数
		int cretenum = 1;
		int cretenum3 = 16;
		//寿命
		int life = 2;
		int life2 = 10;
		//速度
		float spd = 0.0f;
		//パーティクルのサイズ
		float size = 80;
		float size2 = 200;
		//色
		D3DXCOLOR	coler = { 1.0f,0.9f,0.0f,1.0f };
		D3DXCOLOR	coler2 = { 0.7f,0.7f,0.7f,1.0f };
		//重力
		float gravity = 0.0f;
		//空気抵抗
		float Air_Resistance = 0.00f;
		//フレーム毎のサイズ拡大
		float TickScl = 170.0f;
		//フレーム毎のサイズ拡大
		float TickScl2 = 10.0f;
		//地面についたときに止まるか
		bool stopgrond = true;
		for (int i = 0; i < cretenum; i++)
		{
			coler.a = 0.75f + frand() * 0.1f;
			float randroty = -D3DX_PI + frand() * D3DX_PI * 2.0f;
			float randrotx = -D3DX_PI * 0.5f + frand() * D3DX_PI;
			if (Air_Resistance > 1.0f)
			{
				Air_Resistance = 1.0f;
			}
			if (Air_Resistance < 0.0f)
			{
				Air_Resistance = 0.0f;
			}
			//実際の反映値
			float propagated_Air_Resistance = 1.0f - Air_Resistance;
			m_Listparticle.push_back(new Nomal_Polgon_Particle_CR(life, pos, { sinf(randroty) * cosf(randrotx) * spd, sinf(randrotx) * spd, cosf(randroty) * cosf(randrotx) * spd }, { size,size * 2.0f,size }, coler, gravity, propagated_Air_Resistance, TickScl,&RefImageMaterial().m_Blast, stopgrond));
			m_Listparticle.push_back(new Nomal_Polgon_Particle_CR(life2, pos, { sinf(randroty) * cosf(randrotx) * spd, sinf(randrotx) * spd, cosf(randroty) * cosf(randrotx) * spd }, { size2 * 1.5f,size2 * 1.5f,size2 * 1.5f }, coler2, gravity, propagated_Air_Resistance, TickScl2, &RefImageMaterial().m_Blast2, stopgrond));
		}

			for (int j = 0; j < cretenum3; j++)
			{
				float randroty = -D3DX_PI + frand() * D3DX_PI * 2.0f;
				float randrotx = -D3DX_PI * 0.1f + frand() * D3DX_PI * 0.6f;
				float spd = 30;
				float size = 20;
				float randsize = 20;
				m_Listparticle.push_back( new Particle_Flame(100, { pos.x ,pos.y - 190,pos.z }, { sinf(randroty) * cosf(randrotx) * spd, sinf(randrotx) * spd, cosf(randroty) * cosf(randrotx) * spd },
				{ size,size ,size }, D3DXCOLOR(1.0f, 0.7f, 0.0f, 0.9f + frand() * 0.4f), 0, 0.70f, 1.3f));
			}

		
	}
};
