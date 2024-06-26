#include "player.h"
#include "camera.h"
#include "input.h"	
#include "model.h "
#include "baseeffect.h"
#include "Texture.h"
#include "collision.h"
#include "material.h"
#include "Game.h"
#include "text.h"
#include "sprite.h"
#include "material.h"
#include "floor.h"
#include "fade.h"
#include "sound.h"

#define PLAYER_VEL		(10.0f)			//カメラの移動速度
#define DUSHSPEED		(0.6f)
#define SNEAKSPEED		(0.4f)
#define MAXHP			(100)
#define EASY_MAXHP		(400)
#define PLAYER_HPBERPOS_X (500)
#define PLAYER_HPBERPOS_Y (SCREEN_HEIGHT - 100)

#define PLAYER_HPBERSIZE (5)

bool gamemodeshow;//ゲーム表示がデバックかゲームか切り替わる
int poliline[3];
int g_cardtex[10] = {};
int g_cardtexster = 0;
int g_cardtexflame = 0;

//=============================================================================
// ダメージを受ける
//=============================================================================
void PLAYER::IsDamage(float damage)
{
	float adddamage = damage;
	if (GetGamemode() == Easy)
	{
		adddamage *= 2.0f / 3.0f;
		if (RefHp() - adddamage < 40)
		{
			adddamage = damage * 0.1f;
		}
	}
	if (GetGamemode() == Hard)
	{
		adddamage *= 1.25f;
	}
	SetHp(RefHp() - adddamage);
	//if (RefHp() <= 0);
		//IsDiscard();
}
//=============================================================================
// ダメージを受ける(ドット)
//=============================================================================
void PLAYER::IsDamageDot(float damage)
{
	float adddamage = damage;
	if (GetGamemode() == Easy)
	{
		adddamage *= 2.0f / 3.0f;
	}
	if (GetGamemode() == Hard)
	{
		adddamage *= 1.25f;
	}
	SetHp(RefHp() - adddamage);
	//if (RefHp() <= 0);
		//IsDiscard();
}
void PLAYER::ClerFlug()
{
	m_dush = false;
	SetVolume(m_WorkSound, 0.0f);
	SetVolume(m_DushSound, 0.0f);
}
HRESULT PLAYER::Init(void) {
	m_Button.emplace("DEATHコンテニュー", Button{ { SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT - SCREEN_HEIGHT * 0.5f }, BASE_BUTTTON_SIZE });
	m_Button.emplace("DEATHタイトル", Button{ { SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT - SCREEN_HEIGHT * 0.65f }, BASE_BUTTTON_SIZE });
	effect.InitSound();
	m_pos = D3DXVECTOR3(50, 0, 50);
	m_oldpos = D3DXVECTOR3(50, 0, 50);
	SetPos(D3DXVECTOR3(50, 0, 50));
	SetOldPos();
	m_vel = D3DXVECTOR3(0, 0, 0);
	SetHp(EASY_MAXHP);
	m_movespeed = 1.0f;
	m_stamina = 6000;
	m_minimap = false;
	m_WorkSound = LoadSound("wark");
	m_DushSound = LoadSound("run");
	PlaySound(m_WorkSound, -1, 1.0f);
	PlaySound(m_DushSound, -1, 1.0f);
	return S_OK;
}
void PLAYER::Uninit(void)
{
	m_Button.clear();
	StopSound(m_DushSound);
	StopSound(m_WorkSound);
}
void PLAYER::Update(void) {
	//=================================================
// *******プレイヤーのアップデートの呼び出し順******
// 
// 各パラメーターのリセット	A	: PlayR
// ↓
// 各バフの更新				B	: PlayU
// ↓
// フラグのセット			C	: PlayS
// ↓
// 入力処理					D	: PlayI
//=================================================
#ifndef _DEBUG

#endif // !_DEBUG

	if (RefHp() <= 0)
	{
		SetHp(0);
		CursprLock(false);
		D3DXVECTOR2 mousepos = GetMousePos();
		if (m_Button.at("DEATHコンテニュー").IsPush(mousepos, IsMouseLeftTriggered())) {
			UninitGame();
			InitGame();
		}
		if (m_Button.at("DEATHタイトル").IsPush(mousepos, IsMouseLeftTriggered())) {
			SceneTransition(SCENE_MENU);
		}

	}
//----------------------------
// A
//----------------------------
	PlayR_Stamina();

	PlayR_StateUpdate();
	//----------------------------
	// B
	//----------------------------

	PlayU_EffectUpdate();
	PlayU_Vel();
	//----------------------------
	// C
	//----------------------------
	PlayS_Dush();
	PlayS_sneak();
	//----------------------------
	// D
	//----------------------------
	PlayI_Move();
	PlayI_FlorEffect();
	PlayR_PosUpdate();

	//カーソルロック
	if (GetKeyboardTrigger(DIK_L))
	{
		CursprLock(true);
	}
	if (GetKeyboardTrigger(DIK_K))
	{
		CursprLock(false);
	}
	if (IsMouseSide4Triggered())
	{
		CursprLock(true);
	}	
	if (IsMouseSide5Triggered())
	{
		CursprLock(false);
	}
	//ミニマップの表示
	if (GetKeyboardTrigger(DIK_E))
	{
		m_minimap ? m_minimap = false : m_minimap = true;
	}
	//受けた属性の処理
	for (int index = 0; index < ATTRIBUTE_NUM; index++)
	{
		if (GetAttribute(index) != nullptr)
			GetAttribute(index)->AttributeByType(this);
	}
	//当たり判定の再設定
	for (Collision* pColl : *GetColl())
	{
		pColl->SetCollPos();
	}
}
void PLAYER::Draw() {}
void PLAYER::Draw2D() {
	D3DVECTOR playerpos = GetPos();
	//SetText({ 000.0f,270,500,600 }, "mouse x:" + std::to_string((int)GetMousePos().x) + "y:" + std::to_string((int)GetMousePos().y));
	//SetText({ 000.0f,950,500,1080 }, "pos x:"+std::to_string((int)playerpos.x) + "y:" + std::to_string((int)playerpos.y) + "z:" + std::to_string((int)playerpos.z));
	//SetText({ 000.0f,330,2000,5000 }, "移動 WASD\nジャンプ space\nダッシュ shift\n視点移動 マウス\n選択カード切り替え マウスホイール\nカード使用　左クリック" );
	//SetText({ 000.0f,450,500,600 }, "フロア" + std::to_string((int)GetNowFloor(m_pos)) );
	PlayerDrawUi();
	Playerstatusview();
	UI corsorui = { {SCREEN_CENTER_X,SCREEN_CENTER_Y},{64,64},{0.0f,0.0f},{1.0f,1.0f},DIK_COLER_WHITE,0 };
	DrawScreen(corsorui, RefImageMaterial().m_Reticle);
	if (RefHp() <= 0)
	{
		UI ui = UI{ m_Button.at("DEATHコンテニュー").RefPos(),m_Button.at("DEATHコンテニュー").RefSize()
		,{0.0f,0.0f},{1.0f,1.0f},m_Button.at("DEATHコンテニュー").RefColor(),0.0f };
		DrawScreen(ui, RefImageMaterial().m_Button_ReStart);

		 ui = UI{ m_Button.at("DEATHタイトル").RefPos(),m_Button.at("DEATHタイトル").RefSize()
	,{0.0f,0.0f},{1.0f,1.0f},m_Button.at("DEATHタイトル").RefColor(),0.0f };
		DrawScreen(ui, RefImageMaterial().m_Button_Menu);
	}
}

