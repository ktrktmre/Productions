//=============================================================================
//
// オブジェクト管理処理 [object_management.h]
// Author : 切田海畝斗
//
//=============================================================================
#ifndef _OBJECT_MANAGEMENT_H_
#define _OBJECT_MANAGEMENT_H_
#pragma once

#include <d3dx9.h>
#include <list>
#include <sstream> 
#include "renderer.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class Base_Object;
enum Object_Tag;

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class Object_Manager {
private:
	std::list<Base_Object*>	m_ObjectList;
	Base_Object* m_Player;
	DWORD m_StartTime;
	DWORD m_CurrentTime;
public:
	Object_Manager() = delete;
	Object_Manager(Base_Object* player);
	~Object_Manager();
	void Update(void);
	void Draw(void);

	void Accept(Base_Object* pObj);
	void Delete(void);
	Base_Object* SearchObjByTag(const Object_Tag& tag);
	Base_Object* CollisionByTag(Base_Object* pObj, const Object_Tag& tag);
	void IsCollision(void);
	const int GetTimeGame(void);

	const int SearchObjNumByTag(const Object_Tag& tag);
};

#endif // !_OBJECT_MANAGEMENT_H_