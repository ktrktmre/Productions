//=============================================================================
//
// 弾処理 [cannon_bullet.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "cannon_bullet.h"
#include "normal_bullet_life_penetration.h"
#include "material.h"
#include "sprite.h"
#include "Game.h"
#include "floor.h"
#include "Game.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//=============================================================================
// 引数付きコンストラクタ
//=============================================================================
Cannon_Bullet::Cannon_Bullet(Bullet_Interface* bif, D3DXVECTOR3 pos, D3DXVECTOR3 des, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use,
	Bullet_Side side, int damage, float speed, float gvt, D3DXVECTOR2 uv_v, D3DXVECTOR2 uv_f, Attribute_Type att_type, Attribute_Element att_element, int* tex, DX11_MODEL* model, float circle)
	:Base_Bullet(pos, rot, scl, vel, color, use, cannon, side, damage, speed, gvt, NO_DEC, NULL, uv_v, uv_f, att_type, att_element, tex, model),m_Bif(bif),m_Destination(des)
{
	//当たり判定の設定
	SetColl(new Collision(this, {0.0f,0.0f,0.0f},circle));
	m_Penetration = true;
	// マテリアル設定
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = RefColor();
	GetMaterial()->Ambient = RefColor();
	GetMaterial()->noTexSampling = 0;

	Trajectory();
}
//=============================================================================
// デストラクタ
//=============================================================================
Cannon_Bullet::~Cannon_Bullet()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Cannon_Bullet::Init(void)
{
	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void Cannon_Bullet::Uninit(void)
{

}
//=============================================================================
// 更新処理
//=============================================================================
void Cannon_Bullet::Update(void)
{
	Move();

	//当たり判定の再設定
	for (Collision* pColl : *GetColl())
	{
		pColl->SetCollPos();
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void Cannon_Bullet::Draw(void)
{
	if (GetModelId() != nullptr)
	{
		Draw3DModel(*this, *GetModelId());
	}
	else
	{
		DrawPolygonBill(*this, RefTexId(), RefUv_v(), RefUv_f());
	}

	
}
//=============================================================================
// 弾の動き
//=============================================================================
void Cannon_Bullet::Move(void)
{
	//弾の移動
	SetPos(RefPos() + RefVel());

	//残りの射程距離
	SetRange((int)((float)RefRange() - (float)RefSpeed()));

	//減速と落下
	SetVel({
		RefVel().x * RefDec(),
		RefVel().y + RefGvt(),
		RefVel().z * RefDec() });

	//基底スピードの調整
	SetSpeed(RefSpeed() * RefDec());

	//レンジが0以下になるか、弾のy軸が0以下になったら
	if (RefPos().y <= 0)
	{
		IsDiscard();
		Floor_Adhere ad = Floor_None;
		if (RefAttType() == fire)
		{
			 ad = Floor_flame;
		}
		if (RefAttType() == water)
		{
			 ad = Floor_Water;
		}
		SetAdhere(RefPos(), ad, 600);

		Attribute_Element element;
		element.m_Frame = 30;
		element.m_Interval = 10;
		element.m_Value = 0.3f;
		m_Bif->SetNBullet(life_penetration, RefSide(), { RefPos().x,1.0f,RefPos().z }, NO_VECTOR3, NO_VECTOR3,
			{ 1.0f,1.0f,1.0f,1.0f },
			RefDamage(),
			45, NO_GVT, NO_DEC, 9999999,
			fire, element,
			&RefImageMaterial().m_Cannon_Bullet, 800);
		Emitta(1, RefPos());
	}
}
//=============================================================================
// 弾道計算
//=============================================================================
void Cannon_Bullet::Trajectory(void)
{
	D3DXVECTOR2 vecXZ = { m_Destination.x - RefPos().x,m_Destination.z - RefPos().z };
	float lenght = D3DXVec2Length(&vecXZ);
	int frame = (int)(lenght / RefSpeed());
	float height = m_Destination.y - RefPos().y * 2;
	float gravity = (2.0f * height) / (float)pow(frame, 2) - (2 * RefSpeed()) / frame;
	SetGvt(gravity);
	SetVel(D3DXVECTOR3(RefSpeed() * sinf(RefRot().y), RefSpeed(), RefSpeed() * cosf(RefRot().y)));
}