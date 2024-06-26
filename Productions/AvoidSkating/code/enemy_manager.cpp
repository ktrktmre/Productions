//=============================================================================
//
// 敵管理処理 [enemy_manager.cpp]
// Author : 切田海畝斗
//
//=============================================================================
#include "enemy_manager.h"
#include "object_manager.h"
#include "tree_enemy.h"
#include "lightning_enemy.h"
#include "ball_enemy.h"
#include "shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define VALUE_ADD_DAMAGE	(5)
#define VALUE_ADD_TIME		(20)
#define TREE_INTERVAL		(45)
#define TREE_DAMAGE			(10)
#define LIGHTNING_INTERVAL	(120)
#define LIGHTNING_DAMAGE	(20)
#define BALL_INTERVAL		(180)
#define BALL_DAMAGE			(30)

//=============================================================================
// 引数付きコンストラクタ
//=============================================================================
Enemy_Manager::Enemy_Manager(Object_Manager* manager)
	:m_ObjManager(manager)
{
	m_Frame[tree] = TREE_INTERVAL;
	m_Frame[lightning] = LIGHTNING_INTERVAL;
	m_Frame[ball] = BALL_INTERVAL;
	m_Table.push_back({ 500.0f, 50.0f, 3000.0f });
	m_Table.push_back({ 0.0f, 50.0f, 3000.0f });
	m_Table.push_back({ -500.0f, 50.0f, 3000.0f });
}

//=============================================================================
// 更新
//=============================================================================
void Enemy_Manager::Update(void)
{
	for (auto& map:m_Frame)
	{
		--map.second;

		if (map.second <= 0) {
			Create(map);
		}
	}
}

//=============================================================================
// 生成
//=============================================================================
void Enemy_Manager::Create(std::pair<const Enemy_Tag, int>& pair)
{
	int time = m_ObjManager->GetTimeGame() / VALUE_ADD_TIME;
	int index = rand() % m_Table.size();
	if (pair.first == tree) {
		m_ObjManager->Accept(new Tree_Enemy(m_Table[index], TREE_DAMAGE + time * VALUE_ADD_DAMAGE));
		pair.second = TREE_INTERVAL;
	}
	if (pair.first == lightning) {
		m_ObjManager->Accept(new Lightning_Enemy(m_Table[1], LIGHTNING_DAMAGE + time * VALUE_ADD_DAMAGE));
		pair.second = LIGHTNING_INTERVAL;
	}
	if (pair.first == ball) {
		auto enemy = new Ball_Enemy(m_Table[index], BALL_DAMAGE + time * VALUE_ADD_DAMAGE);
		m_ObjManager->Accept(enemy);
		m_ObjManager->Accept(new Shadow(enemy));
		pair.second = BALL_INTERVAL;
	}
}
