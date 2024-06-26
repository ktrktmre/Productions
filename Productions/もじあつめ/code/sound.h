/*==============================================================================

   サウンド処理 [sound.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once	// インクルードガード

#include <windows.h>
#include "xaudio2.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define VOLUME_DIGIT 3
#define VOLUME_MAX 1.0f
#define SOUND_LOOP -1

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
struct SOUND_RECORD {
	int BGMGameID;
	int SETitleID;
	int SEWaitID;
	int SEResultID;
	int SEButtonID;
	int SECorrectID;
	int SEWrongID;
	int SEGameEndID;
};

/*------------------------------------------------------------------------------
   プロトタイプ宣言
------------------------------------------------------------------------------*/
bool InitSound(HWND hWnd);
void UninitSound(void);

int LoadSound(char* pFilename);
void PlaySound(int index, int loopCount);
void StopSound(int index);
void StopSoundAll(void);
void SetVolume(int index, float vol);
void LoadRecord(void);
void UpdateVolume(void);
float CopyVolumeBGM(void);
float CopyVolumeSE(void);
void SetVolumeBGM(float volume);
void SetVolumeSE(float volume);
SOUND_RECORD* GetSoundRecord(void);