void PLAYER::PlayI_Move() {
	//移動
	//!effect.GetLock()
	if (!effect.GetLock())
	{
		float movespeed = m_movespeed * ((float)m_dush * DUSHSPEED + 1.0f) * (1.0f - m_sneak * SNEAKSPEED) * (1 - m_slowness);
		float sde = movespeed * PLAYER_VEL;
		if (GetKeyboardPress(DIK_W))
		{
			m_pos.z += PLAYER_VEL * cosf(GetCamera()->rot.y) * movespeed;
			m_pos.x += PLAYER_VEL * sinf(GetCamera()->rot.y) * movespeed;
			m_wark = true;
		}
		if (GetKeyboardPress(DIK_S))
		{
			m_pos.z -= PLAYER_VEL * cosf(GetCamera()->rot.y) * movespeed;
			m_pos.x -= PLAYER_VEL * sinf(GetCamera()->rot.y) * movespeed;
			m_wark = true;
		}
		if (GetKeyboardPress(DIK_A))
		{
			m_pos.z += PLAYER_VEL * sinf(GetCamera()->rot.y) * movespeed;
			m_pos.x -= PLAYER_VEL * cosf(GetCamera()->rot.y) * movespeed;
			m_wark = true;
		}
		if (GetKeyboardPress(DIK_D))
		{
			m_pos.z -= PLAYER_VEL * sinf(GetCamera()->rot.y) * movespeed;
			m_pos.x += PLAYER_VEL * cosf(GetCamera()->rot.y) * movespeed;
			m_wark = true;
		}
		if (GetKeyboardPress(DIK_W) || GetKeyboardPress(DIK_A) || GetKeyboardPress(DIK_S)|| GetKeyboardPress(DIK_D))
		{
			SetVolume(m_WorkSound, 1.0f );
			if (m_dush == true)
			{
				SetVolume(m_WorkSound, 0.0f);
				SetVolume(m_DushSound, 1.0f);
			}
			
		}
		else
		{
			SetVolume(m_WorkSound, 0.0f); 
			SetVolume(m_DushSound, 0.0f);
		}
		if (m_dush == false)
		{
			SetVolume(m_DushSound, 0.0f);
		}
		if (GetKeyboardTrigger(DIK_SPACE)  && m_pos.y <= 200)
		{
			m_vel.y += 16.0f;
			m_jump = true;
		}

	}

#ifdef _DEBUG
		if (GetKeyboardTrigger(DIK_M) )
		{
			m_pos.z = 9250;
			m_pos.x = 2900;
			m_oldpos.z = 9250;
			m_oldpos.x = 2900;
			GetCamera()->rot.y = -D3DX_PI * 0.5f;
		}
		if (IsMouseCenterTriggered())
		{
			m_pos.x += sinf(GetCamera()->rot.y) * cosf(GetCamera()->rot.x) * 1000.0f;
			m_pos.z += cosf(GetCamera()->rot.y) * cosf(GetCamera()->rot.x) * 1000.0f;	
			m_oldpos.x += sinf(GetCamera()->rot.y) * cosf(GetCamera()->rot.x) * 1000.0f;
			m_oldpos.z += cosf(GetCamera()->rot.y) * cosf(GetCamera()->rot.x) * 1000.0f;
		}
#endif // _DEBUG



	
}
void PLAYER::PlayS_Dush() {

	if (GetKeyboardPress(DIK_LSHIFT) && GetKeyboardPress(DIK_W) && m_stamina > 0 )
	{
		m_dush = true;
	}
	if (!GetKeyboardPress(DIK_W))
	{
		m_dush = false;
	}
	if (GetKeyboardPress(DIK_S))
	{
		m_dush = false;
	}
	if (m_stamina <= 0)
	{
		m_dush = false;
	}
	if (m_sneak == true)
	{
		m_dush = false;
	}
	if (m_nodush == true)
	{
		m_dush = false;
	}
}
void PLAYER::PlayS_sneak() {
	if (GetKeyboardPress(DIK_LCONTROL))
	{
		m_sneak = true;
	}
	else
	{
		m_sneak = false;
	}
	if (m_sneak == true)
	{
		m_dush = false;
	}
}
void PLAYER::PlayU_Vel() {
	if (m_pos.y > 200)
	{
		m_vel.y -= 0.75f;
	}
	if (m_pos.y < 200)
	{
	m_pos.y = 200;
	m_vel.y = 0;
	}
	if (m_vel.x > 0)
	{
		m_vel.x *= 0.95f;
	}
	if (m_vel.x < 0)
	{
		m_vel.x *= 0.95f;
	}
	if (m_vel.z > 0)
	{
		m_vel.z *= 0.95f;
	}
	if (m_vel.z < 0)
	{
		m_vel.z *= 0.95f;
	}
	if (m_vel.x <= 0.02 && m_vel.x > 0.02)
	{
		m_vel.x = 0.0f;
	}
	if (m_vel.z <= 0.02 && m_vel.z > 0.02)
	{
		m_vel.z = 0.0f;
	}
	m_pos.x += m_vel.x;
	m_pos.y += m_vel.y;
	m_pos.z += m_vel.z;
}
void PLAYER::PlayR_StateUpdate() {
	m_dush = false;
	m_wark = false;
	m_jump = false;
}
PLAYER::~PLAYER(void)
{
}
PLAYER::PLAYER()
{
		//当たり判定の距離の設定
	SetColl(new Collision(this, { 0.0f,0.0f,0.0f }, 100));
	
}
void PLAYER::SetVel(D3DXVECTOR3 vel)
{
	m_vel = vel;
}
void PLAYER::Playerstatusview() {
	if (GetGamemode()!= Easy)
	{
		SetText({ PLAYER_HPBERPOS_X - 200,PLAYER_HPBERPOS_Y - 15,2300,1500 }, "HP" + std::to_string((int)RefHp()) + "/" + std::to_string(MAXHP));
	}
	else
	{
		SetText({ PLAYER_HPBERPOS_X - 200,PLAYER_HPBERPOS_Y - 15,2300,1500 }, "HP" + std::to_string((int)RefHp()) + "/" + std::to_string(EASY_MAXHP));
	}
	SetText({ PLAYER_HPBERPOS_X-200,PLAYER_HPBERPOS_Y -10+ 55,2300,1500 }, "スタミナ" + std::to_string(m_stamina) + "/" + std::to_string(6000));
	//effect.DrawEffect();
}
void PLAYER::PlayerHeal(float heal) {
	SetHp(RefHp() + heal);
	if (GetGamemode() != Easy)
	{
		if (RefHp() > MAXHP)
		{
			SetHp(MAXHP);
		}
	}
	else {
	
	}	if (RefHp() > EASY_MAXHP)
	{
		SetHp(EASY_MAXHP);
	}

}
void PLAYER::PlayR_Stamina() {
	if (m_dush == false)
	{
		m_stamina += 10;
	}
	if (m_wark == false)
	{
		m_stamina += 50;
	}
	if (m_jump == true)
	{
		m_stamina -= 1500;
	}
	if (m_dush == true)
	{
		m_stamina -= 10;
	}
	if (m_stamina >= 6000)
	{
		m_stamina = 6000;
		m_nodush = false;
	}
	if (m_stamina <= 0)
	{
		m_nodush = true;
		m_stamina =0;
	}
	
}
void PLAYER::PlayR_PosUpdate() {
	//壁判定
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			float in = 1.0f;
			float jn = 1.0f;
			if (i == 1)
			{
				in = -1.0f;

			}
			if (j == 1)
			{
				jn = -1.0f;
			}
			if ((int)GetNowFloor({ m_pos.x + 30.0f * in,m_pos.y,m_oldpos.z + 30.0f * jn }) == 0)
			{
				m_pos.x = m_oldpos.x;
			}
			if ((int)GetNowFloor({ m_oldpos.x + 30.0f * in,m_pos.y,m_pos.z + 30.0f * jn }) == 0)
			{
				m_pos.z = m_oldpos.z;
			}

		}
	}
	if (m_pos.x < 0 )
	{
		m_pos.x = 0.0f;
	}	
	if (m_pos.z < 0)
	{
		m_pos.z = 0.0f;
	}
	if (m_pos.x > 10000) {
		m_pos.x = 10000;
	}
	if (m_pos.z > 10000) {
		m_pos.z = 10000;
	}
	//oldposの更新
	m_oldpos = m_pos;
	SetPos(m_oldpos);
}
void PLAYER::PlayU_EffectUpdate() {
	m_slowness = effect.GetSlowness();
	SetHp(RefHp() - effect.GetSlipdamage());
	PlayerHeal(effect.GetRegen());
	effect.Update();
}
void PLAYER::PlayI_FlorEffect() {
	int num = (int)((m_oldpos.x > 0 ? m_oldpos.x + 50 : m_oldpos.x - 50) / 100) + 50 + 100 * ((int)((m_oldpos.z > 0 ? m_oldpos.z + 50.0f : m_oldpos.z - 50.0f) / -100) + 1);

}
void PLAYER::PlayerDrawUi() {


	UI ui = { D3DXVECTOR2(PLAYER_HPBERPOS_X  ,PLAYER_HPBERPOS_Y),
	D3DXVECTOR2(7.25f * 13.8f * PLAYER_HPBERSIZE  ,5.625f * PLAYER_HPBERSIZE),
	D3DXVECTOR2(0.0f + 0.5f * (1 - RefHp() / MAXHP),0.0f),
	D3DXVECTOR2(0.5f,0.5f),
	D3DXCOLOR(1.0f,0.0f,0.0f,1.0f),
	0 };
	if (GetGamemode() == Easy)
	{
		ui.m_Uv_v = D3DXVECTOR2(0.0f + 0.5f * (1 - RefHp() / EASY_MAXHP), 0.0f);
	}
	DrawScreen(ui, RefImageMaterial().m_Hp);

	ui = { D3DXVECTOR2(PLAYER_HPBERPOS_X  ,PLAYER_HPBERPOS_Y + 55),
	D3DXVECTOR2(7.25f * 13.8f * PLAYER_HPBERSIZE  ,5.625f * PLAYER_HPBERSIZE),
	D3DXVECTOR2(0.0f + 0.5f * (1 - m_stamina / 6000.0f),0.0f),
	D3DXVECTOR2(0.5f,0.5f),
	D3DXCOLOR(0.2f,0.3f,0.9f,1.0f),
	0 };
	DrawScreen(ui, RefImageMaterial().m_Hp);

	ui = { D3DXVECTOR2(PLAYER_HPBERPOS_X,PLAYER_HPBERPOS_Y),
		D3DXVECTOR2(7.25f * 15.0f * PLAYER_HPBERSIZE ,15.0f * PLAYER_HPBERSIZE),
		D3DXVECTOR2(0.0f,0.0f),
		D3DXVECTOR2(1.0f,1.0f),
		D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),
		0 };
	DrawScreen(ui, RefImageMaterial().m_HpFrame);

	if (m_minimap) {
		//ミニマップ
		if (GetStageSelect() == Stage1)
		{
			D3DXVECTOR2 tex_pos = { std::roundf(m_pos.z),std::roundf(m_pos.x) };
			tex_pos /= 10000.0f;
			//アドレッシングモード：ボーダー（指定した色を繰り返す）
			SetSamplerState(FILTER_MODE_LINEAR, ADDRESS_MODE_BORDER);
			SetSamplerBorderColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
			DrawScreenCircle({ 220,220 }, tex_pos, 200, 0.2f, DIK_COLER_WHITE, RefImageMaterial().m_MiniMap_1);
			SetSamplerState(FILTER_MODE_POINT, ADDRESS_MODE_WRAP);
			//ミニマップフレーム
			ui = { { 220,220 },{460,460},{0.0f,0.0f},{1.0f,1.0f},{1.0f,1.0f,0.0f,1.0f} };
			DrawScreen(ui, RefImageMaterial().m_MiniMapFrame);
			//プレイヤー
			ui = { { 220,220 },{50,50},{0.0f,0.0f},{1.0f,1.0f},{1.0f,0.0f,0.0f,1.0f},GetCamera()->rot.y };
			DrawScreen(ui, RefImageMaterial().m_SoundUi1);
		}
		if (GetStageSelect() == Stage2)
		{
			D3DXVECTOR2 tex_pos = { std::roundf(m_pos.z),std::roundf(m_pos.x) };
			tex_pos /= 10000.0f;
			//アドレッシングモード：ボーダー（指定した色を繰り返す）
			SetSamplerState(FILTER_MODE_LINEAR, ADDRESS_MODE_BORDER);
			SetSamplerBorderColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
			DrawScreenCircle({ 220,220 }, tex_pos, 200, 0.2f, DIK_COLER_WHITE, RefImageMaterial().m_MiniMap_2);
			SetSamplerState(FILTER_MODE_POINT, ADDRESS_MODE_WRAP);
			//ミニマップフレーム
			ui = { { 220,220 },{460,460},{0.0f,0.0f},{1.0f,1.0f},{1.0f,1.0f,0.0f,1.0f} };
			DrawScreen(ui, RefImageMaterial().m_MiniMapFrame);
			//プレイヤー
			ui = { { 220,220 },{50,50},{0.0f,0.0f},{1.0f,1.0f},{1.0f,0.0f,0.0f,1.0f},GetCamera()->rot.y };
			DrawScreen(ui, RefImageMaterial().m_SoundUi1);
		}
	}
}