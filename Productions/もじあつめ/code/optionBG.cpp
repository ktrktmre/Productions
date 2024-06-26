/*==============================================================================

   設定BG管理 [option.cpp]
														 Author :切田 海畝斗
														 Date   :2023/09/11
--------------------------------------------------------------------------------

==============================================================================*/
#include "sprite.h"
#include "texture.h"
#include "myfunction.h"
#include "optionBG.h"
#include "option.h"
#include "player.h"
#include "collision.h"
#include "fade.h"
#include "image.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define OPTION_BUTTON_SIZE 80.0f
#define OPTION_FONT_SIZE 50.0f
#define OPTION_ADJUSTMENT_SIZE_X 1000.0f
#define OPTION_ADJUSTMENT_SIZE_Y OPTION_ADJUSTMENT_SIZE_X/100
#define VOLUME_INTERVAL 150

//*****************************************************************************
// グローバル変数
//*****************************************************************************
OPTION g_OptionBG;
OPTION g_OptionBGButton;
OPTION g_OptionSetting[SETTING_NUM];
OPTION g_OptionAdjustment[ADJUSTMENT_NUM];
OPTION g_OptionAdCursor[ADJUSTMENT_NUM];
static float g_OptionAdCursorLImit;
int g_TexVolumeID;
int g_TexColorID;
int g_TexSEID;
int g_TexCursorID;
int g_TexWordID;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void SetSetting(int index, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR color);
void SetAdjustment(int index, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR color);
void SetAdCursor(int index, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR color);

