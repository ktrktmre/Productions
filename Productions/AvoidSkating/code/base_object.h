//=============================================================================
//
// オブジェクト処理 [base_object.h]
// Author : 切田海畝斗
//
//=============================================================================
#ifndef _BASE_OBJECT_H_
#define _BASE_OBJECT_H_
#pragma once

#include <d3dx9.h>
#include <vector>
#include "renderer.h"
#include "base_collision.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class Object_Manager;
class Player;
class Base_Enemy;
class Base_Item;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define DISTANCE_DIFF	(10.0f)					// mayaと開発環境の距離の差
#define NO_VECTOR3		{0.0f,0.0f,0.0f}		// 3dベクターの0初期化
#define NO_COLOR		{0.0f,0.0f,0.0f,0.0f}	// カラーの0初期化
#define DEF_COLOR		{1.0f,1.0f,1.0f,1.0f}	// デフォルトカラー

//*****************************************************************************
// 列挙体
//*****************************************************************************
enum Object_Tag {
	player,
	enemy,
	item,
	anime,
	ability,
	background,
	inviolability
};

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class Base_Object {
private:
	Object_Manager*					m_ObjManager;				// マネージャー
	Object_Tag						m_ObjTag;					// オブジェクトタグ
	D3DXVECTOR3						m_Pos;						// ポリゴンの座標
	D3DXVECTOR3						m_Rot;						// ポリゴンの向き(回転)
	D3DXVECTOR3						m_Scl;						// ポリゴンの大きさ(スケール)
	D3DXVECTOR3						m_Vel;						// 速度
	D3DXCOLOR						m_Color;					// ポリゴンのカラー
	D3DXMATRIX						m_MtxWorld;					// ワールドマトリックス
	MATERIAL						m_Material;					// マテリアル
	std::vector<Base_Collision*>	m_Collision;				// コリジョン
	bool							m_Use;						// 使用フラグ
public:
	Base_Object() = default;
	Base_Object(Object_Tag tag, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use);
	virtual ~Base_Object();

	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	//ゲッター
	Object_Manager* GetObjManager(void);
	D3DXMATRIX* GetMtx(void);
	MATERIAL* GetMaterial(void);
	const std::vector<Base_Collision*>* GetColl(void);
	Base_Collision* GetColl(int index);

	//リファレンス
	Object_Tag& RefTag(void);
	D3DXVECTOR3& RefPos(void);
	D3DXVECTOR3& RefRot(void);
	D3DXVECTOR3& RefScl(void);
	D3DXVECTOR3& RefVel(void);
	D3DXCOLOR& RefColor(void);
	const bool& RefUse(void) const;

	//セッター
	void SetObjManager(Object_Manager* manager);
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	void SetScl(D3DXVECTOR3 scl);
	void SetVel(D3DXVECTOR3 vel);
	void SetColor(D3DXCOLOR color);
	void SetUse(bool use);
	void SetColl(Base_Collision* coll);

	//衝突アクション
	virtual void CollDispatch(Base_Object* pObj) = 0;
	virtual void CollAction(Player* player);
	virtual void CollAction(Base_Enemy* enemy);
	virtual void CollAction(Base_Item* item);
};

#endif // !_BASE_OBJECT_H_