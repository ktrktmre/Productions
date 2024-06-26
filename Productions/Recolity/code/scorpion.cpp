//=============================================================================
//
// 敵処理 [scorpion.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "scorpion.h"
#include "material.h"
#include "sprite.h"
#include "floor.h"
#include "Game.h"
#include "card.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define HIT_POINT	(300)							// ヒットポイント
#define COLL_CIRCLE	(100.0f)						// 当たり判定の半径
#define DROPCHANSE			(0.55f)						//ドロップ率
#define DROPRANK2			(0.5f)						//ランク２率
#define HEARING_DISTANCE (1300*1300)
//=============================================================================
// 引数付きコンストラクタ
//=============================================================================
Scorpion::Scorpion(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use,Bullet_Interface* pBif)
	:Base_Enemy(pos, rot, scl, vel, color, use, HIT_POINT, scorpion_enemy), m_LegIndex(0)
{
	SetPos({ pos.x,45.0f,pos.z });

	//本体の中心点から尻尾までの距離
	float length; 
	length = sqrtf((0.03f * DISTANCE_DIFF * SCORPION_SCALE) * (0.03f * DISTANCE_DIFF * SCORPION_SCALE) + (-0.44f * DISTANCE_DIFF * SCORPION_SCALE) * (-0.44f * DISTANCE_DIFF * SCORPION_SCALE));
	//尻尾のインスタンス化
	m_Tail = new Scorpion_Tail(D3DXVECTOR3(RefPos().x, RefPos().y + (0.03f * DISTANCE_DIFF * SCORPION_SCALE), RefPos().z + (-0.44f * DISTANCE_DIFF * SCORPION_SCALE))
		, RefRot(), RefScl(), RefVel(), RefColor(), true, length, pBif);

	//足ごとの初期角度テーブル
	float InitRotArray[] = { D3DXToRadian(5.0f),D3DXToRadian(22.0f),D3DXToRadian(30.0f),D3DXToRadian(18.0f),D3DXToRadian(0.0f),D3DXToRadian(40.0f) };
	//脚のインスタンス化
	for (int i = 0; i < SCORPION_LEG_NUM; i += 2)
	{
		//本体の中心点から足までの距離
		length = sqrtf(DISTANCE_DIFF * SCORPION_LEG_WIDHT * (i / 2) * DISTANCE_DIFF * SCORPION_LEG_WIDHT * (i / 2));

		m_Leg[i] = new Scorpion_Leg(D3DXVECTOR3(RefPos().x, RefPos().y, RefPos().z - DISTANCE_DIFF * SCORPION_LEG_WIDHT * (i / 2))
			, D3DXVECTOR3(RefRot().x + (InitRotArray[i]), RefRot().y, RefRot().z)
			, RefScl(), RefVel(), RefColor(), true, length);

		m_Leg[i + 1] = new Scorpion_Leg(D3DXVECTOR3(RefPos().x, RefPos().y, RefPos().z - DISTANCE_DIFF * SCORPION_LEG_WIDHT * (i / 2))
			, D3DXVECTOR3(RefRot().x + (InitRotArray[i+1]), RefRot().y + D3DX_PI, RefRot().z)
			, RefScl(), RefVel(), RefColor(), true, -length);
	}
	
	//当たり判定の距離の設定
	SetColl(new Collision(this, {0,0,0}, 100));
	SetOldPos();
	// マテリアル設定
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = RefColor();	//拡散色
	GetMaterial()->Ambient = RefColor() * 0.3f;	//環境色
	GetMaterial()->Emission = RefColor() * 0.3f;	//自己発光色
	GetMaterial()->noTexSampling = 0;

	SetFootSteps(LoadSound("scorpion"));
	PlaySound(RefFootSteps(), -1, 0.0f);
}
//=============================================================================
// デストラクタ
//=============================================================================
Scorpion::~Scorpion()
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
HRESULT Scorpion::Init(void)
{
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Scorpion::Uninit(void)
{
	//尻尾の解放
	delete m_Tail;
	m_Tail = nullptr;
	StopSound(RefFootSteps());
	//足の解放
	for (int i = 0; i < SCORPION_LEG_NUM; i++)
	{
		delete m_Leg[i];
		m_Leg[i] = nullptr;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Scorpion::Update(void)
{
	DistanceVolume(GetCamera()->pos);
	//ドットダメージの更新
	Update_DotDamage();
	//アクション
	Action();
	//サーチアクション
	SearchAction();
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
		SetColor({ 1.0f,1.0f,1.0f,1.0f });
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
	for (Collision* pColl : *GetColl())
	{
		pColl->SetCollPos();
	}
	SetOldPos();
}

//=============================================================================
// 描画処理
//=============================================================================
void Scorpion::Draw(void)
{
	//カリングを消す
	SetCullingMode(CULL_MODE_NONE);
	// 胴体モデルの描画
	Draw3DModel(*this, RefModelMaterial().m_Scorpion);
	//裏側をカリング
	SetCullingMode(CULL_MODE_BACK);

	//尻尾モデルの描画
	m_Tail->Draw();

	//脚モデルの描画
	for (int i = 0; i < SCORPION_LEG_NUM; i++)
	{
		m_Leg[i]->Draw();
	}
	//HPの表示
	Object hp;
	hp.m_Pos = { RefPos().x,RefPos().y  + 130.0f,RefPos().z };
	hp.m_Uv_v = { 0.0f + 0.5f - 0.5f * ((RefHp() / (float)HIT_POINT)),0.0f };
	hp.m_Uv_f = { 0.5f,1.0f };
	hp.m_Scl = { 150.0f ,10.0f,0.0f };
	hp.m_Color = { 1.0f,0.0f,0.0f,1.0f };
	DrawPolygonBillX(hp, RefImageMaterial().m_Hp, 0);
	Draw_DotDamage();
#if _DEBUG
	//当たり判定球の設定
	Object sphere;
	for (Collision* pColl : *GetColl())
	{
		sphere.m_Pos = pColl->RefCollPos();
		sphere.m_Scl = { COLL_CIRCLE ,COLL_CIRCLE ,COLL_CIRCLE };
		sphere.m_Rot = RefRot();
		//Draw3DModel(sphere, RefModelMaterial().m_Sphere);
	}
	
#endif // _DEBUG
}
//=============================================================================
// アクション
//=============================================================================
void Scorpion::Action(void)
{
	//尻尾の角度、ポジションの設定
	m_Tail->SetRot({ m_Tail->RefRot().x,RefRot().y,m_Tail->RefRot().z });
	m_Tail->SetPos({
		RefPos().x + m_Tail->RefLength() * sinf(RefRot().y + D3DX_PI),
		RefPos().y + (0.03f * DISTANCE_DIFF * SCORPION_SCALE),
		RefPos().z + m_Tail->RefLength() * cosf(RefRot().y + D3DX_PI) });
	//尻尾の更新
	m_Tail->Update();

	//足の角度、ポジションの設定
	for (int i = 0; i < SCORPION_LEG_NUM; i += 2)
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
void Scorpion::SearchAction(void)
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

		m_Tail->SearchAction();
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
void Scorpion::IsDamage(float damage)
{
	//ダメージアクション(色変更)
	DamageAction(30);

	D3DXVECTOR3 pos = RefPos();
	pos.y += 50 - 30.0f + frand() * 60.0f;
	pos.x += -30.0f + frand() * 60.0f;
	pos.z += -30.0f + frand() * 60.0f;
	SetDamageText((int)damage, pos, DIK_COLER_WHITE);

	//ダメージの計算
	SetHp(RefHp() - damage);
	if (RefHp() <= 0) IsDiscard();

	//脚のアクション
	for (int i = 0; i < SCORPION_LEG_NUM; i++) m_Leg[i]->DamageAction(30);

	//尻尾のアクション
	m_Tail->DamageAction(30);
}

//=============================================================================
// 距離による音量の調整
//=============================================================================
void Scorpion::DistanceVolume(D3DXVECTOR3 pos)
{
	//2点間の距離の2乗値の取得
	D3DXVECTOR3 vec = RefPos() - pos;
	float length = D3DXVec3LengthSq(&vec);

	//距離による音量の調整
	if (length > HEARING_DISTANCE) {
		SetVolume(RefFootSteps(), 0);
	}
	else {
		float rate = length / HEARING_DISTANCE;
		SetVolume(RefFootSteps(), 1.0f - rate);
	}
}