//=============================================================================
// 初期化処理
//=============================================================================
void InitOptionBG(void)
{
	ID3D11Device* pDevice = GetDevice();

	//テクスチャの読み込み
	g_TexVolumeID = LoadTexture((char*)"data/TEXTURE/volume.png");
	g_TexColorID = LoadTexture((char*)"data/TEXTURE/color.png");
	g_TexSEID = LoadTexture((char*)"data/TEXTURE/SE.png");
	g_TexCursorID = LoadTexture((char*)"data/TEXTURE/cursor.png");
	g_TexWordID = LoadTexture((char*)"data/TEXTURE/word.png");

	//背景初期化
	g_OptionBG.pos = D3DXVECTOR2(0.0f, 0.0f);
	g_OptionBG.size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	g_OptionBG.tex_v = D3DXVECTOR2(0.0f, 0.0f);
	g_OptionBG.tex_f = D3DXVECTOR2(1.0f, 1.0f);
	g_OptionBG.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_OptionBG.coll = false;
	g_OptionBG.rot = 0.0f;

	//ボタン初期化
	g_OptionBGButton.pos = D3DXVECTOR2(Contrast(422, 257) * OPTION_BUTTON_SIZE, OPTION_BUTTON_SIZE);
	g_OptionBGButton.size = D3DXVECTOR2(Contrast(422, 257) * OPTION_BUTTON_SIZE, OPTION_BUTTON_SIZE);
	g_OptionBGButton.tex_v = D3DXVECTOR2(0.0f, 0.0f);
	g_OptionBGButton.tex_f = D3DXVECTOR2(1.0f, 1.0f);
	g_OptionBGButton.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_OptionBGButton.coll = false;
	g_OptionBGButton.rot = 0.0f;

	//調整バー初期化
	for (int adjCnt = 0; adjCnt < ADJUSTMENT_NUM; adjCnt++)
	{
		g_OptionAdjustment[adjCnt].pos = D3DXVECTOR2(0.0f, 0.0f);
		g_OptionAdjustment[adjCnt].size = D3DXVECTOR2(0.0f, 0.0f);
		g_OptionAdjustment[adjCnt].tex_v = D3DXVECTOR2(0.0f, 0.0f);
		g_OptionAdjustment[adjCnt].tex_f = D3DXVECTOR2(1.0f, 1.0f);
		g_OptionAdjustment[adjCnt].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_OptionAdjustment[adjCnt].coll = false;
		g_OptionAdjustment[adjCnt].rot = 0.0f;

		g_OptionAdCursor[adjCnt].pos = D3DXVECTOR2(0.0f, 0.0f);
		g_OptionAdCursor[adjCnt].size = D3DXVECTOR2(0.0f, 0.0f);
		g_OptionAdCursor[adjCnt].tex_v = D3DXVECTOR2(0.0f, 0.0f);
		g_OptionAdCursor[adjCnt].tex_f = D3DXVECTOR2(1.0f, 1.0f);
		g_OptionAdCursor[adjCnt].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_OptionAdCursor[adjCnt].coll = false;
		g_OptionAdCursor[adjCnt].rot = 0.0f;
	}

	//各設定項目初期化
	for (int setCnt = 0; setCnt < SETTING_NUM; setCnt++)
	{
		g_OptionSetting[setCnt].pos = D3DXVECTOR2(0.0f, 0.0f);
		g_OptionSetting[setCnt].size = D3DXVECTOR2(0.0f, 0.0f);
		g_OptionSetting[setCnt].tex_v = D3DXVECTOR2(0.0f, 0.0f);
		g_OptionSetting[setCnt].tex_f = D3DXVECTOR2(1.0f, 1.0f);
		g_OptionSetting[setCnt].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_OptionSetting[setCnt].coll = false;
		g_OptionSetting[setCnt].rot = 0.0f;
	}

	//設定セット
	SetSetting(VOLUME, D3DXVECTOR2(300, 100), D3DXVECTOR2(Contrast(752, 177) * OPTION_FONT_SIZE, OPTION_FONT_SIZE), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetSetting(BGM, D3DXVECTOR2(400, OPTION_FONT_SIZE*4), D3DXVECTOR2(OPTION_FONT_SIZE, OPTION_FONT_SIZE), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetSetting(SE, D3DXVECTOR2(400, OPTION_FONT_SIZE*6), D3DXVECTOR2(Contrast(561, 177) * OPTION_FONT_SIZE, OPTION_FONT_SIZE), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetSetting(COLOR, D3DXVECTOR2(300, OPTION_FONT_SIZE * 8), D3DXVECTOR2(Contrast(930, 174) * OPTION_FONT_SIZE, OPTION_FONT_SIZE), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetSetting(CURSOR, D3DXVECTOR2(400, OPTION_FONT_SIZE * 10), D3DXVECTOR2(Contrast(730, 154) * OPTION_FONT_SIZE, OPTION_FONT_SIZE), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetSetting(HIT_WORD, D3DXVECTOR2(400, OPTION_FONT_SIZE * 15), D3DXVECTOR2(Contrast(358, 174) * OPTION_FONT_SIZE, OPTION_FONT_SIZE), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//調整バーセット
	//音量
	SetAdjustment(BGM_VOLUME, D3DXVECTOR2(g_OptionSetting[BGM].pos.x + 300, g_OptionSetting[BGM].pos.y),
		D3DXVECTOR2(OPTION_ADJUSTMENT_SIZE_X, OPTION_ADJUSTMENT_SIZE_Y), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetAdjustment(SE_VOLUME, D3DXVECTOR2(g_OptionSetting[SE].pos.x + 300, g_OptionSetting[SE].pos.y),
		D3DXVECTOR2(OPTION_ADJUSTMENT_SIZE_X, OPTION_ADJUSTMENT_SIZE_Y), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//カーソルカラー
	SetAdjustment(CURSOR_R, D3DXVECTOR2(g_OptionSetting[CURSOR].pos.x + 300, g_OptionSetting[CURSOR].pos.y),
		D3DXVECTOR2(OPTION_ADJUSTMENT_SIZE_X, OPTION_ADJUSTMENT_SIZE_Y), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	SetAdjustment(CURSOR_G, D3DXVECTOR2(g_OptionSetting[CURSOR].pos.x + 300, g_OptionSetting[CURSOR].pos.y + OPTION_ADJUSTMENT_SIZE_Y * 6),
		D3DXVECTOR2(OPTION_ADJUSTMENT_SIZE_X, OPTION_ADJUSTMENT_SIZE_Y), D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	SetAdjustment(CURSOR_B, D3DXVECTOR2(g_OptionSetting[CURSOR].pos.x + 300, g_OptionSetting[CURSOR].pos.y + OPTION_ADJUSTMENT_SIZE_Y * 12),
		D3DXVECTOR2(OPTION_ADJUSTMENT_SIZE_X, OPTION_ADJUSTMENT_SIZE_Y), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
	//ヒットした文字カラー
	SetAdjustment(HIT_WORD_R, D3DXVECTOR2(g_OptionSetting[HIT_WORD].pos.x + 300, g_OptionSetting[HIT_WORD].pos.y),
		D3DXVECTOR2(OPTION_ADJUSTMENT_SIZE_X, OPTION_ADJUSTMENT_SIZE_Y), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	SetAdjustment(HIT_WORD_G, D3DXVECTOR2(g_OptionSetting[HIT_WORD].pos.x + 300, g_OptionSetting[HIT_WORD].pos.y + OPTION_ADJUSTMENT_SIZE_Y * 6),
		D3DXVECTOR2(OPTION_ADJUSTMENT_SIZE_X, OPTION_ADJUSTMENT_SIZE_Y), D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	SetAdjustment(HIT_WORD_B, D3DXVECTOR2(g_OptionSetting[HIT_WORD].pos.x + 300, g_OptionSetting[HIT_WORD].pos.y + OPTION_ADJUSTMENT_SIZE_Y * 12),
		D3DXVECTOR2(OPTION_ADJUSTMENT_SIZE_X, OPTION_ADJUSTMENT_SIZE_Y), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));

	//調整カーソルセット
	//音量
	float volume;
	volume = CopyVolumeBGM();
	SetAdCursor(BGM_VOLUME, D3DXVECTOR2(g_OptionAdjustment[BGM_VOLUME].pos.x + OPTION_ADJUSTMENT_SIZE_X * volume, g_OptionAdjustment[BGM_VOLUME].pos.y + OPTION_ADJUSTMENT_SIZE_Y / 2),
		D3DXVECTOR2(OPTION_ADJUSTMENT_SIZE_Y * 2, OPTION_ADJUSTMENT_SIZE_Y * 4), D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f));
	volume = CopyVolumeSE();
	SetAdCursor(SE_VOLUME, D3DXVECTOR2(g_OptionAdjustment[SE_VOLUME].pos.x + OPTION_ADJUSTMENT_SIZE_X * volume, g_OptionAdjustment[SE_VOLUME].pos.y + OPTION_ADJUSTMENT_SIZE_Y / 2),
		D3DXVECTOR2(OPTION_ADJUSTMENT_SIZE_Y * 2, OPTION_ADJUSTMENT_SIZE_Y * 4), D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f));

	//カーソルカラー
	D3DXCOLOR color;
	color = CopyPlayerColor();
	SetAdCursor(CURSOR_R, D3DXVECTOR2(g_OptionAdjustment[CURSOR_R].pos.x + OPTION_ADJUSTMENT_SIZE_X * Contrast(color.r, FULL_COLOR), g_OptionAdjustment[CURSOR_R].pos.y + OPTION_ADJUSTMENT_SIZE_Y / 2),
		D3DXVECTOR2(OPTION_ADJUSTMENT_SIZE_Y * 2, OPTION_ADJUSTMENT_SIZE_Y * 4), D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f));
	SetAdCursor(CURSOR_G, D3DXVECTOR2(g_OptionAdjustment[CURSOR_G].pos.x + OPTION_ADJUSTMENT_SIZE_X * Contrast(color.g, FULL_COLOR), g_OptionAdjustment[CURSOR_G].pos.y + OPTION_ADJUSTMENT_SIZE_Y / 2),
		D3DXVECTOR2(OPTION_ADJUSTMENT_SIZE_Y * 2, OPTION_ADJUSTMENT_SIZE_Y * 4), D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f));
	SetAdCursor(CURSOR_B, D3DXVECTOR2(g_OptionAdjustment[CURSOR_B].pos.x + OPTION_ADJUSTMENT_SIZE_X * Contrast(color.b, FULL_COLOR), g_OptionAdjustment[CURSOR_B].pos.y + OPTION_ADJUSTMENT_SIZE_Y / 2),
		D3DXVECTOR2(OPTION_ADJUSTMENT_SIZE_Y * 2, OPTION_ADJUSTMENT_SIZE_Y * 4), D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f));

	//ヒット文字カラー
	color = CopyCollColor();
	SetAdCursor(HIT_WORD_R, D3DXVECTOR2(g_OptionAdjustment[HIT_WORD_R].pos.x + OPTION_ADJUSTMENT_SIZE_X * Contrast(color.r, FULL_COLOR), g_OptionAdjustment[HIT_WORD_R].pos.y + OPTION_ADJUSTMENT_SIZE_Y / 2),
		D3DXVECTOR2(OPTION_ADJUSTMENT_SIZE_Y * 2, OPTION_ADJUSTMENT_SIZE_Y * 4), D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f));
	SetAdCursor(HIT_WORD_G, D3DXVECTOR2(g_OptionAdjustment[HIT_WORD_G].pos.x + OPTION_ADJUSTMENT_SIZE_X * Contrast(color.g, FULL_COLOR), g_OptionAdjustment[HIT_WORD_G].pos.y + OPTION_ADJUSTMENT_SIZE_Y / 2),
		D3DXVECTOR2(OPTION_ADJUSTMENT_SIZE_Y * 2, OPTION_ADJUSTMENT_SIZE_Y * 4), D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f));
	SetAdCursor(HIT_WORD_B, D3DXVECTOR2(g_OptionAdjustment[HIT_WORD_B].pos.x + OPTION_ADJUSTMENT_SIZE_X * Contrast(color.b, FULL_COLOR), g_OptionAdjustment[HIT_WORD_B].pos.y + OPTION_ADJUSTMENT_SIZE_Y / 2),
		D3DXVECTOR2(OPTION_ADJUSTMENT_SIZE_Y * 2, OPTION_ADJUSTMENT_SIZE_Y * 4), D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f));

	//調整カーソル移動限界セット(最大値)
	g_OptionAdCursorLImit = g_OptionAdjustment[BGM_VOLUME].pos.x + OPTION_ADJUSTMENT_SIZE_X;

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitOptionBG(void)
{
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateOptionBG(void)
{
	PLAYER* pPlayer = GetPlayer();
	//シーン遷移
	if (g_OptionBGButton.coll && pPlayer->shoot)
	{
		//フェードが起きていなかったら
		MODE_FADE* pFade = GetFade();
		if (*pFade == FADE_NOT)
		{
			SetFade(FADE_OUT);
		}
	}
	//調整カーソル移動(音量、カラー調整)
	for (int adjCnt = 0; adjCnt < ADJUSTMENT_NUM; adjCnt++)
	{
		if (g_OptionAdCursor[adjCnt].coll && pPlayer->grab)
		{
			g_OptionAdCursor[adjCnt].pos.x = pPlayer->pos.x;
		}

		//調整カーソル移動限界(最大、最小値制限)
		if (g_OptionAdCursor[adjCnt].pos.x > g_OptionAdCursorLImit)
		{
			g_OptionAdCursor[adjCnt].pos.x = g_OptionAdCursorLImit;
		}
		if (g_OptionAdCursor[adjCnt].pos.x < g_OptionAdjustment->pos.x)
		{
			g_OptionAdCursor[adjCnt].pos.x = g_OptionAdjustment->pos.x;
		}
	}
	//ボリュームの調整
	float volume;
	volume = (g_OptionAdCursor[BGM_VOLUME].pos.x - g_OptionAdjustment[BGM_VOLUME].pos.x) / OPTION_ADJUSTMENT_SIZE_X;
	SetVolumeBGM(volume);
	volume = (g_OptionAdCursor[SE_VOLUME].pos.x - g_OptionAdjustment[SE_VOLUME].pos.x) / OPTION_ADJUSTMENT_SIZE_X;
	SetVolumeSE(volume);

	//カラーの調整
	//カーソルカラー
	D3DXCOLOR color;
	color.r= (g_OptionAdCursor[CURSOR_R].pos.x - g_OptionAdjustment[CURSOR_R].pos.x) / OPTION_ADJUSTMENT_SIZE_X;
	color.g= (g_OptionAdCursor[CURSOR_G].pos.x - g_OptionAdjustment[CURSOR_G].pos.x) / OPTION_ADJUSTMENT_SIZE_X;
	color.b= (g_OptionAdCursor[CURSOR_B].pos.x - g_OptionAdjustment[CURSOR_B].pos.x) / OPTION_ADJUSTMENT_SIZE_X;
	SetPlayerColor(color);

	//ヒット文字カラー
	color.r = (g_OptionAdCursor[HIT_WORD_R].pos.x - g_OptionAdjustment[HIT_WORD_R].pos.x) / OPTION_ADJUSTMENT_SIZE_X;
	color.g = (g_OptionAdCursor[HIT_WORD_G].pos.x - g_OptionAdjustment[HIT_WORD_G].pos.x) / OPTION_ADJUSTMENT_SIZE_X;
	color.b = (g_OptionAdCursor[HIT_WORD_B].pos.x - g_OptionAdjustment[HIT_WORD_B].pos.x) / OPTION_ADJUSTMENT_SIZE_X;
	SetCollColor(color);
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawOptionBG(void)
{
	SetSamplerState(FILTER_MODE_LINEAR, ADDRESS_MODE_WRAP);
	IMAGE* pImage = GetImage();
	float volume;
	D3DXCOLOR color;

	//タイトルBGの描画
	DrawSpriteLeftTop(pImage->TexBlackBoardID,
		g_OptionBG.pos,
		g_OptionBG.size,
		g_OptionBG.tex_v,
		g_OptionBG.tex_f);

	//音量設定描画
	DrawSpriteLeftTopColor(g_TexVolumeID,
		g_OptionSetting[VOLUME].pos,
		g_OptionSetting[VOLUME].size,
		g_OptionSetting[VOLUME].tex_v,
		g_OptionSetting[VOLUME].tex_f,
		g_OptionSetting[VOLUME].color
	);

	//BGM設定描画
	DrawWord(pImage->TexDefChrID,
		g_OptionSetting[BGM].pos,
		"bgm",
		g_OptionSetting[BGM].size.x,
		g_OptionSetting[BGM].color
	);
	DrawSpriteLeftTopColor(pImage->TexBoxID,
		g_OptionAdjustment[BGM_VOLUME].pos,
		g_OptionAdjustment[BGM_VOLUME].size,
		g_OptionAdjustment[BGM_VOLUME].tex_v,
		g_OptionAdjustment[BGM_VOLUME].tex_f,
		g_OptionAdjustment[BGM_VOLUME].color
	);
	DrawSpriteColor(pImage->TexBoxID,
		g_OptionAdCursor[BGM_VOLUME].pos,
		g_OptionAdCursor[BGM_VOLUME].size,
		g_OptionAdCursor[BGM_VOLUME].tex_v,
		g_OptionAdCursor[BGM_VOLUME].tex_f,
		g_OptionAdCursor[BGM_VOLUME].color
	);
	volume = CopyVolumeBGM() * 100.0f;
	for (int bgmCnt = 0; bgmCnt < VOLUME_DIGIT; bgmCnt++)
	{
		int bottom = BottomDigit(volume);
		volume /= 10;

		DrawSpriteColor(pImage->TexDefNumID,
			D3DXVECTOR2(g_OptionAdCursorLImit + VOLUME_INTERVAL - bgmCnt * OPTION_FONT_SIZE, g_OptionAdCursor[BGM_VOLUME].pos.y),
			D3DXVECTOR2(OPTION_FONT_SIZE, OPTION_FONT_SIZE),
			D3DXVECTOR2(bottom % NUM_PART_X * TEX_PART(NUM_PART_X), bottom / NUM_PART_X * TEX_PART(NUM_PART_Y)),
			D3DXVECTOR2(TEX_PART(NUM_PART_X), TEX_PART(NUM_PART_Y)),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
		);
	}

	//効果音設定描画
	DrawSpriteLeftTopColor(g_TexSEID,
		g_OptionSetting[SE].pos,
		g_OptionSetting[SE].size,
		g_OptionSetting[SE].tex_v,
		g_OptionSetting[SE].tex_f,
		g_OptionSetting[SE].color
	);
	DrawSpriteLeftTopColor(pImage->TexBoxID,
		g_OptionAdjustment[SE_VOLUME].pos,
		g_OptionAdjustment[SE_VOLUME].size,
		g_OptionAdjustment[SE_VOLUME].tex_v,
		g_OptionAdjustment[SE_VOLUME].tex_f,
		g_OptionAdjustment[SE_VOLUME].color
	);
	DrawSpriteColor(pImage->TexBoxID,
		g_OptionAdCursor[SE_VOLUME].pos,
		g_OptionAdCursor[SE_VOLUME].size,
		g_OptionAdCursor[SE_VOLUME].tex_v,
		g_OptionAdCursor[SE_VOLUME].tex_f,
		g_OptionAdCursor[SE_VOLUME].color
	);
	volume = CopyVolumeSE() * 100.0f;
	for (int seCnt = 0; seCnt < VOLUME_DIGIT; seCnt++)
	{
		int bottom = BottomDigit(volume);
		volume /= 10;

		DrawSpriteColor(pImage->TexDefNumID,
			D3DXVECTOR2(g_OptionAdCursorLImit + VOLUME_INTERVAL - seCnt * OPTION_FONT_SIZE, g_OptionAdCursor[SE_VOLUME].pos.y),
			D3DXVECTOR2(OPTION_FONT_SIZE, OPTION_FONT_SIZE),
			D3DXVECTOR2(bottom % NUM_PART_X * TEX_PART(NUM_PART_X), bottom / NUM_PART_X * TEX_PART(NUM_PART_Y)),
			D3DXVECTOR2(TEX_PART(NUM_PART_X), TEX_PART(NUM_PART_Y)),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
		);
	}

	//カラー設定描画
	DrawSpriteLeftTopColor(g_TexColorID,
		g_OptionSetting[COLOR].pos,
		g_OptionSetting[COLOR].size,
		g_OptionSetting[COLOR].tex_v,
		g_OptionSetting[COLOR].tex_f,
		g_OptionSetting[COLOR].color
	);

	//カーソルカラー設定描画
	DrawSpriteLeftTopColor(g_TexCursorID,
		g_OptionSetting[CURSOR].pos,
		g_OptionSetting[CURSOR].size,
		g_OptionSetting[CURSOR].tex_v,
		g_OptionSetting[CURSOR].tex_f,
		g_OptionSetting[CURSOR].color
	);
	for (int colorCnt = CURSOR_R; colorCnt <= CURSOR_B; colorCnt++)
	{
		DrawSpriteLeftTopColor(pImage->TexBoxID,
			g_OptionAdjustment[colorCnt].pos,
			g_OptionAdjustment[colorCnt].size,
			g_OptionAdjustment[colorCnt].tex_v,
			g_OptionAdjustment[colorCnt].tex_f,
			g_OptionAdjustment[colorCnt].color
		);

		DrawSpriteColor(pImage->TexBoxID,
			g_OptionAdCursor[colorCnt].pos,
			g_OptionAdCursor[colorCnt].size,
			g_OptionAdCursor[colorCnt].tex_v,
			g_OptionAdCursor[colorCnt].tex_f,
			g_OptionAdCursor[colorCnt].color
		);
	}
	color = CopyPlayerColor();
	for (int rgbCnt = CURSOR_R; rgbCnt <= CURSOR_B; rgbCnt++)
	{
		float rgb;
		switch (rgbCnt)
		{
		case CURSOR_R:
			rgb = color.r;
			break;
		case CURSOR_G:
			rgb = color.g;
			break;
		case CURSOR_B:
			rgb = color.b;
			break;
		default:
			break;
		}
		for (int seCnt = 0; seCnt < VOLUME_DIGIT; seCnt++)
		{
			int bottom = BottomDigit(rgb);
			rgb /= 10;

			DrawSpriteColor(pImage->TexDefNumID,
				D3DXVECTOR2(g_OptionAdCursorLImit + VOLUME_INTERVAL - seCnt * OPTION_FONT_SIZE, g_OptionAdCursor[rgbCnt].pos.y),
				D3DXVECTOR2(OPTION_FONT_SIZE, OPTION_FONT_SIZE),
				D3DXVECTOR2(bottom % NUM_PART_X * TEX_PART(NUM_PART_X), bottom / NUM_PART_X * TEX_PART(NUM_PART_Y)),
				D3DXVECTOR2(TEX_PART(NUM_PART_X), TEX_PART(NUM_PART_Y)),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			);
		}
	}
	//カーソルサンプル
	DrawSpriteLeftTopColor(pImage->TexCursorID,
		D3DXVECTOR2(g_OptionSetting[CURSOR].pos.x + OPTION_FONT_SIZE*2, g_OptionSetting[CURSOR].pos.y + OPTION_FONT_SIZE*2),
		D3DXVECTOR2(OPTION_FONT_SIZE * 2, OPTION_FONT_SIZE * 2),
		D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f, 1.0f),
		D3DXCOLOR(color.r / FULL_COLOR, color.g / FULL_COLOR, color.b / FULL_COLOR, color.a)
	);

	//ヒット文字カラー設定描画
	DrawSpriteLeftTopColor(g_TexWordID,
		g_OptionSetting[HIT_WORD].pos,
		g_OptionSetting[HIT_WORD].size,
		g_OptionSetting[HIT_WORD].tex_v,
		g_OptionSetting[HIT_WORD].tex_f,
		g_OptionSetting[HIT_WORD].color
	);
	for (int colorCnt = HIT_WORD_R; colorCnt <= HIT_WORD_B; colorCnt++)
	{
		DrawSpriteLeftTopColor(pImage->TexBoxID,
			g_OptionAdjustment[colorCnt].pos,
			g_OptionAdjustment[colorCnt].size,
			g_OptionAdjustment[colorCnt].tex_v,
			g_OptionAdjustment[colorCnt].tex_f,
			g_OptionAdjustment[colorCnt].color
		);

		DrawSpriteColor(pImage->TexBoxID,
			g_OptionAdCursor[colorCnt].pos,
			g_OptionAdCursor[colorCnt].size,
			g_OptionAdCursor[colorCnt].tex_v,
			g_OptionAdCursor[colorCnt].tex_f,
			g_OptionAdCursor[colorCnt].color
		);
	}
	color = CopyCollColor();
	for (int rgbCnt = HIT_WORD_R; rgbCnt <= HIT_WORD_B; rgbCnt++)
	{
		float rgb;
		switch (rgbCnt)
		{
		case HIT_WORD_R:
			rgb = color.r;
			break;
		case HIT_WORD_G:
			rgb = color.g;
			break;
		case HIT_WORD_B:
			rgb = color.b;
			break;
		default:
			break;
		}
		for (int seCnt = 0; seCnt < VOLUME_DIGIT; seCnt++)
		{
			int bottom = BottomDigit(rgb);
			rgb /= 10;

			DrawSpriteColor(pImage->TexDefNumID,
				D3DXVECTOR2(g_OptionAdCursorLImit + VOLUME_INTERVAL - seCnt * OPTION_FONT_SIZE, g_OptionAdCursor[rgbCnt].pos.y),
				D3DXVECTOR2(OPTION_FONT_SIZE, OPTION_FONT_SIZE),
				D3DXVECTOR2(bottom % NUM_PART_X * TEX_PART(NUM_PART_X), bottom / NUM_PART_X * TEX_PART(NUM_PART_Y)),
				D3DXVECTOR2(TEX_PART(NUM_PART_X), TEX_PART(NUM_PART_Y)),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			);
		}
	}
	DrawChar(pImage->TexDefChrID,
		D3DXVECTOR2(g_OptionSetting[HIT_WORD].pos.x + OPTION_FONT_SIZE * 2, g_OptionSetting[HIT_WORD].pos.y + OPTION_FONT_SIZE * 2),
		"a",
		OPTION_FONT_SIZE * 2,
		D3DXCOLOR(color.r / FULL_COLOR, color.g / FULL_COLOR, color.b / FULL_COLOR, color.a)
	);

	//ボタン描画
	DrawSpriteColor(pImage->TexReturnID,
		g_OptionBGButton.pos,
		g_OptionBGButton.size,
		g_OptionBGButton.tex_v,
		g_OptionBGButton.tex_f,
		g_OptionBGButton.color
	);
}

//=============================================================================
// 設定セッター
//=============================================================================
void SetSetting(int index, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR color)
{
	g_OptionSetting[index].pos = pos;
	g_OptionSetting[index].size = size;
	g_OptionSetting[index].color = color;
}

//=============================================================================
// 調整バーセッター
//=============================================================================
void SetAdjustment(int index, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR color)
{
	g_OptionAdjustment[index].pos = pos;
	g_OptionAdjustment[index].size = size;
	g_OptionAdjustment[index].color= color;
}

//=============================================================================
// 調整カーソルセッター
//=============================================================================
void SetAdCursor(int index, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR color)
{
	g_OptionAdCursor[index].pos = pos;
	g_OptionAdCursor[index].size = size;
	g_OptionAdCursor[index].color = color;
}

//=============================================================================
// 調整カーソルゲッター
//=============================================================================
OPTION* GetAdCursor(void)
{
	return g_OptionAdCursor;
}

//=============================================================================
// ボタンゲッター
//=============================================================================
OPTION* GetOptionBGButton(void)
{
	return &g_OptionBGButton;
}