/*==============================================================================

   ���Ȋ֐��Ǘ� [myfunction.h]
														 Author :�ؓc �C���l
														 Date   :2023/06/16
--------------------------------------------------------------------------------

==============================================================================*/
#include "main.h"
#include "myfunction.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// ���ォ�璆�S
//=============================================================================
D3DXVECTOR2 LeftTopToCenter(D3DXVECTOR2 pos, D3DXVECTOR2 size, float rot)
{
	D3DXVECTOR2 center;
	float width = size.x / 2;
	float height = size.y / 2;

	center.x = pos.x + (width * cosf(rot) - height * sinf(rot));
	center.y = pos.y + (width * sinf(rot) + height * cosf(rot));

	return center;
}

//=============================================================================
// ���S���獶��
//=============================================================================
D3DXVECTOR2 CenterToLeftTop(D3DXVECTOR2 pos, D3DXVECTOR2 size, float rot)
{
	D3DXVECTOR2 center;
	float width = size.x / 2;
	float height = size.y / 2;

	center.x = pos.x + ((-width) * cosf(rot) - (-height) * sinf(rot));
	center.y = pos.y + ((-width) * sinf(rot) + (-height) * cosf(rot));

	return center;
}

//=============================================================================
// ���ォ��E��
//=============================================================================
D3DXVECTOR2 LeftTopToRightTop(D3DXVECTOR2 pos, D3DXVECTOR2 size, float rot)
{
	D3DXVECTOR2 center;
	float width = size.x;

	center.x = pos.x + width * cosf(rot);
	center.y = pos.y + width * sinf(rot);

	return center;
}

//=============================================================================
// �l�̌ܓ�
//=============================================================================
float RoundOff(float num)
{
	int integer;
	float decimal;

	//���������̒��o
	decimal = num - (int)num;

	//�������
	integer = decimal * 10;

	//�����̏���
	num = (int)num;

	if ((int)integer < 5)
	{
		return num;
	}
	else
	{
		return num + 1;
	}
}

//=============================================================================
// �J����������W�̎擾
//=============================================================================
D3DXVECTOR2 LeftTopCamera(D3DXVECTOR2 wpos, D3DXVECTOR2 lpos)
{
	D3DXVECTOR2 LTpos;
	LTpos.x = wpos.x - lpos.x;
	LTpos.y = wpos.y - (SCREEN_HEIGHT - lpos.y);

	return LTpos;
}

//=============================================================================
// �����̏o��
//=============================================================================
int PlusMinus(void)
{
	int pm = rand() % 100;
	if (pm < 50)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

//=============================================================================
// �����_���p�[�Z���g
//=============================================================================
float RandPercent(int max, int min)
{
	float percent;

	percent = ((rand() % (max - min)) + 1) + min;
	percent *= 0.01;

	return percent;
}

//=============================================================================
// ���ꌅ�̎��o��
//=============================================================================
int BottomDigit(int num)
{
	int bottom;
	bottom = num % 10;
	return bottom;
}

//=============================================================================
// �ȈՃ\�[�g:int�^
//=============================================================================
void MySortInt(int array[], int num,int data)
{
	//�z�񂪎g���Ă��Ȃ�������
	if (array[0] < 0)
	{
		array[0] = data;
	}
	else
	{
		//�}���ʒu�̒T��
		int hit = 0;
		for (int i = 0; i < num; i++)
		{
			if (array[i] == data)
			{
				hit = -1;
				break;
			}
			if (array[i] < data)
			{
				break;
			}
			hit++;
		}

		//�q�b�g���[���ȏゾ������
		if (hit >= 0)
		{
			for (int j = num; j > hit; j--)
			{
				array[j] = array[j - 1];
			}
			array[hit] = data;
		}
	}
}

//=============================================================================
// �����:�����Ő^�A��ŋU
//=============================================================================
bool EvenOdd(int num)
{
	if (num % 2 == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//=============================================================================
// �Δ�v�Z
// num1:�����鐔
// num2:���鐔
//=============================================================================
float Contrast(float num1, float num2)
{
	float contrast;

	contrast = num1 / num2;

	return contrast;
}