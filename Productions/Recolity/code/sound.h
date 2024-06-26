//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 切田海畝斗
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_
#pragma once

#include <windows.h>
#include <string>
#include <unordered_map>
#include "xaudio2.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BGM "BGM"
#define SE "SE"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
bool InitSound(HWND hWnd);
void UninitSound(void);
int LoadSound(std::string name);
bool LoadShareSound(std::string name);
void PlaySound(int index, int loopCount, float vol);
void PlaySound(int index, int loopCount, float vol, UINT32 sample);
void PlaySound(std::string name, int loopCount, float vol);
void PlaySound(std::string name, float vol);
void ResumeSound(int index);
void ResumeSound(std::string name);
void PuaseSound(int index);
void PuaseSound(std::string name);
void PuaseSoundAll(void);
void StopSound(int index);
void StopSound(std::string name);
void StopSoundAll(void);
void SetVolume(int index, float vol);
void SetVolumeAll(float world);
void SetVolumeKinds(std::string kinds, float vol);
void SetVolume(std::string name, float vol);
void RegisterSound(void);
float GetWolrdSound(void);
float GetSESound(void);
float GetBGMSound(void);


#ifdef _DEBUG
const int DataSize(void);
#endif // _DEBUG

#endif // !_SOUND_H_