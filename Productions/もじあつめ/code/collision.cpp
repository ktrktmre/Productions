/*==============================================================================

   �����蔻��Ǘ� [collision.h]
														 Author :�ؓc �C���l
														 Date   :2023/06/16
--------------------------------------------------------------------------------

==============================================================================*/
#include "main.h"
#include "myfunction.h"
#include "collision.h"
#include "player.h"
#include "word.h"
#include "titleBG.h"
#include "resultBG.h"
#include "explanationBG.h"
#include "optionBG.h"
#include "sound.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);
bool CollisionBC(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2);
bool CollisionBCSq(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
D3DXCOLOR g_CollColor;
D3DXCOLOR g_UpdateCollColor;
bool g_OnceCollColor = false;

//=============================================================================
// �����蔻�菈��
//=============================================================================
void UpdateCollision(void)
{
	SCENE* pScene = GetScene();

	if (*pScene == SCENE_TITLE)
	{
		TITLEBG* pButton = GetTitleButton();
		PLAYER* pPlayer = GetPlayer();
		//�{�^���ƃv���C���[
		for (int buttonCnt = 0; buttonCnt < TITLE_BUTTON_NUM; buttonCnt++)
		{
			if (CollisionBB(pPlayer->pos, pButton[buttonCnt].pos, D3DXVECTOR2(PALYER_COLL_SIZE, PALYER_COLL_SIZE), pButton[buttonCnt].size))
			{
				pButton[buttonCnt].color = g_CollColor;
				pButton[buttonCnt].coll = true;
				pPlayer->coll = true;
				break;
			}
			else
			{
				pButton[buttonCnt].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pButton[buttonCnt].coll = false;
				pPlayer->coll = false;
			}
		}
	}
	else if (*pScene == SCENE_EXPLANATION)
	{
		EXPLANATIONBG* pButton = GetExplanationBGButton();
		PLAYER* pPlayer = GetPlayer();
		//�{�^���ƃv���C���[
		if (CollisionBB(pPlayer->pos, pButton->pos, D3DXVECTOR2(PALYER_COLL_SIZE, PALYER_COLL_SIZE), pButton->size))
		{
			pButton->color = g_CollColor;
			pButton->coll = true;
			pPlayer->coll = true;
		}
		else
		{
			pButton->color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pButton->coll = false;
			pPlayer->coll = false;
		}
	}
	else if (*pScene == SCENE_OPTION)
	{
		OPTION* pButton = GetOptionBGButton();
		OPTION* pAdCursor = GetAdCursor();
		PLAYER* pPlayer = GetPlayer();
		//�{�^���ƃv���C���[
		if (CollisionBB(pPlayer->pos, pButton->pos, D3DXVECTOR2(PALYER_COLL_SIZE, PALYER_COLL_SIZE), pButton->size))
		{
			pButton->color = g_CollColor;
			pButton->coll = true;
			pPlayer->coll = true;
		}
		else
		{
			pButton->color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pButton->coll = false;
			pPlayer->coll = false;
		}
		//�����J�[�\���ƃv���C���[
		for (int adjCnt = 0; adjCnt < ADJUSTMENT_NUM; adjCnt++)
		{
			if (CollisionBB(pPlayer->pos, pAdCursor[adjCnt].pos, D3DXVECTOR2(PALYER_COLL_SIZE, PALYER_COLL_SIZE), pAdCursor[adjCnt].size))
			{
				pAdCursor[adjCnt].coll = true;
				pAdCursor[adjCnt].color = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
				break;
			}
			else
			{
				pAdCursor[adjCnt].coll = false;
				pAdCursor[adjCnt].color = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
			}
		}
	}
	else if (*pScene == SCENE_GAME)
	{
		PLAYER* pPlayer = GetPlayer();
		WORDS* pWord = GetWord();
		//�����ƃv���C���[
		for (int cntWord = 0; cntWord < WORD_NUM; cntWord++)
		{
			if (pWord[cntWord].use)
			{
				if (CollisionBC(pWord[cntWord].pos, pPlayer->pos, pWord[cntWord].size.x / 2, PALYER_COLL_SIZE))
				{
					pWord[cntWord].color = g_CollColor;
					pWord[cntWord].coll = true;
					pPlayer->coll = true;
					break;
				}
				else
				{
					pWord[cntWord].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pWord[cntWord].coll = false;
					pPlayer->coll = false;
					pPlayer->shoot = false;
				}
			}
		}
	}
	else if (*pScene == SCENE_RESULT)
	{
		RESULTBG* pButton = GetResultButton();
		PLAYER* pPlayer = GetPlayer();

		//�{�^���ƃv���C���[
		for (int buttonCnt = 0; buttonCnt < RESULT_BUTTON_NUM; buttonCnt++)
		{
			if (CollisionBB(pPlayer->pos, pButton[buttonCnt].pos, D3DXVECTOR2(PALYER_COLL_SIZE, PALYER_COLL_SIZE), pButton[buttonCnt].size))
			{
				pButton[buttonCnt].color = g_CollColor;
				pButton[buttonCnt].coll = true;
				pPlayer->coll = true;
				break;
			}
			else
			{
				pButton[buttonCnt].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pButton[buttonCnt].coll = false;
				pPlayer->coll = false;
			}
		}
	}
}

//=============================================================================
// BB�ɂ�铖���蔻�菈��
// ��]�͍l�����Ȃ�
// �߂�l�F�������Ă���true
//=============================================================================
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	D3DXVECTOR2 min1, max1;
	D3DXVECTOR2 min2, max2;

	min1.x = pos1.x - size1.x / 2;
	min1.y = pos1.y - size1.y / 2;
	max1.x = pos1.x + size1.x / 2;
	max1.y = pos1.y + size1.y / 2;

	min2.x = pos2.x - size2.x / 2;
	min2.y = pos2.y - size2.y / 2;
	max2.x = pos2.x + size2.x / 2;
	max2.y = pos2.y + size2.y / 2;

	//X���̔���
	if (min1.x < max2.x && max1.x > min2.x)
	{
		//Y���̔���
		if (min1.y < max2.y && max1.y > min2.y)
		{
			//�S�Ă̏�����TRUE�Ȃ�q�b�g����
			return true;
		}
	}

	return false;
}

