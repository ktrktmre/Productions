//=============================================================================
//
// 敵処理 [enemy_management.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "model.h"
#include "texture.h"
#include "enemy_management.h"
#include "normal_enemy.h"
#include "patrol_enemy.h"
#include "bullet_enemy.h"
#include "boss.h"
#include "scorpion.h"
#include "moth.h"
#include "spider.h"
#include "scene.h"
#include "boss2_main.h"
#include "boss3_main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//=============================================================================
// 引数付きコンストラクタ
//=============================================================================
Enemy_Management::Enemy_Management(Bullet_Interface* bif)
	:m_BulletIF(bif)
{
}
//=============================================================================
// デストラクタ
//=============================================================================
Enemy_Management::~Enemy_Management()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Enemy_Management::Init(void)
{
	//Create(patrol_enemy, {700,0,1300});
	//Create(patrol_enemy, { 1800,0,1600 });
	//Create(patrol_enemy, { 2200,0,1600 });
	//Create(bullet_enemy, { 4250,0,2150 });
	//Create(boss_enemy, { 4100,0,4600 });
	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void Enemy_Management::Uninit(void)
{
	//終了
	for (Base_Enemy* pEnemy : m_EnemyList)
	{
		delete pEnemy;
	}
	m_EnemyList.erase(m_EnemyList.begin(), m_EnemyList.end());
}
//=============================================================================
// 更新処理
//=============================================================================
void Enemy_Management::Update(void)
{
#ifdef _DEBUG



	if (m_EnemyList.size() == 0)
	{
		//SetScene(SCENE_RESULT);
	}
	//生成
	if (GetKeyboardTrigger(DIK_1))
	{
		Create(normal_enemy, { GetCamera()->pos.x ,0,GetCamera()->pos.z });
	}
	if (GetKeyboardTrigger(DIK_2))
	{
		Create(patrol_enemy, { GetCamera()->pos.x ,0,GetCamera()->pos.z});
	}
	if (GetKeyboardTrigger(DIK_3))
	{
		Create(bullet_enemy, { GetCamera()->pos.x ,0,GetCamera()->pos.z });
	}
	if (GetKeyboardTrigger(DIK_4))
	{
		Create(boss_enemy, { GetCamera()->pos.x ,0,GetCamera()->pos.z });
	}
	if (GetKeyboardTrigger(DIK_5))
	{
		Create(scorpion_enemy, { GetCamera()->pos.x ,0,GetCamera()->pos.z });
	}
	if (GetKeyboardTrigger(DIK_6))
	{
		Create(moth_enemy, { GetCamera()->pos.x ,0,GetCamera()->pos.z });
	}
	if (GetKeyboardTrigger(DIK_7))
	{
		Create(spider_enemy, { GetCamera()->pos.x ,0,GetCamera()->pos.z });
	}	
	if (GetKeyboardTrigger(DIK_8))
	{
		Create(boss2, { GetCamera()->pos.x ,0,GetCamera()->pos.z });
	}
	if (GetKeyboardTrigger(DIK_9))
	{
		Create(boss3, { GetCamera()->pos.x ,0,GetCamera()->pos.z });
	}
#endif // _DEBUG

	//更新
	for (Base_Enemy* pEnemy : m_EnemyList)
	{
		pEnemy->Update();
	}

	//削除
	Delete();
}
//=============================================================================
// 描画処理
//=============================================================================
void Enemy_Management::Draw(void)
{
	//描画
	for (Base_Enemy* pEnemy : m_EnemyList)
	{
		pEnemy->Draw();
	}
}
//=============================================================================
// 生成
//=============================================================================
void Enemy_Management::Create(Enemy_Type type,D3DXVECTOR3 pos)
{
	CAMERA* pCam = GetCamera();




	if (type == normal_enemy)
	{
		m_EnemyList.push_back(new Normal_Enemy(
			pos,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(BASE_ENEMY_SCALE, BASE_ENEMY_SCALE, BASE_ENEMY_SCALE),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			true)
		);
	}
	if (type == patrol_enemy)
	{
		m_EnemyList.push_back(new Patrol_Enemy(
			pos,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(BASE_ENEMY_SCALE, BASE_ENEMY_SCALE, BASE_ENEMY_SCALE),
			D3DXVECTOR3(5.0f, 5.0f, 5.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			true)
		);
	}
	if (type == bullet_enemy)
	{
		m_EnemyList.push_back(new Bullet_Enemy(
			pos,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(BASE_ENEMY_SCALE, BASE_ENEMY_SCALE, BASE_ENEMY_SCALE),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			true,
			m_BulletIF)
		);
	}
	if (type == boss_enemy)
	{
		m_EnemyList.push_back(new Boss(
			pos,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(BOSS_SCALE, BOSS_SCALE, BOSS_SCALE),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			true,
			m_BulletIF)
		);
	}
	if (type == scorpion_enemy)
	{
		m_EnemyList.push_back(new Scorpion(
			pos,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(SCORPION_SCALE, SCORPION_SCALE, SCORPION_SCALE),
			D3DXVECTOR3(5.0f, 0.0f, 5.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			true,
			m_BulletIF)
		);
	}
	if (type == spider_enemy)
	{
		m_EnemyList.push_back(new Spider(
			pos,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(SPIDER_SCALE, SPIDER_SCALE, SPIDER_SCALE),
			D3DXVECTOR3(5.0f, 0.0f, 5.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			true,
			m_BulletIF)
		);
	}
	if (type == boss2 )
	{
		m_EnemyList.push_back(new Boss2_Main(
			pos,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(SPIDER_SCALE, SPIDER_SCALE, SPIDER_SCALE),
			D3DXVECTOR3(5.0f, 0.0f, 5.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			true,
			m_BulletIF)
		);
	}
	if (type == boss3)
	{
		m_EnemyList.push_back(new Boss3_Main(
			pos,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(SPIDER_SCALE, SPIDER_SCALE, SPIDER_SCALE),
			D3DXVECTOR3(5.0f, 0.0f, 5.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			true,
			m_BulletIF)
		);
	}
}
//=============================================================================
// 削除
//=============================================================================
void Enemy_Management::Delete(void)
{
	m_EnemyList.remove_if([](Base_Enemy* pEnemy) {
		if (!pEnemy->RefUse()) {
			delete pEnemy;
			return true;
		}
		return false; }
	);
}
//=============================================================================
// エネミーリストゲッター
//=============================================================================
std::list<Base_Enemy*>* Enemy_Management::GetEnemyList(void)
{
	return &m_EnemyList;
}
