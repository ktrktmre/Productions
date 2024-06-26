//=============================================================================
//
// 敵処理 [scorpion_tail.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "scorpion_tail.h"
#include "material.h"
#include "sprite.h"
#include "Game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BULLET_DAMAGE	(10)							// 通常弾のダメージ量
#define BULLET_SCALE	{30,30,30}						// 移動量
#define BULLET_SPEED	(30.0f)						// 移動量
#define BULLET_RANGE	(2500)						// 射程距離
#define SHOT_INTERVAL	(210)						// 射撃インターバル

//=============================================================================
// 引数付きコンストラクタ
//=============================================================================
Scorpion_Tail::Scorpion_Tail(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use, float len, Bullet_Interface* pBif)
	:Base_Enemy(pos, rot, scl, vel, color, use, NULL, scorpion_enemy),m_Reverse(1),m_Length(len),m_BulletIF(pBif),m_Itv_b(SHOT_INTERVAL)
{

	// マテリアル設定
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = RefColor();	//拡散色
	GetMaterial()->Ambient = RefColor();	//環境色
	GetMaterial()->Emission = RefColor();	//自己発光色
	GetMaterial()->noTexSampling = 0;
}
//=============================================================================
// デストラクタ
//=============================================================================
Scorpion_Tail::~Scorpion_Tail()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Scorpion_Tail::Init(void)
{
	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void Scorpion_Tail::Uninit(void)
{
}
//=============================================================================
// 更新処理
//=============================================================================
void Scorpion_Tail::Update(void)
{
	//アクション
	Action();

	//カラー変更
	if (RefHitFrame() > 0) {
		SetHitFrame(RefHitFrame() - 1);
	}
	else {
		GetMaterial()->Diffuse = RefColor();	//拡散色
		GetMaterial()->Ambient = RefColor();	//環境色
		GetMaterial()->Emission = RefColor();	//自己発光色
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void Scorpion_Tail::Draw(void)
{
	// 尻尾モデルの描画
	Draw3DModel(*this, RefModelMaterial().m_Scorpion_Tail);

}
//=============================================================================
// アクション
//=============================================================================
void Scorpion_Tail::Action(void)
{
	SetRot({ RefRot().x + VALUE_TAIL_ROTATE * m_Reverse,RefRot().y,RefRot().z });
	if (RefRot().x >= LIMIT_TAIL_ANGLE || RefRot().x <= -LIMIT_TAIL_ANGLE)
	{
		m_Reverse *= -1;
	}
}
//=============================================================================
// プレイヤーとのアクション
//=============================================================================
void Scorpion_Tail::SearchAction(void)
{
	SetRot({ 0.0f,RefRot().y,RefRot().z });
	// 弾の発射
	m_Itv_b--;
	if (m_Itv_b >= 30 && m_Itv_b <= 50) {
		D3DXVECTOR3 pos = D3DXVECTOR3(RefPos().x + 20.0f * DISTANCE_DIFF * sinf(RefRot().y),
			RefPos().y + (RefScl().y + 1.0f * DISTANCE_DIFF),
			RefPos().z + 20.0f * DISTANCE_DIFF * cosf(RefRot().y));
		Emitta(6, pos);
	}
	if (m_Itv_b <= 0)
	{
		//弾の発射位置
		D3DXVECTOR3 pos = D3DXVECTOR3(RefPos().x + 20.0f * DISTANCE_DIFF * sinf(RefRot().y),
			RefPos().y + (RefScl().y + 2.0f * DISTANCE_DIFF),
			RefPos().z + 20.0f * DISTANCE_DIFF * cosf(RefRot().y));

		//弾の発射速度
		D3DXVECTOR3 vel = D3DXVECTOR3(BULLET_SPEED * sinf(RefRot().y), 0.0f, BULLET_SPEED * cosf(RefRot().y));

		Attribute_Element element;
		element.m_Frame = 300;
		element.m_Interval = 6;
		element.m_Value = 0.1f;

		m_BulletIF->SetNBullet(bullet, enemy, pos, RefRot(), BULLET_SCALE, { 1.0f,1.0f,1.0f,1.0f }, BULLET_DAMAGE,
			BULLET_SPEED, NO_GVT, NO_DEC, BULLET_RANGE, fire, element, &RefImageMaterial().m_sasori_bullet);
		m_Itv_b = SHOT_INTERVAL;
	}
}
