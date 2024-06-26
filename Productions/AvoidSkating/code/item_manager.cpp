//=============================================================================
//
// アイテム管理処理 [item_manager.cpp]
// Author : 切田海畝斗
//
//=============================================================================
#include "item_manager.h"
#include "object_manager.h"
#include "torus_item.h"
#include "crystal_item.h"
#include "shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TORUS_INTERVAL (30)
#define CRYSTAL_INTERVAL (90)

//=============================================================================
// 引数付きコンストラクタ
//=============================================================================
Item_Manager::Item_Manager(Object_Manager* manager)
	:m_ObjManager(manager)
{
	m_Frame[torus] = TORUS_INTERVAL;
	m_Frame[crystal] = CRYSTAL_INTERVAL;
	m_Table.push_back({ 500.0f, 150.0f, 3000.0f });
	m_Table.push_back({ 0.0f, 150.0f, 3000.0f });
	m_Table.push_back({ -500.0f, 150.0f, 3000.0f });
}

//=============================================================================
// 更新
//=============================================================================
void Item_Manager::Update(void)
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
void Item_Manager::Create(std::pair<const Item_Tag, int>& pair)
{
	int index;
	if (pair.first == torus) {
		index = rand() % m_Table.size();
		auto item = new Torus_Item(m_Table[index]);
		m_ObjManager->Accept(item);
		m_ObjManager->Accept(new Shadow(item));
		pair.second = TORUS_INTERVAL;
	}
	if (pair.first == crystal) {
		index = rand() % m_Table.size();
		auto item = new Crystal_Item(m_Table[index]);
		m_ObjManager->Accept(item);
		m_ObjManager->Accept(new Shadow(item));
		pair.second = CRYSTAL_INTERVAL;
	}
}
