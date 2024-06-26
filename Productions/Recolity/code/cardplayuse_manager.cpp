#include "cardplayuse_manager.h"
#include "cardplayuse_parameter.h"
#include "Game.h"
#include "input.h"
#define MANA_UI_SIZE (10.0f)
#define MANA_UI_SIZE_CRISTAL (MANA_UI_SIZE * 7.0f)
#define CARD_HAND_MAX (5)
bool g_Debugfanc = false;
bool g_Load = false;
void CardPlayUse_Manager::Update() {
	m_Parameter.Update();
	m_play.Update(m_Use.CardGetHandNum());
	m_Use.CardReset();
	//カードを使用する
	if (m_Use.CardGetHandNum() > 0 &&
		IsMouseLeftTriggered() &&
		(int)m_Parameter.GetMana()->GetMana() >= m_Use.CardDiscardCost(m_play.SclectNo()))
	{
	
		Play();
		m_Parameter.GetMana()->ReduceMana((float)m_Use.CardDiscardCost(m_play.SclectNo()));
		m_Use.CardDiscard(m_play.SclectNo());

	}
	//デバック表示用
	if (GetKeyboardTrigger(DIK_G))
	{
		//g_Debugfanc = !g_Debugfanc;
	}
	//==================================================
	// 元のタイプ
	// //クールタイムが上がったらカードをドローする
	//================================================== 
	
	if (m_Parameter.GetTimer()->GetDrawTime() <= 0 && //手札が最大数より多くならないようにする
		m_Use.CardGetHandNum() < CARD_HAND_MAX)
	{
		m_Parameter.GetTimer()->SetDrawTime(CARD_DRAW_TIME);
		m_Use.CardDraw();
	}

	if (m_Use.CardGetHandNum() >= CARD_HAND_MAX)	//カードを最大数持っていたらCDが始まらない
	{
		m_Parameter.GetTimer()->SetDrawTime(CARD_DRAW_TIME);
	}
}
void CardPlayUse_Manager::Draw() {
	//SetText({ 0,0,10000,10000 }, "デバック表示切り替えG");
	UI ui = { {0.0f,0.0f} ,D3DXVECTOR2(MANA_UI_SIZE_CRISTAL,MANA_UI_SIZE_CRISTAL),UI_PRSET_UV1 ,DIK_COLER_WHITE };
	for (int i = 0; i < (int)m_Parameter.GetMana()->GetMana(); i++)
	{
		ui.m_Pos = D3DXVECTOR2((SCREEN_WIDTH - MANA_UI_SIZE_CRISTAL), 650 - i * MANA_UI_SIZE_CRISTAL);
		DrawScreen(ui, RefImageMaterial().m_Crystal);
	}
	float f = m_Parameter.GetMana()->GetMana() - (float)(int)m_Parameter.GetMana()->GetMana();

	ui = { D3DXVECTOR2((SCREEN_WIDTH - MANA_UI_SIZE_CRISTAL),650 - (int)m_Parameter.GetMana()->GetMana() * MANA_UI_SIZE_CRISTAL) ,D3DXVECTOR2(MANA_UI_SIZE_CRISTAL,MANA_UI_SIZE_CRISTAL),D3DXVECTOR2(0.0f,0.0f),D3DXVECTOR2(1.0f,1.0f) ,D3DXCOLOR(0.6f,0.6f,0.6f,f) };
	DrawScreen(ui, RefImageMaterial().m_Crystal);
	if (g_Debugfanc)
	{
		m_Use.DebugDraw(m_play.SclectNo());
	}
	else
	{
		m_Use.Draw(m_play.SclectNo());
	}
}

void CardPlayUse_Manager::InitLink(CardPlay_Manager* card)
{
	 m_Use.InitPlayUse(card); m_Parameter.Init();
	 m_UseSound = LoadSound("use_card");
	
}

void CardPlayUse_Manager::Uninit()
{
	m_Use.Uninit();
	StopSound(m_UseSound);
}

void CardPlayUse_Manager::Play()
{
	PlaySound(m_UseSound, 0, 1.0f);
}
