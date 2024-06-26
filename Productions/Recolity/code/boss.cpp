//=============================================================================
//
// 敵処理 [boss.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "camera.h"
#include "boss.h"
#include "material.h"
#include "sprite.h"
#include "fire_attribute.h"
#include "floor.h"
#include "Game.h"
#include "scene.h"
#include "fade.h"
#include "sound.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define HIT_POINT	(350)							// ヒットポイント
#define COLL_CIRCLE	(100.0f)						// 当たり判定の半径
#define BULLET_DAMAGE	(4)							// 通常弾のダメージ量
#define BULLET_SCALE	{30,30,30}						// 通常弾のサイズ
#define BULLET_SPEED	(25.0f)						// 通常弾の移動量
#define BULLET_RANGE	(3000)						// 通常弾の射程距離
#define CANNON_DAMAGE	(10)						// 大砲のダメージ量
#define CANNON_SCALE	{150,150,150}				// 大砲のサイズ
#define CANNON_SPEED	(15.0f)						// 大砲の移動量
#define CANNON_GVT		(1.0f)						// 大砲の重力
#define CANNON_FALL_AMOUNT	(0.5f)					// 落下量
#define CANNON_RANGE	(10000)						// 大砲の射程距離
#define NORMAL_SHOT_INTERVAL	(127)				// 通常弾の射撃インターバル
#define CANNON_SHOT_INTERVAL	(300)				// 大砲の射撃インターバル

