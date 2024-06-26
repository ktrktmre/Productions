/*==============================================================================

   自己関数管理 [myfunction.h]
														 Author :切田 海畝斗
														 Date   :2023/06/16
--------------------------------------------------------------------------------

==============================================================================*/
#include "main.h"
#include "myfunction.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// 左上から中心
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
// 中心から左上
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
// 左上から右上
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
// 四捨五入
//=============================================================================
float RoundOff(float num)
{
	int integer;
	float decimal;

	//小数部分の抽出
	decimal = num - (int)num;

	//小数第一
	integer = decimal * 10;

	//小数の除去
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
// カメラ左上座標の取得
//=============================================================================
D3DXVECTOR2 LeftTopCamera(D3DXVECTOR2 wpos, D3DXVECTOR2 lpos)
{
	D3DXVECTOR2 LTpos;
	LTpos.x = wpos.x - lpos.x;
	LTpos.y = wpos.y - (SCREEN_HEIGHT - lpos.y);

	return LTpos;
}

//=============================================================================
// 正負の出力
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
// ランダムパーセント
//=============================================================================
float RandPercent(int max, int min)
{
	float percent;

	percent = ((rand() % (max - min)) + 1) + min;
	percent *= 0.01;

	return percent;
}

//=============================================================================
// 下一桁の取り出し
//=============================================================================
int BottomDigit(int num)
{
	int bottom;
	bottom = num % 10;
	return bottom;
}

//=============================================================================
// 簡易ソート:int型
//=============================================================================
void MySortInt(int array[], int num,int data)
{
	//配列が使われていなかったら
	if (array[0] < 0)
	{
		array[0] = data;
	}
	else
	{
		//挿入位置の探索
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

		//ヒットがゼロ以上だったら
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
// 偶数奇数:偶数で真、奇数で偽
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
// 対比計算
// num1:割られる数
// num2:割る数
//=============================================================================
float Contrast(float num1, float num2)
{
	float contrast;

	contrast = num1 / num2;

	return contrast;
}