//=============================================================================
//
// 敵処理 [base_enemy.cpp]
// Author : 
//
//=============================================================================
#include "base_enemy.h"
#include "DrawDamageDot.h"
#include "floor.h"
#include "Game.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define HEARING_DISTANCE (2000*2000)

//=============================================================================
// 引数付きコンストラクタ
//=============================================================================
Base_Enemy::Base_Enemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use, int hp, Enemy_Type type)
	:Base_Character(pos, rot, scl, vel, color, hp, use), m_Type(type)
{
}

//=============================================================================
// リファレンス
//=============================================================================
const Enemy_Type& Base_Enemy::RefType(void) const
{
	return m_Type;
}
//=============================================================================
// セッター
//=============================================================================
void Base_Enemy::SetType(Enemy_Type type)
{
	m_Type = type;
}

//=============================================================================
// ダメージ処理
//=============================================================================
void Base_Enemy::IsDamage(float damage)
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
	if (RefHp() <= 0)
		IsDiscard();
}
//=============================================================================
// ダメージを受けた時のアクション
//=============================================================================
void Base_Enemy::DamageAction(int frame)
{
	D3DXCOLOR color = RefColor();
	color.b *= 0.3f;
	color.g *= 0.3f;
	color.a = 1.0f;
	GetMaterial()->Diffuse = color;	//拡散色
	GetMaterial()->Ambient =color * 0.3f;	//環境色
	GetMaterial()->Emission =color * 0.3f;	//環境色
	SetHitFrame(frame);
}
//=============================================================================
// 追跡
//=============================================================================
void Base_Enemy::Chase(D3DXVECTOR3 pos)
{
	//正規化した2点間の座標
	D3DXVECTOR3 vDis = pos - RefPos();
	float lenght = D3DXVec3Length(&vDis);
	vDis = D3DXVECTOR3(vDis.x / lenght, 0.0f, vDis.z / lenght);
	float floorslow = 1.0f;
	if (GetNowAdhere(RefPos()) == Floor_Water)
	{
		floorslow = 0.85f;
	}
	//追跡先に移動
	SetPos(D3DXVECTOR3(RefPos().x + vDis.x * RefVel().x * floorslow, RefPos().y, RefPos().z + vDis.z * RefVel().z * floorslow));
}
//=============================================================================
// プレイヤーとのアクション
//=============================================================================
void Base_Enemy::SearchAction(void)
{
}
//=============================================================================
// 距離による音量の調整
//=============================================================================
void Base_Enemy::DistanceVolume(D3DXVECTOR3 pos)
{
	//2点間の距離の2乗値の取得
	D3DXVECTOR3 vec = RefPos() - pos;
	float length = D3DXVec3LengthSq(&vec);

	//距離による音量の調整
	if (length > HEARING_DISTANCE) {
		SetVolume(RefFootSteps(), 0);
	}
	else{
		float rate = length / HEARING_DISTANCE;
		SetVolume(RefFootSteps(), 1.0f - rate);
	}
}
