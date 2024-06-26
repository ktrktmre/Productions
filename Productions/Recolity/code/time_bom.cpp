#include "time_bom.h"
#include "main.h"
#include "input.h"
#include "camera.h"
#include "material.h"
#include "sprite.h"
#include "Game.h"
#include "floor.h"
//=====================================
// 敵には使えません
// プレイヤー以外には特に効果のないバレットです
// コリジョンありますが設定などはできないプレイヤーをフックするためだけにあるんでめちゃめちゃ例外的な物です
// updateで当たり判定取ってます
// 使用追加できなかったので苦肉の策
//=====================================
Time_bom_Bullet::Time_bom_Bullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use, Bullet_Side side,
	int damage, float speed, float gvt, float dec, int range, D3DXVECTOR2 uv_v, D3DXVECTOR2 uv_f, Attribute_Type att_type,
	Attribute_Element att_element, int* tex, DX11_MODEL* model, float circle)
	:Base_Bullet(pos, { rot.x * -1.0f,rot.y,rot.z }, scl, vel, color, true, hook, side, damage, speed, gvt, dec, range, uv_v, uv_f, att_type, att_element, tex, model)
{
	life = 90;
	m_pullpoint = pos;
	//当たり判定の設定
	m_Penetration = true;
	// マテリアル設定
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = RefColor();
	GetMaterial()->Ambient = RefColor();
	GetMaterial()->Emission = RefColor();
	GetMaterial()->noTexSampling = 0;
}
//=============================================================================
// デストラクタ
//=============================================================================
Time_bom_Bullet::~Time_bom_Bullet()
{



}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Time_bom_Bullet::Init(void)
{
	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void Time_bom_Bullet::Uninit(void)
{

}
//=============================================================================
// 更新処理
//=============================================================================
void Time_bom_Bullet::Update(void)
{
	//フロアが0だったら消える
	Floor_Type type = GetNowFloor(RefPos());
	if (type == Floor_Wall)
		IsDiscard();
	if (life > 0)
	{
		life--;
	}
	D3DXVECTOR3 Vec = GetCamera()->pos - RefPos();
	float length = D3DXVec3LengthSq(&Vec);
	if (life <= 0)
	{
		IsDiscard();
		if (length < 300 * 300)
		{
			GetPlayer()->IsDamage(RefDamage());
			SetDamage(0);

		}
		Emitta(9, this->RefPos());
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
void Time_bom_Bullet::Draw(void)
{


}
//=============================================================================
// 弾の動き
//=============================================================================
void Time_bom_Bullet::Move(void)
{

	//弾の移動
	SetPos(RefPos() + RefVel());

	//残りの射程距離
	SetRange(RefRange() - RefSpeed());

	//減速と落下
	SetVel({
		RefVel().x * RefDec(),
		RefVel().y - RefGvt(),
		RefVel().z * RefDec() });

	//基底スピードの調整
	SetSpeed(RefSpeed() * RefDec());

	//フロアが0だったら消える
	Floor_Type type = GetNowFloor(RefPos());
	if (type == Floor_Wall)
		IsDiscard();

	//レンジが0以下になるか、弾のy軸が0以下になったら
	if (RefPos().y <= 0 || RefRange() <= 0 || RefSpeed() <= 0.01f)
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
	}
}
