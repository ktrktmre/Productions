//================================================
// 
// ステージ使用のマネージャ
// 
// manager--------swap
//   |  └-use
//	 |
// parameter
// |      |
// mana  timer
//================================================

#pragma once
#include "sound.h"
#include "cardplaypdeckmanager.h"
#include "cardplayuse.h"
#include "cardplayuse_parameter.h"
#include "cardplayuse_player.h"
typedef struct 
{
	bool use;
	int m_UseSound;
	int time;
}cardSoud;
class CardPlayUse_Manager
{
private:
	CardPlay_Use_Parameter m_Parameter;
	CardPlay_Use m_Use;
	CardPlay_Use_Play m_play;
	int m_UseSound;
public:
	CardPlayUse_Manager() {};
	~CardPlayUse_Manager(){};
	void Update();
	void Draw();
	//CardPlay_ManagerとのリンクInitで呼び出す
	void InitLink(CardPlay_Manager* card) ;
	void Uninit();
	void Play();
};

