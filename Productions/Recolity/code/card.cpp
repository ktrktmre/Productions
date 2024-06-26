//=============================================================================
//
// カードメイン処理 [card.cpp]
// Author : 
//
//=============================================================================
#include "carddatamanager.h"
#include "cardmenumanager.h"
#include "cardplaypdeckmanager.h"
#include "cardplayuse_manager.h"
#include "card_base.h"
#include "cardplaygetcardh.h"

#include "input.h"
#include "cardmanuget.h"
#include "camera.h"
//*****************************************************************************
// グローバル変数
//*****************************************************************************
CardDataManager			g_CardData;//ゲームカードデータ保管
CardMenu_Manager		g_CardMenu(&g_CardData);//メニュー画面のカードデータ保管
CardPlay_Manager		g_CardPlayDeck;//ゲーム内カードデータ保管
Card_GetCard			g_CardGet;//カード取得処理
CardPlayUse_Manager		g_CardPlayUse;//ゲーム内のカードの操作
DropCardManager			g_DropCard(&g_CardData, &g_CardGet,&g_CardPlayDeck);
CardMenu_Get			g_CardMenuGet(&g_CardMenu, &g_CardData);
void InitCard() {
	g_CardData.InitCard();
	g_CardPlayUse.InitLink(&g_CardPlayDeck);
	
	g_CardGet.LinkData(&g_CardPlayDeck, &g_DropCard);

	g_CardPlayDeck.GetDeck(&g_CardMenu);

}
void UninitCard() {
	g_DropCard.Uninit();
	g_CardPlayUse.Uninit();
	g_CardGet.Uninit();
}
void UpdateCard() {


	if (g_CardGet.InData() == false)
	{
		g_CardPlayUse.Update();
	}
	g_DropCard.Update();
	g_CardGet.Update();
#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_V))
	{
		g_DropCard.NoHaveCardDrop(GetCamera()->pos, 0.5f);
	}
#endif // _DEBUG


	
}
void DrawCard() {

	g_DropCard.Draw();
	
}
void DrawCard2D() {

	//ゲームプレイ画面のＵＩ表示
	g_CardPlayUse.Draw();

	//Tab押した時の画面表示
	if (g_CardGet.InData() == false)
	{
		g_CardPlayDeck.TabDraw();
	}
	

	//カード取得処理表示
	g_CardGet.DrawUI();
	//メニューのカード表示
  //  g_CardMenu.DrawCard();
}
void Update_Menu_deck(void) {
	g_CardMenuGet.Update();
}
void Draw_Menu_deck(void) {
	g_CardMenuGet.DrawUI();
}
bool GetCardflug() {
	if (g_CardGet.InData())
	{
		return true;
	}
	return false;
}
DropCardManager* PGetDropCard() {
	return &g_DropCard;
}
void CardDropChance(D3DXVECTOR3 droppos,float rank2Weight) {
	g_DropCard.NoHaveCardDrop(droppos, rank2Weight);
}