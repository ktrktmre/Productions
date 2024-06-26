/*==============================================================================

   フェード管理 [fade.cpp]
														 Author :切田 海畝斗
														 Date   :2023/06/16
--------------------------------------------------------------------------------

==============================================================================*/
#include "main.h"
#include "fade.h"
#include "sprite.h"
#include "texture.h"
#include "result.h"
#include "game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FADE_SPEED 0.02f

//*****************************************************************************
// グローバル変数
//*****************************************************************************
FADE g_Fade;	//実体
MODE_FADE g_Mode_Fade;	//フェードモード
int g_FadeTexNo = 0;	//テクスチャID
float g_FadeAlpha = 0;	//フェードアルファ値
//=============================================================================
// 初期化処理
//=============================================================================
void InitFade(void)
{
	ID3D11Device* pDevice = GetDevice();

	//テクスチャの読み込み
	g_FadeTexNo = LoadTexture((char*)"data/TEXTURE/fade.png");

	//フェードの初期化
	g_Fade.pos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	g_Fade.size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	g_Fade.tex_v = D3DXVECTOR2(0.0f, 0.0f);
	g_Fade.tex_f = D3DXVECTOR2(1.0f, 1.0f);
	g_Fade.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//フェードアルファ値の初期化
	g_FadeAlpha = 0.0f;

	//フェードモードの初期化
	g_Mode_Fade = FADE_NOT;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitFade(void)
{
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateFade(void)
{
	//フェードモード分岐
	switch (g_Mode_Fade)
	{
	case FADE_NOT:
		break;
	case FADE_IN:
		g_FadeAlpha -= FADE_SPEED;

		//フェードの終了
		if (g_FadeAlpha <= 0.0f)
		{
			g_Mode_Fade = FADE_NOT;
		}

		break;
	case FADE_OUT:
		g_FadeAlpha += FADE_SPEED;

		if (g_FadeAlpha >= 1.0f)
		{
			g_Mode_Fade = FADE_IN;

			//シーンの切り替え
			SCENE* pScene = GetScene();

			switch (*pScene)
			{
			case SCENE_TITLE:
			{
				GAME_DIFF* pGameDiff = GetGameDiff();
				if (*pGameDiff <= FULL)
				{
					SetScene(SCENE_WAIT);
				}
				else if (*pGameDiff == OPTION)
				{
					SetScene(SCENE_OPTION);
				}
				else
				{
					SetScene(SCENE_EXPLANATION);
				}
				break;
			}
			case SCENE_OPTION:
				SetScene(SCENE_TITLE);
				break;
			case SCENE_EXPLANATION:
				SetScene(SCENE_TITLE);
				break;
			case SCENE_WAIT:
				SetScene(SCENE_GAME);
				break;
			case SCENE_GAME:
				SetScene(SCENE_RESULT);
				break;
			case SCENE_RESULT:
			{
				RESULT_MODE* pResultMode = GetResultMode();
				if (*pResultMode == RETURN)
				{
					SetScene(SCENE_TITLE);
				}
				else if (*pResultMode == REPLAY)
				{
					SetScene(SCENE_WAIT);
				}
			}
				break;
			default:
				break;
			}
		}

		break;
	case FADE_MAX:
		g_FadeAlpha = 1.0f;
		break;
	default:
		break;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawFade(void)
{
	SetSamplerState(FILTER_MODE_LINEAR, ADDRESS_MODE_WRAP);
	//フェードの描画
	DrawSpriteColor(g_FadeTexNo,
		g_Fade.pos,
		g_Fade.size,
		g_Fade.tex_v,
		g_Fade.tex_f,
		D3DXCOLOR(g_Fade.color.r, g_Fade.color.g, g_Fade.color.b, g_FadeAlpha)
	);
}

//=============================================================================
// フェードセット関数
//=============================================================================
void SetFade(MODE_FADE mode)
{
	//フェードモードのセット
	g_Mode_Fade = mode;

	//フェードアルファ値の初期化
	if (g_Mode_Fade == FADE_IN)
	{
		g_FadeAlpha = 1.0f;
	}
	else if (g_Mode_Fade == FADE_OUT)
	{
		g_FadeAlpha = 0.0f;
	}
}

//=============================================================================
// フェードゲット関数
//=============================================================================
MODE_FADE* GetFade(void)
{
	return &g_Mode_Fade;
}