//=============================================================================
//
// オブジェクト管理処理 [object_management.cpp]
// Author : 切田海畝斗
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "object_manager.h"
#include "base_object.h"
#include "wall.h"
#include "shadow.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
Object_Manager::Object_Manager(Base_Object* player)
{
	Accept(new Wall({ 750.0f,0.0f,0.0f }, { 0.0f,D3DXToRadian(90),0.0f }));
	Accept(new Wall({ -750.0f,0.0f,0.0f }, { 0.0f,D3DXToRadian(-90),0.0f }));
	m_Player = player;
	Accept(m_Player);
	Accept(new Shadow(m_Player));
	//タイマーの最小精度を1msecに設定
	timeBeginPeriod(1);
	m_StartTime = m_CurrentTime = timeGetTime();
}

//=============================================================================
// デストラクタ
//=============================================================================
Object_Manager::~Object_Manager()
{
	//タイマーの最小精度を戻す
	timeEndPeriod(1);
	//終了
	for (Base_Object* pObj : m_ObjectList)
	{
		delete pObj;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Object_Manager::Update(void)
{
	//更新
	for (Base_Object* pObj : m_ObjectList)
	{
		pObj->Update();
	}

	IsCollision();

	m_CurrentTime = timeGetTime();
}
//=============================================================================
// 描画処理
//=============================================================================
void Object_Manager::Draw(void)
{
	//描画
	for (Base_Object* pObj : m_ObjectList)
	{
		pObj->Draw();
	}

	//削除
	Delete();


#ifdef _DEBUG
	std::stringstream ss;
	ss <<"Object: "<< m_ObjectList.size();
	DebugTextOut(ss.str().c_str(), 10, 10);

	ss << "shadow: " << SearchObjNumByTag(inviolability);
	DebugTextOut(ss.str().c_str(), 10, 200);
#endif // _DEBUG
}
//=============================================================================
// 追加
//=============================================================================
void Object_Manager::Accept(Base_Object* pObj)
{
	pObj->SetObjManager(this);
	m_ObjectList.push_back(pObj);
}
//=============================================================================
// 削除
//=============================================================================
void Object_Manager::Delete(void)
{
	m_ObjectList.remove_if([](Base_Object* pObj) {
		if (!pObj->RefUse()) {
			delete pObj;
			pObj = nullptr;
			return true;
		}
		return false;
		}
	);
}

//=============================================================================
// タグ別検索
//=============================================================================
Base_Object* Object_Manager::SearchObjByTag(const Object_Tag& tag)
{
	for (Base_Object* pObj:m_ObjectList)
	{
		if (pObj->RefTag() == tag)
			return pObj;
	}
	return nullptr;
}

//=============================================================================
// タグ別当たり判定
//=============================================================================
Base_Object* Object_Manager::CollisionByTag(Base_Object* pObj, const Object_Tag& tag)
{
	for (Base_Object* pTarget : m_ObjectList)
	{
		if (pTarget->RefTag() != tag || pTarget->GetColl()->size() < 1)
			continue;
		for (Base_Collision* pColl : *pObj->GetColl())
		{
			for (Base_Collision* pTColl : *pTarget->GetColl())
			{
				if (pColl->IsCollision(pTColl))
					return pTarget;
			}
		}
	}

	return nullptr;
}

//=============================================================================
// 当たり判定
//=============================================================================
void Object_Manager::IsCollision(void)
{
	auto current = m_ObjectList.begin();
	for (int i = 0; i < m_ObjectList.size() - 1; i++)
	{
		auto next = current;
		++next;
		if ((*current)->RefTag() == (*next)->RefTag() || (*current)->GetColl()->size() < 1) {
			++current;
			continue;
		}

		for (int j=i+1;j<m_ObjectList.size();j++)
		{
			for (Base_Collision* pColl : *(*current)->GetColl()) {
				if ((*next)->GetColl()->size() < 1)
					break;
				for (Base_Collision* pTColl : *(*next)->GetColl()) {
					if (pColl->IsCollision(pTColl)) {
						(*current)->CollDispatch(*next);
						(*next)->CollDispatch(*current);
					}
				}
			}
			++next;
		}
		++current;
	}
}

//=============================================================================
// 時間の計測
//=============================================================================
const int Object_Manager::GetTimeGame(void)
{
	const int time = ((double)(m_CurrentTime - m_StartTime) / 1000);
	return time;
}

//=============================================================================
// オブジェクトの数
//=============================================================================
const int Object_Manager::SearchObjNumByTag(const Object_Tag& tag)
{
	int count = 0;
	for (Base_Object* pObj : m_ObjectList)
	{
		if (pObj->RefTag() == tag)
			count++;
	}
	return count;
}