#define HEARING_DISTANCE (1300*1300)
//=============================================================================
// 引数付きコンストラクタ
//=============================================================================
Boss::Boss(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use, Bullet_Interface* bif)
	:Base_Enemy(pos, rot, scl, vel, color, use, HIT_POINT, boss_enemy),
	m_Itv_b(NORMAL_SHOT_INTERVAL), m_Itv_c(CANNON_SHOT_INTERVAL),m_BulletIF(bif)
{
	
	//当たり判定の設定
	SetColl(new Collision(this, {0.0f,100.0f,0.0f}, 150));
	SetColl(new Collision(this, { 0.0f,300.0f,0.0f }, 150));
	// マテリアル設定
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = RefColor();	//拡散色
	GetMaterial()->Ambient = RefColor() * 0.3f;	//環境色
	GetMaterial()->Emission = RefColor() * 0.3f;	//自己発光
	GetMaterial()->noTexSampling = 0;

	m_BulletSound = LoadSound("bossbullet1");
	m_CannonSound = LoadSound("bossbullet2");
}
//=============================================================================
// デストラクタ
//=============================================================================
Boss::~Boss()
{
	Uninit();
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Boss::Init(void)
{
	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void Boss::Uninit(void)
{
	StopSound(m_BulletSound);
	StopSound(m_CannonSound);
	if (RefUse() == false)
	{
		SceneTransition(SCENE_RESULT);
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void Boss::Update(void)
{
	DistanceVolume(GetCamera()->pos);
	SetOldPos();
	//アクション
	SearchAction();
	Update_DotDamage();
	if (GetNowAdhere(RefPos()) == Floor_flame)
	{
		IsDamageDot(3.0f / 60.0f);
	}
	//カラーの変更
	if (RefHitFrame() > 0) {
		SetHitFrame(RefHitFrame() - 1);
	}
	else {
		GetMaterial()->Diffuse = RefColor();	//拡散色
		GetMaterial()->Ambient = RefColor() * 0.3f;	//環境色
		GetMaterial()->Emission = RefColor() * 0.3f;	//自己発光色
	}
	//床ダメージ
	if (GetNowAdhere(RefPos()) == Floor_flame)
	{
		IsDamageDot(3.0f / 60.0f);
	}
	//受けた属性の処理
	for (int index = 0; index < ATTRIBUTE_NUM; index++)
	{
		if (GetAttribute(index) != nullptr)
			GetAttribute(index)->AttributeByType(this);
	}
	//フロア効果の適応
	GetFloorPos();

	//当たり判定の再設定
	for (Collision* pColl:*GetColl())
	{
		pColl->SetCollPos();
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void Boss::Draw(void)
{
	Draw3DModel(*this, RefModelMaterial().m_Boss);
	Draw_DotDamage();
	//HPの表示
	Object hp;
	hp.m_Pos = { RefPos().x,RefPos().y + 450.0f,RefPos().z };
	hp.m_Uv_v = { 0.0f + 0.5f - 0.5f * ((RefHp() / (float)HIT_POINT)),0.0f };
	hp.m_Uv_f = { 0.5f,1.0f };
	hp.m_Scl = { 200.0f ,20.0f,0.0f };
	hp.m_Color = { 1.0f,0.0f,0.0f,1.0f };
	DrawPolygonBillX(hp, RefImageMaterial().m_Hp, 0);
#if _DEBUG
	//当たり判定の描画
	Object sphere;
	for (Collision* pColl : *GetColl())
	{
		sphere.m_Pos = pColl->RefCollPos();
		sphere.m_Scl = { COLL_CIRCLE ,COLL_CIRCLE ,COLL_CIRCLE };
		sphere.m_Rot = RefRot();
		Draw3DModel(sphere, RefModelMaterial().m_Sphere);
	}
	
#endif // _DEBUG
}
//=============================================================================
// アクション
//=============================================================================
void Boss::Action(void)
{
	CAMERA* pCam = GetCamera();

	// カメラ(プレイヤー)のいる方向へエネミーを向かせる処理
	D3DXVECTOR3 Vec = D3DXVECTOR3(pCam->pos.x - RefPos().x, pCam->pos.y - RefPos().y - 200.0f, pCam->pos.z - RefPos().z);
	float rot_y = -atan2f(Vec.z, Vec.x) + D3DX_PI / 2.0f;
	float rot_x = atan2f(Vec.y, Vec.z);
	SetRot(D3DXVECTOR3(0.0f, rot_y, 0.0f));

	// 大砲の発射
	m_Itv_c--;
	if (m_Itv_c <= 0)
	{
		PlaySound(m_CannonSound, 0, 1.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(
			RefPos().x,
			RefPos().y + (12.5f * DISTANCE_DIFF * BOSS_SCALE),
			RefPos().z
		);

		Attribute_Element element;
		element.m_Frame = 30;
		element.m_Interval = 10;
		element.m_Value = 1.0f;
		Emitta(2, { GetCamera()->pos.x,0,GetCamera()->pos.z });
		m_BulletIF->SetCBullet(cannon, enemy, pos, GetCamera()->pos, { 45.0f,RefRot().y,0.0f }, CANNON_SCALE, { 1.0f,1.0f,0.0f,1.0f }, CANNON_DAMAGE,
			CANNON_SPEED, CANNON_GVT, NO_DEC, CANNON_RANGE, none, element, &RefImageMaterial().m_Cannon_Bullet);
		m_Itv_c = CANNON_SHOT_INTERVAL;
	}

	// 通常弾の発射
	m_Itv_b--;
	if (m_Itv_b <= 0 )
	{
		PlaySound(m_BulletSound, 0, 1.0f);
		float len = sqrtf((1.7f * DISTANCE_DIFF * BOSS_SCALE) * (1.7f * DISTANCE_DIFF * BOSS_SCALE) + (5.4f * DISTANCE_DIFF * BOSS_SCALE) * (5.4f * DISTANCE_DIFF * BOSS_SCALE));
		D3DXVECTOR3 pos = D3DXVECTOR3(
			RefPos().x + len * sinf(rot_y + D3DXToRadian(18.0f)),
			RefPos().y + (3.5f * DISTANCE_DIFF * BOSS_SCALE),
			RefPos().z + len * cosf(rot_y + D3DXToRadian(18.0f))
		);
		Attribute_Element element;
		element.m_Frame = 30;
		element.m_Interval = 10;
		element.m_Value = 0.5f;
		m_BulletIF->SetNBullet(bullet, enemy, pos, { 0.0f,RefRot().y - D3DXToRadian(5.0f),0.0f }, BULLET_SCALE, { 1.0f,1.0f,1.0f,1.0f }, BULLET_DAMAGE,
			BULLET_SPEED, NO_GVT, NO_DEC, BULLET_RANGE, none, element, &RefImageMaterial().m_EnemyBulletCannon);

		m_Itv_b = NORMAL_SHOT_INTERVAL;
	}
}
//=============================================================================
// プレイヤーとのアクション
//=============================================================================
void Boss::SearchAction(void)
{
	D3DXVECTOR3 Vec = GetCamera()->pos - RefPos();
	float length = D3DXVec3LengthSq(&Vec);
	if (length < 2000 * 2000)
	{
		Action();
	}
	if (length < 300 * 300)
	{
		GetPlayer()->IsDamage(0.5f);
	}
}
