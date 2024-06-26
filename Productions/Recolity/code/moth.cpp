//=============================================================================
//
// 敵処理 [moth.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "moth.h"
#include "moth_wing.h"
#include "material.h"
#include "sprite.h"
#include "sound.h"
#include "floor.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define HIT_POINT	(100)							// ヒットポイント
#define COLL_CIRCLE	(100.0f)						// 当たり判定の半径

//=============================================================================
// 引数付きコンストラクタ
//=============================================================================
Moth::Moth(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use)
	:Base_Enemy(pos, rot, scl, vel, color, use, HIT_POINT, moth_enemy)
{
	//翼のインスタンス化
	m_Wing[w_left] = new Moth_Wing({ RefPos().x, RefPos().y ,RefPos().z },
		RefRot(), RefScl(), RefVel(), RefColor(),
		true, w_left, 0.0f);
	m_Wing[w_right] = new Moth_Wing({ RefPos().x, RefPos().y ,RefPos().z },
		RefRot(), RefScl(), RefVel(), RefColor(),
		true, w_right, 0.0f);

	//当たり判定の設定
	SetColl(new Collision(this, {}, 100));

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
Moth::~Moth()
{
	Uninit();
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Moth::Init(void)
{
	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void Moth::Uninit(void)
{
	//StopSound(m_SoundIndex);

	//翼の解放
	for (int i = 0; i < MOTH_WING_NUM; i++)
	{
		delete m_Wing[i];
		m_Wing[i] = nullptr;
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void Moth::Update(void)
{
	//アクション
	Action();
	if (GetNowAdhere(RefPos()) == Floor_flame)
	{
		IsDamage(1);
	}
	//当たり判定の再設定
	for (Collision* pColl : *GetColl())
	{
		pColl->SetCollPos();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void Moth::Draw(void)
{
	// 胴体モデルの描画
	Draw3DModel(*this, RefModelMaterial().m_Moth);

	// 翼モデルの描画
	for (int i = 0; i < MOTH_WING_NUM; i++)
	{
		m_Wing[i]->Draw();
	}

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
	//HPの表示
	Object hp;
	hp.m_Pos = { RefPos().x,RefPos().y + 0.3f * RefScl().y * DISTANCE_DIFF,RefPos().z };
	hp.m_Scl = { 1.0f * RefHp(),10.0f,0.0f };
	hp.m_Color = { 1.0f,0.0f,0.0f,1.0f };
	DrawPolygonBill(hp, RefImageMaterial().m_White_Square);
#endif // _DEBUG
}
//=============================================================================
// アクション
//=============================================================================
void Moth::Action(void)
{
	CAMERA* pCam = GetCamera();

	////カメラ(プレイヤー)のいる方向へエネミーを向かせる処理
	//D3DXVECTOR3 vec = D3DXVECTOR3(pCam->pos.x - RefPos().x, pCam->pos.y - RefPos().y, pCam->pos.z - RefPos().z);
	//float rot = -atan2f(vec.z, vec.x) + D3DX_PI / 2;
	//SetRot(D3DXVECTOR3(MOTH_ANGLE, rot, 0.0f));
	////追跡
	//Chase(pCam->pos);
	//SetPos({ RefPos().x,RefPos().y + 100.0f,RefPos().z });

	//翼の更新
	for (int i = 0; i < MOTH_WING_NUM; i++)
	{
		m_Wing[i]->SetPos({ RefPos().x,RefPos().y,RefPos().z });
		m_Wing[i]->SetRot({ { RefRot().x,m_Wing[i]->RefRot().y,RefRot().z } });
		m_Wing[i]->Update();
	}
}
