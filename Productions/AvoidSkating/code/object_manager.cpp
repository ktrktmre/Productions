//=============================================================================
//
// �I�u�W�F�N�g�Ǘ����� [object_management.cpp]
// Author : �ؓc�C���l
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "object_manager.h"
#include "base_object.h"
#include "wall.h"
#include "shadow.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Object_Manager::Object_Manager(Base_Object* player)
{
	Accept(new Wall({ 750.0f,0.0f,0.0f }, { 0.0f,D3DXToRadian(90),0.0f }));
	Accept(new Wall({ -750.0f,0.0f,0.0f }, { 0.0f,D3DXToRadian(-90),0.0f }));
	m_Player = player;
	Accept(m_Player);
	Accept(new Shadow(m_Player));
	//�^�C�}�[�̍ŏ����x��1msec�ɐݒ�
	timeBeginPeriod(1);
	m_StartTime = m_CurrentTime = timeGetTime();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Object_Manager::~Object_Manager()
{
	//�^�C�}�[�̍ŏ����x��߂�
	timeEndPeriod(1);
	//�I��
	for (Base_Object* pObj : m_ObjectList)
	{
		delete pObj;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void Object_Manager::Update(void)
{
	//�X�V
	for (Base_Object* pObj : m_ObjectList)
	{
		pObj->Update();
	}

	IsCollision();

	m_CurrentTime = timeGetTime();
}
//=============================================================================
// �`�揈��
//=============================================================================
void Object_Manager::Draw(void)
{
	//�`��
	for (Base_Object* pObj : m_ObjectList)
	{
		pObj->Draw();
	}

	//�폜
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
// �ǉ�
//=============================================================================
void Object_Manager::Accept(Base_Object* pObj)
{
	pObj->SetObjManager(this);
	m_ObjectList.push_back(pObj);
}
//=============================================================================
// �폜
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
// �^�O�ʌ���
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
// �^�O�ʓ����蔻��
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
// �����蔻��
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
// ���Ԃ̌v��
//=============================================================================
const int Object_Manager::GetTimeGame(void)
{
	const int time = ((double)(m_CurrentTime - m_StartTime) / 1000);
	return time;
}

//=============================================================================
// �I�u�W�F�N�g�̐�
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
