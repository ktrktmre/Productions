#pragma once
#include "main.h"
//====================================
// スロウ
//====================================
#define SLOWNESS_LOW (30.0f)//(%)
#define SLOWNESS_MID (60.0f)//(%)
#define SLOWNESS_HIGH (90.0f)//(%)
//====================================
// スネア
//====================================
#define LOCK_LOW 1.5f //(s)
#define LOCK_MID 2.5f //(s)
#define LOCK_HIGH 4.0f //(s)
//====================================
// 持続ダメージ
//====================================
#define SLIPDAMAGE_LOW 0.01f//(f)
#define SLIPDAMAGE_MID 0.05f//(f)
#define SLIPDAMAGE_HIGH 0.1f//(f)
//====================================
// 持続回復
//====================================
#define REGEN_LOW 0.083334f//(f)
#define REGEN_MID 0.05f//(f)
#define REGEN_HIGH 0.1f//(f)

//====================================
// 炎連射
//====================================
#define FLAMESFIRE_TICK 15//(f)
enum EffectStrngth
{
	low = 1,
	mid,
	high,
};
enum Effectname
{
	slowness = 1,
	lock,
	slipdamage,
	regeneration,
	flamefire,
};
//enum クラス
class BASEEFFECT
{
public:

	BASEEFFECT() {};
	~BASEEFFECT() {};
	virtual void Update(void) = 0;
	virtual bool Draw(D2D1_RECT_F rect) = 0;

};


