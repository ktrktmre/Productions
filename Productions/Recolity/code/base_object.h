//=============================================================================
//
// オブジェクト処理 [base_object.h]
// Author : 
//
//=============================================================================
#ifndef _BASE_OBJECT_H_
#define _BASE_OBJECT_H_
#pragma once

#include <d3dx9.h>
#include <iostream>
#include <list>
#include <vector>
#include "renderer.h"
#include "collision.h"
#include "model.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class Base_Attribute;
enum Attribute_Type;
struct Attribute_Element;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define DISTANCE_DIFF	(10.0f)					// mayaと開発環境の距離の差
#define ATTRIBUTE_NUM	(3)						// 属性の数
#define NO_VECTOR3		{0.0f,0.0f,0.0f}		// 3dベクターの0初期化
#define NO_COLOR		{0.0f,0.0f,0.0f,0.0f}	// カラーの0初期化

//*****************************************************************************
// 列挙体
//*****************************************************************************
enum Object_Type {	//オブジェクトタイプ
	character,
	ground,
	destructible,
	inviolability
};

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class Base_Object {
private:
	D3DXVECTOR3				m_Pos;						// ポリゴンの座標
	D3DXVECTOR3				m_OldPos;					// 1フレーム前の座標
	D3DXVECTOR3				m_Rot;						// ポリゴンの向き(回転)
	D3DXVECTOR3				m_Scl;						// ポリゴンの大きさ(スケール)
	D3DXVECTOR3				m_Vel;						// 速度
	D3DXCOLOR				m_Color;					// ポリゴンのカラー
	D3DXMATRIX				m_MtxWorld;					// ワールドマトリックス
	MATERIAL				m_Material;					// マテリアル
	Object_Type				m_ObjType;					// オブジェクトタイプ
	std::vector<Collision*>	m_Collision;				// 当たり判定
	Base_Attribute*			m_Attribute[ATTRIBUTE_NUM];	// 受けた属性
	Attribute_Type			m_AttType;					// 自身の属性
	bool					m_Use;						// 使用フラグ
public:
	Base_Object() = default;
	Base_Object(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, Object_Type obj_type, bool use);
	virtual ~Base_Object();

	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual void IsDiscard(void);

	//ゲッター
	D3DXMATRIX* GetMtx(void);
	MATERIAL* GetMaterial(void);
	std::vector<Collision*>* GetColl(void);
	Collision* GetColl(int index);
	Base_Attribute* GetAttribute(int index);

	//リファレンス
	const D3DXVECTOR3& RefPos(void) const;
	const D3DXVECTOR3& RefOldPos(void) const;
	const D3DXVECTOR3& RefRot(void) const;
	const D3DXVECTOR3& RefScl(void) const;
	const D3DXVECTOR3& RefVel(void) const;
	const D3DXCOLOR& RefColor(void) const;
	const Object_Type& RefObjType(void) const;
	const Attribute_Type& RefAttType(void) const;
	const bool& RefUse(void) const;

	//セッター
	void SetPos(D3DXVECTOR3 pos);
	void SetOldPos(void);
	void SetRot(D3DXVECTOR3 rot);
	void SetScl(D3DXVECTOR3 scl);
	void SetVel(D3DXVECTOR3 vel);
	void SetColor(D3DXCOLOR color);
	void SetUse(bool use);
	void SetColl(Collision* coll);
	void SetColl(int index);
	void SetAttribute(Base_Attribute* attribute, Attribute_Type att_type);
	void SetAttType(Attribute_Type att_type);

	
};

#endif // !_BASE_OBJECT_H_