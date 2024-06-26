#pragma once
#include "bullet_interface.h"
#include "dropcard.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 構造体
//*****************************************************************************
 void InitCard();
 void UninitCard();
 void UpdateCard();
 void DrawCard();
 void DrawCard2D();
 void Update_Menu_deck(void);
 void Draw_Menu_deck(void);
 bool GetCardflug();
 void CardDropChance(D3DXVECTOR3 droppos, float rank2Weight);
 DropCardManager* PGetDropCard();