//=============================================================================
// BC�ɂ�铖���蔻�菈��
// �T�C�Y�͔��a
// �߂�l�F�������Ă���true
//=============================================================================
bool CollisionBC(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2)
{
	//pos1��pos2���Ȃ��x�N�g�������
	D3DXVECTOR2 vDistance = pos1 - pos2;

	//vDistance�̃x�N�g�����𓾂�
	float length;
	length = D3DXVec2Length(&vDistance);

	//1��2�̔��a�𑫂�
	float size = size1 + size2;

	//���������a�ƃx�N�g�����Ƃő傫���𔻒肷��
	//�����̃x�N�g�����̕�����������΃q�b�g���Ă���
	if (length < size)
	{
		return true;
	}

	return false;
}

//=============================================================================
// BC�ɂ�铖���蔻�菈��
// �T�C�Y�͔��a
// �߂�l�F�������Ă���true
//=============================================================================
bool CollisionBCSq(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2)
{
	//pos1��pos2���Ȃ��x�N�g�������
	D3DXVECTOR2 vDistance = pos1 - pos2;

	//vDistance�̃x�N�g������2��̒l�𓾂�
	float length;
	length = D3DXVec2LengthSq(&vDistance);

	//1��2�̔��a�𑫂���2�悷��
	float size = (size1 + size2) * (size1 + size2);

	//���������a�ƃx�N�g�����Ƃő傫���𔻒肷��
	//�����̃x�N�g�����̕�����������΃q�b�g���Ă���
	if (length < size)
	{
		return true;
	}

	return false;
}

//=============================================================================
// �Փ˃J���[������
//=============================================================================
void InitCollColor(void)
{
	//������
	g_CollColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	if (!g_OnceCollColor)	//���񂾂��Ńf�t�H���g�̐F�ŌĂяo��
	{
		SetCollColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	}
	else
	{
		SetCollColor(g_UpdateCollColor);
	}
}

//=============================================================================
// �Փ˃J���[�R�s�[
//=============================================================================
D3DXCOLOR CopyCollColor(void)
{
	return (D3DXCOLOR(g_CollColor.r * FULL_COLOR, g_CollColor.g * FULL_COLOR, g_CollColor.b * FULL_COLOR, g_CollColor.a));
}

//=============================================================================
// �Փ˃J���[�Z�b�^�[
//=============================================================================
void SetCollColor(D3DXCOLOR color)
{
	g_CollColor.r = color.r;
	g_CollColor.g = color.g;
	g_CollColor.b = color.b;
	g_CollColor.a = 1.0f;

	g_UpdateCollColor = g_CollColor;

	g_OnceCollColor = true;
}