//=============================================================================
//
// 敵処理 [boss.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "camera.h"
#include "boss3_main.h"
#include "material.h"
#include "sprite.h"
#include "fire_attribute.h"
#include "floor.h"
#include "Game.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define HIT_POINT	(3000)							// ヒットポイント
#define COLL_CIRCLE	(300.0f)						// 当たり判定の半径
#define BULLET_DAMAGE	(20)							// 通常弾のダメージ量
#define BULLET_DAMAGE_RAIN	(20)							// 通常弾のダメージ量
#define BULLET_DAMAGE_HOOK	(20)							// 通常弾のダメージ量
#define BULLET_DAMAGE_BALL	(10)							// 通常弾のダメージ量
#define BULLET_DAMAGE_BOM	(20)							// 通常弾のダメージ量
#define BULLET_SCALE	{25,25,25}						// 通常弾のサイズ
#define BULLET_SPEED	(50.0f)						// 通常弾の移動量
#define NORMAL_SHOT_INTERVAL	(90)				// 通常弾の射撃インターバル
#define CANNON_SHOT_INTERVAL	(120)				// 大砲の射撃インターバル

#define NOMALATTACK_CD (90)
#define CARDATTACK_CD (470)
//=============================================================================
// 引数付きコンストラクタ
//=============================================================================
Boss3_Main::Boss3_Main(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use, Bullet_Interface* bif)
	:Base_Enemy(pos, rot, scl, vel, color, use, HIT_POINT, boss_enemy),
	m_Itv_b(NORMAL_SHOT_INTERVAL), m_Itv_c(CANNON_SHOT_INTERVAL), m_BulletIF(bif)
{
	SetPos({ pos.x,pos.y + 400,pos.z });
	//当たり判定の設定
	SetColl(new Collision(this, { 0.0f,0.0f,0.0f }, 470));
	SetOldPos();
	m_state = Boss3_idol;
	cd = 0;
	// マテリアル設定
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = RefColor();	//拡散色
	GetMaterial()->Ambient = RefColor();	//環境色
	GetMaterial()->noTexSampling = 0;
}
//=============================================================================
// デストラクタ
//=============================================================================
Boss3_Main::~Boss3_Main()
{
	Uninit();
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Boss3_Main::Init(void)
{
	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void Boss3_Main::Uninit(void)
{
}
//=============================================================================
// 更新処理
//=============================================================================
void Boss3_Main::Update(void)
{
	SetOldPos();
	//アクション
	SearchAction();
	Update_DotDamage();
	if (nomalattack > 0)
	{
		nomalattack--;
	}
	if (m_card != Boss3_None)
	{
		m_card_attacktime++;
	}
	if (cardattackcd > 0)
	{
		cardattackcd--;
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
	//受けた属性の処理
	for (int index = 0; index < 1; index++)
	{
		if (GetAttribute(index) != nullptr)
			GetAttribute(index)->AttributeByType(this);
	}

	//当たり判定の再設定
	for (Collision* pColl : *GetColl())
	{
		pColl->SetCollPos();
	}
	//何もない時の状態
	if (m_state == Boss3_idol)
	{
		idoltime += 0.03f;
		SetPos({ RefPos().x,400.0f + sinf(idoltime) * 30.0f, RefPos().z });
		if (m_agro == true)
		{
			cd++;
			if (cardattackcd <= 0)
			{
				CardAttack();
			}

			if (cd > 420)
			{
				cd = (int)(frand() * 120.0f);
				StateSwap_Move({ 100.0f + frand() * 2800.0f,0, 7100.0f + frand() * 2800.0f });
			}
		}

	}
	//移動状態
	if (m_state == Boss3_move)
	{
		m_MoveStatetime--;
		if (m_MoveStatetime < 0)
		{
			StateSwap_Idol();
		}
		SetPos({ RefPos().x + m_MoveStatepos.x,RefPos().y ,RefPos().z + m_MoveStatepos.y });
	}
	//カード選択状態
	if (m_state == Boss3_card_attack)
	{
		m_Card_attackcelecttime++;
		if (m_Card_attackcelecttime == 150)
		{
			m_card = (Card3Sclect)((int)rand() % 4 + 1);
			StateSwap_Idol();
			m_card_attacktime = 0;
		}
	}
	//選択後の効果
	if (m_card == Boss3_FireRain)
	{
		if (m_card_attacktime > 100)
		{
			m_card = Boss3_None;
		}
		Attribute_Element element;
		element.m_Frame = 300;
		element.m_Interval = 12;
		element.m_Value = 0.5f;
		D3DXVECTOR3 pos = { 100.0f + frand() * 2800.0f,8000, 7100.0f + frand() * 2800.0f };
		Emitta(8, { pos.x,1.0f + (float)m_card_attacktime * 0.0001f,pos.z });
		m_BulletIF->SetNBullet(bullet, enemy, pos, { D3DX_PI * -0.5f,0.0f,0.0f }, BULLET_SCALE, { 1.0f,1.0f,1.0f,1.0f }, BULLET_DAMAGE_RAIN,
			BULLET_SPEED, NO_GVT, NO_DEC, 210000000, fire, element, &RefImageMaterial().m_Cannon_Bullet, 150);

	}
	if (m_card == Boss3_Hook)
	{
		if (m_card_attacktime == 60)
		{
			m_card = Boss3_None;
			Attribute_Element element;
			element.m_Frame = 300;
			element.m_Interval = 12;
			element.m_Value = 0.2f;
			CAMERA* pCam = GetCamera();
			D3DXVECTOR3 Vec = D3DXVECTOR3(pCam->pos.x - RefPos().x, pCam->pos.y - RefPos().y + 100.0f, pCam->pos.z - RefPos().z);
			float range2 = sqrt(powf(Vec.x, 2) + powf(Vec.z, 2));
			float lanege = powf(Vec.x, 2) + powf(Vec.y, 2) + powf(Vec.z, 2);
			Vec = { Vec.x / lanege,Vec.y / lanege ,Vec.z / lanege };
			float rot_y = -atan2f(Vec.z, Vec.x) + D3DX_PI / 2.0f;
			float rot_x = atan2f(pCam->pos.y - RefPos().y - 100.0f, range2);
			m_BulletIF->SetNBullet(hook, enemy, RefPos(), { rot_x ,rot_y ,0 }, BULLET_SCALE, { 1.0f,1.0f,1.0f,1.0f }, BULLET_DAMAGE_HOOK,
				BULLET_SPEED, NO_GVT, NO_DEC, 4000, none, element, &RefModelMaterial().m_Kama);
		}

	}
	if (m_card == Boss3_Ball)
	{

		if (m_card_attacktime == 180)
		{
			m_card = Boss3_None;
			Attribute_Element element;
			element.m_Frame = 300;
			element.m_Interval = 12;
			element.m_Value = 0.2f;
			CAMERA* pCam = GetCamera();
			D3DXVECTOR3 Pos;
			for (int i = 0; i < 7; i++)
			{
				float randscl = 400.0f;
				float xrand = frand() * randscl - randscl * 0.5f;
				float zrand = frand() * randscl - randscl * 0.5f;
				Pos = {
					RefPos().x + sinf(RefRot().y - D3DX_PI * 0.5f) * cosf((D3DX_PI / 7) * 2.0f * (float)i) * 300.0f,
					RefPos().y + sinf((D3DX_PI / 7) * 2.0f * (float)i) * 300.0f,
					RefPos().z + cosf(RefRot().y - D3DX_PI * 0.5f) * cosf((D3DX_PI / 7) * 2.0f * (float)i) * 300.0f };
				D3DXVECTOR3 Vec = D3DXVECTOR3(pCam->pos.x - Pos.x + xrand, pCam->pos.y - Pos.y - 100, pCam->pos.z - Pos.z + zrand);

				float range2 = sqrt(powf(Vec.x, 2) + powf(Vec.z, 2));
				float lanege = powf(Vec.x, 2) + powf(Vec.y, 2) + powf(Vec.z, 2);
				Vec = { Vec.x / lanege,Vec.y / lanege ,Vec.z / lanege };
				float rot_y = -atan2f(Vec.z, Vec.x) + D3DX_PI / 2.0f;
				float rot_x = atan2f(pCam->pos.y - Pos.y - 100.0f, range2);
				m_BulletIF->SetNBullet(bullet, enemy, Pos, { rot_x ,rot_y ,0 }, { 85,85,85 }, { 1.0f,1.0f,1.0f,1.0f }, BULLET_DAMAGE_BALL,
					BULLET_SPEED, NO_GVT, NO_DEC, 30000, none, element, &RefImageMaterial().m_Boss_Bullet, 150);
			}


		}

	}
	if (m_card == Boss3_Blast)
	{
		if (m_card_attacktime == 60)
		{

			m_card = Boss3_None;
			Attribute_Element element;
			element.m_Frame = 300;
			element.m_Interval = 12;
			element.m_Value = 0.2f;




			for (int j = 0; j < 8; j++)
			{
				CAMERA* pCam = GetCamera();
				D3DXVECTOR3 Pos = RefPos();
				D3DXVECTOR3 Vec = D3DXVECTOR3(sinf(RefRot().y + D3DX_PI + D3DX_PI * 0.25f * (float)j), 0, cosf(RefRot().y + D3DX_PI + D3DX_PI * 0.25f * (float)j));
				for (int i = 1; i < 10; i++)
				{
					D3DXVECTOR3 pos = { RefPos().x + Vec.x * (float)i * 400.0f,0.1f ,RefPos().z + Vec.z * (float)i * 400.0f };
					if (GetNowFloor(pos) != Floor_Wall)
					{
						Emitta(10, pos);
						m_BulletIF->SetNBullet(time_bom, enemy, pos, { D3DX_PI * -0.5f,0.0f,0.0f }, BULLET_SCALE, { 1.0f,1.0f,1.0f,1.0f }, BULLET_DAMAGE_BOM,
							BULLET_SPEED, NO_GVT, NO_DEC, 210000000, fire, element, &RefImageMaterial().m_Cannon_Bullet, 150);
					}

				}
			}
		}


	}

}

//=============================================================================
// 描画処理
//=============================================================================
void Boss3_Main::Draw(void)
{


	int bosscardtex[4];
	bosscardtex[0] = RefImageMaterial().BossCard_Hook;
	bosscardtex[1] = RefImageMaterial().BossCard_Blast;
	bosscardtex[2] = RefImageMaterial().BossCard_7boll;
	bosscardtex[3] = RefImageMaterial().BossCard_Firelain;

	if (m_state == Boss3_card_attack && m_Card_attackcelecttime < 149)
	{
		Object carddraw;
		float size = 60.0f;
		carddraw.m_Pos = RefPos();
		carddraw.m_Pos.x += sinf(RefRot().y - D3DX_PI) * 240.0f;
		carddraw.m_Pos.z += cosf(RefRot().y - D3DX_PI) * 240.0f;
		carddraw.m_Scl = { size ,size * 1.561f ,size };
		D3DXCOLOR coler = { 1.0f,1.0f ,1.0f ,1.0f };
		int yplus = 60;
		if (m_Card_attackcelecttime < 60)
		{
			yplus = m_Card_attackcelecttime;
		}
		if (m_Card_attackcelecttime < 45)
		{
			coler.a = (float)m_Card_attackcelecttime / 45.0f;
		}
		carddraw.m_Color = coler;
		ZeroMemory(&carddraw.m_Material, sizeof(&carddraw.m_Material));
		carddraw.m_Material.Ambient = carddraw.m_Color;
		carddraw.m_Material.Emission = carddraw.m_Color;
		carddraw.m_Material.Diffuse = carddraw.m_Color;
		for (int i = 0; i < 4; i++)
		{
			DrawPolygonBillXY(carddraw, bosscardtex[i], -90.0f + (float)i * 60.0f, -30.0f + (float)yplus);
		}
	}
	if (m_card != Boss3_None)
	{
		Object cardcelect;
		float size = 100.0f;
		cardcelect.m_Pos = RefPos();
		cardcelect.m_Pos.x += sinf(RefRot().y - D3DX_PI) * 260.0f;
		cardcelect.m_Pos.z += cosf(RefRot().y - D3DX_PI) * 260.0f;
		cardcelect.m_Scl = { size ,size * 1.561f ,size };
		D3DXCOLOR coler = { 1.0f,1.0f ,1.0f ,1.0f };
		cardcelect.m_Color = coler;
		ZeroMemory(&cardcelect.m_Material, sizeof(&cardcelect.m_Material));
		cardcelect.m_Material.Ambient = cardcelect.m_Color;
		cardcelect.m_Material.Emission = cardcelect.m_Color;
		cardcelect.m_Material.Diffuse = cardcelect.m_Color;

		DrawPolygonBillXY(cardcelect, bosscardtex[m_card - 1], 0, 0);
	}

	if (m_card == Boss3_Ball && m_card_attacktime > 30)
	{
		float rot = m_card_attacktime * 0.025f;
		float a = (float)(m_card_attacktime - 30) * 0.02f;
		Object cardcelect;
		float size = 100.0f;
		cardcelect.m_Pos = RefPos();
		cardcelect.m_Scl = { size ,size  ,size };
		D3DXCOLOR coler = { 1.0f,1.0f ,1.0f ,a };
		cardcelect.m_Color = coler;
		ZeroMemory(&cardcelect.m_Material, sizeof(&cardcelect.m_Material));
		cardcelect.m_Material.Ambient = cardcelect.m_Color;
		cardcelect.m_Material.Emission = cardcelect.m_Color;
		cardcelect.m_Material.Diffuse = cardcelect.m_Color;
		for (int i = 0; i < 7; i++)
		{
			if (m_card_attacktime - 45 > i * 12)
			{
				DrawPolygonBillXY(cardcelect, RefImageMaterial().m_Boss_Bullet, cosf(rot + (D3DX_PI / 7) * 2.0f * (float)i) * 270.0f, sinf(rot + (D3DX_PI / 7) * 2.0f * (float)i) * 270.0f);
			}

		}

	}
	Object bossmodel;
	bossmodel.m_Scl = RefScl();
	bossmodel.m_Pos = RefPos();
	bossmodel.m_Rot = { RefRot().x,RefRot().y ,RefRot().z };
	if (nomalattack > 70)
	{
		bossmodel.m_Rot.y += (float)nomalattack * 0.7f;
	}
	ZeroMemory(&bossmodel.m_Material, sizeof(&bossmodel.m_Material));
	bossmodel.m_Color = RefColor();
	bossmodel.m_Material.Emission = GetMaterial()->Diffuse;
	bossmodel.m_Material.Diffuse = GetMaterial()->Diffuse;
	bossmodel.m_Material.Ambient = GetMaterial()->Diffuse;

	Draw3DModel(bossmodel, RefModelMaterial().m_Boss2);
	Draw_DotDamage();
#if _DEBUG
	//当たり判定の描画
	Object sphere;
	for (Collision* pColl : *GetColl())
	{
		sphere.m_Pos = pColl->RefCollPos();
		sphere.m_Scl = { COLL_CIRCLE ,COLL_CIRCLE ,COLL_CIRCLE };
		sphere.m_Rot = RefRot();
		//Draw3DModel(sphere, RefModelMaterial().m_Sphere);
	}
	//HPの表示
	Object hp;
	hp.m_Pos = { RefPos().x,RefPos().y + 300.0f,RefPos().z };
	hp.m_Scl = { 1.0f * RefHp(),10.0f,0.0f };
	hp.m_Color = { 1.0f,0.0f,0.0f,1.0f };
	hp.m_Material.Emission = hp.m_Color;
	DrawPolygonBill(hp, RefImageMaterial().m_White_Square);
#endif // _DEBUG
}
//=============================================================================
// アクション
//=============================================================================
void Boss3_Main::Action(void)
{
	CAMERA* pCam = GetCamera();

	// カメラ(プレイヤー)のいる方向へエネミーを向かせる処理
	D3DXVECTOR3 Vec = D3DXVECTOR3(pCam->pos.x - RefPos().x, pCam->pos.y - RefPos().y - 200.0f, pCam->pos.z - RefPos().z);
	float rot_y = -atan2f(Vec.z, Vec.x) - D3DX_PI / 2.0f;
	float rot_x = atan2f(Vec.y, Vec.z);
	SetRot(D3DXVECTOR3(0, rot_y, 0.0f));




}
//=============================================================================
// プレイヤーとのアクション
//=============================================================================
void Boss3_Main::SearchAction(void)
{
	D3DXVECTOR3 Plpos = GetCamera()->pos;
	D3DXVECTOR3 Vec = GetCamera()->pos - RefPos();
	float length = D3DXVec3LengthSq(&Vec);
	if (Plpos.x > 100 && Plpos.x < 2900 && Plpos.z > 7100 && Plpos.z < 9900)
	{
		m_agro = true;
	}
	if (m_agro == true)
	{
		Action();
	}
	if (length < 300 * 300 && nomalattack <= 0)
	{
		nomalattack = NOMALATTACK_CD;
		GetPlayer()->IsDamage(20);
	}

}
void Boss3_Main::StateSwap_Move(D3DXVECTOR3 pos)
{

	//正規化した2点間の座標
	D3DXVECTOR3 vDis = pos - RefPos();
	float lenght = D3DXVec3Length(&vDis);

	m_MoveStatetime = (int)(25.0f / (300.0f / lenght));
	m_MoveStatepos = { (pos.x - RefPos().x) / m_MoveStatetime,(pos.z - RefPos().z) / m_MoveStatetime };
	m_state = Boss3_move;
}

void Boss3_Main::StateSwap_Idol()
{
	m_state = Boss3_idol;
}

void Boss3_Main::CardAttack()
{
	m_state = Boss3_card_attack;
	m_Card_attackcelecttime = 0;
	cardattackcd = CARDATTACK_CD;
}


