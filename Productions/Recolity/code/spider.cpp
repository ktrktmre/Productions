//=============================================================================
//
// 敵処理 [spider.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "camera.h"
#include "spider.h"
#include "base_attribute.h"
#include "material.h"
#include "sprite.h"
#include "sound.h"
#include "floor.h"
#include "Game.h"
#include "card.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define HIT_POINT	(300)							// ヒットポイント
#define COLL_CIRCLE	(100.0f)						// 当たり判定の半径
#define BULLET_DAMAGE	(10)							// 通常弾のダメージ量
#define BULLET_SCALE	{30,30,30}						// 移動量
#define BULLET_SPEED	(30.0f)						// 移動量
#define BULLET_RANGE	(2500)						// 射程距離
#define SHOT_INTERVAL	(240)						// 射撃インターバル
#define DROPCHANSE			(0.75f)						//ドロップ率
#define DROPRANK2			(0.5f)						//ランク２率
//=============================================================================
// 引数付きコンストラクタ
//=============================================================================
Spider::Spider(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use, Bullet_Interface* pBif)
	:Base_Enemy(pos, rot, scl, vel, color, use, HIT_POINT, spider_enemy), m_LegIndex(0),m_BulletIF(pBif),m_Itv_b(SHOT_INTERVAL)
{
	SetPos({ pos.x,pos.y + 45.0f,pos.z });
	SetOldPos();
	//足ごとの初期角度テーブル
	float InitRotArray[] = { D3DXToRadian(5.0f),D3DXToRadian(22.0f),D3DXToRadian(30.0f),D3DXToRadian(18.0f),D3DXToRadian(0.0f),D3DXToRadian(40.0f) };
	//愛のインスタンス化
	for (int i = 0; i < SPIDER_LEG_NUM; i += 2)
	{
		//本体の中心点から足までの距離
		float length = sqrtf((DISTANCE_DIFF * SPIDER_LEG_WIDHT * (i / 2)) * (DISTANCE_DIFF * SPIDER_LEG_WIDHT * (i / 2)));

		m_Leg[i] = new Spider_Leg(D3DXVECTOR3(RefPos().x , RefPos().y, RefPos().z - DISTANCE_DIFF * SPIDER_LEG_WIDHT * (i / 2) )
			, D3DXVECTOR3(RefRot().x + (InitRotArray[i]), RefRot().y, RefRot().z)
			, RefScl(), RefVel(), RefColor(), true, length);

		m_Leg[i + 1] = new Spider_Leg(D3DXVECTOR3(RefPos().x , RefPos().y, RefPos().z - DISTANCE_DIFF * SPIDER_LEG_WIDHT * (i / 2))
			, D3DXVECTOR3(RefRot().x + (InitRotArray[i+1]), RefRot().y + D3DX_PI, RefRot().z)
			, RefScl(), RefVel(), RefColor(), true, -length);
	}

	//当たり判定の距離の設定
	SetColl(new Collision(this, {0,0,0}, 100));
	SetColl(new Collision(this, {0,0,0}, 160));

	// マテリアル設定
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = RefColor();	//拡散色
	GetMaterial()->Ambient = RefColor() * 0.3f;	//環境色
	GetMaterial()->Emission = RefColor() * 0.3f;	//自己発光色
	GetMaterial()->noTexSampling = 0;

	SetFootSteps(LoadSound("spider"));
	PlaySound(RefFootSteps(), -1, 0.0f);

}
//=============================================================================
// デストラクタ
//=============================================================================
Spider::~Spider()
{
	if (RefUse() == false)
	{

		if (frand() < DROPCHANSE)
		{
			CardDropChance(RefPos(), DROPRANK2);
		}

	}
	Uninit();
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Spider::Init(void)
{
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Spider::Uninit(void)
{
	//サウンドの解放
	StopSound(RefFootSteps());

	//足の解放
	for (int i = 0; i < SPIDER_LEG_NUM; i++)
	{
		delete m_Leg[i];
		m_Leg[i] = nullptr;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Spider::Update(void)
{
	//ドットダメージの更新
	Update_DotDamage();
	//アクション
	Action();
	//サーチアクション
	SearchAction();
	DistanceVolume(GetCamera()->pos);
	//近距離攻撃のクールタイム
	if (m_Attackdirei > 0)
	{
		m_Attackdirei--;
	}

	//カラー変更
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
	GetColl(0)->SetCollPos();
	GetColl(1)->SetCollPos({
		RefPos().x + 2.0f * RefScl().x * DISTANCE_DIFF * sinf(-RefRot().y),
		RefPos().y,
		RefPos().z - 2.0f * RefScl().z * DISTANCE_DIFF * cosf(-RefRot().y) });
	SetOldPos();
}

//=============================================================================
// 描画処理
//=============================================================================
void Spider::Draw(void)
{
	// 胴体モデルの描画
	Draw3DModel(*this, RefModelMaterial().m_Spider);

	//足モデルの描画
	for (int i = 0; i < SPIDER_LEG_NUM; i++)
	{
		m_Leg[i]->Draw();
	}
	//HPの表示
	Object hp;
	hp.m_Pos = { RefPos().x,RefPos().y + 130.0f,RefPos().z };
	hp.m_Uv_v = { 0.0f + 0.5f - 0.5f * ((RefHp() / (float)HIT_POINT)),0.0f };
	hp.m_Uv_f = { 0.5f,1.0f };
	hp.m_Scl = { 150.0f ,10.0f,0.0f };
	hp.m_Color = { 1.0f,0.0f,0.0f,1.0f };
	DrawPolygonBillX(hp, RefImageMaterial().m_Hp, 0);
	Draw_DotDamage();
#if _DEBUG
	//当たり判定の描画
	Object sphere;
	for (Collision* pColl : *GetColl())
	{
		sphere.m_Pos = pColl->RefCollPos();
		sphere.m_Scl = { pColl->RefCollCircle() ,pColl->RefCollCircle() ,pColl->RefCollCircle() };
		sphere.m_Rot = RefRot();
		//Draw3DModel(sphere, RefModelMaterial().m_Sphere);
	}
	
#endif // _DEBUG
}
//=============================================================================
// アクション
//=============================================================================
void Spider::Action(void)
{

	//足の角度、ポジションの設定
	for (int i = 0; i < SPIDER_LEG_NUM; i += 2)
	{
		m_Leg[i]->SetRot({ m_Leg[i]->RefRot().x,RefRot().y,m_Leg[i]->RefRot().z });
		m_Leg[i]->SetPos({
		RefPos().x + m_Leg[i]->RefLength() * sinf(RefRot().y + D3DX_PI),
		RefPos().y,
		RefPos().z + m_Leg[i]->RefLength() * cosf(RefRot().y + D3DX_PI) });

		m_Leg[i + 1]->SetRot({ m_Leg[i + 1]->RefRot().x,RefRot().y + D3DX_PI ,m_Leg[i + 1]->RefRot().z });
		m_Leg[i + 1]->SetPos({
		RefPos().x - m_Leg[i + 1]->RefLength() * sinf(RefRot().y + D3DX_PI),
		RefPos().y,
		RefPos().z - m_Leg[i + 1]->RefLength() * cosf(RefRot().y + D3DX_PI) });

		//足の更新
		m_Leg[i]->Update();
		m_Leg[i + 1]->Update();
	}
}
//=============================================================================
// プレイヤーとのアクション
//=============================================================================
void Spider::SearchAction(void)
{
	D3DXVECTOR3 Vec = GetCamera()->pos - RefPos();
	float length = D3DXVec3LengthSq(&Vec);
	if (length < 1000 * 1000)
	{
		//カメラ(プレイヤー)のいる方向へエネミーを向かせる処理
		D3DXVECTOR3 vec = D3DXVECTOR3(GetCamera()->pos.x - RefPos().x, GetCamera()->pos.y - RefPos().y, GetCamera()->pos.z - RefPos().z);
		float rot = -atan2f(vec.z, vec.x) + D3DX_PI / 2;
		SetRot(D3DXVECTOR3(0.0f, rot, 0.0f));
		//追跡
		Chase(GetCamera()->pos);
		SetPos({ RefPos().x,RefPos().y,RefPos().z });


		SetRot({ 0.0f,RefRot().y,RefRot().z });
		// 弾の発射
		m_Itv_b--;
		if (m_Itv_b >= 30 && m_Itv_b <= 50) {
			//弾の発射位置
			D3DXVECTOR3 pos = D3DXVECTOR3(RefPos().x + 10.0f * DISTANCE_DIFF * sinf(RefRot().y),
				RefPos().y + (RefScl().y + 2.0f * DISTANCE_DIFF),
				RefPos().z + 10.0f * DISTANCE_DIFF * cosf(RefRot().y));
			Emitta(7, pos);
		}
		if (m_Itv_b <= 0)
		{
			//弾の発射位置
			D3DXVECTOR3 pos = D3DXVECTOR3(RefPos().x + 10.0f * DISTANCE_DIFF * sinf(RefRot().y),
				RefPos().y + (RefScl().y +  80),
				RefPos().z + 10.0f * DISTANCE_DIFF * cosf(RefRot().y));
			//弾の発射速度
			D3DXVECTOR3 vel = D3DXVECTOR3(BULLET_SPEED * sinf(RefRot().y), 0.0f, BULLET_SPEED * cosf(RefRot().y));

			Attribute_Element element;
			element.m_Frame = 120;
			element.m_Interval = 0;
			element.m_Value = 3.0f;

			m_BulletIF->SetNBullet(bullet, enemy, pos, RefRot(), BULLET_SCALE, { 1.0f,1.0f,1.0f,1.0f }, BULLET_DAMAGE,
				BULLET_SPEED, NO_GVT, NO_DEC, BULLET_RANGE, water, element, &RefImageMaterial().m_Kumo_bullet,100);
			m_Itv_b = SHOT_INTERVAL;
		}
	}
	if (length < 300 * 300 && m_Attackdirei == 0)
	{
		m_Attackdirei = 90;
		GetPlayer()->IsDamage(15.0f);
	}
}
//=============================================================================
// ダメージを受ける
//=============================================================================
void Spider::IsDamage(float damage)
{
	//ダメージアクション(色変更)
	DamageAction(30);

	D3DXVECTOR3 pos = RefPos();
	pos.y += 150 - 30.0f + frand() * 60.0f;
	pos.x += -30.0f + frand() * 60.0f;
	pos.z += -30.0f + frand() * 60.0f;
	SetDamageText((int)damage, pos, DIK_COLER_WHITE);

	//ダメージの計算
	SetHp(RefHp() - damage);
	if (RefHp() <= 0) IsDiscard();

	//脚のアクション
	for (int i = 0; i < SPIDER_LEG_NUM; i++) m_Leg[i]->DamageAction(30);
}