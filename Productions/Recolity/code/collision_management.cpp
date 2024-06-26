//=============================================================================
//
// 当たり判定管理処理 [collision_management.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "collision_management.h"
#include "Game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//=============================================================================
// 引数付きコンストラクタ
//=============================================================================
Collision_Management::Collision_Management(std::list<Base_Enemy*>* enemey_list, std::list<Base_Bullet*>* bullet_list, Attribute_Management* att_manager)
	:m_EnemyList(enemey_list),m_BulletList(bullet_list),m_AttributeManagement(att_manager)
{
}
//=============================================================================
// 更新
//=============================================================================
void Collision_Management::Update(void)
{
	//敵と弾の当たり判定
	for (Base_Bullet* pBullet : *m_BulletList)
	{
		//使っていない弾だったら
		if (!pBullet->RefUse())
			continue;

		if (pBullet->RefSide() != enemy) {
			for (Base_Enemy* pEnemy : *m_EnemyList)
			{
				//敵についている当たり判定の数回す
				for (int index = 0; index < pEnemy->GetColl()->size(); index++)
				{
					Collision* pColl = pEnemy->GetColl(index);
					//弾についている当たり判定の数回す
					if (pBullet->GetColl(0) != nullptr && pBullet->GetColl(0)->IsCollision(pColl))
					{
						//ダメージ処理
						pEnemy->IsDamage(pBullet->RefDamage());
						//属性の付与
						if (pEnemy->GetAttribute(pBullet->RefAttType()) == nullptr)
						{
							pEnemy->SetAttribute(m_AttributeManagement->Create(pBullet->RefElemet(), pBullet->RefAttType(), pBullet), pBullet->RefAttType());
						}
						pBullet->IsDiscard();
					}
				}
			}
		}
		else {
			//プレイヤーについている当たり判定の数回す
			for (int index = 0; index < GetPlayer()->GetColl()->size(); index++)
			{
				Collision* pColl = GetPlayer()->GetColl(index);
				//弾についている当たり判定の数回す
				if (pBullet->GetColl(0) != nullptr && pBullet->GetColl(0)->IsCollision(pColl))
				{
					//ダメージ処理
					GetPlayer()->IsDamage(pBullet->RefDamage());
					GetPlayer()->SetAttribute(m_AttributeManagement->Create(pBullet->RefElemet(), pBullet->RefAttType(), pBullet), pBullet->RefAttType());
					if (pBullet->RefAttType() == water) {
						GetPlayer()->effect.SetEffect(slowness, low, pBullet->RefElemet().m_Frame);
					}
					pBullet->IsDiscard();
				}
			}
		}
	}
	//エネミー同士の衝突
	for (Base_Enemy* pEnemy : *m_EnemyList)
	{
		for (Base_Enemy* pAnother : *m_EnemyList)
		{
			//自分自身の回避
			if (pAnother == pEnemy)
				continue;

			D3DXVECTOR2 vec = { pEnemy->RefPos().x - pAnother->RefPos().x,pEnemy->RefPos().z - pAnother->RefPos().z };
			float angle = atan2f(vec.y, vec.x);
			float lenght = D3DXVec2LengthSq(&vec);
			float speed = 3.0f;
			if (lenght <= 100.0f * 100.0f) {
				pEnemy->SetPos({ pEnemy->RefPos().x + speed * cosf(angle),pEnemy->RefPos().y,pEnemy->RefPos().z + speed * sinf(angle) });
				angle += D3DX_PI;
				pAnother->SetPos({ pAnother->RefPos().x + speed * cosf(angle),pAnother->RefPos().y,pAnother->RefPos().z + speed * sinf(angle) });
			}
		}
	}
}


